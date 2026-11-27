#include "CppUnitTest.h"

#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "ConstGenerator.h"
#include "DuplicateAfterEvenRowsTask.h"
#include "IStreamGenerator.h"
#include "InvertRowMaxTask.h"
#include "Matrix.h"
#include "RandomGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::algebra;

namespace Tests
{
    /**
     * @brief Тесты шаблонного класса Matrix
     */
    TEST_CLASS(MatrixTests)
    {
    public:
        /**
         * @brief Конструктор по умолчанию создаёт матрицу 0×0
         */
        TEST_METHOD(DefaultConstructor_Test)
        {
            Matrix<int> matrix;
            Assert::AreEqual(static_cast<std::size_t>(0), matrix.getRows());
            Assert::AreEqual(static_cast<std::size_t>(0), matrix.getColumns());
            Assert::AreEqual(std::string(), matrix.toString());
        }

        /**
         * @brief Конструктор с размерами создаёт матрицу, заполненную нулями
         */
        TEST_METHOD(ParameterizedConstructor_Test)
        {
            Matrix<int> matrix(2, 3);
            Assert::AreEqual(static_cast<std::size_t>(2), matrix.getRows());
            Assert::AreEqual(static_cast<std::size_t>(3), matrix.getCols());
            for (std::size_t row = 0; row < matrix.getRows(); ++row)
            {
                for (std::size_t column = 0; column < matrix.getColumns(); ++column)
                {
                    Assert::AreEqual(0, matrix[row][column]);
                }
            }
        }

        /**
         * @brief Конструктор копирования создаёт независимую копию
         */
        TEST_METHOD(CopyConstructor_Test)
        {
            Matrix<int> original(2, 2);
            original[0][0] = 10;
            original[1][1] = 20;
            Matrix<int> copy(original);
            Assert::AreEqual(10, copy[0][0]);
            Assert::AreEqual(20, copy[1][1]);
            copy[0][0] = 99;
            Assert::AreEqual(10, original[0][0]);
        }

        /**
         * @brief Конструктор перемещения сохраняет размеры и значения
         */
        TEST_METHOD(MoveConstructor_Test)
        {
            Matrix<int> original(2, 2);
            original[0][1] = 42;
            Matrix<int> moved(std::move(original));
            Assert::AreEqual(static_cast<std::size_t>(2), moved.getRows());
            Assert::AreEqual(42, moved[0][1]);
        }

        /**
         * @brief Присваивание копированием копирует содержимое
         */
        TEST_METHOD(CopyAssignment_Test)
        {
            Matrix<int> source(2, 2);
            source[0][0] = 7;
            Matrix<int> target;
            target = source;
            Assert::AreEqual(static_cast<std::size_t>(2), target.getRows());
            Assert::AreEqual(7, target[0][0]);
        }

        /**
         * @brief Присваивание перемещением передаёт владение данными
         */
        TEST_METHOD(MoveAssignment_Test)
        {
            Matrix<int> source(2, 2);
            source[1][0] = 15;
            Matrix<int> target;
            target = std::move(source);
            Assert::AreEqual(static_cast<std::size_t>(2), target.getRows());
            Assert::AreEqual(15, target[1][0]);
        }

        /**
         * @brief operator[] доступен в неконстантной и константной версиях
         */
        TEST_METHOD(SubscriptOperator_Test)
        {
            Matrix<int> matrix(2, 2);
            matrix[0][0] = 1;
            matrix[1][1] = 4;
            const Matrix<int>& constMatrix = matrix;
            Assert::AreEqual(1, constMatrix[0][0]);
            Assert::AreEqual(4, constMatrix[1][1]);
        }

        /**
         * @brief operator[] выбрасывает out_of_range при неверном индексе
         */
        TEST_METHOD(SubscriptOperator_OutOfRange_Test)
        {
            Matrix<int> matrix(2, 2);
            Assert::ExpectException<std::out_of_range>([&]() { matrix[2][0] = 1; });
        }

        /**
         * @brief getRow возвращает копию строки
         */
        TEST_METHOD(GetRow_Test)
        {
            Matrix<int> matrix(2, 2);
            matrix[1][0] = 8;
            matrix[1][1] = 9;
            const std::vector<int> row = matrix.getRow(1);
            Assert::AreEqual(static_cast<std::size_t>(2), row.size());
            Assert::AreEqual(8, row[0]);
            Assert::AreEqual(9, row[1]);
            Assert::ExpectException<std::out_of_range>([&]() { matrix.getRow(5); });
        }

        /**
         * @brief insertRow вставляет строку перед заданным индексом
         */
        TEST_METHOD(InsertRow_Test)
        {
            Matrix<int> matrix(2, 2);
            matrix[0][0] = 1; matrix[0][1] = 2;
            matrix[1][0] = 3; matrix[1][1] = 4;
            matrix.insertRow(1, std::vector<int>{5, 6});
            Assert::AreEqual(static_cast<std::size_t>(3), matrix.getRows());
            Assert::AreEqual(5, matrix[1][0]);
            Assert::AreEqual(3, matrix[2][0]);
            Assert::ExpectException<std::out_of_range>([&]()
            {
                matrix.insertRow(10, std::vector<int>{0, 0});
            });
            Assert::ExpectException<std::invalid_argument>([&]()
            {
                matrix.insertRow(0, std::vector<int>{0});
            });
        }

        /**
         * @brief fill заполняет матрицу через генератор
         */
        TEST_METHOD(Fill_Test)
        {
            Matrix<int> matrix(2, 3);
            ConstGenerator generator(7);
            matrix.fill(generator);
            Assert::AreEqual(7, matrix[0][0]);
            Assert::AreEqual(7, matrix[1][2]);
        }

        /**
         * @brief toString не добавляет лишних разделителей в конце
         */
        TEST_METHOD(ToString_Test)
        {
            Matrix<int> matrix(1, 2);
            matrix[0][0] = 5;
            matrix[0][1] = 9;
            Assert::AreEqual(std::string("5\t9"), matrix.toString());
        }

        /**
         * @brief operator<< выводит то же, что toString()
         */
        TEST_METHOD(StreamOutput_Test)
        {
            Matrix<int> matrix(2, 2);
            matrix[0][0] = 3;
            matrix[1][1] = 7;
            std::ostringstream stream;
            stream << matrix;
            Assert::AreEqual(matrix.toString(), stream.str());
        }

        /**
         * @brief operator>> читает элементы в заранее созданную матрицу
         */
        TEST_METHOD(StreamInput_Test)
        {
            Matrix<int> matrix(2, 2);
            std::istringstream input("10 20 30 40");
            input >> matrix;
            Assert::AreEqual(10, matrix[0][0]);
            Assert::AreEqual(20, matrix[0][1]);
            Assert::AreEqual(30, matrix[1][0]);
            Assert::AreEqual(40, matrix[1][1]);
        }
    };

    /**
     * @brief Тесты генераторов
     */
    TEST_CLASS(GeneratorTests)
    {
    public:
        /**
         * @brief ConstGenerator всегда возвращает одно значение
         */
        TEST_METHOD(ConstGenerator_Test)
        {
            ConstGenerator generator(99);
            Assert::AreEqual(99, generator.generate());
            Assert::AreEqual(99, generator.generate());
            ConstGenerator defaultGenerator;
            Assert::AreEqual(0, defaultGenerator.generate());
        }

        /**
         * @brief IStreamGenerator читает числа из потока по порядку
         */
        TEST_METHOD(IStreamGenerator_Test)
        {
            std::istringstream input("42 15 -7");
            IStreamGenerator generator(input);
            Assert::AreEqual(42, generator.generate());
            Assert::AreEqual(15, generator.generate());
            Assert::AreEqual(-7, generator.generate());
        }

        /**
         * @brief RandomGenerator не выходит за границы диапазона
         */
        TEST_METHOD(RandomGenerator_Test)
        {
            RandomGenerator generator(-5, 5);
            for (int i = 0; i < 20; ++i)
            {
                const int value = generator.generate();
                Assert::IsTrue(value >= -5 && value <= 5);
            }
        }
    };

    /**
     * @brief Тесты первого пункта варианта 1
     */
    TEST_CLASS(InvertRowMaxTaskTests)
    {
    public:
        /**
         * @brief Инвертируются все элементы с максимальным модулем в строке
         */
        TEST_METHOD(InvertRowMax_TiesAndZeros_Test)
        {
            std::istringstream input("1 -5 3 -7 2 7 0 0 4");
            IStreamGenerator generator(input);
            InvertRowMaxTask task(3, 3, generator);
            task.solve();
            const Matrix<int>& result = task.getMatrix();
            Assert::AreEqual(1, result[0][0]);
            Assert::AreEqual(5, result[0][1]);
            Assert::AreEqual(3, result[0][2]);
            Assert::AreEqual(7, result[1][0]);
            Assert::AreEqual(2, result[1][1]);
            Assert::AreEqual(-7, result[1][2]);
            Assert::AreEqual(0, result[2][0]);
            Assert::AreEqual(0, result[2][1]);
            Assert::AreEqual(-4, result[2][2]);
        }

        /**
         * @brief INT_MIN не меняется: его противоположность не представима в int
         */
        TEST_METHOD(InvertRowMax_IntMinStays_Test)
        {
            std::istringstream input("-2147483648 1");
            IStreamGenerator generator(input);
            InvertRowMaxTask task(1, 2, generator);
            task.solve();
            Assert::AreEqual(std::numeric_limits<int>::min(), task.getMatrix()[0][0]);
            Assert::AreEqual(1, task.getMatrix()[0][1]);
        }
    };

    /**
     * @brief Тесты второго пункта варианта 1
     */
    TEST_CLASS(DuplicateAfterEvenRowsTaskTests)
    {
    public:
        /**
         * @brief После 2-й и 4-й строк вставляется копия первой
         */
        TEST_METHOD(DuplicateAfterEvenRows_FourRows_Test)
        {
            std::istringstream input("1 2 3 4 5 6 7 8");
            IStreamGenerator generator(input);
            DuplicateAfterEvenRowsTask task(4, 2, generator);
            task.solve();
            const Matrix<int>& result = task.getMatrix();
            Assert::AreEqual(static_cast<std::size_t>(6), result.getRows());
            Assert::AreEqual(1, result[2][0]);
            Assert::AreEqual(2, result[2][1]);
            Assert::AreEqual(3, result[3][0]);
            Assert::AreEqual(7, result[4][0]);
            Assert::AreEqual(1, result[5][0]);
            Assert::AreEqual(2, result[5][1]);
        }

        /**
         * @brief Возникновение новых «чётных» строк не вызывает новые вставки
         */
        TEST_METHOD(DuplicateAfterEvenRows_ThreeRows_Test)
        {
            std::istringstream input("1 2 3 4 5 6 7 8 9");
            IStreamGenerator generator(input);
            DuplicateAfterEvenRowsTask task(3, 3, generator);
            task.solve();
            const Matrix<int>& result = task.getMatrix();
            Assert::AreEqual(static_cast<std::size_t>(4), result.getRows());
            Assert::AreEqual(4, result[1][0]);
            Assert::AreEqual(1, result[2][0]);
            Assert::AreEqual(7, result[3][0]);
        }

        /**
         * @brief Если строк меньше двух, вставок нет
         */
        TEST_METHOD(DuplicateAfterEvenRows_OneRow_Test)
        {
            std::istringstream input("1 2");
            IStreamGenerator generator(input);
            DuplicateAfterEvenRowsTask task(1, 2, generator);
            task.solve();
            Assert::AreEqual(static_cast<std::size_t>(1), task.getMatrix().getRows());
            Assert::AreEqual(2, task.getMatrix()[0][1]);
        }

        /**
         * @brief Последовательное применение обоих пунктов варианта 1
         */
        TEST_METHOD(VariantOne_Chain_Test)
        {
            std::istringstream input("1 -5 3 -7 2 7 0 0 4 -2 -9 6");
            IStreamGenerator generator(input);
            InvertRowMaxTask inversion(4, 3, generator);
            inversion.solve();
            DuplicateAfterEvenRowsTask duplication(inversion.getMatrix(), generator);
            duplication.solve();
            const Matrix<int>& result = duplication.getMatrix();
            Assert::AreEqual(static_cast<std::size_t>(6), result.getRows());
            Assert::AreEqual(5, result[0][1]);
            Assert::AreEqual(-7, result[1][2]);
            Assert::AreEqual(5, result[2][1]);
            Assert::AreEqual(9, result[4][1]);
            Assert::AreEqual(5, result[5][1]);
        }
    };
}
