
// file graphm.cpp
// Memeber function definitions for class GraphM
// CSS 343 Programing Assignment #3 Part 1     // Yonghoon Choi

#include "graphm.h"

//----------------------------------------------------------------------------
// Default Constructor
// Default Constructor for class GraphM
// Default Contructor initialize Data memeber T and C 2-dimentional matrix
// distances between nodes as infinitiy, visted bool to false, and set paths
// from to 0 for every rows of data members arrays.

GraphM::GraphM() {
    size = 0;        // set the number (size) of node to 0

    for (int i = 1; i < MAXNODES_M; i++) {
        for (int j = 1; j < MAXNODES_M; j++) {
            // set values of C matrix array(lengths to edges) to 
            // adjements to infinite
            C[i][j] = INT_MAX;

            // all the nodes are not visited
            T[i][j].visited = false;

            // set each nodes distance to infinite
            T[i][j].dist = INT_MAX;

            // set every path is from 0
            T[i][j].path = 0;
        }
    }
}

//----------------------------------------------------------------------------
// buildGraph
// buildGraph function to build graph with input data
// build graph and infomation of distance of matrixs for edges between nodes

void GraphM::buildGraph(ifstream& infile) {
    // from and to node ends of edge and distance between from to end
    int fromNode, toNode, dist;


    infile >> size;                // read the number of nodes
    if (infile.eof()) return;      // stop reading if no more data

    string s;                      // used to read to end of line holding size
    getline(infile, s);

    // read graph node information
    for (int i = 1; i <= size; i++) {
        data[i].setData(infile);
    }

    // read the edge data and add to the adjacency list
    for (;;) {
        infile >> fromNode >> toNode >> dist;
        if (fromNode == 0 && toNode == 0) return;     // end of edge data

        // insert a valid edge into the adjacency edge STL list for fromNode
        C[fromNode][toNode] = dist;
    }

}

//----------------------------------------------------------------------------
// insertEdge
// insertEdge function to insert new edge to the graph
// from and to nodes and the distances between the nodes are passed in

bool GraphM::insertEdge(int from, int to, int dist) {

    // check if the size and from node are correct form
    // if from node is bigger than nodes size and from node is elss than 1
    if (from > size || from < 1) {
        return false;
    }

    // if to node is bigger than nodes size and to node is elss than 1
    if (to > size || to < 1) {
        return false;
    }

    // if from node and to node are same and distance given is not 0
    if (dist != 0 && from == to) {
        return false;
    }

    // if distance is neagtive
    if (dist < 0) {
        return false;
    }

    C[from][to] = dist;   // new edge inserted

    // Dijkstra's algorithm to finde shortestpaths between every nodes
    // with changed graph for the new insert node
    findShortestPath();

    return true;
}


//----------------------------------------------------------------------------
// removeEdge
// removeEdge function to remove edge between two nodes.
// from and to nodes are passed in to be removed

bool GraphM::removeEdge(int from, int to) {

    // check if from node is bigger than the total numbers of nodes
    // and if from node is smaller than 1
    if (from > size || from < 1) {
        return false;
    }

    // check if to node is bigger than the total numbers of nodes
    // and if to node is smaller than 1
    if (to > size || to < 1) {
        return false;
    }

    // edge removed and set the edge distance to infinity
    C[from][to] = INT_MAX;

    // Dijkstra's algorithm to finde shortestpaths between every nodes
    // with changed graph for remove node
    findShortestPath();

    return true;
}

//----------------------------------------------------------------------------
// findShortestPath
// findShortestPath function to find shortest path between every nodes
// call smallestNode function to set int value of nextEdge to find smallest 
// distanced edge for Dijkstra's algorithm process. Next shortest distanced
// edge is set as nextEdge to process distance comparion process to find
// the shortest paths between every nodes.

void GraphM::findShortestPath() {
    int nextEdge = 1;

    for (int source = 1; source <= size; source++) {
        T[source][source].dist = 0;

        for (int i = 1; i <= size; i++) {

            // set nextEdge in value to where the distance to the edge
            // is the shortest
            nextEdge = smallestNode(source);

            // mark the node as visited
            T[source][nextEdge].visited = true;
            if (nextEdge != 0) {
                for (int w = 1; w <= size; w++) {

                    // if the distance between node are ifinity and the
                    // node have not visited
                    if (C[nextEdge][w] != INT_MAX && 
                        T[source][w].visited == false) {

                        // if exisiting distance is longer than the 
                        // distance through the seleced node as path edge
                        if (T[source][nextEdge].dist + C[nextEdge][w] 
                            < T[source][w].dist) {

                            // set the shorter path as path between node
                            T[source][w].path = nextEdge;
                        }

                        // distance between nodes is set for the shorter
                        // distance between nodes
                        T[source][w].dist = min(T[source][w].dist, 
                            (T[source][nextEdge].dist + C[nextEdge][w]));
                    }
                }
            }
        }
    }
}

int GraphM::smallestNode(int source) {
    int min = INT_MAX;
    int small = 0;

    for (int j = 1; j <= size; j++) {

        // if the new edge has not been visited and distance between nodes
        // are infinity
        if (T[source][j].dist != INT_MAX && T[source][j].visited == false) {

            // find out which not visted node is the shortest distanced edge
            if (T[source][j].dist < min) {
                min = T[source][j].dist;
                if (min != INT_MAX) {

                    // set the node number as small
                    small = j;
                }
            }
        }
    }

    if (min == INT_MAX) {
        return 0;
    }
    
    // return the not visted shortest distance edge
    return small;
}

//----------------------------------------------------------------------------
// displayAll
// displayAll function to display every nodes shortest distance to every
// nodes with paths. call findpath helper function to find possible paths
// for each node. findPath function finds paths for a given edge recursively

void GraphM::displayAll() {
   
    cout << "Description " << setw(49);
    cout << "From node  To node  Dijkstra's  Path" << endl;

    for (int from = 1; from <= size; from++) {
        cout << data[from] << endl;        // print node name

        for (int to = 1; to <= size; to++) {
            if (T[from][to].dist != 0) {
                
                cout << setw(31) << from;  // print from node
                cout << setw(9) << to;     // print to node

                if (T[from][to].dist == INT_MAX) {
                    // no distance, not an edge of the node
                    cout << setw(11) << "----" << endl;
                }
                else {
                    cout << setw(11) << T[from][to].dist;  // print distance
                    cout << setw(7);

                    // call findPath helper function to print paths
                    findPath(from, to);
                    cout << endl;
                }
            }
        }
    }
}

void GraphM::findPath(int from, int to) {

    // if there is no path between two nodes
    if (T[from][to].dist == INT_MAX) {
        return; 
    }

    // if from and to nodes are same
    if (from == to) {
        cout << to << " ";  // print data

        return;
    }

    // assign pathData as to node
    int pathData = to;

    // find paths along with selected edges in order
    findPath(from, to = T[from][to].path);

    cout << pathData << " ";   // print paths for each edge
}


//----------------------------------------------------------------------------
// display
// display function to display shortest distance bewteen given two nodes
// call helper function findPath to print paths
// call helper function findData to chedk if there is path between and
// print the to node

void GraphM::display(int from, int to) {

    // check if there is edge from the node
    if ((from > size || from < 0) || (to > size || to < 0)) {

        // there is no path between nodes
        cout << "   " << from << "       " << to;   
        cout << setw(7) << "----" << endl;        

        return;
    }

    // print from and end node
    cout << "   " << from << setw(7) << to;

    // if the distance between from and end is not infinity (path exist)
    if (T[from][to].dist != INT_MAX) {

        // print distance between two node
        cout << "   " << T[from][to].dist << "       ";

        // print correct paths between nodes
        findPath(from, to);
        cout << endl;

        // print infomation about the edge
        findData(from, to);
    }

    // if there is no path between two nodes
    else {
        cout << "       " << "----" << endl;
    }

    cout << endl;
}

void GraphM::findData(int from, int to) {

    // no paths between the nodes
    if (T[from][to].dist == INT_MAX) {
        return;
    }

    // if end and to nodes are the same
    if (from == to) {
        cout << data[to] << endl;
        return;
    }

    int nodeData = to; // assign to node to nodeData

    findData(from, to = T[from][to].path);  // call helper

    // print the edge information
    cout << data[nodeData] << endl << endl;    
}
