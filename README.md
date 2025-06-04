
# 🧭 Weighted Maze Path Finder

This C++ program explores a **3x3 maze** with weighted cells, aiming to find the **longest path** (in terms of total weight) from the top-left corner to the bottom-right corner. It considers **jump limits based on cell values** and ensures **no revisits** to the same cell during path exploration.

---

## 📌 Features

- Validates maze values (must be between 0 and 5).
- Supports **variable-length jumps** based on current cell weight.
- Avoids revisiting any cell.
- Tracks and prints the **path with the maximum total weight**.
- Displays the **path in weighted form** and with **directional arrows** (`→`, `↓`, `←`, `↑`) for clarity.
- Marks the **Start (`S`)** and **End (`E`)** positions in the arrow path.

---

## 📐 Maze Rules

- The maze is represented as a 3x3 integer grid.
- Each cell’s value (1–5) indicates how far the mouse can "jump" in **any of the four directions**.
- `0` represents a **blocked** or **unreachable** cell.
- Movement is allowed in four directions: up, down, left, right.
- The path must not revisit any cell.

---

## 🔁 Example Maze

```cpp
int maze[3][3] = {
    { 4, 2, 1 },
    { 0, 5, 0 },
    { 1, 3, 2 }
};
```

---

## 📤 Output Example

```
3x3 Maze:
4 2 1
0 5 0
1 3 2

Maze Exploration With Cell-Based Jump Limits (1-5 Cells), No Revisiting
------------------------------------------------------------------------
Longest path found!
Maximum Weight: 14

Path with weights:
4 2 . 
. 5 . 
1 3 2 

Mouse Path (using arrows):
S →2 . 
. ↓ . 
. → E 
```

---

## 🧱 Code Structure

- `isValidMaze(...)`: Validates cell values.
- `findLongestPath(...)`: Core recursive backtracking function to find all valid paths.
- `printWeightedPath(...)`: Prints the final maze path with weights.
- `printArrowPath(...)`: Visualizes the path using directional arrows.
- `solveMaze(...)`: Controls the process, checks validity, and initiates solving.

---

## 🚀 How to Run

1. **Compile:**

   ```bash
   g++ -o maze_solver maze_solver.cpp
   ```

2. **Run:**

   ```bash
   ./maze_solver
   ```

> **Note:** This project uses the standard C++ library only, with no external dependencies.

---

## 🛠️ Future Improvements

- Support for **larger mazes** (e.g., 5x5 or 10x10).
- Allow user input for dynamic maze configuration.
- Add **graphical visualization** using a GUI library like SFML or SDL.
- Highlight **multiple optimal paths**, if available.

---

## 📄 License

This project is for academic and learning purposes. Feel free to modify or enhance it for your own maze-solving explorations.
