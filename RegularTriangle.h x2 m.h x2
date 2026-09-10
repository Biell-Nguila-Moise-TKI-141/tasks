#pragma once

#include "Polygon.h"
#include "Point.h"

/**
 * @brief Класс правильного треугольника.
 * @details Наследуется от Polygon. Все стороны равны, все углы по 60°.
 */
class RegularTriangle : public Polygon {
private:
/**
     * @brief Первая вершина треугольника.
     * @details Координаты первой точки, задающей положение треугольника в пространстве.
     */
    Point m_p1; 
    
    /**
     * @brief Вторая вершина треугольника.
     * @details Координаты второй точки, задающей положение треугольника в пространстве.
     */
    Point m_p2;
     /**
     * @brief Третья вершина треугольника.
     * @details Координаты третьей точки, задающей положение треугольника в пространстве.
     */ 

    Point m_p3; 

    /**
     * @brief Вычисление расстояния между двумя точками.
     * @param a Первая точка.
     * @param b Вторая точка.
     * @return Расстояние между точками.
     */
    double calculateDistance(const Point& a, const Point& b) const;

    /**
     * @brief Проверка, образуют ли точки правильный треугольник.
     * @param p1 Первая точка.
     * @param p2 Вторая точка.
     * @param p3 Третья точка.
     * @return true, если треугольник правильный.
     */
    bool isValidRegularTriangle(const Point& p1, const Point& p2, const Point& p3) const;

public:
    /**
     * @brief Конструктор по умолчанию.
     * @details Создаёт треугольник с вершинами в (0,0), (1,0), (0.5, sqrt(3)/2).
     */
    RegularTriangle();

    /**
     * @brief Конструктор из трёх точек.
     * @param p1 Первая вершина.
     * @param p2 Вторая вершина.
     * @param p3 Третья вершина.
     */
    RegularTriangle(const Point& p1, const Point& p2, const Point& p3);

    /**
     * @brief Конструктор из координат.
     * @param x1 Координата x первой вершины.
     * @param y1 Координата y первой вершины.
     * @param x2 Координата x второй вершины.
     * @param y2 Координата y второй вершины.
     * @param x3 Координата x третьей вершины.
     * @param y3 Координата y третьей вершины.
     */
    RegularTriangle(const double x1, const double y1, const double x2, const double y2, const double x3,const double y3);

    /**
     * @brief Строковое представление треугольника.
     * @return Строка с координатами вершин.
     */
    std::string ToString() const override;

    /**
     * @brief Вычисление площади.
     * @return Площадь треугольника.
     */
    double getArea() const override;

    /**
     * @brief Вычисление периметра.
     * @return Периметр треугольника.
     */
    double getPerimeter() const override;

    /**
     * @brief Вычисление радиуса описанной окружности.
     * @return Радиус описанной окружности.
     */
    double getCircumradius() const override;

    /**
     * @brief Чтение треугольника из потока.
     * @param in Входной поток.
     */
    void read(std::istream& in) override;

    Point getP1() const { return m_p1; }
    Point getP2() const { return m_p2; }
    Point getP3() const { return m_p3; }

    /**
     * @brief Сравнение двух треугольников на равенство.
     * @param other Другой треугольник.
     * @return true, если треугольники равны.
     */
    bool operator==(const RegularTriangle& other) const;

    /**
     * @brief Сравнение двух треугольников на неравенство.
     * @param other Другой треугольник.
     * @return true, если треугольники не равны.
     */
    bool operator!=(const RegularTriangle& other) const;
};

