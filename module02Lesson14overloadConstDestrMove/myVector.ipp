#pragma once
#include <iostream>

template <typename T>
class Vector
{
public:
    // Конструктор по-умолчанию /default constructor/
    Vector() : memoryBlock_(nullptr), size_{0} {}

    // Конструктор копирования /copy constructor/
    Vector(const Vector &other) = delete;

    // Копирующий оператор присваивания /copy assignment operator/
    Vector &operator=(const Vector &other) = delete;

    // Деструктор /destructor/
    ~Vector() { delete[] memoryBlock_; }

    // Метод класса /member function/: получить текущий размер контейнера ( getSize )
    size_t getSize() const
    {
        return size_;
    }

    // Перегрузка оператора /operator overloading/: получить доступ по индексу только для чтения ( operator[] )
    const T &operator[](size_t idx) const
    {
        return memoryBlock_[idx];
    }

    // Перегрузка оператора /operator overloading/: получить доступ по индексу только для записи ( operator[] )
    T &operator[](size_t idx)
    {
        return memoryBlock_[idx];
    }

    // Метод класса /member function/: добавить элемент в конец контейнера ( pushBack )
    bool pushBack(const T &value)
    {
        T *newMemoryBlock = new T[size_ + 1];
        for (size_t i = 0; i < size_; ++i)
        {
            newMemoryBlock[i] = memoryBlock_[i];
        }
        newMemoryBlock[size_] = value;
        delete[] memoryBlock_;
        memoryBlock_ = newMemoryBlock;
        ++size_;
        return true;
    }

    // Метод класса: вставить элемент в заданной позиции в контейнер ( insert )
    bool insert(const size_t idx, const T &value)
    {
        if (idx > size_)
            return false;

        T *newMemoryBlock = new T[size_ + 1];

        // Скопировать элементы до позиции idx
        for (size_t i = 0; i < idx; ++i)
            newMemoryBlock[i] = memoryBlock_[i];

        // Собственно вставка
        newMemoryBlock[idx] = value;

        // Скопировать элементы после позиции idx
        for (size_t i = idx; i < size_; ++i)
            newMemoryBlock[i + 1] = memoryBlock_[i];

        // Перезаписать старый массив
        delete[] memoryBlock_;
        memoryBlock_ = newMemoryBlock;
        ++size_;

        return true;
    }

    // Метод класса: удалить элемент в заданной позиции из контейнера ( erase )
    bool erase(const size_t idx)
    {
        if (idx < size_)
        {
            size_t i = idx;
            while (i < (size_ - 1))
            {
                memoryBlock_[i] = memoryBlock_[i + 1];
                ++i;
            }
            --size_; // для последнего элемента контейнера будет выполнено только уменьшение размера

            T *newMemoryBlock = new T[size_];
            for (size_t i = 0; i < size_; ++i)
            {
                newMemoryBlock[i] = memoryBlock_[i];
            }
            delete[] memoryBlock_;
            memoryBlock_ = newMemoryBlock;
            return true;
        }
        else
            return false;
    }

private:
    T *memoryBlock_;
    size_t size_;
};

// свободная шаблонная функция: вывести размер и элементы вектора
template <typename T>
void printVector(const Vector<T> &vec)
{
    size_t size = vec.getSize();
    std::cout << "\n"
              << "Vector size: " << size << "\n";

    std::cout << "Vector elements: " << "\n";
    for (size_t i = 0; i < size; ++i)
        std::cout << vec[i] << ' ';
    std::cout << "\n";
}