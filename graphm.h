
// file graphm.h
// Simple class GraphM (Dijkstra's shortest path algorithm)
// CSS 343 Programing Assignment #3  Part 1    // Yonghoon Choi

#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"

#include <limits.h> // for INT_MAX
#include <iostream>
#include <iomanip>
using namespace std;

//---------------------------------------------------------------------------
// GraphM class: Implement Dijkstra's shortest path algorithm to find 
//   lowest cost paths and display the cost and path from every node to
//   every other node also includes additional features:
//   -- GraphM class store node data in TableType struct and data for graph
//      node information is stored in NodeData object's array.
//   -- Int array C stores each cost of edges from the nodes.
//   -- TableType T array stores Diijktra's path infroamtion (2-dimensional 
//      of structs).
//   -- Build 2-dimensional matrix map with layered arrays of structs.
//   -- Find shortest paths between nodes.
//   -- Insert or Remove edge.
//   -- Dispay every nodes, edges, distance, path.
//   -- Display shortest path between given nodes.
// 
// Implementation and assumptions:
//   -- Input data file has correct formatted data.
//   -- Data memeber T is intialied in the default consturctor with infinity
//      distance for every souce node to other nodes in the row.
//   -- All the array of every data memeber for different class objects are
//      set as 100.
//---------------------------------------------------------------------------

// const int MAXNODES_M value of 100 for different arrays and data members.
int const MAXNODES_M= 100;

class GraphM {
public:
    GraphM();                               // default constructor

    void buildGraph(ifstream&);             // build graph with input data

    // add new edge
    bool insertEdge(int from, int to, int dist);

    // remove edge
    bool removeEdge(int from, int to);
    void findShortestPath();                // find shortestpaths
    void displayAll();                      // display all information

    // display shortest path between given two nodes if there is any
    void display(int from, int to);         
 
private:
    
    // TableType struct to store each Node data member information
    struct TableType {
        bool visited; // whether node has been visited
        int dist;     // currently known shortest distance from source
        int path;     // previous node in path of min dist
    };
    NodeData data[MAXNODES_M];     // data for graph nodes information
    int C[MAXNODES_M][MAXNODES_M]; // Cost array, the adjacency matrix
    int size;                           // number of nodes in the graph
    TableType T[MAXNODES_M][MAXNODES_M];// stores Dijkstra information 

     // helper for display()
    void findData(int from, int to);

    // helper for display() and displayAll()
    void findPath(int from, int to);

    // helper for findShortestPath()
    int smallestNode(int i);
};

#endif
