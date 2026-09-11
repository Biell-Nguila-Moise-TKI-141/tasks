#include "pch.h"
#include "CppUnitTest.h"
#include "RegularTriangle.h" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LabTests
{
    TEST_CLASS(RegularTriangleTests)
    {
    public:
        // Тест создания корректного равностороннего треугольника со стороной 2
        TEST_METHOD(TestValidRegularTriangleCalculations)
        {
            Point p1{ 0.0, 0.0 };
            Point p2{ 2.0, 0.0 };
            Point p3{ 1.0, std::sqrt(3.0) }; // Вершина идеального правильного треугольника

            RegularTriangle t(p1, p2, p3);

            // Ожидаемый периметр = 3 * 2 = 6
            Assert::AreEqual(6.0, t.getPerimeter(), 1e-4);

            // Ожидаемая площадь = (sqrt(3)/4) * 4 = sqrt(3) ≈ 1.73205
            Assert::AreEqual(std::sqrt(3.0), t.getArea(), 1e-4);

            // Ожидаемый радиус описанной окружности = 2 / sqrt(3) ≈ 1.1547
            Assert::AreEqual(2.0 / std::sqrt(3.0), t.getCircumradius(), 1e-4);
        }

        // Тест на исключение при неверных сторонах (произвольный треугольник)
        TEST_METHOD(TestInvalidTriangleThrowsException)
        {
            Point p1{ 0.0, 0.0 };
            Point p2{ 3.0, 0.0 };
            Point p3{ 0.0, 4.0 }; // Это прямоугольный треугольник, а не правильный

            auto expression = [&]() { RegularTriangle t(p1, p2, p3); };
            Assert::ExpectException<std::invalid_argument>(expression);
        }

        // Тест операторов сравнения
        TEST_METHOD(TestEqualityOperators)
        {
            RegularTriangle t1(0, 0, 2, 0, 1, std::sqrt(3.0));
            RegularTriangle t2(0, 0, 2, 0, 1, std::sqrt(3.0));
            RegularTriangle t3; // Дефолтный (0,0)

            Assert::IsTrue(t1 == t2);
            Assert::IsTrue(t1 != t3);
        }
    };
}