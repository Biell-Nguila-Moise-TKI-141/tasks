#include <iostream>
#include <windows.h>
#include "Vector.h"

/**
 * @brief Точка входа в программу.
 */
int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Vector v;
    int n, value;

    std::cout << "Введите количество элементов: ";
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cout << "Введите элемент " << i + 1 << ": ";
        std::cin >> value;
        v << value;
    }

    try {
        std::cout << "Вектор: " << v.ToString() << std::endl;
        std::cout << "Размер: " << v.size() << std::endl;

        int last;
        v >> last;
        std::cout << "Извлечён последний элемент: " << last << std::endl;
        std::cout << "Вектор после извлечения: " << v.ToString() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
