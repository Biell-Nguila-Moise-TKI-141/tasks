#include <iostream>
#include <windows.h>
#include "Triangle.h" 

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
        Triangle triangle(p1, p2, p3);

        std::cout << "Периметр треугольника: " << triangle.getPerimeter() << std::endl;
        std::cout << "Площадь треугольника: " << triangle.getArea() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}