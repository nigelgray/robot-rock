![](https://cdn2.iconfinder.com/data/icons/daft-punk-helments/512/Off.png)

![](https://github.com/nigelgray/robot-rock/actions/workflows/cmake.yml/badge.svg)

# Toy Robot Class

This class implements a toy robot game.

The user can enter commands to place, rotate and move a toy robot on a 5x5 board.

| 0,4 | 1,4 | 2,4 | 3,4 | 4,4 |
| 0,3 | 1,3 | 2,3 | 3,3 | 4,3 |
| 0,2 | 1,2 | 2,2 | 3,2 | 4,2 |
| 0,1 | 1,1 | 2,1 | 3,1 | 4,1 |
| 0,0 | 1,0 | 2,0 | 3,0 | 4,0 |

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

```
$ ./RobotRock
Welcome to the Toy Robot Game!
place 4,4,south
move
move
left
report
Output: 4,2,EAST
```

## Test Results

```
$ ctest
Test project /Users/nigelgray/workspace/robot-rock/build
      Start  1: ToyRobotTest.BadUserInput
 1/16 Test  #1: ToyRobotTest.BadUserInput .......................   Passed    0.01 sec
      Start  2: ToyRobotTest.PlaceTooFewArguments
 2/16 Test  #2: ToyRobotTest.PlaceTooFewArguments ...............   Passed    0.00 sec
      Start  3: ToyRobotTest.PlaceTooManyArguments
 3/16 Test  #3: ToyRobotTest.PlaceTooManyArguments ..............   Passed    0.00 sec
      Start  4: ToyRobotTest.MovingBeforeBeingPlaced
 4/16 Test  #4: ToyRobotTest.MovingBeforeBeingPlaced ............   Passed    0.00 sec
      Start  5: ToyRobotTest.PlacingOutOfBoundsLongitude
 5/16 Test  #5: ToyRobotTest.PlacingOutOfBoundsLongitude ........   Passed    0.00 sec
      Start  6: ToyRobotTest.PlacingOutOfBoundsLatitude
 6/16 Test  #6: ToyRobotTest.PlacingOutOfBoundsLatitude .........   Passed    0.00 sec
      Start  7: ToyRobotTest.PlacingWithInvalidBearing
 7/16 Test  #7: ToyRobotTest.PlacingWithInvalidBearing ..........   Passed    0.00 sec
      Start  8: ToyRobotTest.PlacingInvalidLongitude
 8/16 Test  #8: ToyRobotTest.PlacingInvalidLongitude ............   Passed    0.00 sec
      Start  9: ToyRobotTest.PlacingNonIntegerLatitude
 9/16 Test  #9: ToyRobotTest.PlacingNonIntegerLatitude ..........   Passed    0.00 sec
      Start 10: ToyRobotTest.LowerAndUpperCaseSupported
10/16 Test #10: ToyRobotTest.LowerAndUpperCaseSupported .........   Passed    0.00 sec
      Start 11: ToyRobotTest.Left
11/16 Test #11: ToyRobotTest.Left ...............................   Passed    0.00 sec
      Start 12: ToyRobotTest.LeftLeftLeft
12/16 Test #12: ToyRobotTest.LeftLeftLeft .......................   Passed    0.00 sec
      Start 13: ToyRobotTest.RightMove
13/16 Test #13: ToyRobotTest.RightMove ..........................   Passed    0.00 sec
      Start 14: ToyRobotTest.MoveFiveTimesTriggersOutOfBounds
14/16 Test #14: ToyRobotTest.MoveFiveTimesTriggersOutOfBounds ...   Passed    0.01 sec
      Start 15: ToyRobotTest.SecondPlace
15/16 Test #15: ToyRobotTest.SecondPlace ........................   Passed    0.00 sec
      Start 16: ToyRobotTest.CanStillMoveAfterOutOfBounds
16/16 Test #16: ToyRobotTest.CanStillMoveAfterOutOfBounds .......   Passed    0.00 sec

100% tests passed, 0 tests failed out of 16

Total Test time (real) =   0.06 sec
```
