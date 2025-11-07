#include <iostream>
#include <string>
#include "lib/check_value.hpp"
#include "lib/high_scores.hpp"
#include "lib/random_value.hpp"


int main(int argc, char** argv)
{
    // analyzing launch arguments
    int min_value = 1;      // defaulf const
    int max_value = 100;    // default
    
    if (argc > 1)
    {

    	std::string arg1_value{ argv[1] };
		if (arg1_value == "-max")
        {
			if (argc < 3)
            {
				std::cout << "Wrong usage! The argument '-max' requires some value!" << std::endl;
				return EXIT_FAILURE;
			}
			max_value = std::stoi(argv[2]);
			std::cout << "The '-max' value = " << max_value << std::endl;            
		}
	}

    // generating random from 1 to max_value
    int generated_value = random_value(min_value, max_value);
    
    // playing the game and counting number of attemts made by player
    std::string player_name;
    std::cout << "Hi! Enter your name, please:" << std::endl;
	std::cin >> player_name;
    int player_tries = check_value(generated_value);

    // saving results
    high_scores(player_name, player_tries);

    return EXIT_SUCCESS;
}
