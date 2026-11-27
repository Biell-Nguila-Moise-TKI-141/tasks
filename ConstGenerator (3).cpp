#include "ConstGenerator.h"

/**
 * @details Аргумент по умолчанию объявлен в заголовке, поэтому здесь
 * параметр записывается без значения по умолчанию повторно его указывать нельзя.
 */
miit::algebra::ConstGenerator::ConstGenerator(const int val)
    : value{ val }
{
}

/**
 * @details Метод не меняет состояние объекта, но не помечен const,
 * так как он переопределяет неконстантный виртуальный метод Generator::generate().
 */
int miit::algebra::ConstGenerator::generate()
{
    return this->value;
}
