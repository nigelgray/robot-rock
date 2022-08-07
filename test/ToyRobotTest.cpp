#include "ToyRobot.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::StartsWith;

TEST(ToyRobotTest, BadUserInput)
{
	ToyRobot toyRobot;

	EXPECT_EQ(toyRobot.process("garbage"), "Cannot parse command: garbage");
}

TEST(ToyRobotTest, MovingBeforeBeingPlacedTriggersWarning)
{
	ToyRobot toyRobot;

	EXPECT_EQ(toyRobot.process("move"), "You need to place Toy Robot first!");
}

TEST(ToyRobotTest, MoveLowerAndUpperCaseSupported)
{
	ToyRobot toyRobot;

	toyRobot.process("place");
	toyRobot.process("move");
	toyRobot.process("MOVE");
	toyRobot.process("mOvE");

	EXPECT_EQ(toyRobot.process("report"), "Output: 0,3,NORTH");
}

TEST(ToyRobotTest, Left)
{
	ToyRobot toyRobot;

	toyRobot.process("place");
	toyRobot.process("left");

	EXPECT_EQ(toyRobot.process("report"), "Output: 0,0,WEST");
}

TEST(ToyRobotTest, LeftLeftLeft)
{
	ToyRobot toyRobot;

	toyRobot.process("place");
	toyRobot.process("left");
	toyRobot.process("left");
	toyRobot.process("left");

	EXPECT_EQ(toyRobot.process("report"), "Output: 0,0,EAST");
}

TEST(ToyRobotTest, RightMove)
{
	ToyRobot toyRobot;

	toyRobot.process("place");
	toyRobot.process("right");
	toyRobot.process("move");

	EXPECT_EQ(toyRobot.process("report"), "Output: 1,0,EAST");
}

TEST(ToyRobotTest, MoveSixTimesTriggersOutOfBounds)
{
	ToyRobot toyRobot;

	toyRobot.process("place");
	for(auto iter = 1u; iter <= 5; iter++)
	{
		EXPECT_EQ(toyRobot.process("move"),"");
	}
	EXPECT_THAT(toyRobot.process("move"), StartsWith("Trying to move Toy Robot outside board area:"));

	EXPECT_EQ(toyRobot.process("report"), "Output: 0,5,NORTH");
}
