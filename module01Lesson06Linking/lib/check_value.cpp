#include <iostream>

int check_value(const int target_value) {

	int current_value {0};
	int try_counter {0};

	std::cout << "Enter your guess:" << std::endl;

	// game's logic
	do {
		++try_counter;
		std::cin >> current_value;

		if (current_value < target_value) {
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value > target_value) {
			std::cout << "greater than " << current_value << std::endl;
		}
		else {
			std::cout << "you win!" << std::endl;
			break;
		}
	
	} while(true);

	return try_counter;
}