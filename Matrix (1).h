#pragma once

#include <cstddef>
#include <iosfwd>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Шаблонный класс матрицы (двумерного массива)
     * @tparam T Тип элементов матрицы (в задании используется int)
     * @details Хранилище организовано как вектор векторов: data[i] — i-я строка,
     * data[i][j] — элемент в i-й строке и j-м столбце. Размеры rows и columns
     * хранятся отдельно, чтобы не вычислять их каждый раз через size().
     * Класс не знает о консоли: потоковые операторы лишь реализуют
     * текстовое представление по требованию задания.
     */
    template <typename T>
    class Matrix
    {
    private:
        /** @brief Вектор строк матрицы; каждая строка — вектор элементов типа T */
        std::vector<std::vector<T>> data;

        /** @brief Количество строк матрицы */
        std::size_t rows = 0;

        /** @brief Количество столбцов матрицы */
        std::size_t columns = 0;

    public:
        /**
         * @brief Конструктор по умолчанию
         * @details Создаёт пустую матрицу 0×0. Благодаря инициализаторам полей
         * rows и columns равны нулю, а data не содержит ни одной строки.
         */
        Matrix() = default;

        /**
         * @brief Конструктор матрицы заданного размера
         * @param rowCount Количество строк
         * @param columnCount Количество столбцов
         * @details Все элементы value-инициализируются, то есть для int
         * получаются нули. Порядок инициализации совпадает с порядком полей:
         * data, rows, columns.
         */
        Matrix(const std::size_t rowCount, const std::size_t columnCount)
            : data(rowCount, std::vector<T>(columnCount)),
              rows(rowCount),
              columns(columnCount)
        {
        }

        /**
         * @brief Конструктор копирования
         * @param other Матрица, которую нужно скопировать
         * @details Глубокое копирование обеспечивается std::vector: копия
         * владеет собственными строками и не зависит от исходной матрицы.
         */
        Matrix(const Matrix& other) = default;

        /**
         * @brief Конструктор перемещения
         * @param other Временная матрица, ресурсы которой передаются новой
         * @details После перемещения other остаётся корректным пустым объектом
         */
        Matrix(Matrix&& other) noexcept = default;

        /**
         * @brief Деструктор
         * @details Освобождение памяти выполняет std::vector, ручного delete нет
         */
        ~Matrix() = default;

        /**
         * @brief Оператор присваивания копированием
         * @param other Матрица-источник
         * @return Ссылка на этот объект для цепочки присваиваний
         */
        Matrix& operator=(const Matrix& other) = default;

        /**
         * @brief Оператор присваивания перемещением
         * @param other Временная матрица, ресурсы которой переносятся сюда
         * @return Ссылка на этот объект
         */
        Matrix& operator=(Matrix&& other) noexcept = default;

        /**
         * @brief Получить количество строк
         * @return Значение поля rows
         */
        std::size_t getRows() const noexcept
        {
            return this->rows;
        }

        /**
         * @brief Получить количество столбцов
         * @return Значение поля columns
         */
        std::size_t getColumns() const noexcept
        {
            return this->columns;
        }

        /**
         * @brief Получить количество столбцов (краткий псевдоним)
         * @return То же значение, что и getColumns()
         */
        std::size_t getCols() const noexcept
        {
            return this->getColumns();
        }

        /**
         * @brief Доступ к строке для чтения и изменения
         * @param rowIndex Индекс строки (отсчёт с нуля)
         * @return Ссылка на вектор-строку; можно писать matrix[i][j]
         * @throw std::out_of_range Если rowIndex >= количества строк
         */
        std::vector<T>& operator[](const std::size_t rowIndex)
        {
            if (rowIndex >= this->rows)
            {
                throw std::out_of_range("Индекс строки вышел за границы матрицы");
            }
            return this->data[rowIndex];
        }

        /**
         * @brief Доступ к строке только для чтения
         * @param rowIndex Индекс строки (отсчёт с нуля)
         * @return Константная ссылка на вектор-строку
         * @throw std::out_of_range Если rowIndex >= количества строк
         */
        const std::vector<T>& operator[](const std::size_t rowIndex) const
        {
            if (rowIndex >= this->rows)
            {
                throw std::out_of_range("Индекс строки вышел за границы матрицы");
            }
            return this->data[rowIndex];
        }

        /**
         * @brief Получить копию указанной строки
         * @param rowIndex Индекс строки
         * @return Вектор значений строки
         * @details Возвращается копия, поэтому изменение результата не меняет матрицу.
         * Это важно при вставке: исходная строка не будет перезаписана.
         * @throw std::out_of_range Если индекс не существует
         */
        std::vector<T> getRow(const std::size_t rowIndex) const
        {
            return this->operator[](rowIndex);
        }

        /**
         * @brief Вставить строку перед указанным индексом
         * @param index Позиция вставки: 0..getRows(); index == rows означает вставку в конец
         * @param row Вектор значений новой строки
         * @details Рост матрицы происходит за счёт std::vector::insert,
         * поле rows увеличивается на единицу. Длина строки должна совпадать
         * с числом столбцов, иначе матрица стала бы «рваной».
         * @throw std::out_of_range Если index > getRows()
         * @throw std::invalid_argument Если размер row не равен количеству столбцов
         */
        void insertRow(const std::size_t index, const std::vector<T>& row)
        {
            if (index > this->rows)
            {
                throw std::out_of_range("Индекс вставки вышел за границы матрицы");
            }
            if (row.size() != this->columns)
            {
                throw std::invalid_argument("Длина вставляемой строки не равна числу столбцов");
            }
            this->data.insert(this->data.begin() + static_cast<std::ptrdiff_t>(index), row);
            ++this->rows;
        }

        /**
         * @brief Заполнить матрицу значениями генератора
         * @param generator Генератор, у которого для каждой ячейки вызывается generate()
         * @details Обход построчно: от строки 0 до rows-1, в каждой строке
         * слева направо. int-результат приводится к типу T через static_cast.
         */
        void fill(Generator& generator)
        {
            for (auto& row : this->data)
            {
                for (auto& item : row)
                {
                    item = static_cast<T>(generator.generate());
                }
            }
        }

        /**
         * @brief Представить матрицу в виде строки
         * @return Элементы разделены табуляцией, строки — переводом строки
         * @details Завершающие разделители не добавляются, поэтому вывод
         * выглядит аккуратно и в консоли, и в строковом представлении.
         */
        std::string toString() const
        {
            std::ostringstream stream;
            for (std::size_t i = 0; i < this->rows; ++i)
            {
                for (std::size_t j = 0; j < this->columns; ++j)
                {
                    stream << this->data[i][j];
                    if (j + 1 < this->columns)
                    {
                        stream << '\t';
                    }
                }
                if (i + 1 < this->rows)
                {
                    stream << '\n';
                }
            }
            return stream.str();
        }

        /**
         * @brief Сравнить матрицы по размеру и содержимому
         * @param other Матрица, с которой выполняется сравнение
         * @return true, если размеры и все элементы совпадают
         */
        bool operator==(const Matrix& other) const
        {
            return this->rows == other.rows && this->columns == other.columns
                && this->data == other.data;
        }

        /**
         * @brief Вывести матрицу в поток
         * @param os Поток вывода
         * @param matrix Матрица для вывода
         * @return Тот же поток для цепочки вызовов
         * @details Формат совпадает с toString(): строки и столбцы без заголовка
         */
        friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
        {
            os << matrix.toString();
            return os;
        }

        /**
         * @brief Прочитать элементы матрицы из потока
         * @param is Поток ввода
         * @param matrix Матрица, элементы которой будут перезаписаны
         * @return Тот же поток; при неудачном чтении он находится в состоянии fail
         * @details Предполагается, что размеры матрицы заданы заранее
         * (например, Matrix<int> m(2, 3)). Числа читаются построчно:
         * строка 0 слева направо, затем строка 1 и т. д.
         */
        friend std::istream& operator>>(std::istream& is, Matrix<T>& matrix)
        {
            for (auto& row : matrix.data)
            {
                for (auto& item : row)
                {
                    if (!(is >> item))
                    {
                        return is; // поток уже пометил ошибку, матрица частично заполнена
                    }
                }
            }
            return is;
        }
    };
}
