#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Maze size (3x3 in our case)
#define N 3

// Struct to store the coordinates of each step in the path
struct Step {
    int row, col;
};

// This will store the current path being followed (used for arrow output)
vector<Step> pathSteps;

// Function to check if all values in the maze are valid (between 0 and 5)
bool isValidMaze(int maze[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (maze[i][j] < 0 || maze[i][j] > 5) {
                return false; // Invalid cell value found
            }
        }
    }
    return true;
}

// This function prints the maze path using the weights of the longest path
void printWeightedPath(int maze[N][N], vector<vector<int>>& solution) {
    cout << "Path with weights:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (solution[i][j] == 1) {
                cout << maze[i][j] << " "; // Part of the final path
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// This function prints arrows to show the direction the rat takes
void printArrowPath() {
    cout << "Mouse Path (using arrows):\n";
    vector<vector<string>> arrows(N, vector<string>(N, "."));

    for (size_t i = 0; i < pathSteps.size(); i++) {
        int r = pathSteps[i].row;
        int c = pathSteps[i].col;

        // Mark start and end points
        if (i == 0) {
            arrows[r][c] = "S"; // Start
        } else if (i == pathSteps.size() - 1) {
            arrows[r][c] = "E"; // End
        } else {
            // Find direction between current and next step
            int nextR = pathSteps[i + 1].row;
            int nextC = pathSteps[i + 1].col;

            if (nextR > r) arrows[r][c] = "↓"; // Down
            else if (nextR < r) arrows[r][c] = "↑"; // Up
            else if (nextC > c) arrows[r][c] = "→"; // Right
            else if (nextC < c) arrows[r][c] = "←"; // Left

            // If jump was more than 1, add number
            int jump = max(abs(nextR - r), abs(nextC - c));
            if (jump > 1) {
                arrows[r][c] += to_string(jump);
            }
        }
    }

    // Print the final path with arrows
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << arrows[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Recursive function to explore all possible paths and track the one with max weight
bool findLongestPath(int maze[N][N], int i, int j, vector<vector<int>>& solution,
                     int& currentWeight, int& maxWeight, vector<vector<int>>& bestSolution,
                     vector<Step>& bestSteps) {
    
    // Check bounds, dead ends, and revisits
    if (i < 0 || i >= N || j < 0 || j >= N || maze[i][j] == 0 || solution[i][j] == 1) {
        return false;
    }

    // Mark the current cell and add its weight to the path
    solution[i][j] = 1;
    currentWeight += maze[i][j];
    pathSteps.push_back({i, j});

    bool pathFound = false;

    // Check if destination is reached
    if (i == N - 1 && j == N - 1) {
        if (currentWeight > maxWeight) {
            maxWeight = currentWeight;
            bestSolution = solution;   // Copy the current solution
            bestSteps = pathSteps;     // Store the path for arrow print
        }
        pathFound = true;
    } else {
        // Only jump up to the value in the current cell
        for (int step = 1; step <= maze[i][j]; step++) {
            // Try moving in 4 directions
            pathFound |= findLongestPath(maze, i, j + step, solution, currentWeight, maxWeight, bestSolution, bestSteps); // Right
            pathFound |= findLongestPath(maze, i + step, j, solution, currentWeight, maxWeight, bestSolution, bestSteps); // Down
            pathFound |= findLongestPath(maze, i, j - step, solution, currentWeight, maxWeight, bestSolution, bestSteps); // Left
            pathFound |= findLongestPath(maze, i - step, j, solution, currentWeight, maxWeight, bestSolution, bestSteps); // Up
        }
    }

    // Backtrack: unmark the cell and remove weight
    solution[i][j] = 0;
    currentWeight -= maze[i][j];
    pathSteps.pop_back();

    return pathFound;
}

// Main function that prepares everything and starts solving
void solveMaze(int maze[N][N]) {
    int maxWeight = 0;
    int currentWeight = 0;
    
    // Matrix to track visited cells during recursion
    vector<vector<int>> solution(N, vector<int>(N, 0));
    
    // Matrix to hold the best path found
    vector<vector<int>> bestSolution(N, vector<int>(N, 0));
    
    // Steps taken in the best path
    vector<Step> bestSteps;

    // Start only if the source is not blocked
    if (maze[0][0] != 0) {
        bool pathExists = findLongestPath(maze, 0, 0, solution, currentWeight, maxWeight, bestSolution, bestSteps);
        if (pathExists) {
            cout << "Longest path found!\n";
            cout << "Maximum Weight: " << maxWeight << "\n\n";
            printWeightedPath(maze, bestSolution);
            pathSteps = bestSteps; // Set pathSteps to the best one found
            printArrowPath();
        } else {
            cout << "No valid path exists from source to destination." << endl;
        }
    } else {
        cout << "Source is blocked. No path exists." << endl;
    }
}

// Main function where everything starts
int main() {
    // Sample 3x3 maze
    int maze[N][N] = {
        { 4, 2, 1 },
        { 0, 5, 0 },
        { 1, 3, 2 }
    };

    // Check if all values are in the valid range
    if (!isValidMaze(maze)) {
        cout << "Invalid maze: cell values must be in the range [1, 5]." << endl;
        return 1;
    }

    // Print the initial maze
    cout << "3x3 Maze:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nMaze Exploration With Cell-Based Jump Limits (1-5 Cells), No Revisiting\n";
    cout << "------------------------------------------------------------------------\n";

    // Start solving the maze
    solveMaze(maze);

    return 0;
}
