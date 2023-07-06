/* SixDegrees_unit_tests.cpp
**
** Written by: Dan Vaccaro
**
** Last updated: April 23, 2023
**
** Purpose: Testing file for SixDegrees.cpp. Reads various test artist files and tests
**          BFS, DFS, and NOT traversals. The graph formats tested are empty, 1, 2, and 5
**          elements, both connected and disconnected. All results are printed to the
**          console.
** 
*/

#include "SixDegrees.h"

void bfs_tests(SixDegrees graph);
void dfs_tests(SixDegrees graph);
void not_tests(SixDegrees graph);

int main()
{
    SixDegrees empty_graph;
    empty_graph.populate_graph("testfiles/empty_list.txt");

    SixDegrees single_elt_graph;
    single_elt_graph.populate_graph("testfiles/single_list.txt");

    SixDegrees two_elt_one_edge_graph;
    two_elt_one_edge_graph.populate_graph("testfiles/two_elt_one_edge_list.txt");

    SixDegrees two_elt_no_edge_graph;
    two_elt_one_edge_graph.populate_graph("testfiles/two_elt_no_edge_list.txt");

    SixDegrees five_elt_well_connected_graph;
    five_elt_well_connected_graph.populate_graph("testfiles/five_elt_well_connected.txt");

    SixDegrees five_elt_disconnected_graph;
    five_elt_disconnected_graph.populate_graph("testfiles/five_elt_disconnected.txt");

    std::cout << "EMPTY GRAPH TESTS\n";
    bfs_tests(empty_graph);
    dfs_tests(empty_graph);
    not_tests(empty_graph);

    std::cout << "1-ELT GRAPH TESTS\n";
    bfs_tests(single_elt_graph);
    dfs_tests(single_elt_graph);
    not_tests(single_elt_graph);
    
    std::cout << "2-ELT ONE EDGE GRAPH TESTS\n";
    bfs_tests(two_elt_one_edge_graph);
    std::cout << "\n";
    dfs_tests(two_elt_one_edge_graph);
    std::cout << "\n";
    not_tests(two_elt_one_edge_graph);
    std::cout << "\n";
    std::cout << "\n";

    std::cout << "2-ELT NO EDGE GRAPH TESTS\n";
    bfs_tests(two_elt_no_edge_graph);
    std::cout << "\n";
    dfs_tests(two_elt_no_edge_graph);
    std::cout << "\n";
    not_tests(two_elt_no_edge_graph);
    std::cout << "\n";
    std::cout << "\n";
    
    std::cout << "5-ELT WELL-CONNECTED GRAPH TESTS\n";
    bfs_tests(five_elt_well_connected_graph);
    std::cout << "\n";
    dfs_tests(five_elt_well_connected_graph);
    std::cout << "\n";
    not_tests(five_elt_well_connected_graph);
    std::cout << "\n";
    std::cout << "\n";
    
    std::cout << "5-ELT DISCONNECTED GRAPH TESTS\n";
    bfs_tests(five_elt_disconnected_graph);
    std::cout << "\n";
    not_tests(five_elt_disconnected_graph);
    std::cout << "\n";
    dfs_tests(five_elt_disconnected_graph);
    std::cout << "\n";
    std::cout << "\n";

    return 0;
}

void bfs_tests(SixDegrees graph) {
    std::cout << "BFS TESTING 1 - 5\n";
    Artist source1("artist1");
    Artist dest1("artist5");
    graph.breadthFirstSearch(source1, dest1, std::cout);
    std::cout << "BFS TESTING 1 - 2\n";
    Artist source2("artist1");
    Artist dest2("artist2");
    graph.breadthFirstSearch(source2, dest2, std::cout);
}


void dfs_tests(SixDegrees graph) {
    std::cout << "DFS TESTING 1 - 5\n";
    Artist source1("artist1");
    Artist dest1("artist5");
    graph.depthFirstSearch(source1, dest1, std::cout);
    std::cout << "DFS TESTING 1 - 2\n";
    Artist source2("artist1");
    Artist dest2("artist2");
    graph.depthFirstSearch(source2, dest2, std::cout);
}
void not_tests(SixDegrees graph) {
    std::cout << "NOT TESTING 1-5 EXCL 2\n";
    std::vector<std::string> artists_viable = { "artist1", "artist5", "artist2" };
    graph.exclusiveSearch(artists_viable, std::cout);
    std::cout << "NOT TESTING 1-5 EXCL 2,3\n";
    std::vector<std::string> artists_not_viable = { "artist1", "artist5", "artist2", "artist3" };
    graph.exclusiveSearch(artists_not_viable, std::cout);
    std::cout << "NOT TESTING 1-2 EXCL 3\n";
    std::vector<std::string> artists_viable2 = { "artist1", "artist2", "artist5", "artist3" };
    graph.exclusiveSearch(artists_viable2, std::cout);
}
    