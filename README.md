
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



# Huffman Coding and Decoding in C++

This is a C++ implementation of the **Huffman Coding** algorithm for data compression. It includes both **encoding** and **recursive decoding** functionality.

## Features

- Constructs a Huffman Tree from a set of characters and their frequencies
- Generates Huffman codes for each character
- Encodes a given string using the generated codes
- Recursively decodes an encoded string back to the original message
- Efficient use of memory and bit-level operations

## Files

- `main.cpp`: Contains the complete implementation of Huffman encoding and decoding.

## Usage

### Example Character Set and Frequencies
```cpp
char arr[] = {'A', 'B', 'C', 'D', 'E'};
int freq[] = {5, 1, 6, 3, 2};
```

### Example Input Text
```cpp
"AABCADE"
```

### Output
```
Original character set and frequencies:
A: 5
B: 1
C: 6
D: 3
E: 2

Huffman Codes:
A: 01
B: 000
C: 11
D: 10
E: 001

Original text: AABCADE
Encoded text: 0101000001111001001
Decoded text: AABCADE
```

## How It Works

1. **Min Heap Construction**: A min-heap is used to efficiently extract the two least frequent characters.
2. **Huffman Tree Building**: Internal nodes are created by combining the two least frequent nodes repeatedly until the tree is complete.
3. **Encoding**: Traverse the tree to generate binary codes for each character.
4. **Decoding**: Use a recursive traversal of the tree based on the encoded binary string to recover the original text.

## Compilation and Execution

```sh
g++ main.cpp -o huffman
./huffman
```

## License

This project is open-source and free to use under the MIT License.

