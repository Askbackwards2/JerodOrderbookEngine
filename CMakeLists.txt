cmake_minimum_required(VERSION 3.16)

# Use GCC 14 for C++23 support
set(CMAKE_CXX_COMPILER g++-14)
set(CMAKE_C_COMPILER gcc-14)

project(LimitOrderBook VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags for debugging and warnings
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Create OrderBook static library
add_library(OrderBookLib STATIC
    ../src/OrderBook.cpp
)

# Set include directories for the library
target_include_directories(OrderBookLib PUBLIC 
    include/              # Headers in include directory
)

# Create the main executable (only contains main.cpp)
add_executable(LimitOrderBook
    main.cpp
)

# Link the OrderBook library to the main executable
target_link_libraries(LimitOrderBook PRIVATE OrderBookLib)

# Enable testing
enable_testing()

# Optional: Add test executable
add_executable(OrderBookTests
    ../test/OrderBookTest.cpp
)

# Set include directories for the library
target_include_directories(OrderBookTests PUBLIC 
    include/              # Headers in include directory
)

target_link_libraries(OrderBookTests PRIVATE OrderBookLib)
add_test(NAME OrderBookUnitTests COMMAND OrderBookTests)

# Print configuration info
message(STATUS "Building ${PROJECT_NAME} with C++${CMAKE_CXX_STANDARD}")
message(STATUS "Library: OrderBookLib (static)")
message(STATUS "Executable: LimitOrderBook")
