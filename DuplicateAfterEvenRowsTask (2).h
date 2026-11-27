#pragma once

#include <cstddef>

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Задание: вставить копию первой строки после каждой чётной строки
     * @details Второй пункт варианта 1. Чётными считаются строки с номерами
     * 2, 4, 6, ... в человеческом счёте, то есть с индексами 1, 3, 5, ...
     */
    class DuplicateAfterEvenRowsTask : public Exercise
    {
    public:
        /**
         * @brief Конструктор с созданием и заполнением новой матрицы
         * @param rowCount Количество строк матрицы
         * @param columnCount Количество столбцов матрицы
         * @param gen Генератор для заполнения матрицы
         */
        DuplicateAfterEvenRowsTask(const std::size_t rowCount, const std::size_t columnCount, Generator& gen);

        /**
         * @brief Конструктор из уже готовой матрицы
         * @param source Матрица-результат предыдущего задания
         * @param gen Генератор, который сохраняется в базовом классе
         */
        DuplicateAfterEvenRowsTask(Matrix<int> source, Generator& gen);

        /**
         * @brief Вставить копию первой строки после каждой чётной строки
         * @details Вставка идёт снизу вверх, чтобы добавленные строки
         * не считались чётными и не порождали новые вставки.
         * Если строк меньше двух, матрица не изменяется.
         */
        void solve() override;
    };
}
