#pragma once

#include "Point.h"

/**
 * @brief Класс, представляющий треугольник на плоскости.
 * @param m_a Первая вершина.
 * @param m_a Вторая вершина.
 * @param m_a Третья вершина.
 */
class Triangle {
private:
  /** @brief Первая вершина треугольника. */
    Point m_a; 
 /** @brief Вторая вершина треугольника. */
    Point m_b;
     /** @brief Третья вершина треугольника. */ 
    Point m_c; 

    /**
     * @brief Вычисление расстояния между двумя точками.
     * @param p1 Первая точка.
     * @param p2 Вторая точка.
     * @return Расстояние между точками.
     */
    double calculateDistance(const Point& p1, const Point& p2) const;

    /**
     * @brief Проверка, образуют ли точки треугольник.
     * @param a Первая точка.
     * @param b Вторая точка.
     * @param c Третья точка.
     * @return true, если точки образуют треугольник.
     */
    bool isValidTriangle(const Point& a, const Point& b, const Point& c) const;

public:
    /**
     * @brief Конструктор из трёх точек.
     * @param a Первая вершина.
     * @param b Вторая вершина.
     * @param c Третья вершина.
     */
    Triangle(const Point& a, const Point& b, const Point& c);

    Point getA() const { return m_a; }
    Point getB() const { return m_b; }
    Point getC() const { return m_c; }

    /**
     * @brief Установка вершин треугольника.
     * @param a Первая вершина.
     * @param b Вторая вершина.
     * @param c Третья вершина.
     */
    void setPoints(const Point& a, const Point& b, const Point& c);

    /**
     * @brief Вычисление периметра треугольника.
     * @return Периметр треугольника.
     */
    double getPerimeter() const;

    /**
     * @brief Вычисление площади треугольника.
     * @return Площадь треугольника.
     */
    double getArea() const;
};
