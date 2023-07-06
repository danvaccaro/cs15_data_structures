/*
 * maze.cpp
 *
 * Comp 15 Lab 5
 * Originally created by Chris Gregg (Feb 2014) based on maze creater at
 *                         http://azerdark.wordpress.com/2009/03/29/588/
 * Edited and updated by:
 *        Eliza Schreibman and Mark A. Sheldon (Feb 2017)
 *        Tonya Sinha and Matias Korman (Feb 2019)
 *        Elizabeth Hom (Sept 2020)
 *
 * Implementation of a maze class that creates directed, acyclic, perfect
 * mazes, and recursive functions for solving them. Offers two ways to idnex
 * the maze: using Position object or manipulating row/col directly.
 *
 * TODO: Student must complete the implementation of solve() and determine
 *       the length of the completion paths.
 *
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdio.h>

#include "maze.h"
#include "position.h"

/*
 * really_random == true
 * makes the random number generator use the current time for more
 * random mazes.
 * If it's false, then always seeds random number generator with 0 so
 * maze sequence is repeatable for debugging.
 */

/* really_random == true makes random number generator in Constructor use the
 *     current time for more random mazes. really_random == false seeds the
 *     random number generator with 0 so maze sequence is repeatable for
 *     debugging purposes.
 */
#ifdef RANDOM
static const bool really_random = true;
#else
static const bool really_random = false;
#endif

using namespace std;

// Constructor -- establishes random number generator and creates maze
Maze::Maze(int size) {
    if (really_random)
        srand(time(NULL));
    else
        srand(0U);

    maze_size       = size;
    maze_array_size = maze_size * 2 + 1; // Actual size of array
    generate_maze();
}

/* mazeAt
 *    Purpose: One way to index the maze by using a Position object, rather
 *             than specifying row/col separately.
 * Parameters: Position object
 *    Returns: Returns row/col within the maze using Position object
 *
 *       Note: Useful for functions that want to pass an return Positions
 */
char& Maze::mazeAt(Position p) {
    return maze[p.row][p.col];
}

/* solve
 *    Purpose: Public solve function that drives solving of maze
 * Parameters: none
 *    Returns: none
 */
void Maze::solve() {
    solve(1, 1);     // Uncomment this line if using other solve()
    // implementation

    //solve(Position(1, 1));
    maze[1][1] = START; // Necessary to reset start position to START because
                        // private solve() sets to '.'
}

/* solve
 *    Purpose: Solves the maze using separate row/col indices. Assumes an
 *             unsolved maze with a start row/col of (1,1).
 * Parameters: Current row/col indices
 *    Returns: True if maze can be solved, false if no solution
 *
 *       Note: Dead end paths that have been tested should be marked with 'b',
 *             correct path should be marked with periods '.'.
 *
 *             BE CAREFUL! 2D arrays seem backwards and upside down compared to
 *             Cartesian coordinates:
 *                 maze[0][0] == top left
 *                 maze[1][0] == one down, zero to the right
 *                 maze[0][1] == zero down, one to the right
 *                 maze[row][col] == row down and col to the right
 */
bool Maze::solve(int row, int col) {
    //base 1: position is F - return true
    if (maze[row][col] == FINISH)
        return true;
    //base 2: if value is not a space, return false
    if (maze[row][col] == WALL || maze[row][col] == PATH || maze[row][col] == REJECT)
        return false;
    //initialize the current position as a reject
    maze[row][col] = REJECT;
    //if the current position is in the solution, mark it as a path and return true
    if (solve(row - 1, col) || //north
        solve(row, col + 1) || //south
        solve(row + 1, col) || //east
        solve(row, col - 1))   //west
    {
        maze[row][col] = PATH;
        return true;
    }
    else return false;
}

/* solve
 *    Purpose: Solves the maze using Position object.
 * Parameters: Position object
 *    Returns: True if maze can be solved, false if no solution
 *
 *       Note: You can choose which private solve() implementation to use,
 *             either this one or the above one
 */
bool Maze::solve(Position p) {
    //base 1: position is F - return true
    if (mazeAt(p.north()) == 'F' || mazeAt(p.east()) ||
        mazeAt(p.south()) == 'F' || mazeAt(p.west()) == 'F')
        return true;
    //if north is open (not X)
    if (mazeAt(p.north()) != 'X') {
        //set the value at p.north to a dot
        maze[p.north().row][p.north().col] = '.';
        std::cerr << "North is open" << std::endl;
        //solve the puzzle from north
        return solve(p.north());
    }
    if (mazeAt(p.east()) != 'X') {
        maze[p.east().row][p.east().col] = '.';
        std::cerr << "East is open" << std::endl;
        return solve(p.east());
    }
        
    if (mazeAt(p.south()) != 'X') {
        maze[p.south().row][p.south().col] = '.';
        std::cerr << "South is open" << std::endl;
        return solve(p.south());
    }
    if (mazeAt(p.west()) != 'X') {
        maze[p.west().row][p.west().col] = '.';
        std::cerr << "West is open" << std::endl;
        return solve(p.west());
    }
    else return false;
}

/* path_length
 *    Purpose: Determines length of path from start to finish
 * Parameters: none
 *    Returns: Returns path length
 */
int Maze::path_length() {
    return num_dots_by_rows(1) + 1;
};

/* num_dots_by_rows
 *    Purpose: Determines number of dots in the maze starting at a given row
 *             by recursing on row index
 * Parameters: Row to start counting dots
 *    Returns: Number of dots in maze path
 */
int Maze::num_dots_by_rows(int row) {
    //base case: we are past the last row
    if (row > (2 * maze_size - 1))
        return 0;
    //add the number of dots in this row to the number of dots in the remaining rows
    return num_dots_in_row(row, 1) + num_dots_by_rows(row + 1);
}

/* num_dots_in_row
 *    Purpose: Determines number of dots in a given row starting at a given
 *             column by recursing on column index
 * Parameters: Row/col position
 *    Returns: Number of dots in a given row starting at given column
 */
int Maze::num_dots_in_row(int row, int col) {
    //base case: value is past the end of the row
    if (col > 2 * maze_size - 1)
        return 0;
    //if we encounter a '.', add 1 and recurse on column index
    else if (maze[row][col] ==  '.')
        return 1 + num_dots_in_row(row, col + 1);
    //if there is not a dot, recurse on column index
    else
        return num_dots_in_row(row, col + 1);    
}

/* solve_and_count
 *    Purpose: Assumes the maze is not solved and recursively solves the maze
 *             AND counts final path length.
 * Parameters: none
 *    Returns: Length of final path, i.e. the number of '.'s + 1
 */
int Maze::solve_and_count() {
    int distance;

    // distance = solve_and_count(1, 1);
    distance = solve_and_count(1, 1);

    maze[1][1] = START;
    return distance;
};

/* solve_and_count
 *    Purpose: Solves the maze and returns path starting at given position
 * Parameters: Row/col position
 *    Returns: Length of path starting at the given position
 *
 *       Note: Complete this function or the one using a Position object below
 */
int Maze::solve_and_count(int row, int col) {
    //solve the puzzle
    solve();
    //return the path length
    return path_length();
}

/* solve_and_count
 *    Purpose: Solves the maze and returns path starting at given position
 * Parameters: Position object
 *    Returns: Length of path starting at the given position
 *
 *       Note: Complete this function or the one using row/col index above
 */
int Maze::solve_and_count(Position p) {
    // TODO: YOUR CODE HERE
    // This is a stub -- remove entire body, then implement
    (void)p;

    return NOT_FOUND;
}

/* succeeds
 *    Purpose: Determines whether a given distance is valid
 * Parameters: int -- distance traveled
 *    Returns: True if the distance is valid (!= -1), otherwise false
 */
bool Maze::succeeds(int distance) {
    return distance != NOT_FOUND;
}


/*************************************************************/
/*** The code below here was originally taken from         ***/
/*** https://azerdark.wordpress.com/2009/03/29/588/        ***/
/***                                                       ***/
/*** Chris Gregg added a function to convert the           ***/
/*** original mazes from an integer-based representation   ***/
/*** to a character-based one so we could have ASCII       ***/
/*** output.                                               ***/
/***                                                       ***/
/*** Mark A. Sheldon changed the principle representation  ***/
/*** to be character-based and reorganized the code to be  ***/
/*** more modular, to have abstraction boundaries, and to  ***/
/*** have better variable names.                           ***/
/***                                                       ***/
/*** You are not expected to understand this code.         ***/
/*************************************************************/

/* generate_maze
 *    Purpose: Generates and initializes a maze
 */
void Maze::generate_maze() {
    int index = 0;
    int backtrack_x[MAX_CELLS];
    int backtrack_y[MAX_CELLS];

    initialize_maze();

    backtrack_x[index] = 1;
    backtrack_y[index] = 1;
    maze_generator(index, backtrack_x, backtrack_y, 1, 1, maze_size, 1);

    install_start_finish();
}

/* initialize_maze
 *    Purpose: Sets up a maze, including the walls and borders
 */
void Maze::initialize_maze() {
    for (int row = 0; row < MAX_ARRAY_SIZE; ++row) {
        for (int col = 0; col < MAX_ARRAY_SIZE; ++col) {
            if (row % 2 == 0 or col % 2 == 0) {
                maze[row][col] = WALL;
            } else {
                maze[row][col] = EMPTY;
            }
        }
    }
}

/* install_start_finish
 *    Purpose: Installs the start and finish points of the maze. Currently,
 *             always starts in the upper left corner (inside border walls) and
 *             finishes in the lower right corner (also inside border walls).
 */
void Maze::install_start_finish() {
    maze[1][1]                                     = START;
    maze[maze_array_size - 2][maze_array_size - 2] = FINISH;
}

/* maze_generator
 *    Purpose: Generates actual maze through using a backtracking search with
 *             some randomness to generate the maze.
 */
void Maze::maze_generator(int index, int backtrack_x[MAX_CELLS],
                          int backtrack_y[MAX_CELLS], int x, int y, int n,
                          int visited) {
    if (visited < n * n) {
        int neighbour_valid = -1;
        int neighbour_x[4];
        int neighbour_y[4];
        int step[4];

        int x_next;
        int y_next;

        if (x - 2 > 0 and is_closed(x - 2, y)) { // upside
            neighbour_valid++;
            neighbour_x[neighbour_valid] = x - 2;
            ;
            neighbour_y[neighbour_valid] = y;
            step[neighbour_valid]        = 1;
        }

        if (y - 2 > 0 and is_closed(x, y - 2)) { // leftside
            neighbour_valid++;
            neighbour_x[neighbour_valid] = x;
            neighbour_y[neighbour_valid] = y - 2;
            step[neighbour_valid]        = 2;
        }

        if (y + 2 < n * 2 + 1 and is_closed(x, y + 2)) { // rightside
            neighbour_valid++;
            neighbour_x[neighbour_valid] = x;
            neighbour_y[neighbour_valid] = y + 2;
            step[neighbour_valid]        = 3;
        }

        if (x + 2 < n * 2 + 1 and is_closed(x + 2, y)) { // downside
            neighbour_valid++;
            neighbour_x[neighbour_valid] = x + 2;
            neighbour_y[neighbour_valid] = y;
            step[neighbour_valid]        = 4;
        }

        if (neighbour_valid == -1) {
            // backtrack
            x_next = backtrack_x[index];
            y_next = backtrack_y[index];
            index--;
        }

        if (neighbour_valid != -1) {
            int randomization = neighbour_valid + 1;
            int random        = rand() % randomization;
            x_next            = neighbour_x[random];
            y_next            = neighbour_y[random];
            index++;
            backtrack_x[index] = x_next;
            backtrack_y[index] = y_next;

            int rstep = step[random];

            if (rstep == 1)
                maze[x_next + 1][y_next] = EMPTY;
            else if (rstep == 2)
                maze[x_next][y_next + 1] = EMPTY;
            else if (rstep == 3)
                maze[x_next][y_next - 1] = EMPTY;
            else if (rstep == 4)
                maze[x_next - 1][y_next] = EMPTY;
            visited++;
        }

        maze_generator(index, backtrack_x, backtrack_y, x_next, y_next, n,
                       visited);
    }
}

/* print
 *    Purpose: Prints maze to standard output
 * Parameters: none
 *    Returns: none
 */
void Maze::print() {
    for (int row = 0; row < maze_array_size; ++row) {
        for (int col = 0; col < maze_array_size; ++col) {
            cout << maze[row][col];
        }
        cout << endl;
    }
    cout << endl;
}

/*
void Maze::human_readable_maze()
{
    for (int a = 0; a < maze_array_size; a++) {
        for (int b = 0; b < maze_array_size; b++) {
            if (a == 1 and b == 1)
                maze[a][b] = 'S'; // the start location
            else if (a == maze_array_size - 2 and
                                 b == maze_array_size - 2) {
                // the finish location
                maze[a][b] = 'F';
            } else if (maze[a][b] == WALL)
                maze[a][b] = 'X';
            else
                maze[a][b] = ' ';
        }
    }
}
*/

/* is_closed
 *    Purpose: Determines whether the maze is closed
 * Parameters: int -- (x,y) position indices
 *    Returns: 1 if maze is fully closed, otherwise 0
 */
int Maze::is_closed(int x, int y) {
    if (maze[x - 1][y] == WALL and maze[x][y - 1] == WALL and
        maze[x][y + 1] == WALL and maze[x + 1][y] == WALL) {
        return 1;
    }

    return 0;
}

/* isSameSolutionAs
 *    Purpose: Determines whether two mazes have the same solution
 * Parameters: a different Maze object
 *    Returns: False if current maze solution is different from pssed in Maze,
 *             otherwise True
 */
bool Maze::isSameSolutionAs(Maze anotherMaze) {
    for (int row = 0; row < maze_array_size; row++) {
        for (int col = 0; col < maze_array_size; col++) {
            if (maze[row][col] != anotherMaze.maze[row][col]) { return false; }
        }
    }

    return true;
}
