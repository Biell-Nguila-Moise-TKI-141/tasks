#pragma once

#include <cstddef>
#include <utility>

#include "Generator.h"
#include "Matrix.h"

namespace miit::algebra
{
    /**
     * @brief Базовый абстрактный класс задания
     * @details Агрегирует матрицу и генератор: матрица создаётся или сразу
     * заполняется через генератор, а конкретные задания реализуют solve().
     * Второй конструктор позволяет передать уже готовую матрицу — это нужно,
     * чтобы оба пункта одного варианта выполнялись последовательно.
     */
    class Exercise
    {
    protected:
        /** @brief Матрица, с которой работает задание */
        Matrix<int> matrix;

        /** @brief Ссылка на генератор, использованный при заполнении матрицы */
        Generator& generator;

    public:
        /**
         * @brief Конструктор с созданием и заполнением новой матрицы
         * @param rowCount Количество строк
         * @param columnCount Количество столбцов
         * @param gen Генератор значений (ссылка на существующий объект)
         * @details Сначала создаётся матрица нужного размера, затем вызывается
         * matrix.fill(generator), то есть автоматического ввода нет.
         */
        Exercise(const std::size_t rowCount, const std::size_t columnCount, Generator& gen)
            : matrix(rowCount, columnCount), generator(gen)
        {
            this->matrix.fill(this->generator);
        }

        /**
         * @brief Конструктор из уже готовой матрицы
         * @param source Матрица, которая будет перемещена в поле matrix
         * @param gen Генератор (сохраняется для единообразия наследников)
         * @details Позволяет применить второе задание варианта к результату первого
         */
        Exercise(Matrix<int> source, Generator& gen)
            : matrix(std::move(source)), generator(gen)
        {
        }

        /**
         * @brief Виртуальный деструктор
         * @details Позволяет удалять наследников через указатель на Exercise
         */
        virtual ~Exercise() = default;

        /**
         * @brief Выполнить задание
         * @details Чисто виртуальный метод, обязателен к переопределению.
         * Реализация изменяет внутреннюю матрицу, новый объект не создаётся.
         */
        virtual void solve() = 0;

        /**
         * @brief Получить текущее состояние матрицы
         * @return Константная ссылка на внутреннюю матрицу
         * @details Ссылка константная, поэтому результат solve() нельзя случайно
         * испортить извне; для цепочки заданий можно скопировать матрицу.
         */
        const Matrix<int>& getMatrix() const noexcept
        {
            return this->matrix;
        }
    };
}
