#pragma once

#include <string>
#include <iostream>

/**
 * @brief Абстрактный базовый класс для всех многоугольников.
 */
class Polygon {
public:
    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~Polygon() = default;

    /**
     * @brief Строковое представление многоугольника.
     * @return Строковое представление.
     */
    virtual std::string ToString() const = 0;

    /**
     * @brief Вычисление площади.
     * @return Площадь многоугольника.
     */
    virtual double getArea() const = 0;

    /**
     * @brief Вычисление периметра.
     * @return Периметр многоугольника.
     */
    virtual double getPerimeter() const = 0;

    /**
     * @brief Вычисление радиуса описанной окружности.
     * @return Радиус описанной окружности.
     */
    virtual double getCircumradius() const = 0;

    /**
     * @brief Чтение многоугольника из потока.
     * @param in Входной поток.
     */
    virtual void read(std::istream& in) = 0;

    /**
     * @brief Оператор вывода в поток.
     * @param os Выходной поток.
     * @param poly Многоугольник.
     * @return Ссылка на поток.
     */
    friend std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
        os << poly.ToString();
        return os;
    }

    /**
     * @brief Оператор ввода из потока.
     * @param is Входной поток.
     * @param poly Многоугольник.
     * @return Ссылка на поток.
     */
    friend std::istream& operator>>(std::istream& is, Polygon& poly) {
        poly.read(is);
        return is;
    }
};
