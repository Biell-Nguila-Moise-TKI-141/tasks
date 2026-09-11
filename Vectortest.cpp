#include "pch.h" 
#include "CppUnitTest.h"
#include "Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorTests
{
    TEST_CLASS(VectorTests)
    {
    public:
        
        TEST_METHOD(TestInitializerListAndToString)
        {
            Vector v = { 1, 2, 3 };
            Assert::IsFalse(v.isEmpty());
            Assert::AreEqual(std::string("[1, 2, 3]"), v.ToString());
            Assert::AreEqual((size_t)3, v.size());
        }

        TEST_METHOD(TestInsertAndRemove)
        {
            Vector v;
            v.insert(0, 10);
            v.insert(1, 30);
            v.insert(1, 20); // Вставляем между 10 и 30
            Assert::AreEqual(std::string("[10, 20, 30]"), v.ToString());

            v.remove(1); // Удаляем 20
            Assert::AreEqual(std::string("[10, 30]"), v.ToString());
        }

        TEST_METHOD(TestFindAndIndexOperator)
        {
            Vector v = { 5, 15, 25 };
            Assert::AreEqual(1, v.find(15));
            Assert::AreEqual(-1, v.find(99)); // Несуществующий элемент

            Assert::AreEqual(25, v[2]);
            v[2] = 100;
            Assert::AreEqual(100, v[2]);
        }

        TEST_METHOD(TestShiftOperators)
        {
            Vector v;
            v << 1 << 2 << 3; // Проверяем множественный сдвиг
            Assert::AreEqual(std::string("[1, 2, 3]"), v.ToString());

            int val;
            v >> val;
            Assert::AreEqual(3, val);
            Assert::AreEqual(std::string("[1, 2]"), v.ToString());
        }

        TEST_METHOD(TestCopyAndAssignment)
        {
            Vector v1 = { 1, 2 };
            Vector v2 = v1; // Конструктор копирования
            v1[0] = 9;

            Assert::AreEqual(std::string("[9, 2]"), v1.ToString());
            Assert::AreEqual(std::string("[1, 2]"), v2.ToString()); // v2 не должен измениться

            Vector v3;
            v3 = v1; // Оператор присваивания
            Assert::AreEqual(std::string("[9, 2]"), v3.ToString());
        }
    };
}