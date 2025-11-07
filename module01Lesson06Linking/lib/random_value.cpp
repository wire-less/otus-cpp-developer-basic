#include <cstdlib>
#include <ctime>

int random_value(int min_value, int max_value)
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	
	// generating random, using formula "A + (rand() % (B - A + 1))"
	int random = min_value + (std::rand() % (max_value - min_value + 1));

	return random;
}