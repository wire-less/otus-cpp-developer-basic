#include "myVector.hpp"

// свободная функция: продемонстрировать возможности вектора
void testVector()
{
	Vector<int> vector;
	// Показать размер и пустое содержимое контейнера
	printVector(vector);

	// Наполнить 10-ю элементами int
	for (int i = 0; i < 10; ++i)
	{
		vector.pushBack(i);
	}
	// Показать модифицированный размер и содержимое контейнера
	printVector(vector);

	// Удалить третий, пятый и седьмой элементы (последовательно, по индексу)
	vector.erase(2);
	vector.erase(4);
	vector.erase(6);
	printVector(vector);

	// Добавить элемент 10 в начало контейнера
	vector.insert(0, 10);
	printVector(vector);

	// Добавить элемент 20 в средину контейнера
	vector.insert(4, 20);
	printVector(vector);

	// Добавить элемент 30 в конец контейнера
	vector.insert(9, 30);
	printVector(vector);
}

int main()
{
	testVector();
	return 0;
}