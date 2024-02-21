//
// Created by Lucas on 2024-02-21.
//

#ifndef ASSIGNMENT_2_MAZE_H
#define ASSIGNMENT_2_MAZE_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

class Cell {
public:
    Cell(int row, int col, char hold)
            : m_row(row), m_col(col), m_hold(hold), m_visited(false) {}

    char hold() const { return m_hold; }
    void set_hold(char hold) { m_hold = hold; }
    bool visited() const { return m_visited; }
    void set_visited(bool visited = true) { m_visited = visited; }

private:
    char m_hold; // Content of cell
    int m_row;
    int m_col;
    bool m_visited;
};

class Maze {
public:
    Maze() {}
    Cell& cell(int row, int col);
    void clear();
    void set_maze_vector(vector<vector<Cell>> maze);
    const size_t row_size() const;
    const size_t col_size() const;

    friend ostream& operator<<(ostream& os, const Maze& maze);

private:
    vector<vector<Cell>> m_maze;
    size_t m_rowSize;
    size_t m_colSize;
};

void read_maze(istream& is, Maze& maze);
bool solve_maze(Maze& maze, int row, int col, stack<pair<int, int>>& solution_path);
void mark_solution_path(Maze& maze, stack<pair<int, int>>& solution_path);
void clean_maze(Maze& maze);
void save_maze_to_file(Maze& maze, int count);

#endif //ASSIGNMENT_2_MAZE_H
