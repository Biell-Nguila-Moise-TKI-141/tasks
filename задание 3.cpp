#pragma once
#include <initializer_list>
#include <string>
#include <stdexcept>

class Vector {
private:
    int* m_data;       // Указатель на динамический массив
    size_t m_size;     // Текущее количество элементов
    size_t m_capacity; // Выделенная память (вместимость)

    // Вспомогательный метод для расширения памяти
    void reallocate(size_t new_capacity);

public:
    // Конструкторы и деструктор
    Vector();
    Vector(std::initializer_list<int> list);
    Vector(const Vector& other);            // Конструктор копирования
    Vector(Vector&& other) noexcept;        // Конструктор перемещения
    ~Vector();

    // Основные методы (Вариант 1)
    void insert(size_t index, int value);   // Вставка элемента по индексу
    void remove(size_t index);              // Удаление элемента по индексу
    int find(int value) const;              // Поиск элемента (возвращает индекс или -1)
    
    bool isEmpty() const;                   // Проверка на пустоту
    std::string ToString() const;           // Вывод в строку
    size_t size() const;                    // Получение текущего размера

    // Переопределение операторов
    Vector& operator=(const Vector& other); // Оператор присваивания
    Vector& operator=(Vector&& other) noexcept; // Оператор перемещения
    
    int& operator[](size_t index);          // Разыменование по индексу
    const int& operator[](size_t index) const;

    // Операторы сдвига (без использования iostream!)
    // << добавляет элемент в конец, >> извлекает последний элемент
    Vector& operator<<(int value);          
    Vector& operator>>(int& value);         
};
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
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorTests
{
    TEST_CLASS(VectorTests)
    {
    public:
        
        TEST_METHOD(TestInitializerListAndToString)
        {
            Vector v = { 1, 2, 3 };
            Assert::IsFalse(v.isEmpty());
            Assert::AreEqual(std::string("[1, 2, 3]"), v.ToString());
            Assert::AreEqual((size_t)3, v.size());
        }

        TEST_METHOD(TestInsertAndRemove)
        {
            Vector v;
            v.insert(0, 10);
            v.insert(1, 30);
            v.insert(1, 20); // Вставляем между 10 и 30
            Assert::AreEqual(std::string("[10, 20, 30]"), v.ToString());

            v.remove(1); // Удаляем 20
            Assert::AreEqual(std::string("[10, 30]"), v.ToString());
        }

        TEST_METHOD(TestFindAndIndexOperator)
        {
            Vector v = { 5, 15, 25 };
            Assert::AreEqual(1, v.find(15));
            Assert::AreEqual(-1, v.find(99)); // Несуществующий элемент

            Assert::AreEqual(25, v[2]);
            v[2] = 100;
            Assert::AreEqual(100, v[2]);
        }

        TEST_METHOD(TestShiftOperators)
        {
            Vector v;
            v << 1 << 2 << 3; // Проверяем множественный сдвиг
            Assert::AreEqual(std::string("[1, 2, 3]"), v.ToString());

            int val;
            v >> val;
            Assert::AreEqual(3, val);
            Assert::AreEqual(std::string("[1, 2]"), v.ToString());
        }

        TEST_METHOD(TestCopyAndAssignment)
        {
            Vector v1 = { 1, 2 };
            Vector v2 = v1; // Конструктор копирования
            v1[0] = 9;

            Assert::AreEqual(std::string("[9, 2]"), v1.ToString());
            Assert::AreEqual(std::string("[1, 2]"), v2.ToString()); // v2 не должен измениться

            Vector v3;
            v3 = v1; // Оператор присваивания
            Assert::AreEqual(std::string("[9, 2]"), v3.ToString());
        }
    };
}
