cmake_minimum_required(VERSION 3.16)

project(NetlistPlacementRoutingSimulator VERSION 1.0)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header files
include_directories(include)

# Create executable
add_executable(NetlistPlacementRoutingSimulator 
    src/main.cpp
    src/Graph.cpp
    src/Netlist.cpp
    src/Placement.cpp
    src/Routing.cpp
    src/Visualization.cpp
)

# Copy the input folder after building (optional)
file(COPY netlist.txt DESTINATION ${CMAKE_BINARY_DIR})
