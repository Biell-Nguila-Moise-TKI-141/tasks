#include "pch.h"
#include "CppUnitTest.h"
#include "RegularTriangle.h" 
#include <cmath> // Для std::sqrt

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LabTests
{
    TEST_CLASS(RegularTriangleTests)
    {
    private:
        // Вспомогательная функция для создания точки
        Point makePoint(double x, double y) {
            return Point{ x, y };
        }

    public:
        // Тест создания корректного равностороннего треугольника со стороной 2
        TEST_METHOD(TestValidRegularTriangleCalculations)
        {
            // Для стороны 2: координаты правильного треугольника
            Point p1{ 0.0, 0.0 };
            Point p2{ 2.0, 0.0 };
            Point p3{ 1.0, std::sqrt(3.0) }; // (2*sqrt(3)/2 = sqrt(3)) ✓

            RegularTriangle t(p1, p2, p3);

            // Проверка, что треугольник равносторонний
            // Для треугольника со стороной 2:
            // - Периметр = 6
            // - Площадь = sqrt(3) ≈ 1.73205
            // - Радиус описанной окружности = 2/sqrt(3) ≈ 1.1547
            
            Assert::AreEqual(6.0, t.getPerimeter(), 1e-4, L"Неверный периметр");
            Assert::AreEqual(std::sqrt(3.0), t.getArea(), 1e-4, L"Неверная площадь");
            Assert::AreEqual(2.0 / std::sqrt(3.0), t.getCircumradius(), 1e-4, L"Неверный радиус");
        }

        // Тест на исключение при неверных сторонах
        TEST_METHOD(TestInvalidTriangleThrowsException)
        {
            Point p1{ 0.0, 0.0 };
            Point p2{ 3.0, 0.0 };
            Point p3{ 0.0, 4.0 }; // Прямоугольный треугольник (3-4-5)

            auto expression = [&]() { 
                RegularTriangle t(p1, p2, p3); 
            };
            
            Assert::ExpectException<std::invalid_argument>(expression, 
                L"Должно быть выброшено исключение для неправильного треугольника");
        }

        // Тест операторов сравнения
        TEST_METHOD(TestEqualityOperators)
        {
            Point p1{ 0.0, 0.0 };
            Point p2{ 2.0, 0.0 };
            Point p3{ 1.0, std::sqrt(3.0) };
            
            RegularTriangle t1(p1, p2, p3);
            RegularTriangle t2(p1, p2, p3);
            
            // Создаем другой треугольник (сторона 1)
            Point q1{ 0.0, 0.0 };
            Point q2{ 1.0, 0.0 };
            Point q3{ 0.5, std::sqrt(3.0)/2.0 };
            RegularTriangle t3(q1, q2, q3);

            // Проверяем рефлексивность
            Assert::IsTrue(t1 == t1, L"Треугольник должен быть равен сам себе");
            
            // Проверяем симметричность
            Assert::IsTrue(t1 == t2, L"Одинаковые треугольники должны быть равны");
            Assert::IsTrue(t2 == t1, L"Равенство должно быть симметричным");
            
            // Проверяем неравенство
            Assert::IsTrue(t1 != t3, L"Разные треугольники должны быть неравны");
            
            // Проверяем, что оператор != противоположен ==
            bool isEqual = (t1 == t2);
            bool isNotEqual = (t1 != t2);
            Assert::IsTrue(isEqual != isNotEqual, 
                L"Операторы == и != должны давать противоположные результаты");
        }

        // Дополнительный тест: проверка корректности сторон
        TEST_METHOD(TestSideLengths)
        {
            Point p1{ 0.0, 0.0 };
            Point p2{ 3.0, 0.0 };
            Point p3{ 1.5, 3.0 * std::sqrt(3.0) / 2.0 }; // Сторона 3
            
            RegularTriangle t(p1, p2, p3);
            
            // Все стороны должны быть равны
            double side1 = t.getSide1(); // Предполагаемый метод
            double side2 = t.getSide2();
            double side3 = t.getSide3();
            
            Assert::AreEqual(side1, side2, 1e-4, L"Сторона 1 != сторона 2");
            Assert::AreEqual(side2, side3, 1e-4, L"Сторона 2 != сторона 3");
            Assert::AreEqual(side3, 3.0, 1e-4, L"Сторона должна быть равна 3");
        }
    };
}

