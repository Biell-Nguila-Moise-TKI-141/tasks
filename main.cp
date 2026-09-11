#include <iostream>
#include <windows.h>
#include "RegularTriangle.h"

/**
 * @brief Точка входа в программу.
 */
int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Point p1, p2, p3;

    std::cout << "Введите координаты первой точки (x y): ";
    std::cin >> p1.x >> p1.y;

    std::cout << "Введите координаты второй точки (x y): ";
    std::cin >> p2.x >> p2.y;

    std::cout << "Введите координаты третьей точки (x y): ";
    std::cin >> p3.x >> p3.y;

    try {
        RegularTriangle triangle(p1, p2, p3);

        std::cout << "Периметр треугольника: " << triangle.getPerimeter() << std::endl;
        std::cout << "Площадь треугольника: " << triangle.getArea() << std::endl;
        std::cout << "Радиус описанной окружности: " << triangle.getCircumradius() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}


