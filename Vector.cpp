#include "pch.h"
#include "Vector.h"

Vector::Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

Vector::Vector(std::initializer_list<int> list) : m_size(list.size()), m_capacity(list.size()) {
    m_data = new int[m_capacity];
    size_t i = 0;
    for (int val : list) {
        m_data[i++] = val;
    }
}

// Конструктор копирования
Vector::Vector(const Vector& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
    m_data = new int[m_capacity];
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
}

// Конструктор перемещения
Vector::Vector(Vector&& other) noexcept : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) {
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

Vector::~Vector() {
    delete[] m_data;
}

void Vector::reallocate(size_t new_capacity) {
    int* new_data = new int[new_capacity];
    for (size_t i = 0; i < m_size; ++i) {
        new_data[i] = m_data[i];
    }
    delete[] m_data;
    m_data = new_data;
    m_capacity = new_capacity;
}

void Vector::insert(size_t index, int value) {
    if (index > m_size) {
        throw std::out_of_range("Индекс за пределами вектора");
    }
    if (m_size == m_capacity) {
        reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    // Сдвигаем элементы вправо, чтобы освободить место
    for (size_t i = m_size; i > index; --i) {
        m_data[i] = m_data[i - 1];
    }
    m_data[index] = value;
    ++m_size;
}

void Vector::remove(size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("Индекс за пределами вектора");
    }
    // Сдвигаем элементы влево, затирая удаляемый
    for (size_t i = index; i < m_size - 1; ++i) {
        m_data[i] = m_data[i + 1];
    }
    --m_size;
}

int Vector::find(int value) const {
    for (size_t i = 0; i < m_size; ++i) {
        if (m_data[i] == value) return static_cast<int>(i);
    }
    return -1; // Если не найден
}

bool Vector::isEmpty() const {
    return m_size == 0;
}

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

size_t Vector::size() const {
    return m_size;
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = new int[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] m_data;
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    return *this;
}

int& Vector::operator[](size_t index) {
    if (index >= m_size) throw std::out_of_range("Индекс за пределами вектора");
    return m_data[index];
}

const int& Vector::operator[](size_t index) const {
    if (index >= m_size) throw std::out_of_range("Индекс за пределами вектора");
    return m_data[index];
}

Vector& Vector::operator<<(int value) {
    insert(m_size, value); // Добавляем в конец
    return *this;
}

Vector& Vector::operator>>(int& value) {
    if (isEmpty()) throw std::out_of_range("Вектор пуст");
    value = m_data[m_size - 1]; // Забираем последний элемент
    remove(m_size - 1);
    return *this;
}