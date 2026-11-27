#pragma once

#include <iostream>

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, читающий числа из потока ввода
     * @details Единственный класс, которому разрешается работать с потоками
     * ввода-вывода внутри алгоритма заполнения: он инкапсулирует чтение
     * клавиатурного ввода за интерфейсом Generator.
     */
    class IStreamGenerator : public Generator
    {
    private:
        /** @brief Ссылка на поток, из которого читаются числа */
        std::istream& in;

    public:
        /**
         * @brief Конструктор генератора
         * @param in Поток ввода; по умолчанию используется std::cin
         * @details Ссылка сохраняется, объект потока не копируется
         */
        IStreamGenerator(std::istream& in = std::cin);

        /**
         * @brief Прочитать очередное целое число из потока
         * @return Прочитанное число; 0, если чтение не удалось
         * @details При неудаче поток остаётся в состоянии fail,
         * поэтому последующие вызовы тоже вернут 0
         */
        int generate() override;
    };
}
