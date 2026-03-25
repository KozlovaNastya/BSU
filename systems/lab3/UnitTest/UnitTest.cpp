#include "pch.h"
#include "CppUnitTest.h"
#include <windows.h>
#include <vector>

#include "main.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab3Tests
{
    TEST_CLASS(MarkerThreadTests)
    {
    public:
        void SetupThreadData(ThreadData& data, int id, int size, int* arr, CRITICAL_SECTION* pcs) {
            data.id = id;
            data.arraySize = size;
            data.array = arr;
            data.hStartEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
            data.hStoppedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
            data.hContinueEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
            data.hExitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
            data.pcs = pcs;
        }

        void CleanupThreadData(ThreadData& data) {
            CloseHandle(data.hStartEvent);
            CloseHandle(data.hStoppedEvent);
            CloseHandle(data.hContinueEvent);
            CloseHandle(data.hExitEvent);
        }

        // ТЕСТ 1
        TEST_METHOD(TestMarkerMarksAndCleansArray)
        {
            const int size = 10;
            int testArray[size] = { 0 };
            CRITICAL_SECTION cs;
            InitializeCriticalSection(&cs);

            ThreadData data;
            SetupThreadData(data, 7, size, testArray, &cs);

            HANDLE hThread = CreateThread(NULL, 0, marker, &data, 0, NULL);
            SetEvent(data.hStartEvent);

            WaitForSingleObject(data.hStoppedEvent, 2000);

            bool found = false;
            for (int i = 0; i < size; i++) {
                if (testArray[i] == 7) found = true;
            }
            Assert::IsTrue(found, L"Поток должен был пометить хотя бы один элемент своим ID");

            SetEvent(data.hExitEvent);
            WaitForSingleObject(hThread, 2000);

            bool clean = true;
            for (int i = 0; i < size; i++) {
                if (testArray[i] == 7) clean = false;
            }
            Assert::IsTrue(clean, L"Поток должен был очистить помеченные элементы перед выходом");

            CloseHandle(hThread);
            CleanupThreadData(data);
            DeleteCriticalSection(&cs);
        }

        // ТЕСТ 2
        TEST_METHOD(TestMarkerWhenArrayIsFull)
        {
            const int size = 5;
            int testArray[size] = { 99, 99, 99, 99, 99 };
            CRITICAL_SECTION cs;
            InitializeCriticalSection(&cs);

            ThreadData data;
            SetupThreadData(data, 3, size, testArray, &cs);

            HANDLE hThread = CreateThread(NULL, 0, marker, &data, 0, NULL);
            SetEvent(data.hStartEvent);

            DWORD waitRes = WaitForSingleObject(data.hStoppedEvent, 1000);
            Assert::AreEqual((DWORD)WAIT_OBJECT_0, waitRes, L"Поток должен сигнализировать об остановке, если массив полон");

            SetEvent(data.hExitEvent);
            WaitForSingleObject(hThread, 1000);

            CloseHandle(hThread);
            CleanupThreadData(data);
            DeleteCriticalSection(&cs);
        }

        // ТЕСТ 3
        TEST_METHOD(TestMarkerContinueSignalWork)
        {
            const int size = 20;
            int testArray[size] = { 0 };
            CRITICAL_SECTION cs;
            InitializeCriticalSection(&cs);

            ThreadData data;
            SetupThreadData(data, 1, size, testArray, &cs);

            HANDLE hThread = CreateThread(NULL, 0, marker, &data, 0, NULL);
            SetEvent(data.hStartEvent);

            WaitForSingleObject(data.hStoppedEvent, 2000);

            ResetEvent(data.hStoppedEvent);
            SetEvent(data.hContinueEvent);

            DWORD waitRes = WaitForSingleObject(data.hStoppedEvent, 2000);
            Assert::AreEqual((DWORD)WAIT_OBJECT_0, waitRes, L"Поток должен продолжить работу после Continue и снова остановиться");

            SetEvent(data.hExitEvent);
            WaitForSingleObject(hThread, 1000);

            CloseHandle(hThread);
            CleanupThreadData(data);
            DeleteCriticalSection(&cs);
        }
    };
}
