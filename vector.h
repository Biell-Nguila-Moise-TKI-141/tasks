#pragma once
#include <initializer_list>
#include <string>
#include <stdexcept>

class Vector {
private:  
    /**
     * @brief Перевыделяет динамическую память под новый размер.
     * Переносит существующие элементы в новый буфер. Старая память освобождается.
     */
    void reallocate(const size_t new_capacity);

public:
 /** @brief Конструктор по умолчанию: создаёт пустой вектор. */
    Vector();
     /** @brief Конструктор из списка инициализации: Vector v = {1, 2, 3}; */
    Vector(const std::initializer_list<int> list);
     /** @brief Конструктор копирования: глубокая копия данных. */
    Vector(const Vector& other);
      /** @brief Конструктор перемещения: передача ресурсов без копирования. */

    Vector(Vector&& other) noexcept; 
    /** @brief Деструктор: освобождает динамическую память. */
    ~Vector();

    /**
     * @brief Вставляет элемент по индексу.
     * Сдвигает последующие элементы вправо. При необходимости расширяет память.
     * @throw std::out_of_range Если index > size().
     */
    void insert(const size_t index, int value);

    /**
     * @brief Удаляет элемент по индексу.
     * Сдвигает последующие элементы влево.
     * @throw std::out_of_range Если индекс некорректен или вектор пуст.
     */
    void remove(const size_t index);

    /**
     * @brief Ищет элемент по значению.
     * @return Индекс первого найденного элемента или -1, если совпадений нет.
     */
    int find(const int value) const;

    bool isEmpty() const;
    std::string ToString() const; // Форматирует вектор в строку для вывода
    size_t size() const;
/** @brief Оператор присваивания копированием: глубокая копия данных. */
    Vector& operator=(const Vector& other);
    /** @brief Оператор присваивания перемещением: передача ресурсов без копирования. */
    Vector& operator=(Vector&& other) noexcept;

    // Операторы [] не проверяют выход за границы для максимальной скорости.
    int& operator[](const size_t index);
    const int& operator[](const size_t index) const;

    /**
     * @brief Добавляет элемент в конец вектора (аналог push_back).
     * Позволяет делать цепочки вызовов: v << 5 << 10;
     */
    Vector& operator<<(const int value);

    /**
     * @brief Извлекает и удаляет последний элемент из вектора (аналог pop_back).
     * @param value Переменная для сохранения извлеченного значения.
     * @throw std::underflow_error Если вектор пуст.
     */
    Vector& operator>>(int& value);
};

