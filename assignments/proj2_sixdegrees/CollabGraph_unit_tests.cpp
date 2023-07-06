/**
 ** CollabGraph_testing.cpp
 **
 ** Project Two: Six Degrees of Collaboration
 **
 ** Written by: Dan Vaccaro
 **
 ** Purpose:
 **       Basic testing for CollabGraph.cpp. Tests vertex/edge insertion
 **       and prints response. report_path was used with cerr statements 
 **       in the function to test. 
 **     
 */
#include <iostream>
#include <fstream>
#include "Artist.h"
#include "CollabGraph.h"

int main() {
    CollabGraph testGraph;
    Artist testArtist1;
    testArtist1.set_name("artist1");
    testArtist1.add_song("notCollab1");
    testArtist1.add_song("collab1-2");
    testArtist1.add_song("collab1-3");
    testGraph.insert_vertex(testArtist1);
    
    Artist testArtist2;
    testArtist2.set_name("artist2");
    testArtist2.add_song("notCollab2");
    testArtist2.add_song("collab1-2");
    testArtist2.add_song("collab2-4");
    testArtist2.add_song("collab2-3");
    testGraph.insert_vertex(testArtist2);
    testGraph.insert_edge(testArtist1, testArtist2, testArtist1.get_collaboration(testArtist2));

    Artist testArtist3;
    testArtist3.set_name("artist3");
    testArtist3.add_song("notCollab3");
    testArtist3.add_song("collab1-3");
    testArtist3.add_song("collab3-4");
    testArtist3.add_song("collab2-3");
    testGraph.insert_vertex(testArtist3);
    testGraph.insert_edge(testArtist1, testArtist3, testArtist1.get_collaboration(testArtist3));
    testGraph.insert_edge(testArtist2, testArtist3, testArtist2.get_collaboration(testArtist3));

    Artist testArtist4;
    testArtist4.set_name("artist4");
    testArtist4.add_song("notCollab4");
    testArtist4.add_song("collab2-4");
    testArtist4.add_song("collab3-4");
    testGraph.insert_vertex(testArtist4);
    testGraph.insert_edge(testArtist2, testArtist4, testArtist4.get_collaboration(testArtist2));
    testGraph.insert_edge(testArtist3, testArtist4, testArtist4.get_collaboration(testArtist3));

    std::stack<Artist> path = testGraph.report_path(testArtist1, testArtist4);
    testGraph.print_graph(std::cout);
}