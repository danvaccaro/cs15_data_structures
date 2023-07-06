/*
 * maze.h
 *
 * Comp 15 Lab 4
 * Originally created by Chris Gregg (Feb 2014) based on maze creater at
 *                         http://azerdark.wordpress.com/2009/03/29/588/
 * Edited and updated by:
 *        Eliza Schreibman and Mark A. Sheldon (Feb 2017)
 *        Tonya Sinha and Matias Korman (Feb 2019)
 *        Elizabeth Hom (Sept 2020)
 *
 * Interface of Maze class that includes relevant functions such as generating,
 * solving, and printing a maze
 */

#ifndef __MazeCreator__maze__H
#define __MazeCreator__maze__H

#include "position.h"

class Maze {
public:
    Maze(int size);
    void print();
    void solve();
    int  solve_and_count();
    int  path_length();
    bool isSameSolutionAs(Maze anotherMaze);
    bool isSameSolutionAs(std::string anotherMaze);

private:
    static const int MAX_MAZE_SIZE  = 30;
    static const int MAX_ARRAY_SIZE = 2 * MAX_MAZE_SIZE;
    static const int MAX_CELLS      = MAX_MAZE_SIZE * MAX_MAZE_SIZE;

    static const char WALL = 'X', EMPTY = ' ', START = 'S', FINISH = 'F',
                      PATH = '.', REJECT = 'b';

    static const int NOT_FOUND = -1;

    char maze[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    int  maze_size;
    int  maze_array_size;

    bool solve(int row, int col);
    int  solve_and_count(int row, int col);
    int  num_dots_by_rows(int row);
    int  num_dots_in_row(int row, int col);

    /* You can solve the lab problems using the Position structure
     * and it's associated operations if you find that useful.
     * Otherwise, you can ignore these. */
    char &mazeAt(Position p);
    bool  solve(Position p);
    int   solve_and_count(Position p);

    bool succeeds(int distance);

    /* These are for the maze infrastructure.  You can ignore them. */
    void initialize_maze();
    void generate_maze();
    void maze_generator(int index, int backtrack_x[MAX_CELLS],
                        int backtrack_y[MAX_CELLS], int x, int y, int n,
                        int visited);
    void install_start_finish();
    int  is_closed(int x, int y);
};

#endif /* defined(__MazeCreator__maze__H) */
