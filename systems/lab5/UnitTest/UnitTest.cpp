#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <windows.h>
#include "../lab5/Employee.h"

struct RowLock {
    int empId;
    int readerCount = 0;
    bool isWriting = false;
    CRITICAL_SECTION cs;
    HANDLE canReadEvent;
    HANDLE canWriteEvent;
};

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab5Tests
{
    TEST_CLASS(ServerLockingTests)
    {
    public:
        void InitLock(RowLock& lock, int id) {
            lock.empId = id;
            lock.readerCount = 0;
            lock.isWriting = false;
            InitializeCriticalSection(&lock.cs);
            lock.canReadEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
            lock.canWriteEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
        }

        void DestroyLock(RowLock& lock) {
            DeleteCriticalSection(&lock.cs);
            CloseHandle(lock.canReadEvent);
            CloseHandle(lock.canWriteEvent);
        }

        // Тест 1: Проверка возможности параллельного чтения (Несколько читателей)
        TEST_METHOD(TestMultipleReadersAllowed)
        {
            RowLock lock;
            InitLock(lock, 1);

            EnterCriticalSection(&lock.cs);
            if (!lock.isWriting) {
                lock.readerCount++;
                ResetEvent(lock.canWriteEvent);
            }
            LeaveCriticalSection(&lock.cs);

            EnterCriticalSection(&lock.cs);
            bool secondReaderAllowed = !lock.isWriting;
            if (secondReaderAllowed) {
                lock.readerCount++;
            }
            LeaveCriticalSection(&lock.cs);

            Assert::IsTrue(secondReaderAllowed, L"Чтение не должно блокироваться другими читателями");
            Assert::AreEqual(2, lock.readerCount, L"Счетчик читателей должен быть равен 2");

            DestroyLock(lock);
        }

        TEST_METHOD(TestWriterBlockedByReaders)
        {
            RowLock lock;
            InitLock(lock, 1);

            EnterCriticalSection(&lock.cs);
            lock.readerCount = 1;
            ResetEvent(lock.canWriteEvent);
            LeaveCriticalSection(&lock.cs);

            EnterCriticalSection(&lock.cs);
            bool writerAllowed = (!lock.isWriting && lock.readerCount == 0);
            LeaveCriticalSection(&lock.cs);

            Assert::IsFalse(writerAllowed, L"Писатель должен быть заблокирован, если запись кто-то читает");

            DestroyLock(lock);
        }

        // Тест 3: Проверка блокировки новых читателей, если активен писатель
        TEST_METHOD(TestReaderBlockedByWriter)
        {
            RowLock lock;
            InitLock(lock, 1);

            EnterCriticalSection(&lock.cs);
            lock.isWriting = true;
            ResetEvent(lock.canReadEvent);
            ResetEvent(lock.canWriteEvent);
            LeaveCriticalSection(&lock.cs);

            EnterCriticalSection(&lock.cs);
            bool readerAllowed = !lock.isWriting;
            LeaveCriticalSection(&lock.cs);

            Assert::IsFalse(readerAllowed, L"Читатель должен быть заблокирован, если запись модифицируется");

            DestroyLock(lock);
        }

        // Тест 4: Проверка освобождения блокировок после ухода писателя
        TEST_METHOD(TestReleaseWriterSignalsEvents)
        {
            RowLock lock;
            InitLock(lock, 1);

            EnterCriticalSection(&lock.cs);
            lock.isWriting = true;
            ResetEvent(lock.canReadEvent);
            ResetEvent(lock.canWriteEvent);
            LeaveCriticalSection(&lock.cs);

            EnterCriticalSection(&lock.cs);
            lock.isWriting = false;
            SetEvent(lock.canReadEvent);
            SetEvent(lock.canWriteEvent);
            LeaveCriticalSection(&lock.cs);

            DWORD readWait = WaitForSingleObject(lock.canReadEvent, 0);
            DWORD writeWait = WaitForSingleObject(lock.canWriteEvent, 0);

            Assert::AreEqual((DWORD)WAIT_OBJECT_0, readWait, L"Событие canReadEvent должно быть сигнальным");
            Assert::AreEqual((DWORD)WAIT_OBJECT_0, writeWait, L"Событие canWriteEvent должно быть сигнальным");

            DestroyLock(lock);
        }
    };
}
