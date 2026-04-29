#include "pch.h"
#include "CppUnitTest.h"
#include "../../Logic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IPC_Tests
{
    TEST_CLASS(QueueLogicTests)
    {
    public:
        // Тест 1: Проверка правильности инициализации заголовка
        TEST_METHOD(TestHeaderInitialization)
        {
            const char* testFile = "test_header.bin";
            int capacity = 10;

            std::fstream f(testFile, std::ios::out | std::ios::binary | std::ios::trunc);
            FileHeader h = { 0, 0, capacity };
            f.write((char*)&h, sizeof(FileHeader));
            f.close();

            std::fstream fIn(testFile, std::ios::in | std::ios::binary);
            FileHeader hRead;
            fIn.read((char*)&hRead, sizeof(FileHeader));
            fIn.close();

            Assert::AreEqual(0, hRead.head);
            Assert::AreEqual(0, hRead.tail);
            Assert::AreEqual(capacity, hRead.maxRecords);
        }

        // Тест 2: Проверка FIFO (запись-чтение)
        TEST_METHOD(TestFIFOLogic)
        {
            const char* testFile = "test_fifo.bin";
            std::fstream f(testFile, std::ios::out | std::ios::binary | std::ios::trunc);
            FileHeader h = { 0, 0, 5 };
            f.write((char*)&h, sizeof(FileHeader));
            f.close();

            f.open(testFile, std::ios::in | std::ios::out | std::ios::binary);

            Message m1; strcpy_s(m1.text, "Msg1");
            Message m2; strcpy_s(m2.text, "Msg2");

            writeToQueue(f, m1);
            writeToQueue(f, m2);

            Message r1 = readFromQueue(f);
            Message r2 = readFromQueue(f);

            Assert::AreEqual(std::string("Msg1"), std::string(r1.text));
            Assert::AreEqual(std::string("Msg2"), std::string(r2.text));

            f.close();
        }

        // Тест 3: Проверка кольцевого переполнения
        TEST_METHOD(TestCircularWrap)
        {
            const char* testFile = "test_wrap.bin";
            std::fstream f(testFile, std::ios::out | std::ios::binary | std::ios::trunc);
            FileHeader h = { 0, 0, 2 };
            f.write((char*)&h, sizeof(FileHeader));
            f.close();

            f.open(testFile, std::ios::in | std::ios::out | std::ios::binary);

            Message m1; strcpy_s(m1.text, "A");
            Message m2; strcpy_s(m2.text, "B");
            Message m3; strcpy_s(m3.text, "C");

            writeToQueue(f, m1);
            writeToQueue(f, m2);

            readFromQueue(f);
            writeToQueue(f, m3);

            Message res = readFromQueue(f);
            Assert::AreEqual(std::string("B"), std::string(res.text));

            f.close();
        }
    };
}
