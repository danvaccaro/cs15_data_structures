/**
 ** main.cpp
 **
 ** Project Two: Six Degrees of Collaboration
 **
 ** Written by: Dan Vaccaro
 **
 ** Purpose:
 **     Main program driver for SixDegrees class. Handles command line arguments,
 **      and input/output for queries.
 **
 */

#include "SixDegrees.h"

const std::string BFS = "bfs";
const std::string PRINT = "print";
const std::string DFS = "dfs";
const std::string NOT = "not";
const std::string QUIT = "quit";
const std::string INCL = "incl";

int main(int argc, char *argv[])
{
    //declare general i/o streams
    std::istream *input_stream;
    std::ostream *output_stream;
    // declare file i/o streams in case we need them
    std::ifstream infile_stream;
    std::ofstream outfile_stream;

    //switch based on number of command line parameters
    switch (argc)
    {
    case (2): // if only the artist file was specified, default to cin/cout
        input_stream = &std::cin;
        output_stream = &std::cout;
        break;
    case (3): //if there is a second parameter, open the commands file
        infile_stream.open(argv[2]);
        // if the file is valid, set the input stream to point to the file
        if (infile_stream.is_open())
        {
            input_stream = &infile_stream;
            output_stream = &std::cout;
        }
        // otherwise return error
        else
        {
            std::cerr << argv[2] << " cannot be opened\n";
            exit(1);
        }
        break;

    case (4): //if an output file was specified, open it
        infile_stream.open(argv[2]);
        input_stream = &infile_stream;
        // if the file is valid, set the input stream to point to the file
        if (infile_stream.is_open())
        {
            input_stream = &infile_stream;
            output_stream = &std::cout;
        }

        // otherwise return error
        else
        {
            std::cerr << argv[2] << " cannot be opened\n";
            exit(1);
        }
        // outfile will be created on open
        outfile_stream.open(argv[3]);
        // set the output stream to the file
        output_stream = &outfile_stream;
        break;
    default:
        //if no parameters a given, report error and exit program
        std::cerr << "Usage: ./SixDegrees dataFile [commandFile] [outputFile]\n";
        exit(1);
    }

    // initialize graph from first argument
    SixDegrees graph;
    graph.populateGraph(argv[1]);
    
    //get the first command
    graph.getCommand(*input_stream, *output_stream);

    // execute commands until invalid command is received
    while (graph.currCommand.isValid())
    {
        //validate the input command
        graph.validateCommand(*output_stream);
        //execute command based on type
        if (graph.currCommand.type == BFS)
            graph.breadthFirstSearch(*output_stream);
        if (graph.currCommand.type == DFS)
            graph.depthFirstSearch(*output_stream);
        if (graph.currCommand.type == NOT)
            graph.exclusiveSearch(*output_stream);
        if (graph.currCommand.type == QUIT)
            return 0;
        //get the next command
        graph.getCommand(*input_stream, *output_stream);
    }
    //end program
    return 0;
}