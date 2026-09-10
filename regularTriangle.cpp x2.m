#include "pch.h"
#include "RegularTriangle.h"
#include <cmath>
#include <stdexcept>
#include <sstream>

RegularTriangle::RegularTriangle() : m_p1{ 0,0 }, m_p2{ 0,0 }, m_p3{ 0,0 } {}

RegularTriangle::RegularTriangle(const Point& p1, const Point& p2, const Point& p3) {
    if (!isValidRegularTriangle(p1, p2, p3)) {
        throw std::invalid_argument("Нарушены правила создания правильного многоугольника: стороны не равны или фигура вырождена.");
    }
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
}

RegularTriangle::RegularTriangle(const double x1, const double y1, const double x2,const double y2,const double x3,const double y3) 
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