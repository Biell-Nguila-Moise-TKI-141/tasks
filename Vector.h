#pragma once
#include <initializer_list>
#include <string>
#include <stdexcept>

class Vector {
private:
    int* data_;         
    size_t size_;           

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

    void insert(const size_t index, const int value);

    void remove(const size_t index);

    int find(const int value) const;

    /** @brief Проверяет, пуст ли вектор. */
    bool isEmpty() const;

    /** @brief Форматирует вектор в строку для вывода. */
    std::string ToString() const;

    /** @brief Возвращает текущее количество элементов в векторе. */
    size_t size() const;

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    
    int& operator[](const size_t index);
    const int& operator[](const size_t index) const;

    Vector& operator<<(const int value);

    /**
     * @brief Извлекает и удаляет последний элемент из вектора (аналог pop_back).
     * @param value Переменная для сохранения извлеченного значения.
     * @throw std::underflow_error Если вектор пуст.
     */
    Vector& operator>>(int& value);
};