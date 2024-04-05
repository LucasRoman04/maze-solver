#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "maze.h"

using namespace std;

int main()
{
    string maze_filename = "tests/test.txt";

    ifstream ifs(maze_filename);

    Maze maze;
    read_maze(ifs, maze);
    cout << "Original maze:" << endl;
    cout << maze;

    stack<pair<int, int>> solution_path;
    if (solve_maze(maze, 1, 0, solution_path)) {
        cout << "Maze solved!" << endl;
    } else {
        cout << "Maze could not be solved!" << endl;
    }

    cout << "Solved maze:" << endl;
    cout << maze;

    return 0;
}
