#include "myList.hpp"

// свободная функция: продемонстрировать возможности списка
void testList()
{
    List<int> list;
    // Показать размер и пустое содержимое контейнера
    printList(list);

    // Наполнить 10-ю элементами int
    for (int i = 0; i < 10; ++i)
    {
        list.pushBack(i);
    }
    // Показать модифицированный размер и содержимое контейнера
    printList(list);

    // Удалить третий, пятый и седьмой элементы (последовательно, по индексу)
    list.erase(2);
    list.erase(4);
    list.erase(6);
    printList(list);

    // Добавить элемент 10 в начало контейнера
    list.pushFront(10);
    printList(list);

    // Добавить элемент 20 в средину контейнера
    list.insert(4, 20);
    printList(list);

    // Добавить элемент 30 в конец контейнера
    list.pushBack(30);
    printList(list);
}

int main()
{
    testList();
    return 0;
}