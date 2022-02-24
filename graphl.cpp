
// file graphl.cpp
// Memeber function definitions for class GraphL
// CSS 343 Programing Assignment #3 Part 2     // Yonghoon Choi

#include "graphl.h"

//----------------------------------------------------------------------------
// Default Constructor
// Default Constructor for class GraphL
// Default Contructor initialize GraphNode data member node_array
// When GrphL object is initialized its EdgeNode, data are null and mark not
// visited. 2-dimentional matrix with 2 structs. Second struct is linked with
// edgeHead and EdgeNode is linked list. node_array contains Node information

GraphL::GraphL() {
    size = 0;

    for (int i = 1; i < MAXNODES_L; ++i) {
        node_array[i].visited = false;
        node_array[i].edgeHead = NULL;
        node_array[i].data = NULL;
    }
}

//----------------------------------------------------------------------------
// Destructor
// Destructor for class GraphL
// Delete an object of GraphL by calling makeEmpty function.

GraphL::~GraphL() {
    makeEmpty();
}

void GraphL::makeEmpty() {
    for (int x = 1; x <= size; ++x) {
        node_array[x].visited = false;

        // delete edge name
        delete node_array[x].data;  

        // set edge name pointer to NULL
        node_array[x].data = NULL;

        // check for linked list if edgeHead
        if (node_array[x].edgeHead != NULL) {
            EdgeNode* del = node_array[x].edgeHead;

            // traverse linked edgeHead
            while (del != NULL) {
                node_array[x].edgeHead = node_array[x].edgeHead->nextEdge;
                delete del;                     // delete node
                del = NULL;                     // set node to NULL
                del = node_array[x].edgeHead;   // move edgeHead root
            }
        }
    }
}

//----------------------------------------------------------------------------
// buildGraph
// buildGraph function to build graph with input data
// build graph and infomation of distance for list of edges between every node
// new insert edge alway insert at the end of the adjacency list of edges 

void GraphL::buildGraph(ifstream& infile) {

   int fromNode, toNode;          // from and to node ends of edge

   makeEmpty();                   // include if dynamic memory anywhere

   infile >> size;                // read the number of nodes
   if (infile.eof()) return;      // stop reading if no more data
   
   string s;                      // used to read to end of line holding size
   getline(infile, s);

   // read graph node information
   for (int i=1; i <= size; i++) {
       getline(infile, s);
       NodeData* temp = new NodeData(s);  // store nodes name
       node_array[i].data = temp;         // store node in node_array
   }

   // read the edge data and add to the adjacency list
   for (;;) {
       infile >> fromNode >> toNode;      // read fromNode and toNode
       if (fromNode == 0 && toNode == 0) return;     // end of edge data

       // insert a valid edge into the adjacency edge STL list for fromNode
       // if the edge is the first edge for the node
       if (node_array[fromNode].edgeHead == nullptr) {
           EdgeNode* temp = new EdgeNode; // create new EdgeNode
           temp->adjGraphNode = toNode;   // store edge distance

           // new EdgeNode is the edgeHead (root) of the adjacency list
           node_array[fromNode].edgeHead = temp;

           // set end of the adjacency list to null
           node_array[fromNode].edgeHead->nextEdge = nullptr;
       }

       // if the node already have edge
       else {
           EdgeNode* temp = new EdgeNode;  // create new EdgeNode
           temp->adjGraphNode = toNode;    // store edge distance
           
           // find the end of the adjacency list
           EdgeNode* end = node_array[fromNode].edgeHead;
           while (end->nextEdge != nullptr) {
               end = end->nextEdge;
           }

           // insert the new EdgeNode at the end of the adjacency list
           end->nextEdge = temp;

           // set end of the adjacency list to null
           temp->nextEdge = nullptr;   
       }
   } 
}

//----------------------------------------------------------------------------
// display
// display function to display each node information of edges in the graph

void GraphL::displayGraph() {

    cout << "Graph:" << endl;

    for (int i = 1; i <= size; i++) {

        // print index and name of the node
        cout << "Node " << i << "      " << *node_array[i].data << endl;

        // assign crrent to edgeHead of the GraphNode object
        EdgeNode* current = node_array[i].edgeHead;

        // print out all the edges for the edgehead row
        while (current != NULL) {

            // print the edge
            cout << setw(7) << "edge " << i << setw(2) 
                << current->adjGraphNode << endl;

            // move pointer to next node in EdgeNode
            current = current->nextEdge;
        }
    }
    cout << endl;
}

//----------------------------------------------------------------------------
// depthFirstSearch
// depthFirstSearch function to do a depth-first search and display nodes in
// depth-first order by calling depthFirstSearchHelper function.
// call depthFirstSearchHelper recursively to find Depth-first ordering

void GraphL::depthFirstSearch()
{
    cout << "Depth-fisrt ordering:";

    for (int i = 1; i <= size; i++) {     // loop through size
        if (!node_array[i].visited) {     // check if node has been visited
            depthFirstSearchHelper(i);    // call depthFirstSearchHelper
        }
    }

    cout << endl << endl;
}

void GraphL::depthFirstSearchHelper(int target) {
    cout << setw(2) << target;           // print node
    node_array[target].visited = true;   // mark as visited

    // assign crrent to edgeHead of the GraphNode object
    EdgeNode* current = node_array[target].edgeHead;

    while (current != NULL) { // loop till end of EdgeHead Node

        // check if visited
        if (!node_array[current->adjGraphNode].visited) {

            // check next node of EdgeHead Node
            depthFirstSearchHelper(current->adjGraphNode);
        }

        // move pointer to next node in EdgeHead Node linked list
        current = current->nextEdge;
    }
}
