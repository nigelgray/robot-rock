#include "ToyRobot.h"

#include <iostream>

int main()
{
	std::string input;
	std::cout << "Welcome to the Toy Robot Game!" << std::endl;

	ToyRobot toyRobot;

	while(true)
	{
		std::getline(std::cin, input);
		auto result = toyRobot.process(input);
		if(!result.empty())
		{
			std::cout << result << std::endl;;
		}
	}

	return EXIT_SUCCESS;
}
