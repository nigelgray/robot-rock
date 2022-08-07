#include "ToyRobot.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

using namespace std::string_view_literals;

enum class Command {
	Place,
	Move,
	Left,
	Right,
	Report
};

enum class CompassBearing {
	North,
	East,
	South,
	West
};

struct Location {
	uint8_t latitude{0u};
	uint8_t longitude{0u};
	CompassBearing compassBearing{CompassBearing::North};
};

// This unordered_map is used to convert the user input into the command to execute
static const std::unordered_map<Command, std::string_view> commandDescriptions = {
	{Command::Place,         "PLACE"sv},
	{Command::Move,          "MOVE"sv},
	{Command::Left,          "LEFT"sv},
	{Command::Right,         "RIGHT"sv},
	{Command::Report,        "REPORT"sv}
};

// This unordered map is used for decoding the compass bearing input from the user
// and also to convert back to a string for reporting the robot bearing to the user
static const std::unordered_map<CompassBearing, std::string_view> compassDescriptions = {
	{CompassBearing::North,  "NORTH"sv},
	{CompassBearing::East,   "EAST"sv},
	{CompassBearing::South,  "SOUTH"sv},
	{CompassBearing::West,   "WEST"sv}
};

// Overload the '++' and '--' operators to make it easier to turn the robot left/right
CompassBearing& operator++(CompassBearing& c)
{
	return c = (c == CompassBearing::West) ? CompassBearing::North : static_cast<CompassBearing>(static_cast<int>(c)+1);
}

CompassBearing& operator--(CompassBearing& c)
{
	return c = (c == CompassBearing::North) ? CompassBearing::West : static_cast<CompassBearing>(static_cast<int>(c)-1);
}

// Latitude is the north-south direction
// South-most is MIN_LATITUDE, north-most is MAX_LATITUDE
static const uint8_t MAX_LATITUDE = 5;
static const uint8_t MIN_LATITUDE = 0;

// Longitude is the west-east direction
// West-most is MIN_LONGITUDE, east-most is MAX_LONGITUDE
static const uint8_t MAX_LONGITUDE = 5;
static const uint8_t MIN_LONGITUDE = 0;

// Initialise the robot location with valid values, but with _placed
// initialised to false to block any commands until a valid 'PLACE'
// command has been received
ToyRobot::ToyRobot() :
	_placed(false),
	_latitude(0),
	_longitude(0),
	_compassBearing{CompassBearing::North}
{
}

std::string ToyRobot::process(std::string input)
{
	// Ignore empty input (i.e. carriage returns)
	if(input.empty())
	{
		return {};
	}

	try
	{
		auto tokenized = split(input);
		auto [command, location] = parse(tokenized);
		return execute(command, location);
	}
	catch(std::invalid_argument const& iaex)
	{
		return std::string(iaex.what()) + ": " + input;
	}
	catch(std::out_of_range const& orex)
	{
		return std::string(orex.what()) + ": " + report();
	}
	catch(std::runtime_error const& rtex)
	{
		return std::string(rtex.what());
	}
}

// Split the command string into separate parts
// The first part will be the command to execute, while the 'PLACE'
// command input will also have parameters for the x,y,f settings
std::vector<std::string> ToyRobot::split(std::string input)
{
	// Sanitize the user input so that it is all upper-case
	std::transform(input.begin(), input.end(), input.begin(),
	               [](unsigned char c) -> unsigned char {
		return std::toupper(c);
	});

	// Split the input string by spaces and commas
	const std::regex re(R"([\s|,]+)");
	std::sregex_token_iterator it{ input.begin(), input.end(), re, -1 };
	std::vector<std::string> tokenized{ it, {} };

	// Trim any whitespace from the beginning of the string
	if(tokenized[0] == "" && tokenized.size() > 1)
	{
		tokenized.erase(tokenized.begin());
	}

	// Check there are either 1 or 4 arguments. `PLACE` should have 4, the
	// others should all be 1.
	if(tokenized.size() != 1 && tokenized.size() != 4)
	{
		throw std::invalid_argument("Incorrect number of arguments");
	}

	return tokenized;
}

std::pair<Command, Location> ToyRobot::parse(std::vector<std::string> tokenized)
{
	Location location;

	auto command = parseCommand(tokenized[0]);
	if(command == Command::Place)
	{
		if(tokenized.size() != 4)
		{
			throw std::invalid_argument("Incorrect number of arguments");
		}
		location.longitude = parseLatLong(tokenized[1]);
		location.latitude = parseLatLong(tokenized[2]);
		location.compassBearing = parseBearing(tokenized[3]);
	}

	return {command, location};
}

Command ToyRobot::parseCommand(std::string input)
{
	// Iterate over the unordered map to find the matching value and
	// use that to convert to the Command enum
	for(auto& [command, description] : commandDescriptions)
	{
		if(input.compare(description) == 0)
		{
			return command;
		}
	}

	// If we are unable to match the command, throw an error
	throw std::invalid_argument("Cannot parse command");
}

uint8_t ToyRobot::parseLatLong(std::string input)
{
	int result;
	try
	{
		result = std::stoi(input);
	}
	catch(std::invalid_argument const& iaex)
	{
		// Recast into a more user friendly error message
		throw std::invalid_argument("Lat/long value not a number");
	}

	// Check the value is within the uint8_t limits before casting
	if((result <  std::numeric_limits<uint8_t>::min()) || (result > std::numeric_limits<uint8_t>::max()))
	{
		throw std::invalid_argument("Lat/long value invalid");
	}

	return static_cast<uint8_t>(result);
}

CompassBearing ToyRobot::parseBearing(std::string input)
{
	// Iterate over the unordered map to find the matching value and
	// use that to convert to the CompassBearing enum
	for(auto& [bearing, description] : compassDescriptions)
	{
		if(input.compare(description) == 0)
		{
			return bearing;
		}
	}

	// If we are unable to match the compass bearing, throw an error
	throw std::invalid_argument("Cannot parse compass bearing");
}

std::string ToyRobot::execute(Command command, Location location)
{
	if(!_placed && (command != Command::Place))
	{
		throw std::runtime_error("You need to place Toy Robot first!");
	}

	switch(command)
	{
	case Command::Place:
		place(location);
		break;

	case Command::Move:
		move();
		break;

	case Command::Left:
		--_compassBearing;
		break;

	case Command::Right:
		++_compassBearing;
		break;

	case Command::Report:
		return "Output: " + report();
		break;

	default:
		break;
	}

	return {};
}

void ToyRobot::place(Location location)
{
	if((location.longitude < MIN_LONGITUDE) || (location.longitude > MAX_LONGITUDE))
	{
		throw std::invalid_argument("Longitude value out-of-bounds");
	}
	_longitude = location.longitude;

	if((location.latitude < MIN_LATITUDE) || (location.latitude > MAX_LATITUDE))
	{
		throw std::invalid_argument("Latitude value out-of-bounds");
	}
	_latitude = location.latitude;

	_compassBearing = location.compassBearing;

	_placed = true;
}

void ToyRobot::move()
{
	switch(_compassBearing)
	{
	case CompassBearing::North:
		if(_latitude < MAX_LATITUDE)
		{
			_latitude++;
			return;
		}
		break;
	case CompassBearing::East:
		if(_longitude < MAX_LONGITUDE)
		{
			_longitude++;
			return;
		}
		break;
	case CompassBearing::South:
		if(_latitude != MIN_LATITUDE)
		{
			_latitude--;
			return;
		}
		break;
	case CompassBearing::West:
		if(_longitude != MIN_LONGITUDE)
		{
			_longitude--;
			return;
		}
		break;
	}

	throw std::out_of_range("Trying to move Toy Robot out-of-bounds");
}

std::string ToyRobot::report()
{
	std::string compass;
	auto result = compassDescriptions.find(_compassBearing);
	if(result != compassDescriptions.end()) {
		compass = std::string(result->second);
	}

	std::ostringstream ss;
	ss << +_longitude << ","
	   << +_latitude << ","
	   << compass;

	return ss.str();
}
