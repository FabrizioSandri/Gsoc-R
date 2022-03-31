#include <Rcpp.h>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include "Dijkstra.h"

#define inf INT_MAX

using namespace std;

//' Dijkstra algorithm implementation.
//' This is the final implementation of the Dikstra algorithm by using a
//' min-priority queue.
//' @param graph a vector of Nodes, representing the graph structure
//' @param startNode the starting node which we are interested in calculating
//'         the shortest paths
std::vector<int> dijkstraAlgorithm(const std::vector<Node>& graph, int startNode){

    int numNodes = graph.size();

    /**
     * Min-Priority queue as a queue of pairs, where each pair is defined as a
     * pair of a node id and its priority (the distance). Comparison is a custom
     * comparison way to make the priority queue a Min-Priority queue.
     */
    priority_queue<pair<int,int>, vector<pair<int,int>>, Comparison> minPQueue;

    vector<int> distance(numNodes, inf);

    // inititalization
    minPQueue.push(make_pair(startNode,0));
    distance[startNode] = 0;

    /**
     * Main loop, iterate untile convergence, that is until the min-priority
     * is empty.
     */
    while (!minPQueue.empty()){

        int u = minPQueue.top().first;
        minPQueue.pop();

        // iterate over the adjacent nodes
        for (int i=0; i<graph[u].adj.size(); i++){

            int v = graph[u].adj[i];
            int uvCost = graph[u].costs[i];

            // if found a new shortest path update the distance vector
            int newDistance = distance[u] + uvCost;

            if (newDistance < distance[v]){
                minPQueue.push(make_pair(v, newDistance < distance[v]));
                distance[v] = newDistance;
            }

        }

    }

    return distance;
}


//' Dijkstra algorithm implementation - input a SparseMatrix
//' @param matrix the Graph structure representation as output from
//'         as_adj(graph, attr = "weight")
//' @param startNode the starting node which we are interested in calculating
//'         the shortest paths
// [[Rcpp::export]]
std::vector<int> dijkstraSparseMatrix(Rcpp::S4 matrix, int startNode){
    vector<int> i = matrix.slot("i");
    vector<int> p = matrix.slot("p");
    vector<int> x = matrix.slot("x");
    vector<int> dim = matrix.slot("Dim");

    Rcpp::List labels = matrix.slot("Dimnames");
    Rcpp::List labelsDim0 = labels[0];


    int numNodes = dim[0];
    int numEdges = i.size();

    vector<Node> graph(numNodes);
    vector<int> distance(numNodes, inf);

    vector<vector<int>> distanceMatrix(dim[0],vector<int>(dim[1]));

    /**
     * Parse the dgCMatrix provided by R into a distance matrix
     */
    int row = 0;
    for(int j=0; j<numEdges; j++){
        int col = i[j];

        // every new line in the matrix is specified by the p vector
        if (row<numNodes-1 && p[row+1] == j) {
            row++;
        }

        distanceMatrix[row][col] = x[j];
    }

    /**
     * Parse the distance matrix into a Graph (represented as a vector of Nodes)
     */
    for (int from=0; from<numNodes; from++){
        for(int to=0; to<numNodes; to++){
            if (distanceMatrix[from][to] != 0){
                graph[from].adj.push_back(to);
                graph[from].costs.push_back(distanceMatrix[from][to]);
            }
        }
    }

    // execute the dijkstra algorithm and return the distance vector
    distance = dijkstraAlgorithm(graph, startNode);

    return distance;
}
