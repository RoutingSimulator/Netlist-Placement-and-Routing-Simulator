include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(NETLIST_SIMULATOR_SOURCES
    ${CMAKE_SOURCE_DIR}/src/models/Graph.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/NetlistParser.cpp
    ${CMAKE_SOURCE_DIR}/src/analyzer/GraphAnalyzer.cpp
    ${CMAKE_SOURCE_DIR}/src/placement/PlacementEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/routing/RoutingEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/visualization/SvgExporter.cpp
)

add_executable(netlist_simulator_tests
    test_graph.cpp
    test_netlist_parser.cpp
    test_graph_analyzer.cpp
    test_placement_engine.cpp
    test_routing_engine.cpp
    ${NETLIST_SIMULATOR_SOURCES}
)

target_include_directories(netlist_simulator_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(netlist_simulator_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(netlist_simulator_tests)
