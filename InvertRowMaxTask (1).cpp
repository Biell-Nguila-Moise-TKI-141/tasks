#include "InvertRowMaxTask.h"

#include <limits>

/**
 * @details Конструктор только передаёт параметры базовому классу Exercise,
 * который создаст матрицу и заполнит её через генератор.
 */
miit::algebra::InvertRowMaxTask::InvertRowMaxTask(
    const std::size_t rowCount, const std::size_t columnCount, Generator& gen)
    : Exercise(rowCount, columnCount, gen)
{
}

/**
 * @details Алгоритм состоит из двух проходов по каждой строке.
 * На первом проходе ищется максимальный модуль. На втором — все элементы
 * с найденным модулем меняют знак. Модуль вычисляется в long long:
 * это защищает от переполнения при INT_MIN, для которого -value в int
 * даёт неопределённое поведение. Поэтому INT_MIN пропускается.
 */
void miit::algebra::InvertRowMaxTask::solve()
{
    const std::size_t rowCount = this->matrix.getRows();
    const std::size_t columnCount = this->matrix.getColumns();

    for (std::size_t row = 0; row < rowCount; ++row)
    {
        long long maxMagnitude = 0;

        // Первый проход: максимальный модуль в текущей строке
        for (std::size_t column = 0; column < columnCount; ++column)
        {
            const long long value = this->matrix[row][column];
            const long long magnitude = value < 0 ? -value : value; // расширение до long long
            if (magnitude > maxMagnitude)
            {
                maxMagnitude = magnitude;
            }
        }

        // Второй проход: все элементы с этим модулем меняют знак.
        // Нули имеют модуль 0, но -0 == 0, поэтому они остаются нулями.
        for (std::size_t column = 0; column < columnCount; ++column)
        {
            const int element = this->matrix[row][column];
            if (element == std::numeric_limits<int>::min())
            {
                continue; // противоположное число не представимо в int
            }
            const long long value = element;
            const long long magnitude = value < 0 ? -value : value;
            if (magnitude == maxMagnitude)
            {
                this->matrix[row][column] = -element;
            }
        }
    }
}
