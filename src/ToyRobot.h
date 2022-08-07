#pragma once

#include <string>
#include <vector>

enum class Command;
enum class CompassBearing;
struct Location;

class ToyRobot {
public:
	explicit ToyRobot();
	~ToyRobot() {};

	std::string process(std::string input);

private:
	std::vector<std::string> split(std::string input);
	std::pair<Command, Location> parse(std::vector<std::string> tokenized);
	Command parseCommand(std::string input);
	uint8_t parseLatLong(std::string input);
	CompassBearing parseBearing(std::string input);
	std::string execute(Command command, Location location);
	void place(Location location);
	void move();
	std::string report();

	bool _placed;
	uint8_t _latitude;
	uint8_t _longitude;
	CompassBearing _compassBearing;
};
