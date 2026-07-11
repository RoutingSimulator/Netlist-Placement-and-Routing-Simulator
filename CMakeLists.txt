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

set(NETLIST_OUTPUT ${CMAKE_BINARY_DIR}/netlist.txt)

add_custom_command(
    OUTPUT ${NETLIST_OUTPUT}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/netlist.txt
        ${NETLIST_OUTPUT}
    DEPENDS ${CMAKE_SOURCE_DIR}/netlist.txt
    COMMENT "Copying netlist.txt to build directory"
)

add_custom_target(copy_netlist ALL DEPENDS ${NETLIST_OUTPUT})
add_dependencies(NetlistPlacementRoutingSimulator copy_netlist)
