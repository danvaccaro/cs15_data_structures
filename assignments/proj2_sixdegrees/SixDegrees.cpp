/**
 ** SixDegrees.cpp
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
#include "SixDegrees.h"
#include <stack>
#include <queue>
#include <vector>
/* populateGraph
** Purpose: Reads input from a file into a CollabGraph.
** Parameters: A string, the file to read.
** Returns: Void, populates the graph in the current instance.
*/
void SixDegrees::populateGraph(std::string filename)
{
    // open a filestream to read from the file
    std::ifstream infile(filename);
    // if the file is valid, do stuff
    if (infile.is_open())
    {
        // a string to store the input from the file
        std::string input;
        // an array of artists
        std::vector<Artist> artists;
        // loop until end of file
        while (std::getline(infile, input))
        {
            // first line instantiates a new artist with the name
            Artist newArtist(input);
            // while the following lines are not *, add the songs to the artist's discography
            while (input != "*")
            {
                std::getline(infile, input);
                if (input != "*")
                    newArtist.add_song(input);
            }
            // insert the artist into the graph
            artist_graph.insert_vertex(newArtist);
            // loop through the artists array up to its current size
            // push the artist into the artists list
            artists.push_back(newArtist);
        }
        // loop through each artist and compare against others
        for (Artist artist1 : artists)
        {
            for (Artist artist2 : artists)
            {
                // if the artists aren't equivalent and have a collaboration, insert an edge
                // between the two
                if (artist1 != artist2)
                {
                    std::string song = artist1.get_collaboration(artist2);
                    if (song != "")
                        artist_graph.insert_edge(artist1, artist2, song);
                }
            }
        }
        infile.close();
    }
    // otherwise the filename is bad
    else
    {
        std::cout << filename << " cannot be opened.\n";
    }
}

/* getCommand
** Purpose: Reads input from istream and populates the currCommand struct
**          with command data.
** Parameters: An input stream and an output stream.
** Returns: Void, updates the SixDegrees command struct
*/
void SixDegrees::getCommand(std::istream &in, std::ostream &out)
{
    getline(in, currCommand.type);
    // check for valid command and continue prompting until we get one
    while (!(currCommand.type == "bfs" ||
             currCommand.type == "dfs" ||
             currCommand.type == "not" ||
             currCommand.type == "quit"))
    {
        out << currCommand.type << " is not a command. Please try again.\n";
        getline(in, currCommand.source);
    }
    //if input was quit, return invalid command
    if (currCommand.type == "quit")
        return;
    // populate source and destination artists
    getline(in, currCommand.source);
    getline(in, currCommand.dest);
    // if the command is not, populate excluded artists
    if (currCommand.type == "not")
    {
        std::string excludedArtist;
        getline(in, excludedArtist);
        while (excludedArtist != "*")
        {
            currCommand.excluded.push_back(excludedArtist);
            getline(in, excludedArtist);
        }
    }
    //ensure all artists exist in graph
    validateCommand(out);
}
/* validateCommand
** Purpose: Performs a check on the currCommand member to ensure all
**          member artists are valid.
** Parameters: An output stream to print results
** Returns: True if the command is valid, false if not. If the command
**          is invalid, empties the currCommand.
*/
bool SixDegrees::validateCommand(std::ostream &out)
{
    //if the command is already invalid, do nothing and return false
    if (!currCommand.isValid())
        return false;
    //store whether a bad artist was encountered
    bool badArtistFlag = false;
    //check through source, dest, and excluded artists
    //report invalid artists
    if (!(artist_graph.is_vertex(currCommand.source)))
    {
        badArtistFlag = true;
        out << "\"" << currCommand.source << "\""
            << " was not found in the dataset :(\n";
    }
    if (!(artist_graph.is_vertex(currCommand.dest)))
    {
        badArtistFlag = true;
        out << "\"" << currCommand.dest << "\""
            << " was not found in the dataset :(\n";
    }
    for (std::string excludedArtist : currCommand.excluded)
    {
        if (!artist_graph.is_vertex(excludedArtist))
        {
            badArtistFlag = true;
            out << "\"" << excludedArtist << "\""
                << " was not found in the dataset :(\n";
        }
    }
    // if there was a bad artist, empty the command and return false
    if (badArtistFlag)
    {
        currCommand.clear();
        return false;
    }
    // otherwise return true
    return true;
}
/* breadthFirstSearch
** Purpose: Performs a breadth first traversal of the graph and prints
**          the path between the source and destination to the output stream.
** Parameters: An output stream to send results.
** Returns: Void, only reports the result of traversal. At the end of traversal,
**          predecessor members are set and will need to be reset for future 
**          traversals.        
*/
void SixDegrees::breadthFirstSearch(std::ostream &output_stream)
{
    // reset predecessor/visited members
    artist_graph.clear_metadata();
    // store the shortest path via the report path function
    std::stack<Artist> path = artist_graph.report_path(currCommand.source, currCommand.dest);
    // print the path to the output stream
    printPathStack(currCommand.source, currCommand.dest, path, output_stream);
}
/* depthFirstSearch
** Purpose: Performs a depth first traversal of the graph and prints
**          the first path between the source and destination to the output stream.
** Parameters: An output stream to send results.
** Returns: Void, only reports the result of traversal. At the end of traversal,
**          predecessor members are set and will need to be reset for future 
**          traversals.        
*/
void SixDegrees::depthFirstSearch(std::ostream &output_stream)
{
    // clear the graph metadata
    artist_graph.clear_metadata();
    // traverse the graph and set predecessor paths
    depthFirstSearchHelper(currCommand.source, currCommand.dest);
    std::stack<Artist> path = createPathStack(currCommand.dest);
    printPathStack(currCommand.source, currCommand.dest, path, output_stream);
}
/* depthFirstSearchHelper
** Purpose: Recursively sets predecessors between source and destination artists
** Parameters: An output stream to send results.
** Returns: Void, updates Vertex predecessors.
*/
void SixDegrees::depthFirstSearchHelper(const Artist &source, const Artist &dest)
{
    // store the start node neighbor's in a vector
    std::vector<Artist> neighbors = artist_graph.get_vertex_neighbors(source);
    // mark source as visited
    artist_graph.mark_vertex(source);
    // if the source is the same as the destination do nothing
    if (source == dest)
        return;
    // otherwise we visit neighbors
    else
    {
        // for each neighboring artist
        for (Artist neighbor : neighbors)
        {
            // if the neighbor hasn't been visited
            if (!artist_graph.is_marked(neighbor))
            {
                // mark neighbor's predecessor as source
                artist_graph.set_predecessor(neighbor, source);
                // perform a depth first search from neighbor to dest
                depthFirstSearchHelper(neighbor, dest);
            }
        }
    }
}
/* exclusiveSearch
** Purpose: Performs a breadth-first traversal of the graph, excluding any artists
**          in the currCommand excluded list.
** Parameters: An output stream to send results.
** Returns: Void, only reports the result of traversal. At the end of traversal,
**          predecessor members are set and will need to be reset for future 
**          traversals. 
*/
void SixDegrees::exclusiveSearch(std::ostream &output_stream)
{
    // clear the graph for traversal
    artist_graph.clear_metadata();
    // store the first two artists in vector as source and destination
    Artist source = currCommand.source;
    Artist dest = currCommand.dest;
    // the rest of the vector gets copied into a list of excluded artists
    std::vector<Artist> excludedArtists;
    // if the source is excluded, print error and exit function
    if (isExcluded(currCommand.source, currCommand.excluded))
    {
        output_stream << "A path does not exist between \"" << source << "\" and \"" << dest << "\".\n";
        return;
    }
    // perform breadth first search, but exclude the members of the artists vector
    // instantiate a queue and push the starting Artist
    std::queue<Artist> q;
    q.push(source);
    // loop until all nodes have been visited
    while (!q.empty())
    {
        // store the first node in the queue
        Artist currNode = q.front();
        // remove the node from the front of the queue
        q.pop();
        // mark the node as visited
        artist_graph.mark_vertex(currNode);
        // store the neighbors of the node
        std::vector<Artist> neighbors = artist_graph.get_vertex_neighbors(currNode);
        // visit each neighbor
        for (Artist neighbor : neighbors)
        {
            // if the neighbor hasn't been visited and isn't on the excluded list
            if (!artist_graph.is_marked(neighbor) && !isExcluded(neighbor, currCommand.excluded))
            {
                // set the predecessor of the neighbor to the current node
                artist_graph.set_predecessor(neighbor, currNode);
                // push the neighbor to the queue
                q.push(neighbor);
            }
            // mark the vertex as visited
            artist_graph.mark_vertex(neighbor);
        }
    }
    // create a stack starting from the destination node
    std::stack<Artist> path = createPathStack(dest);
    // output the path to the user
    printPathStack(source, dest, path, output_stream);
}

/* createPathStack
** Purpose: After the graph has been traversed, creates a stack starting
**          from the destination and contiuously pushes predecessors until
**          the path is complete.
** Parameters: A pointer to the destination artist in the path
** Returns: A stack containing the path of artists, with the start at the top
**          and the destination at the bottom. If there was no path, the stack
**          only contains the destination artist.
*/
std::stack<Artist> SixDegrees::createPathStack(const Artist &dest)
{
    // instantiate a path stack
    std::stack<Artist> path;
    // start pushing from the destination node
    Artist currArtist = dest;
    // starting at the destination, push each predecessor until we reach the start
    while (currArtist.get_name() != "")
    {
        // push the current artist to the stack
        path.push(currArtist);
        // update currArtiest to the predecessor node
        currArtist = artist_graph.get_predecessor(currArtist);
    }
    // return the path
    return path;
}
/* printPathStack
** Purpose: Prints the path between the source and destination, if there is one.
** Parameters: The source artist, the destination artist, a stack containing the 
**             path of artists, and a stream to ouput results.
** Returns: Void, prints to output.
*/
void SixDegrees::printPathStack(const Artist &source, const Artist &dest,
                                std::stack<Artist> path, std::ostream &output_stream)
{
    // store the artist on top of the stack
    Artist currArtist = path.top();
    // pop the first artist off the stack
    path.pop();
    // if the path is empty, report it and exit function
    if (path.empty())
    {
        output_stream << "A path does not exist between \"" << source << "\" and \"" << dest << "\".\n";
        return;
    }
    // otherwise there is a path, loop until we have hit each artist in the path
    while (!path.empty())
    {
        // store the next artist in the path as the top of the stack
        Artist nextArtist = path.top();
        // print artists and collaboration
        output_stream << "\"" << currArtist << "\" collaborated with \""
                      << nextArtist << "\" in \""
                      << artist_graph.get_edge(currArtist, nextArtist)
                      << "\".\n";
        // loop will next look at the following artist
        currArtist = nextArtist;
        // pop the next artist off the stack
        path.pop();
    }
    output_stream << "***\n";
}
/* isExcluded
** Purpose: detects whether an artist is on the excluded list for a not command.
** Parameters: An artist to compare and a list of excluded artist names as strings.
** Returns: True if the artist is on the excluded list, false otherwise.
*/
bool SixDegrees::isExcluded(Artist artist, std::vector<std::string> excludedArtists)
{
    // loop through each artist in the list
    for (Artist excludedArtist : excludedArtists)
    {
        // if the input artist is on the list, return true
        if (excludedArtist == artist)
            return true;
    }
    // the artist is not on the excluded list, return false
    return false;
}