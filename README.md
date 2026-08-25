# Netlist Placement and Routing Simulator

A C++17 application that reads a digital netlist, builds a directed graph representation, analyzes connectivity, assigns component positions on a grid, routes interconnections with A* pathfinding, and exports the result as an SVG diagram.

## Overview

This simulator implements a simplified electronic design automation (EDA) workflow: parse a netlist, reason about the underlying graph structure, place nodes in 2D space, compute obstacle-aware Manhattan routes between connected components, and visualize the layout. It is intended as a modular foundation for exploring placement and routing algorithms on small netlists.

## Features

- **Netlist parsing** — reads edge pairs line-by-line from a text file with comment and syntax validation
- **Graph analysis** — BFS/DFS traversal and level assignment from a start node
- **Component placement** — layer-based grid placement using a BFS spanning tree (handles disconnected components)
- **Connection routing** — A* pathfinding on a grid with Manhattan heuristic and obstacle avoidance
- **SVG export** — generates a scalable vector graphic and opens it automatically on Linux

## Pipeline

```
netlist.txt
    │
    ▼
NetlistParser  →  Graph
                      │
                      ├──► GraphAnalyzer  (BFS / DFS / levels)
                      │
                      ▼
               PlacementEngine  (grid placement + spanning tree)
                      │
                      ▼
               RoutingEngine  (A* routing with obstacle avoidance)
                      │
                      ▼
               SvgExporter  →  output.svg
```

## Project Structure

```
Team1Simulator/
├── CMakeLists.txt
├── netlist.txt                 # Sample input netlist
├── include/
│   ├── analyzer/               # Graph traversal and analysis
│   ├── models/                 # Core data types (Graph, Edge, Route, …)
│   ├── parser/                 # Netlist file parser
│   ├── placement/              # Component placement engine
│   ├── routing/                # Wire routing engine
│   └── visualization/          # SVG export
└── src/                        # Implementation files
```

## Requirements

- **CMake** 3.16 or later
- A C++17-compatible compiler (GCC, Clang, or MSVC)
- **Linux (optional):** `xdg-open` for automatic SVG preview after export

## Build

From the project root:

```bash
mkdir -p build
cd build
cmake ..
cmake --build ..
```

The build system automatically copies `netlist.txt` into the build directory at compile time, so edits to the source file are picked up on the next build without re-running CMake.

## Usage

Run the executable from the build directory:

```bash
cd build
./NetlistPlacementRoutingSimulator
```

The program will:

1. Parse `netlist.txt`
2. Print the adjacency list to the console
3. Run graph analysis (BFS order, DFS order, BFS levels)
4. Place components on a grid
5. Compute A* routes for each netlist edge
6. Print placement and routing details
7. Write `output.svg` in the current directory and open it with the default viewer (Linux)

## Input Format

The netlist is a plain text file where each non-comment line defines a directed connection between two single-character component identifiers:

```
<source> <destination>
```

Example (`netlist.txt`):

```
A B
A C
B D
C D
D E
A F
A D
```

### Parser rules

| Rule | Behavior |
|------|----------|
| Blank lines | Ignored |
| Comments | Lines starting with `#` or `//` are ignored |
| Node names | Must be exactly one character |
| Missing destination | Warning printed; line skipped |
| Extra tokens | Warning printed; edge still added if source and destination are valid |
| Self-loops (`A A`) | Warning printed; edge skipped |

## Output

| Output | Description |
|--------|-------------|
| Console | Adjacency list, BFS/DFS traversal orders, BFS levels, node coordinates, and route waypoints |
| `output.svg` | Visual diagram with nodes (circles + labels) and routed connections (line segments); opened automatically on Linux via `xdg-open` |

## Components

| Module | Responsibility |
|--------|-------------|
| `Graph` | Directed adjacency-list representation; node/edge queries |
| `NetlistParser` | Reads a netlist file and populates a `Graph` with validation |
| `GraphAnalyzer` | BFS/DFS traversal and level computation from a start node |
| `PlacementEngine` | Assigns `(x, y)` grid coordinates via BFS layering and spanning-tree construction |
| `RoutingEngine` | Produces obstacle-aware routes using A* with Manhattan distance heuristic |
| `SvgExporter` | Renders placement and routing results to SVG |

## Design Notes

- Internal state in `Graph`, `PlacementEngine`, and `RoutingEngine` is encapsulated behind private members with const getter methods.
- Read-only consumers (`GraphAnalyzer`, `RoutingEngine`, `SvgExporter`) take `const Graph &` references to enforce const-correctness.
- Placement uses a fixed grid unit spacing (`gridUnit = 2`) and assigns nodes to horizontal layers based on BFS depth from a root node; disconnected components are placed in separate layer ranges.
- Routing treats other placed components as obstacles, tracks used waypoint cells to reduce overlap, and falls back to a direct segment when no path is found.
- Route paths are simplified to corner waypoints before export.

