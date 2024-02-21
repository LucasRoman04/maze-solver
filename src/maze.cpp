//
// Created by Lucas on 2024-02-21.
//

#include "maze.h"

Cell::Cell(int row, int col, char hold): m_hold(hold) {}

char Cell::hold() const { return m_hold; }

Maze::Maze() {}


void Maze::clear() { m_maze.clear(); }

void Maze::setMazeVector(std::vector<std::vector<Cell>> maze)
{
    m_maze = maze;
}


std::ostream &operator<<(std::ostream &os, const Maze &maze)
{
    for (auto &row : maze.m_maze)
    {
        for (auto &cell : row)
        {
            os << cell.hold();
        }
        os << '\n';
    }
    return os;
}

void read_maze(std::istream &is, Maze &maze)
{
    maze.clear();
    std::string input;
    std::vector<std::vector<Cell>> maze_v;
    int row, col;
    row = 0;
    while (getline(is, input))
    {
        std::vector<Cell> row_v;
        for (col = 0; col < input.length(); ++col)
        {
            Cell cell(row, col, input[col]);
            row_v.push_back(cell);
        }
        maze_v.push_back(row_v);
        ++row;
    }
    maze.setMazeVector(maze_v);
}
