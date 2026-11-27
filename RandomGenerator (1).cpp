#include "RandomGenerator.h"

#include <stdexcept>

/**
 * @details Сначала распределение создаётся с безопасным диапазоном 0..1: передача
 * неверного диапазона (min > max) в конструктор распределения привела бы
 * к неопределённому поведению. Проверив аргументы, присваиваем новое
 * распределение. Движок «засевается» значением std::random_device,
 * чтобы разные запуски программы давали разные матрицы.
 */
miit::algebra::RandomGenerator::RandomGenerator(const int min, const int max)
    : distribution(0, 1),
      engine(std::random_device{}())
{
    if (min > max)
    {
        throw std::invalid_argument("Минимум диапазона больше максимума");
    }
    // Опасный диапазон уже отсеян, можно безопасно пересоздать распределение
    this->distribution = std::uniform_int_distribution<int>(min, max);
}

/**
 * @details Вызов distribution(engine) возвращает равномерно распределённое
 * целое число из заданного при создании объекта отрезка.
 */
int miit::algebra::RandomGenerator::generate()
{
    return this->distribution(this->engine);
}
