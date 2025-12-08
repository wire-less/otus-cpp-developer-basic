#include <iostream>
#include <format>

template <typename T>
class Vector
{
public:
	// Конструктор по-умолчанию /default constructor/
	Vector() : memoryBlock_(nullptr), size_{0} { std::cout << std::format("\n--- {} ---\n", __func__); }

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
		if (idx < size_)
			return memoryBlock_[idx];
		// else todo
	}

	// Перегрузка оператора /operator overloading/: получить доступ по индексу только для записи ( operator[] )
	T &operator[](size_t idx)
	{
		if (idx < size_)
			return memoryBlock_[idx];
		// else todo
	}

	// Метод класса /member function/: добавить элемент в конец контейнера ( pushBack )
	bool pushBack(const T &value)
	{
		std::cout << std::format("\n--- {} ---\n", __func__);

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
		std::cout << std::format("\n--- {} ---\n", __func__);

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
		std::cout << std::format("\n--- {} ---\n", __func__);

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
	std::cout << std::format("\n--- {} ---\n", __func__);

	size_t size = vec.getSize();
	std::cout << "\n"
			  << "Vector size: " << size << "\n";

	std::cout << "Vector elements: " << "\n";
	for (size_t i = 0; i < size; ++i)
		std::cout << vec[i] << ' ';
	std::cout << "\n";
}

// свободная функция: продемонстрировать возможности вектора
void testVector()
{
	std::cout << std::format("\n--- {} ---\n", __func__);

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
	std::cout << std::format("\n--- {} ---\n", __func__);

	testVector();
	return 0;
}