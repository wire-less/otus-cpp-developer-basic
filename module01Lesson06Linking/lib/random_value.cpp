#include <cstdlib>
#include <ctime>

int random_value(int min_value, int max_value)
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	
	// generating random using formula "A + rand() % ((B + 1) - A)"
	int random = (min_value + std::rand()) % ((max_value + 1) - min_value);

	return random;
}