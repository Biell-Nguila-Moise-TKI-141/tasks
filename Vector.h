#pragma once
#include <initializer_list>
#include <string>
#include <stdexcept>

class Vector {
private:
    int* m_data;          // Указатель на динамический массив
    size_t m_size;       // Текущее количество элементов
    size_t m_capacity;   // Выделенная память

    /**
     * @brief Перевыделяет динамическую память под новый размер.
     * Переносит существующие элементы в новый буфер. Старая память освобождается.
     */
    void reallocate(size_t new_capacity);

public:
    Vector();
    Vector(std::initializer_list<int> list);
    Vector(const Vector& other); // Глубокое копирование
    Vector(Vector&& other) noexcept; // Перенос указателей без копирования
    ~Vector();

    /**
     * @brief Вставляет элемент по индексу.
     * Сдвигает последующие элементы вправо. При необходимости расширяет память.
     * @throw std::out_of_range Если index > size().
     */
    void insert(size_t index, int value);

    /**
     * @brief Удаляет элемент по индексу.
     * Сдвигает последующие элементы влево.
     * @throw std::out_of_range Если индекс некорректен или вектор пуст.
     */
    void remove(size_t index);

    /**
     * @brief Ищет элемент по значению.
     * @return Индекс первого найденного элемента или -1, если совпадений нет.
     */
    int find(int value) const;

    bool isEmpty() const;
    std::string ToString() const; // Форматирует вектор в строку для вывода
    size_t size() const;

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    // Операторы [] не проверяют выход за границы для максимальной скорости.
    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    /**
     * @brief Добавляет элемент в конец вектора (аналог push_back).
     * Позволяет делать цепочки вызовов: v << 5 << 10;
     */
    Vector& operator<<(int value);

    /**
     * @brief Извлекает и удаляет последний элемент из вектора (аналог pop_back).
     * @param value Переменная для сохранения извлеченного значения.
     * @throw std::underflow_error Если вектор пуст.
     */
    Vector& operator>>(int& value);
};
