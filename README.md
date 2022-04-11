#  Dijkstra implementation as Rcpp library

[![R-CMD-check](https://github.com/FabrizioSandri/Gsoc-R/workflows/R-CMD-check/badge.svg)](https://github.com/FabrizioSandri/Gsoc-R/actions)
[![custom-check](https://github.com/FabrizioSandri/Gsoc-R/workflows/custom-check/badge.svg)](https://github.com/FabrizioSandri/Gsoc-R/actions)

This package provides a minimal Dijkstra algorithm implementation library based on a min-priority queue.
The Dijkstra algorithm is written in C++, and interact with the R environment using the Rcpp library.

The algorithm is written in a way that allows any Graph built using `igraph` library to be parserd as input.

## Istallation
The easiest way to use this library is to install it using devtools and include it into a working R environment
```R
devtools::install_github("FabrizioSandri/Gsoc-R")
```
after the installation has succeeded you can import the library
```R
require("Dijkstra")
```

## Usage
After installing and including the library. you can calculate the distance vector of a specific Graph with the function `dijkstraSparseMatrix`, which takes as input a Graph defined as a SparseMatrix (a `dgCMatrix`) and a string representing the source node which we want to calculate the shortest paths to all the other nodes.
```R
dijkstraSparseMatrix <- function(dgCMatrix, soruceNode)
```

The library `igraph` allows you to convert any kind of graph into a `dgCMatrix` by using the provided function `as_adj`. Once the graph is converted into a SparseMatrix, it can be passed alongside with a string representing the source node label to the `dijkstraSparseMatrix` like in the following sample of code
```R
G <-  graph("Zachary")      # sample graph
distanceVector <- dijkstraSparseMatrix(as_adj(G), "1")
```

The function `dijkstraSparseMatrix` returns a distance vector as a named vector, in order to have for each node the  corresponding distance. In fact the content of the distance vector of the example above will look like:
```
 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 
 0  1  1  1  1  1  1  1  1  2  1  1  1  1  3  3  2  1  3  1  3  1  3  3  2  2  3  2  2  3  2  1  2  2 
```
This output can be read in the following way:
* The cost to reach node `1` from node `1` is 0
* The cost to reach node `2` from node `1` is 1
* The cost to reach node `26` from node `1` is 2
* The cost to reach node `30` from node `1` is 3
* ...

**NOTE :** the soruceNode parameter is the label of the source node represented as a string. In this way it could be possibile to have strings as node labels. See the cities graph in the Example section. 

## Weighted graph
If the graph you are dealing with is weighted you have to specify the parameter `attr = "weight"` to `as_adj`. In the following example, we creae a sample weighted graph composed of 6 nodes named with the alphabet letters.
```R
gl <- graph_from_literal(a-+c-+b-+d+-e-+f, a-+b, c-+d, d-+f, b-+e)
E(gl)$weight <- c(2,1,1,3,5,2,1,1,3)       # assign a fixed weight to each edge
distanceVector <- dijkstraSparseMatrix(as_adj(gl, attr = "weight"), "a")
```
The resulting distance vector is
```R
a c b d e f 
0 2 1 4 3 5 
```

## Example
Suppose to have a graph representing some types of connections between capital cities in Europe. The connections are represented by a undirected weighted graph, like the following one. 

![Cities](https://i.postimg.cc/zDpZXg4F/graph.png)

Suppose that we need to find the minimum distance from `Madrid` to all the other cities. The following code will solve the problem. As you can see in the following sample of code the source node is a string representing the city `Madrid`.
```R
G <- graph_from_literal(Rome-Berlin-Paris-Madrid, Paris-London-Berlin, Rome-Madrid) 
E(G)$weight <- c(1,5,2,3,1,4)

distanceVector <- dijkstraSparseMatrix(as_adj(G, attr = "weight"), "Madrid")
```
The resulting distance vector is
```R
  Rome Berlin  Paris Madrid London 
     4      3      1      0      5
```
