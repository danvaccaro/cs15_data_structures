/**
 ** SixDegrees.h
 **
 ** Project Two: Six Degrees of Collaboration
 **
 ** Written by: Dan Vaccaro
 **
 ** Purpose:
 **     Provide functions to allow command line access to a collaboration
 **     graph. Allows the client to load properly formatted files to
 **     create a collaboration graph of artists and songs, and provides
 **     functions for breadth-first, depth-first, and exclusive search
 **     traversal/reporting.
 */

#ifndef __SIXDEGREES_H__
#define __SIXDEGREES_H__

#include "CollabGraph.h"
#include <fstream>
#include <queue>
//A struct that stores command inputs
struct Command
{
    //store generic command inputs
    std::string type, source, dest;
    //store a vector of excluded artist names for not command
    std::vector<std::string> excluded;
    //constructor creates a blank command
    Command()
    {
        type = "";
        source = "";
        dest = "";
    }
    //clear empties the command
    void clear()
    {
        type = "";
        source = "";
        dest = "";
        excluded.clear();
    }
    //a check if the command is empty or not
    bool isValid()
    {
        if (type == "")
            return false;
        else
            return true;
    }
};

class SixDegrees
{
public:
    // populates graph from formatted file
    void populateGraph(std::string filename);
    //stores the user command
    Command currCommand;
    // get input for commands to execute
    void getCommand(std::istream &in, std::ostream &out);
    //validates commands
    bool validateCommand(std::ostream &out);
    // traversal functions
    void breadthFirstSearch(std::ostream &out);
    void depthFirstSearch(std::ostream &out);
    void depthFirstSearchHelper(const Artist &source, const Artist &dest);
    void exclusiveSearch(std::ostream &out);
private:

    // the graph to store artists
    CollabGraph artist_graph;
    // generate a stack containing a path from a traversed graph
    std::stack<Artist> createPathStack(const Artist &dest);
    // print a stack from a path stack
    void printPathStack(const Artist &source, const Artist &dest,
                        std::stack<Artist> path, std::ostream &output_stream);
    // check if an artist is on the list of exclusions
    bool isExcluded(Artist artist, std::vector<std::string> excludedArtists);
};

#endif