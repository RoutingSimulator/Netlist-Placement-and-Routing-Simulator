cmake_minimum_required(VERSION 3.16)

project(NetlistPlacementRoutingSimulator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(NetlistPlacementRoutingSimulator
    src/main.cpp
    src/models/Graph.cpp
    src/parser/NetlistParser.cpp
    src/analyzer/GraphAnalyzer.cpp
    src/placement/PlacementEngine.cpp
    src/routing/RoutingEngine.cpp
    src/visualization/SvgExporter.cpp
)

file(COPY netlist.txt DESTINATION ${CMAKE_BINARY_DIR})
