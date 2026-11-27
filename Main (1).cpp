#include <cstddef>
#include <iostream>
#include <memory>

#include "ConstGenerator.h"
#include "DuplicateAfterEvenRowsTask.h"
#include "Generator.h"
#include "IStreamGenerator.h"
#include "InvertRowMaxTask.h"
#include "RandomGenerator.h"

using namespace miit::algebra;

/**
 * @brief Способы заполнения матрицы, предлагаемые пользователю
 */
enum class FillMethod
{
    Random = 1,   ///< Случайные числа из заданного диапазона
    Keyboard = 2, ///< Числа, вводимые с клавиатуры
    Constant = 3  ///< Одно и то же число для всех ячеек
};

/**
 * @brief Спросить пользователя и создать один из трёх генераторов
 * @return Умный указатель на генератор либо nullptr при неверном выборе
 * @details unique_ptr сам освободит объект в конце области видимости,
 * поэтому в main не нужно вызывать delete вручную
 */
std::unique_ptr<Generator> createGenerator()
{
    std::cout << "Выберите способ заполнения:\n"
              << static_cast<int>(FillMethod::Random) << " - случайными числами\n"
              << static_cast<int>(FillMethod::Keyboard) << " - с клавиатуры\n"
              << static_cast<int>(FillMethod::Constant) << " - константой\n";

    int choice = 0;
    std::cin >> choice;

    switch (static_cast<FillMethod>(choice))
    {
    case FillMethod::Random:
    {
        int min = 0;
        int max = 0;
        std::cout << "Минимум диапазона: ";
        std::cin >> min;
        std::cout << "Максимум диапазона: ";
        std::cin >> max;
        return std::make_unique<RandomGenerator>(min, max);
    }
    case FillMethod::Keyboard:
    {
        std::cout << "Введите элементы матрицы:\n";
        return std::make_unique<IStreamGenerator>(std::cin);
    }
    case FillMethod::Constant:
    {
        int value = 0;
        std::cout << "Значение константы: ";
        std::cin >> value;
        return std::make_unique<ConstGenerator>(value);
    }
    default:
        std::cout << "Неверный выбор способа заполнения\n";
        return nullptr;
    }
}

/**
 * @brief Демонстрационная точка входа
 * @return 0 при успешном завершении, 1 при неверном выборе генератора
 * @details Оба пункта варианта 1 выполняются последовательно:
 * сначала инвертируются максимальные по модулю элементы строк,
 * затем в результат вставляются копии первой строки после чётных строк.
 * Матрица заполняется только один раз — вторым заданиям передаётся
 * уже изменённый результат первого.
 */
int main()
{
    std::size_t rows = 0;
    std::size_t columns = 0;

    std::cout << "Количество строк: ";
    std::cin >> rows;
    std::cout << "Количество столбцов: ";
    std::cin >> columns;

    const std::unique_ptr<Generator> generator = createGenerator();
    if (!generator)
    {
        return 1;
    }

    InvertRowMaxTask inversion(rows, columns, *generator);
    std::cout << "\n=== Задание 1.1. Инвертировать максимум по модулю в каждой строке ===\n";
    std::cout << "Исходная матрица:\n" << inversion.getMatrix() << "\n";
    inversion.solve();
    std::cout << "После инверсии:\n" << inversion.getMatrix() << "\n";

    DuplicateAfterEvenRowsTask duplication(inversion.getMatrix(), *generator);
    std::cout << "\n=== Задание 1.2. Вставить первую строку после каждой чётной ===\n";
    duplication.solve();
    std::cout << "Результат варианта 1:\n" << duplication.getMatrix() << "\n";

    return 0;
}
