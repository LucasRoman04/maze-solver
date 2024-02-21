#include <iostream>
#include <fstream>
#include "maze.h"

int main()
{
    std::ifstream ifs("tests/test.txt");

    Maze maze;
    read_maze(ifs, maze);
    std::cout << maze;

    return 0;
}
