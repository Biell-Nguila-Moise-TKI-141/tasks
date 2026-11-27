#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, всегда возвращающий одно и то же число
     * @details Используется, например, чтобы заполнить матрицу нулями
     * или любым другим постоянным значением.
     */
    class ConstGenerator : public Generator
    {
    private:
        /** @brief Константное значение, возвращаемое генератором */
        int value;

    public:
        /**
         * @brief Конструктор генератора
         * @param val Значение, которое будет возвращать generate(); по умолчанию 0
         */
        ConstGenerator(const int val = 0);

        /**
         * @brief Получить сохранённое константное значение
         * @return Значение поля value
         */
        int generate() override;
    };
}
