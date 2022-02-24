# Dijkstra-s-Shortest-Path

Implement Dijkstra's shortest path algorithm, including recovering the paths. You will find the lowest cost paths and
display the cost and path from every node to every other node. Another display routine will output one path in detail. 

Part 1
In the data, the first line tells the number of nodes, say n (assume nonnegative integer). Following is a text description of
each of the 1 through n nodes, one description per line (assume 50 chars max length). After that, each line consists of 3
ints representing an edge. (Assume correctly formatted data, int data.) If there is an edge from node 1 to node 2 with a
label of 10, the data is: 1 2 10. A zero for the first integer signifies the end of the data for that one graph. There are
several graphs, each having at most 100 nodes.
Class includes the adjacency matrix, number of nodes, TableType array, and an array of NodeData. You do not need to
implement a complete Graph class. The only methods you must have are the constructor, buildGraph (put in edge costs),
insertEdge(), removeEdge(), findShortestPath(), displayAll() (not general output, uses couts to demonstrate that the
algorithm works properly as shown), and display (to display one shortest distance with path). (Some utility functions are
needed.) For insertEdge() and removeEdge(), you figure out reasonable parameters, return type and document their use. 

Part 2
Display the graph information and implement depth-first search (using the ordering as given by the data, i.e., start at
one). Display the node numbers in depth-first order. Implement the specified graph ADT functions.
In the data, the first line tells the number of nodes, say n (assume a nonnegative integer). Following is a text description
of each of the 1 through n nodes, one description per line (max length of 50 characters). After that, each line consists of
2 ints representing an edge. (Assume int data.) For an edge from node 1 to node 2, the data is: 1 2. A zero for the first
integer signifies the end of the data for that one graph. All the edges for the first node will be together first, then all the
edges for the second node, etc. Take them as they come, no sorting. (They appear sorted because the data is in order.
Don’t assume that happens.) There are many graphs, each having at most 100 nodes. As in part1, assume the input data
file has correctly formatted data.
