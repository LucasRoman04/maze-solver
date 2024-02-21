//
// Created by Lucas on 2024-02-21.
//

#include "maze.h"
#include <fstream>

Cell& Maze::cell(int row, int col) {
    return m_maze[row][col];
}

void Maze::clear() {
    m_maze.clear();
}

void Maze::set_maze_vector(vector<vector<Cell>> maze) {
    m_maze = maze;
    m_rowSize = maze.size();
    m_colSize = maze[0].size();
}

const size_t Maze::row_size() const {
    return m_rowSize;
}

const size_t Maze::col_size() const {
    return m_colSize;
}

ostream& operator<<(ostream& os, const Maze& maze) {
    for (auto& row : maze.m_maze) {
        for (auto& cell : row) {
            os << cell.hold();
        }
        os << '\n';
    }
    return os;
}

void read_maze(istream& is, Maze& maze) {
    maze.clear();
    string input;
    vector<vector<Cell>> maze_v;
    int row = 0;
    while (getline(is, input)) {
        vector<Cell> row_v;
        for (int col = 0; col < input.length(); ++col) {
            Cell cell(row, col, input[col]);
            row_v.push_back(cell);
        }
        maze_v.push_back(row_v);
        ++row;
    }
    maze.set_maze_vector(maze_v);
}

void mark_solution_path(Maze& maze, stack<pair<int, int>>& solution_path) {
    while (!solution_path.empty()) {
        auto [row, col] = solution_path.top();
        solution_path.pop();
        maze.cell(row, col).set_hold('#'); // Mark the cell with '#'
    }
}

void clean_maze(Maze& maze) {
    for (size_t i = 0; i < maze.row_size(); ++i) {
        for (size_t j = 0; j < maze.col_size(); ++j) {
            if (maze.cell(i, j).hold() == 'D') {
                maze.cell(i, j).set_hold(' '); // Replace "Dead" cells with empty spaces
            }
        }
    }
}

void save_maze_to_file(Maze& maze, int count) {
    string filename = "solved_maze_" + to_string(count) + ".txt";
    ofstream ofs("solved/" + filename); // Create/open the file in the "solved" directory
    if (ofs.is_open()) {
        for (size_t i = 0; i < maze.row_size(); ++i) {
            for (size_t j = 0; j < maze.col_size(); ++j) {
                ofs << maze.cell(i, j).hold();
            }
            ofs << '\n';
        }
        ofs.close();
    } else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

bool solve_maze(Maze& maze, int row, int col, stack<pair<int, int>>& solution_path) {
    ifstream count_file("solved/count.txt");
    int count;
    if (count_file) {
        count_file >> count;
        count_file.close();
    } else {
        count = 1;
    }

    stack<pair<int, int>> cell_stack;
    cell_stack.push({row, col});
    maze.cell(row, col).set_visited(true);
    solution_path.push({row, col});

    while (!cell_stack.empty()) {
        auto [current_row, current_col] = cell_stack.top();

        if (current_row == maze.row_size() - 2 && current_col == maze.col_size() - 1) {
            // Found the exit
            mark_solution_path(maze, solution_path); // Mark the solution path
            clean_maze(maze); // Clean up the maze
            save_maze_to_file(maze, count++); // Save the solved maze to a file

            ofstream count_file("solved/count.txt");
            count_file << count;
            count_file.close();

            return true;
        }

        bool moved = false;

        // Check neighbors (up, down, left, right)
        vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

        for (const auto& dir : directions) {
            int new_row = current_row + dir.first;
            int new_col = current_col + dir.second;

            if (new_row >= 0 && new_row < maze.row_size() && new_col >= 0 && new_col < maze.col_size() &&
                maze.cell(new_row, new_col).hold() != '|' && maze.cell(new_row, new_col).hold() != '+' &&
                maze.cell(new_row, new_col).hold() != '-' && !maze.cell(new_row, new_col).visited()) {
                cell_stack.push({new_row, new_col});
                maze.cell(new_row, new_col).set_visited(true); // Mark as visited

                solution_path.push({new_row, new_col}); // Add cell to solution path
                moved = true;
                break; // Move to the new cell
            }
        }

        if (!moved) {
            // Dead end, backtrack
            maze.cell(current_row, current_col).set_hold('D'); // Mark the cell as "Dead"
            solution_path.pop(); // Remove the dead end from the solution path
            cell_stack.pop(); // Backtrack
        }
    }

    return false; // Exit not found
}
