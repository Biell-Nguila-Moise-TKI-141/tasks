#include "Triangle.h"
#include <cmath>
#include <stdexcept>

Triangle::Triangle(const Point& a, const Point& b, const Point& c) {
    setPoints(a, b, c);
}

double Triangle::calculateDistance(const Point& p1, const Point& p2) const {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

bool Triangle::isValidTriangle(const Point& a, const Point& b, const Point& c) const {
    double sideA = calculateDistance(b, c);
    double sideB = calculateDistance(a, c);
    double sideC = calculateDistance(a, b);

    const double eps = 1e-9;
    return (sideA + sideB > sideC + eps) &&
           (sideA + sideC > sideB + eps) &&
           (sideB + sideC > sideA + eps);
}

void Triangle::setPoints(const Point& a, const Point& b, const Point& c) {
    if (!isValidTriangle(a, b, c)) {
        throw std::invalid_argument("Заданные точки лежат на одной прямой или совпадают. Треугольник не существует.");
    }
    m_a = a;
    m_b = b;
    m_c = c;
}

double Triangle::getPerimeter() const {
    double sideA = calculateDistance(m_b, m_c);
    double sideB = calculateDistance(m_a, m_c);
    double sideC = calculateDistance(m_a, m_b);
    return sideA + sideB + sideC;
}

double Triangle::getArea() const {
    return 0.5 * std::abs(m_a.x * (m_b.y - m_c.y) + 
                          m_b.x * (m_c.y - m_a.y) + 
                          m_c.x * (m_a.y - m_b.y));
}
