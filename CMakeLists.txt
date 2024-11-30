# Minimum CMake version required
cmake_minimum_required(VERSION 3.30)

# Project name
project(ADS_2024_CA2_Alexandru_Radu)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(BinaryTree)

# Add the main application executable
add_executable(ADS_2024_CA2_Alexandru_Radu
        main.cpp
        BinaryTree/BinaryTree.h
        BinaryTree/BSTNode.h
        BinaryTree/TreeMap.h
)

# Add Google Test subdirectory (ensure googletest is in your project folder)
add_subdirectory(googletest)

# Enable testing
enable_testing()

# Add the test executable
add_executable(tests
        test.cpp
)

# Link the test executable with Google Test libraries
target_link_libraries(tests gtest gtest_main)

# Register tests
add_test(NAME sample_test COMMAND tests)