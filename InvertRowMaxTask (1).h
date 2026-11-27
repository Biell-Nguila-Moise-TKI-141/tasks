#pragma once

#include <cstddef>

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Задание: поменять знак у максимальных по модулю элементов строк
     * @details Первый пункт варианта 1. Для каждой строки отдельно
     * ищется наибольший модуль, после чего все элементы с таким модулем
     * меняют знак. Нули остаются нулями.
     */
    class InvertRowMaxTask : public Exercise
    {
    public:
        /**
         * @brief Конструктор задания
         * @param rowCount Количество строк матрицы
         * @param columnCount Количество столбцов матрицы
         * @param gen Генератор для заполнения матрицы
         */
        InvertRowMaxTask(const std::size_t rowCount, const std::size_t columnCount, Generator& gen);

        /**
         * @brief Инвертировать знак максимальных по модулю элементов каждой строки
         * @details Если несколько элементов имеют одинаковый максимальный модуль,
         * меняется знак у всех. Элемент INT_MIN остаётся без изменения,
         * поскольку его противоположное значение не представимо в int.
         */
        void solve() override;
    };
}
