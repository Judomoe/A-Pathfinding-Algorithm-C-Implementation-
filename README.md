# A* Pathfinding Algorithm 🗺️

A C++ implementation of the **A\* (A-Star) search algorithm** that finds the 
shortest path between two random points on a procedurally generated 9×9 grid maze.

---

## How It Works

### Grid Generation
- A 9×9 grid is randomly generated where each cell is either a **wall (`#`)** or 
  an **empty cell (`.`)**
- A random **start (`S`)** and **end (`E`)** point are chosen from empty cells

### Heuristic
Uses the **diagonal distance heuristic** to estimate cost:
h = (dx + dy) + (√2 - 2) × min(dx, dy)
This accounts for both straight and diagonal movement.

### Algorithm
- **8-directional movement** (horizontal, vertical, and diagonal)
- **Min-heap priority queue** on `f = g + h` for efficient node selection
- Tracks visited nodes via a closed list to avoid revisiting
- Diagonal moves cost `√2`, straight moves cost `1`

### Output
Once a path is found, the grid is printed with:
| Symbol | Meaning |
|--------|---------|
| `S` | Start point |
| `E` | End point |
| `*` | Path taken |
| `.` | Empty cell |
| `#` | Wall |

---

## Tech Stack
- C++20
- CMake 3.31
- Standard Library only (`<queue>`, `<vector>`, `<cmath>`)

## How to Build & Run
```bash
mkdir build && cd build
cmake ..
cmake --build .
./untitled4
```

## Example Output
(2,4) (7,1)
hoorrayyyyyy
2 4
3 3
...
# S # # # # #
# * # . . # #
. * * # . # .
. # . * . # # . .
. # . * # . .
# . # . * . # .
# # # . * # # .
. E * * * # .
# . # # # . . .

## Future Improvements
- Visualize the grid in real time (step-by-step animation)
- Allow user-defined start/end points and grid size
- Add support for weighted terrain costs
- Compare with Dijkstra's and BFS performance
