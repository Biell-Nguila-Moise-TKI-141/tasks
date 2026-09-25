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
     * @param new_capacity Новый размер выделяемой памяти.
     */
    void reallocate(const size_t new_capacity);
public:
    /** 
     * @brief Конструктор по умолчанию: создаёт пустой вектор. 
     */
    Vector();

    /** 
     * @brief Конструктор из списка инициализации: Vector v = {1, 2, 3};
     * @param list Список инициализации с элементами для заполнения вектора.
     */
    Vector(const std::initializer_list<int> list);

    /** 
     * @brief Конструктор копирования: глубокая копия данных.
     * @param other Вектор, из которого копируются данные.
     */
    Vector(const Vector& other);

    /** 
     * @brief Конструктор перемещения: передача ресурсов без копирования.
     * @param other Вектор, ресурсы которого перемещаются.
     */
    Vector(Vector&& other) noexcept; 

    /** 
     * @brief Деструктор: освобождает динамическую память. 
     */
    ~Vector();

    /**
     * @brief Вставляет элемент по указанному индексу, сдвигая последующие элементы.
     * @param index Позиция для вставки нового элемента.
     * @param value Значение, которое нужно вставить.
     * @throw std::out_of_range Если индекс больше текущего размера вектора.
     */
    void insert(const size_t index, const int value);

    /**
     * @brief Удаляет элемент по указанному индексу, сдвигая последующие элементы.
     * @param index Позиция элемента для удаления.
     * @throw std::out_of_range Если индекс выходит за пределы вектора.
     */
    void remove(const size_t index);

    /**
     * @brief Находит индекс первого вхождения указанного значения.
     * @param value Значение для поиска.
     * @return Индекс первого вхождения или -1, если значение не найдено.
     */
    int find(const int value) const;

    /** 
     * @brief Проверяет, пуст ли вектор. 
     * @return true, если вектор пуст; false в противном случае.
     */
    bool isEmpty() const;

    /** 
     * @brief Форматирует вектор в строку для вывода. 
     * @return Строковое представление вектора в формате "[elem1, elem2, ...]".
     */
    std::string ToString() const;

    /** 
     * @brief Возвращает текущее количество элементов в векторе. 
     * @return Количество элементов в векторе.
     */
    size_t size() const;

    /**
     * @brief Оператор присваивания копированием.
     * @param other Вектор, из которого копируются данные.
     * @return Ссылка на текущий вектор.
     */
    Vector& operator=(const Vector& other);

    /**
     * @brief Оператор присваивания перемещением.
     * @param other Вектор, ресурсы которого перемещаются.
     * @return Ссылка на текущий вектор.
     */
    Vector& operator=(Vector&& other) noexcept;

    /**
     * @brief Оператор доступа по индексу (изменяемый).
     * @param index Индекс элемента.
     * @return Ссылка на элемент по указанному индексу.
     * @throw std::out_of_range Если индекс выходит за пределы вектора.
     */
    int& operator[](const size_t index);

    /**
     * @brief Оператор доступа по индексу (константный).
     * @param index Индекс элемента.
     * @return Константная ссылка на элемент по указанному индексу.
     * @throw std::out_of_range Если индекс выходит за пределы вектора.
     */
    const int& operator[](const size_t index) const;

    /**
     * @brief Оператор добавления элемента в конец вектора.
     * @param value Значение, которое нужно добавить.
     * @return Ссылка на текущий вектор.
     */
    Vector& operator<<(const int value);

    /**
     * @brief Извлекает и удаляет последний элемент из вектора (аналог pop_back).
     * @param value Переменная для сохранения извлеченного значения.
     * @return Ссылка на текущий вектор.
     * @throw std::underflow_error Если вектор пуст.
     */
    Vector& operator>>(int& value);
};
