cmake_minimum_required(VERSION 3.14)

project(RobotRock CXX)

# Setup GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/ToyRobot.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)

enable_testing()

set(TEST_NAME ${PROJECT_NAME}Test)

add_executable(
  ${TEST_NAME}
    src/ToyRobot.cpp
    test/ToyRobotTest.cpp
)

target_link_libraries(
  ${TEST_NAME}
    GTest::gmock
    GTest::gtest_main
)

target_include_directories(${TEST_NAME} PUBLIC src)
target_compile_features(${TEST_NAME} PRIVATE cxx_std_17)
target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})