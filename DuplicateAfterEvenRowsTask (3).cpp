#include "DuplicateAfterEvenRowsTask.h"

#include <utility>
#include <vector>

/**
 * @details Обычный конструктор: базовый класс создаст и заполнит матрицу.
 */
miit::algebra::DuplicateAfterEvenRowsTask::DuplicateAfterEvenRowsTask(
    const std::size_t rowCount, const std::size_t columnCount, Generator& gen)
    : Exercise(rowCount, columnCount, gen)
{
}

/**
 * @details Матрица принимается по значению и перемещается в базовый класс,
 * поэтому копия результата первого задания остаётся у вызывающего кода.
 */
miit::algebra::DuplicateAfterEvenRowsTask::DuplicateAfterEvenRowsTask(
    Matrix<int> source, Generator& gen)
    : Exercise(std::move(source), gen)
{
}

/**
 * @details Копия первой строки сохраняется до вставок: после добавления строк
 * первая строка остаётся на месте, но копировать каждый раз заново не нужно.
 *
 * Индексы чётных строк — нечётные числа (1, 3, 5, ...). Вставлять нужно
 * после них, то есть по индексам 2, 4, 6, ... Идём от последней позиции
 * вставки к первой с шагом -2: тогда каждая вставка сдвигает только строки
 * ниже, а уже вставленные копии никогда не анализируются как «чётные».
 */
void miit::algebra::DuplicateAfterEvenRowsTask::solve()
{
    const std::size_t rowCount = this->matrix.getRows();

    // Меньше двух строк — чётных строк (2-й, 4-й, ...) нет
    if (rowCount < 2)
    {
        return;
    }

    const std::vector<int> firstRow = this->matrix.getRow(0);

    // Последняя позиция вставки: rowCount, если число строк чётно,
    // иначе rowCount - 1 (последняя чётная строка — предпоследняя)
    std::size_t insertAt = (rowCount % 2 == 0) ? rowCount : rowCount - 1;
    while (insertAt > 0)
    {
        this->matrix.insertRow(insertAt, firstRow);
        if (insertAt < 2)
        {
            break; // следующая позиция была бы нулевой — это не «после чётной строки»
        }
        insertAt -= 2;
    }
}
