set(TEST_NAME ${PROJECT_NAME}Test)

add_executable(
  ${TEST_NAME}
    ../src/ToyRobot.cpp
    ToyRobotTest.cpp
)

target_link_libraries(
  ${TEST_NAME}
    GTest::gmock
    GTest::gtest_main
)

target_include_directories(${TEST_NAME} PUBLIC ../src)
target_compile_features(${TEST_NAME} PRIVATE cxx_std_17)
if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
  target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
