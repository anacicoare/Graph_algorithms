Here I have created an application using the most used algorithms
in the graph theory.


The program reads a graph's basic information (the nr of links,
number of nodes and number of algorithms to apply) and its linkings
and weight of the link (0 1 2.5 for example means that node 0 connects
to node 1 with a weight of 2.5). Example of graph reading:


5 6 1

0 1 2.5

0 3 1.4

1 4 2.3

2 0 3.0

3 0 1.4

4 2 0.5

0


For the first task I applied Dijkstra's algorithm to find the shortest 
distance between 2 nodes and I modified it so that it remembered the shortest
path tree (basically a Dijkstra + Prim implementation).

For the 2nd part I implemented Tarjan's strongly connected components algorithm.

And in the third part I improved Tarjan by taking the most efficient road.
