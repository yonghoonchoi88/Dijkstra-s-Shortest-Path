
// file graphm.h
// Simple class GraphL (emphasis on depth-first search)
// CSS 343 Programing Assignment #3  Part 2    // Yonghoon Choi

#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"

#include <iostream>
#include <iomanip>
using namespace std;

//---------------------------------------------------------------------------
// GraphL class: GrphL class calculate depth-first algorithm from the first
//               node. Read data from frile, build graph, do the depth-
//               first serach.
//   -- GraphL class store node data in GraphNode struct that holds node's
//      information and EdgeNode struct to store each edge rows information.
//   -- Implemenet as Graph by using array and linked list
//   -- Insert edges always insert at the end of the adgacendy lest of edge.
//   -- Build 2-dimensional matrix map with of structs.
//   -- EdgeNode exist in GraphNode to hold information about the adjacents
// 
// Implementation and assumptions:
//   -- Input data file has correct formatted data.
//   -- The array of every data memeber for different class objects are
//      set as 100.
//---------------------------------------------------------------------------

// const int MAXNODES_M value of 100 for different arrays and data members.
int const MAXNODES_L = 100;

// declation of EdgeNode struct to use in GrpahNode struct
struct EdgeNode;

//STL list of ints // list of edges (edge nodes), the adjacent graph node
struct GraphNode {
    EdgeNode* edgeHead;        // head of the list of edges nodes
    NodeData* data;            // information on the graph node
    bool visited;              // check if the node has been visited

};

// store edges information for the node and linked to next path edge
struct EdgeNode {
    int adjGraphNode;         // current edge
    EdgeNode* nextEdge;       // linked to next edge
};

class GraphL {
public:
    GraphL();                 // Constructor
    ~GraphL();                // Destructor

    void buildGraph(ifstream&);  // build graph with input data
    void displayGraph();         // display all information
    void depthFirstSearch();     // do depth-first search and display

private:
    int size;                 // number of nodes in the graph

    // array of GraphNodes, static array is fine, 
    // assume at most 100 nodes
    GraphNode node_array[MAXNODES_L];

    // Delete object
    void makeEmpty();

    // helper for depthFirstSearch
    void depthFirstSearchHelper(int target);

};

#endif

