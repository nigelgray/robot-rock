![](https://cdn2.iconfinder.com/data/icons/daft-punk-helments/512/Off.png)

# Toy Robot Class

This class implements a toy robot game.

The user can enter commands to place, rotate and move a toy robot on a 5x5 board.

## Building

This has been tested with `clang 13` on macOS but should work with all modern compilers.

This project assumes you have the following installed:
- C/C++ compiler
- CMake
- Ninja

```
$ mkdir build
$ cd build
$ cmake -G Ninja ..
$ ninja
```

## Commands

`PLACE X,Y,F`

Place the robot on the board, where X = longitude, Y = latitude and F = the compass direction (NORTH, EAST, SOUTH, WEST).
A value of X = 0 and Y =0 will place the toy at the south-west most corner.

`MOVE`

Move the robot one space in the direction it is currently facing.

`LEFT`

Rotate the robot left 90 degrees.

`RIGHT`

Rotate the robot right 90 degrees.

`REPORT`

Will print out the current location of the robot, and the direction it is facing.


## Example output

## Test Results

```
$ ctest
Test project /Users/nigelgray/workspace/robot-rock/build
    Start 1: ToyRobotTest.BadUserInput
1/7 Test #1: ToyRobotTest.BadUserInput .............................   Passed    0.01 sec
    Start 2: ToyRobotTest.MovingBeforeBeingPlacedTriggersWarning
2/7 Test #2: ToyRobotTest.MovingBeforeBeingPlacedTriggersWarning ...   Passed    0.00 sec
    Start 3: ToyRobotTest.MoveLowerAndUpperCaseSupported
3/7 Test #3: ToyRobotTest.MoveLowerAndUpperCaseSupported ...........   Passed    0.00 sec
    Start 4: ToyRobotTest.Left
4/7 Test #4: ToyRobotTest.Left .....................................   Passed    0.00 sec
    Start 5: ToyRobotTest.LeftLeftLeft
5/7 Test #5: ToyRobotTest.LeftLeftLeft .............................   Passed    0.00 sec
    Start 6: ToyRobotTest.RightMove
6/7 Test #6: ToyRobotTest.RightMove ................................   Passed    0.00 sec
    Start 7: ToyRobotTest.MoveSixTimesTriggersOutOfBounds
7/7 Test #7: ToyRobotTest.MoveSixTimesTriggersOutOfBounds ..........   Passed    0.00 sec

100% tests passed, 0 tests failed out of 7

Total Test time (real) =   0.04 sec
```
