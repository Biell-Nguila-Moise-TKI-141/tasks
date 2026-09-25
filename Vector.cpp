#include "pch.h"
#include "Vector.h"

/**
 * @brief Обычный конструктор.
 * Создает пустой вектор. Указатель равен nullptr, размер равен 0.
 */
Vector::Vector() : m_data(nullptr), m_size(0) {}

/**
 * @brief Конструктор из списка.
 * @param list Список чисел для копирования в вектор.
 */
Vector::Vector(std::initializer_list<int> list) : m_size(list.size()) {
    m_data = new int[m_size];
    size_t i = 0;
    for (int val : list) {
        m_data[i++] = val;
    }
}

/**
 * @brief Конструктор копирования.
 * Делает глубокую копию другого вектора.
 * @param other Вектор, который нужно скопировать.
 */
Vector::Vector(const Vector& other) : m_size(other.m_size) {
    m_data = new int[m_size];
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
}

/**
 * @brief Конструктор перемещения.
 * Забирает данные у другого вектора. Копирования нет.
 * @param other Вектор, у которого забираем данные. Он станет пустым.
 */
Vector::Vector(Vector&& other) noexcept : m_data(other.m_data), m_size(other.m_size) {
    other.m_data = nullptr;
    other.m_size = 0;
}

/**
 * @brief Деструктор.
 * Освобождает память.
 */
Vector::~Vector() {
    delete[] m_data;
}

/**
 * @brief Выделяет новый массив нужного размера.
 * Копирует старые элементы в новый массив.
 * @param new_size Новый размер массива.
 */
void Vector::reallocate(size_t new_size) {
    int* new_data = new int[new_size];
    for (size_t i = 0; i < m_size && i < new_size; ++i) {
        new_data[i] = m_data[i];
    }
    delete[] m_data;
    m_data = new_data;
}

/**
 * @brief Вставляет число на заданную позицию.
 * @param index Позиция для вставки (от 0 до m_size).
 * @param value Число для вставки.
 * @throws std::out_of_range Если индекс неправильный.
 */
void Vector::insert(size_t index, const int value) {
    if (index > m_size) {
        throw std::out_of_range("Индекс за пределами вектора");
    }

    reallocate(m_size + 1);

    for (size_t i = m_size; i > index; --i) {
        m_data[i] = m_data[i - 1];
    }
    m_data[index] = value;
    ++m_size;
}

/**
 * @brief Удаляет элемент на заданной позиции.
 * @param index Позиция элемента для удаления.
 * @throws std::out_of_range Если индекс неправильный.
 */
void Vector::remove(size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("Индекс за пределами вектора");
    }
    for (size_t i = index; i < m_size - 1; ++i) {
        m_data[i] = m_data[i + 1];
    }
    --m_size;
    if (m_size == 0) {
        delete[] m_data;
        m_data = nullptr;
    } else {
        reallocate(m_size);
    }
}

/**
 * @brief Ищет число в векторе.
 * @param value Число для поиска.
 * @return Индекс первого найденного числа или -1, если числа нет.
 */
int Vector::find(int value) const {
    for (size_t i = 0; i < m_size; ++i) {
        if (m_data[i] == value) return static_cast<int>(i);
    }
    return -1; 
}

/**
 * @brief Проверяет, пустой ли вектор.
 * @return true, если вектор пустой, иначе false.
 */
bool Vector::isEmpty() const {
    return m_size == 0;
}

/**
 * @brief Делает строку из вектора.
 * @return Строка вида "[число1, число2, ...]".
 */
std::string Vector::ToString() const {
    if (isEmpty()) return "[]";
    std::string result = "[";
    for (size_t i = 0; i < m_size; ++i) {
        result += std::to_string(m_data[i]);
        if (i < m_size - 1) result += ", ";
    }
    result += "]";
    return result;
}

/**
 * @brief Возвращает размер вектора.
 * @return Сколько чисел в векторе.
 */
size_t Vector::size() const {
    return m_size;
}

/**
 * @brief Оператор присваивания копированием.
 * Делает глубокую копию другого вектора.
 * @param other Вектор для копирования.
 * @return Ссылка на текущий вектор.
 */
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] m_data;
        m_size = other.m_size;
        m_data = new int[m_size];
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }
    return *this;
}

/**
 * @brief Оператор присваивания перемещением.
 * Забирает данные у другого вектора.
 * @param other Вектор, у которого забираем данные.
 * @return Ссылка на текущий вектор.
 */
Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] m_data;
        m_data = other.m_data;
        m_size = other.m_size;
        other.m_data = nullptr;
        other.m_size = 0;
    }
    return *this;
}

/**
 * @brief Оператор доступа по индексу (обычный).
 * @param index Позиция элемента.
 * @return Ссылка на элемент. Можно менять.
 * @throws std::out_of_range Если индекс неправильный.
 */
int& Vector::operator[](size_t index) {
    if (index >= m_size) throw std::out_of_range("Индекс за пределами вектора");
    return m_data[index];
}

/**
 * @brief Оператор доступа по индексу (константный).
 * @param index Позиция элемента.
 * @return Константная ссылка на элемент. Менять нельзя.
 * @throws std::out_of_range Если индекс неправильный.
 */
const int& Vector::operator[](size_t index) const {
    if (index >= m_size) throw std::out_of_range("Индекс за пределами вектора");
    return m_data[index];
}

/**
 * @brief Оператор добавления в конец.
 * @param value Число для добавления.
 * @return Ссылка на текущий вектор.
 */
Vector& Vector::operator<<(const int value) {
    insert(m_size, value); 
    return *this;
}

/**
 * @brief Оператор удаления последнего элемента.
 * @param value Сюда запишется удаленное число.
 * @return Ссылка на текущий вектор.
 * @throws std::out_of_range Если вектор пустой.
 */
Vector& Vector::operator>>(int& value) {
    if (isEmpty()) throw std::out_of_range("Вектор пуст");
    value = m_data[m_size - 1]; 
    remove(m_size - 1);
    return *this;
}
