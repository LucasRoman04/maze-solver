//
// Created by Lucas on 2024-02-21.
//

#ifndef ASSIGNMENT_2_MAZE_H
#define ASSIGNMENT_2_MAZE_H

#include <iostream>
#include <vector>
#include <string>

class Cell
{
public:
    Cell(int row, int col, char hold);

    char hold() const;

private:
    char m_hold;
};

class Maze
{
public:
    Maze();

    void clear();
    void setMazeVector(std::vector<std::vector<Cell>> maze);

    friend std::ostream &operator<<(std::ostream &os, const Maze &maze);

private:
    std::vector<std::vector<Cell>> m_maze;
};

void read_maze(std::istream &is, Maze &maze);


#endif //ASSIGNMENT_2_MAZE_H
