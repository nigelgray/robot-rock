#pragma once

#include <string>
#include <vector>

enum class Command;

enum class CompassBearing;

class ToyRobot {
public:
	explicit ToyRobot();
	~ToyRobot() {};

	std::string process(std::string input);

private:
	std::vector<std::string> split(std::string input);
	Command parse(std::string input);
	std::string execute(Command command);
	void move();
	std::string report();

	bool _placed;
	uint8_t _latitude;
	uint8_t _longitude;
	CompassBearing _compassBearing;
};
