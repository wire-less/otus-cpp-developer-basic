#pragma once
#include <iostream>

template <typename T>
class List
{
private:
    struct Node // структура с узлом списка
    {
        Node *next;
        Node *prev;
        T data;

        // Параметризированный конструктор структуры Node
        Node(const T &val) : prev(nullptr), next(nullptr), data(val) {}
    };

    Node *first_; // указатель на первый элемент
    Node *last_;  // указатель на последний элемент
    size_t size_; // количество элементов

public:
    // Конструктор класса List по умолчанию
    List() : first_(nullptr), last_(nullptr), size_(0) {}

    // Деструктор класса List
    ~List()
    {
        clear();
    }

    // Конструктор копирования класса List
    List(const List &other) : first_(nullptr), last_(nullptr), size_(0)
    {
        Node *current = other.first_;
        while (current)
        {
            pushBack(current->data);
            current = current->next;
        }
    }

    // Оператор присваивания класса List
    List &operator=(const List &other)
    {
        if (this != &other)
        {
            clear();
            Node *current = other.first_;
            while (current)
            {
                pushBack(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Метод очистить список
    void clear()
    {
        Node *current = first_;
        while (current)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
        first_ = last_ = nullptr;
        size_ = 0;
    }

    // Метод добавить элемент в конец
    void pushBack(const T &value)
    {
        Node *newNode = new Node(value);

        if (last_)
        {
            // Если список не пустой
            last_->next = newNode;
            newNode->prev = last_;
            last_ = newNode;
        }
        else
        {
            // Если список пустой
            first_ = last_ = newNode;
        }

        ++size_;
    }

    // Метод добавить элемент в начало
    void pushFront(const T &value)
    {
        Node *newNode = new Node(value);

        if (first_)
        {
            // Если список не пустой
            newNode->next = first_;
            first_->prev = newNode;
            first_ = newNode;
        }
        else
        {
            // Если список пустой
            first_ = last_ = newNode;
        }

        ++size_;
    }

    // Метод вставить элемент по индексу
    bool insert(size_t index, const T &value)
    {
        if (index > size_)
        {
            return false; // Неверный индекс
        }

        if (index == 0)
        {
            pushFront(value);
            return true;
        }

        if (index == size_)
        {
            pushBack(value);
            return true;
        }

        // Найти узел для вставки перед ним
        Node *current = getNode(index);
        if (!current)
            return false;

        Node *newNode = new Node(value);

        // Вставить перед current
        newNode->prev = current->prev;
        newNode->next = current;

        if (current->prev)
        {
            current->prev->next = newNode;
        }
        current->prev = newNode;

        ++size_;
        return true;
    }

    // Метод удалить элемент по индексу
    bool erase(size_t index)
    {
        if (index >= size_)
        {
            return false; // Неверный индекс
        }

        Node *node2Detete = getNode(index);
        if (!node2Detete)
            return false;

        // Перестроить связи
        if (node2Detete->prev)
        {
            node2Detete->prev->next = node2Detete->next;
        }
        else
        {
            // Удалить первый элемент
            first_ = node2Detete->next;
        }

        if (node2Detete->next)
        {
            node2Detete->next->prev = node2Detete->prev;
        }
        else
        {
            // Удалить последний элемент
            last_ = node2Detete->prev;
        }

        delete node2Detete;
        --size_;
        return true;
    }

    // Метод получить текущий размер
    size_t getSize() const { return size_; }

    // Метод проверить на пустой размер
    bool empty() const { return size_ == 0; }

    // Оператор доступа по индексу (неконстантная версия)
    T &operator[](size_t index)
    {
        Node *node = getNode(index);
        return node->data;
    }

    // Оператор доступа по индексу (константная версия)
    const T &operator[](size_t index) const
    {
        Node *node = getNode(index);
        return node->data;
    }

private:
    // Вспомогательный метод получить узел по индексу
    Node *getNode(size_t index) const
    {
        if (index >= size_)
            return nullptr;

        // Оптимизация: выбрать направление обхода
        if (index < size_ / 2)
        {
            // Обход с начала
            Node *current = first_;
            for (size_t i = 0; i < index; ++i)
            {
                current = current->next;
            }
            return current;
        }
        else
        {
            // Обход с конца
            Node *current = last_;
            for (size_t i = size_ - 1; i > index; --i)
            {
                current = current->prev;
            }
            return current;
        }
    }
};

// Свободная шаблонная функция: вывести размер и элементы списка
template <typename T>
void printList(const List<T> &list)
{
    size_t size = list.getSize();
    std::cout << "\n"
              << "List size: " << size << "\n";

    std::cout << "List elements: " << "\n";
    for (size_t i = 0; i < size; ++i)
        std::cout << list[i] << ' ';
    std::cout << "\n";
}