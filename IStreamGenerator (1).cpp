#include "IStreamGenerator.h"

/**
 * @details Поле in — ссылка, поэтому оно обязательно инициализируется
 * в списке инициализации; копирование потока было бы запрещено.
 */
miit::algebra::IStreamGenerator::IStreamGenerator(std::istream& in)
    : in{ in }
{
}

/**
 * @details Операция >> сама выставляет failbit при неверном вводе.
 * Значение value предварительно обнулено, поэтому при ошибке метод
 * возвращает 0 и не использует неинициализированную память.
 */
int miit::algebra::IStreamGenerator::generate()
{
    int value = 0;
    this->in >> value;
    return value;
}
