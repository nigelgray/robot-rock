#include "ToyRobot.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::StartsWith;

TEST(ToyRobotTest, BadUserInput)
{
	ToyRobot toyRobot;

	EXPECT_EQ(toyRobot.process("garbage"), "Cannot parse command: garbage");
}

TEST(ToyRobotTest, PlaceTooFewArguments)
{
	ToyRobot toyRobot;

	EXPECT_THAT(toyRobot.process("place"), StartsWith("Incorrect number of arguments:"));
}

TEST(ToyRobotTest, PlaceTooManyArguments)
{
	ToyRobot toyRobot;

	EXPECT_THAT(toyRobot.process("place 0,0,north,garbage"), StartsWith("Incorrect number of arguments:"));
}

TEST(ToyRobotTest, MovingBeforeBeingPlaced)
{
	ToyRobot toyRobot;

	EXPECT_EQ(toyRobot.process("move"), "You need to place Toy Robot first!");
}

TEST(ToyRobotTest, PlacingOutOfBoundsLongitude)
{
	ToyRobot toyRobot;

	EXPECT_THAT(toyRobot.process("place 5,0,north"), StartsWith("Longitude value out-of-bounds:"));
}

TEST(ToyRobotTest, PlacingOutOfBoundsLatitude)
{
	ToyRobot toyRobot;

	EXPECT_THAT(toyRobot.process("place 0,5,north"), StartsWith("Latitude value out-of-bounds:"));
}

TEST(ToyRobotTest, PlacingWithInvalidBearing)
{
	ToyRobot toyRobot;

	EXPECT_THAT(toyRobot.process("place 0,0,garbage"), StartsWith("Cannot parse compass bearing:"));
}

TEST(ToyRobotTest, PlacingInvalidLongitude)
{
	ToyRobot toyRobot;

	EXPECT_THAT(toyRobot.process("place -1000,0,north"), StartsWith("Lat/long value invalid:"));
}

TEST(ToyRobotTest, PlacingNonIntegerLatitude)
{
	ToyRobot toyRobot;

	EXPECT_THAT(toyRobot.process("place 0,garbage,north"), StartsWith("Lat/long value not a number:"));
}

TEST(ToyRobotTest, LowerAndUpperCaseSupported)
{
	ToyRobot toyRobot;

	EXPECT_EQ(toyRobot.process("place 0,0,north"), "");
	EXPECT_EQ(toyRobot.process("move"), "");
	EXPECT_EQ(toyRobot.process("MOVE"), "");
	EXPECT_EQ(toyRobot.process("mOvE"), "");

	EXPECT_EQ(toyRobot.process("report"), "Output: 0,3,NORTH");
}

TEST(ToyRobotTest, Left)
{
	ToyRobot toyRobot;

	EXPECT_EQ(toyRobot.process("place 0,0,north"), "");
	EXPECT_EQ(toyRobot.process("left"), "");

	EXPECT_EQ(toyRobot.process("report"), "Output: 0,0,WEST");
}

TEST(ToyRobotTest, LeftLeftLeft)
{
	ToyRobot toyRobot;

	EXPECT_EQ(toyRobot.process("place 0,0,north"), "");
	EXPECT_EQ(toyRobot.process("left"), "");
	EXPECT_EQ(toyRobot.process("left"), "");
	EXPECT_EQ(toyRobot.process("left"), "");

	EXPECT_EQ(toyRobot.process("report"), "Output: 0,0,EAST");
}

TEST(ToyRobotTest, RightMove)
{
	ToyRobot toyRobot;

	EXPECT_EQ(toyRobot.process("place 0,0,north"), "");
	EXPECT_EQ(toyRobot.process("right"), "");
	EXPECT_EQ(toyRobot.process("move"), "");

	EXPECT_EQ(toyRobot.process("report"), "Output: 1,0,EAST");
}

TEST(ToyRobotTest, MoveFiveTimesTriggersOutOfBounds)
{
	ToyRobot toyRobot;

	EXPECT_EQ(toyRobot.process("place 0,0,north"), "");
	for(auto iter = 1u; iter <= 4; iter++)
	{
		EXPECT_EQ(toyRobot.process("move"), "");
	}
	EXPECT_THAT(toyRobot.process("move"), StartsWith("Trying to move Toy Robot out-of-bounds:"));

	EXPECT_EQ(toyRobot.process("report"), "Output: 0,4,NORTH");
}

TEST(ToyRobotTest, SecondPlace)
{
	ToyRobot toyRobot;

	EXPECT_EQ(toyRobot.process("place 0,0,north"), "");
	EXPECT_EQ(toyRobot.process("report"), "Output: 0,0,NORTH");

	EXPECT_EQ(toyRobot.process("place 1,0,east"), "");
	EXPECT_EQ(toyRobot.process("report"), "Output: 1,0,EAST");
}

TEST(ToyRobotTest, CanStillMoveAfterOutOfBounds)
{
	ToyRobot toyRobot;

	EXPECT_EQ(toyRobot.process("place 0,0,west"), "");
	EXPECT_THAT(toyRobot.process("move"), StartsWith("Trying to move Toy Robot out-of-bounds:"));

	EXPECT_EQ(toyRobot.process("right"), "");
	EXPECT_EQ(toyRobot.process("move"), "");
	EXPECT_EQ(toyRobot.process("report"), "Output: 0,1,NORTH");
}
