#pragma once
#include <string>
#include <iostream>

class Polygon {
public:
    virtual ~Polygon() = default;

    // Виртуальные методы
    virtual std::string ToString() const = 0;
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual double getCircumradius() const = 0;
    virtual void read(std::istream& in) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
        os << poly.ToString();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Polygon& poly) {
        poly.read(is);
        return is;
    }
};
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
class RegularTriangle : public Polygon {
private:
    Point m_p1;
    Point m_p2;
    Point m_p3;

    double calculateDistance(const Point& a, const Point& b) const;
    bool isValidRegularTriangle(const Point& p1, const Point& p2, const Point& p3) const;

public:
    RegularTriangle();
    RegularTriangle(const Point& p1, const Point& p2, const Point& p3);
    RegularTriangle(double x1, double y1, double x2, double y2, double x3, double y3);

    // Реализация виртуальных методов
    std::string ToString() const override;
    double getArea() const override;
    double getPerimeter() const override;
    double getCircumradius() const override;
    void read(std::istream& in) override;

    Point getP1() const { return m_p1; }
    Point getP2() const { return m_p2; }
    Point getP3() const { return m_p3; }

    // Операторы сравнения треугольников
    bool operator==(const RegularTriangle& other) const;
    bool operator!=(const RegularTriangle& other) const;
};
RegularTriangle::RegularTriangle() : m_p1{ 0,0 }, m_p2{ 0,0 }, m_p3{ 0,0 } {}

RegularTriangle::RegularTriangle(const Point& p1, const Point& p2, const Point& p3) {
    if (!isValidRegularTriangle(p1, p2, p3)) {
        throw std::invalid_argument("Нарушены правила создания правильного многоугольника: стороны не равны или фигура вырождена.");
    }
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
}

RegularTriangle::RegularTriangle(double x1, double y1, double x2, double y2, double x3, double y3) 
    : RegularTriangle(Point{ x1, y1 }, Point{ x2, y2 }, Point{ x3, y3 }) {}

double RegularTriangle::calculateDistance(const Point& a, const Point& b) const {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

bool RegularTriangle::isValidRegularTriangle(const Point& p1, const Point& p2, const Point& p3) const {
    double s1 = calculateDistance(p1, p2);
    double s2 = calculateDistance(p2, p3);
    double s3 = calculateDistance(p3, p1);

    const double eps = 1e-4; // Небольшой допуск для вычислений с плавающей точкой

    // Стороны должны быть равны и больше нуля (неотрицательны по условию)
    if (s1 < eps || s2 < eps || s3 < eps) return false;
    return (std::abs(s1 - s2) < eps) && (std::abs(s2 - s3) < eps);
}

std::string RegularTriangle::ToString() const {
    std::stringstream ss;
    ss << "RegularTriangle: A" << m_p1 << ", B" << m_p2 << ", C" << m_p3;
    return ss.str();
}

double RegularTriangle::getPerimeter() const {
    return 3.0 * calculateDistance(m_p1, m_p2);
}

double RegularTriangle::getArea() const {
    double side = calculateDistance(m_p1, m_p2);
    return (std::sqrt(3.0) / 4.0) * std::pow(side, 2);
}

double RegularTriangle::getCircumradius() const {
    double side = calculateDistance(m_p1, m_p2);
    return side / std::sqrt(3.0);
}

void RegularTriangle::read(std::istream& in) {
    Point p1, p2, p3;
    if (in >> p1 >> p2 >> p3) {
        if (!isValidRegularTriangle(p1, p2, p3)) {
            throw std::invalid_argument("Считанные точки не образуют правильный треугольник.");
        }
        m_p1 = p1;
        m_p2 = p2;
        m_p3 = p3;
    }
}

bool RegularTriangle::operator==(const RegularTriangle& other) const {
    return (m_p1 == other.m_p1 && m_p2 == other.m_p2 && m_p3 == other.m_p3);
}

bool RegularTriangle::operator!=(const RegularTriangle& other) const {
    return !(*this == other);
}
struct Point {
    double x;
    double y;

    // Операторы сравнения точек
    bool operator==(const Point& other) const {
        const double eps = 1e-9;
        return std::abs(x - other.x) < eps && std::abs(y - other.y) < eps;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

// Операторы ввода-вывода для Точки
inline std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

inline std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}
