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
            v.insert(1, 20); 
            Assert::AreEqual(std::string("[10, 20, 30]"), v.ToString());
            v.remove(1); 
            Assert::AreEqual(std::string("[10, 30]"), v.ToString());
        }

        TEST_METHOD(TestFindAndIndexOperator)
        {
            Vector v = { 5, 15, 25 };
            Assert::AreEqual(1, v.find(15));
            Assert::AreEqual(-1, v.find(99)); 
            Assert::AreEqual(25, v[2]);
            v[2] = 100;
            Assert::AreEqual(100, v[2]);
        }

        TEST_METHOD(TestShiftOperators)
        {
            Vector v;
            v << 1 << 2 << 3; 
            Assert::AreEqual(std::string("[1, 2, 3]"), v.ToString());
            int val;
            v >> val;
            Assert::AreEqual(3, val);
            Assert::AreEqual(std::string("[1, 2]"), v.ToString());
        }

        TEST_METHOD(TestCopyAndAssignment)
        {
            Vector v1 = { 1, 2 };
            Vector v2 = v1; 
            v1[0] = 9;
            Assert::AreEqual(std::string("[9, 2]"), v1.ToString());
            Assert::AreEqual(std::string("[1, 2]"), v2.ToString()); 
            Vector v3;
            v3 = v1; 
            Assert::AreEqual(std::string("[9, 2]"), v3.ToString());
        }

        

        TEST_METHOD(TestDefaultConstructor)
        {
            Vector v;
            Assert::IsTrue(v.isEmpty());
            Assert::AreEqual((size_t)0, v.size());
            Assert::AreEqual(std::string("[]"), v.ToString());
        }

        TEST_METHOD(TestIsEmpty)
        {
            Vector v;
            Assert::IsTrue(v.isEmpty());
            v << 1;
            Assert::IsFalse(v.isEmpty());
        }

        TEST_METHOD(TestSize)
        {
            Vector v;
            Assert::AreEqual((size_t)0, v.size());
            v << 1 << 2 << 3;
            Assert::AreEqual((size_t)3, v.size());
        }

        TEST_METHOD(TestClear)
        {
            Vector v = { 1, 2, 3 };
            v.clear();
            Assert::IsTrue(v.isEmpty());
            Assert::AreEqual((size_t)0, v.size());
            Assert::AreEqual(std::string("[]"), v.ToString());
        }

        TEST_METHOD(TestPushBackAndPopBack)
        {
            Vector v;
            v.push_back(10);
            v.push_back(20);
            v.push_back(30);
            Assert::AreEqual(std::string("[10, 20, 30]"), v.ToString());

            v.pop_back();
            Assert::AreEqual(std::string("[10, 20]"), v.ToString());
            v.pop_back();
            v.pop_back();
            Assert::IsTrue(v.isEmpty());
        }

        TEST_METHOD(TestInsertAtBeginningAndEnd)
        {
            Vector v = { 2, 3 };
            v.insert(0, 1); 
            Assert::AreEqual(std::string("[1, 2, 3]"), v.ToString());

            v.insert(v.size(), 4); 
            Assert::AreEqual(std::string("[1, 2, 3, 4]"), v.ToString());
        }

        TEST_METHOD(TestRemoveFirstAndLast)
        {
            Vector v = { 1, 2, 3, 4 };
            v.remove(0); 
            Assert::AreEqual(std::string("[2, 3, 4]"), v.ToString());

            v.remove(v.size() - 1); 
            Assert::AreEqual(std::string("[2, 3]"), v.ToString());
        }

        TEST_METHOD(TestFindExistingAndMissing)
        {
            Vector v = { 10, 20, 30, 20 };
            Assert::AreEqual(1, v.find(20)); 
            Assert::AreEqual(0, v.find(10));
            Assert::AreEqual(2, v.find(30));
            Assert::AreEqual(-1, v.find(99));
        }

        TEST_METHOD(TestIndexOperatorReadWrite)
        {
            Vector v = { 1, 2, 3 };
            Assert::AreEqual(1, v[0]);
            Assert::AreEqual(2, v[1]);
            Assert::AreEqual(3, v[2]);

            v[0] = 100;
            v[1] = 200;
            v[2] = 300;
            Assert::AreEqual(std::string("[100, 200, 300]"), v.ToString());
        }

        TEST_METHOD(TestSelfAssignment)
        {
            Vector v = { 1, 2, 3 };
            v = v; 
            Assert::AreEqual(std::string("[1, 2, 3]"), v.ToString());
        }

        TEST_METHOD(TestShiftOperatorChain)
        {
            Vector v;
            v << 5 << 10 << 15 << 20;
            Assert::AreEqual(std::string("[5, 10, 15, 20]"), v.ToString());
        }

        TEST_METHOD(TestExtractFromEmptyVector)
        {
            Vector v;
            int val = -1;
            v >> val;
            Assert::AreEqual(-1, val); 
        }

        TEST_METHOD(TestCopyConstructorDeepCopy)
        {
            Vector v1 = { 1, 2, 3 };
            Vector v2 = v1;
            v2[0] = 99;
            Assert::AreEqual(std::string("[1, 2, 3]"), v1.ToString());
            Assert::AreEqual(std::string("[99, 2, 3]"), v2.ToString());
        }

        TEST_METHOD(TestAssignmentOperatorDeepCopy)
        {
            Vector v1 = { 1, 2, 3 };
            Vector v2;
            v2 = v1;
            v2[0] = 99;
            Assert::AreEqual(std::string("[1, 2, 3]"), v1.ToString());
            Assert::AreEqual(std::string("[99, 2, 3]"), v2.ToString());
        }
    };
}