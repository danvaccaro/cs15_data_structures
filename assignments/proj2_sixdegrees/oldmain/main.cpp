/*
 * main.cpp
 *
 * CS 15 Project 2: Six Degrees of Collaboration
 *
 * by Dan Vaccaro, 16 April 2023
 */

#include "SixDegrees.h"

const std::string BFS = "bfs";
const std::string PRINT = "print";
const std::string DFS = "dfs";
const std::string NOT = "not";
const std::string QUIT = "quit";
const std::string INCL = "incl";

int main(int argc, char **argv) {
    std::istream &input_stream = std::cin;
    std::ostream &output_stream = std::cout;
    //check for proper number of arguments
    if (argc < 2) {
        std::cout << "Usage: ./SixDegrees dataFile [commandFile] [outputFile]\n";
        return 0;
    }
    SixDegrees graph;
    graph.populate_graph(argv[1]);
    std::string command = graph.getCommand(input_stream, output_stream);
    while (command != QUIT)
    {
        std::vector<std::string> artists = graph.getArtists(command, input_stream, output_stream);
        if (command == BFS && !artists.empty())
            graph.breadthFirstSearch(artists[0], artists[1], output_stream);
        if (command == DFS && !artists.empty())
            graph.depthFirstSearch(artists[0], artists[1], output_stream);
        if (command == NOT && !artists.empty())
            graph.exclusiveSearch(artists, output_stream);
        if (command == PRINT)
            graph.print_graph();
        command = graph.getCommand(input_stream, output_stream);
    }
    return 0;
}
