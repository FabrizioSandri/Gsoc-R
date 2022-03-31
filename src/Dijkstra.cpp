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

    /**
     * Inititalization with the starting node
     */
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
//' @param dgCMatrix the Graph structure representation as output from
//'         as_adj(graph, attr = "weight")
//' @param startNode the label of the starting node which we are interested in +
//'         calculating the shortest paths
// [[Rcpp::export]]
Rcpp::NumericVector dijkstraSparseMatrix(Rcpp::S4 dgCMatrix, Rcpp::String startNode){
    vector<int> i = dgCMatrix.slot("i");
    vector<int> p = dgCMatrix.slot("p");
    vector<int> x = dgCMatrix.slot("x");
    vector<int> dim = dgCMatrix.slot("Dim");
    Rcpp::List bothDimLabels = dgCMatrix.slot("Dimnames");
    Rcpp::List nodeLabels = bothDimLabels[0];

    int numNodes = dim[0];
    int numEdges = i.size();

    int startNodeIndex = 0;

    /**
     * Representation of a graph as a vector of nodes. See the header file
     * related to this source code ("Dijkstra.h") in the definition of the struct
     * Node for more info about the Node structure.
     */
    vector<Node> graph(numNodes);

    /**
     * Resulting distance vector after applying the Dijkstra algorithm
     * on the graph
     */
    vector<int> distance;

    /**
     * Parse the dgCMatrix provided by R into an easier structure: a vector
     * of Nodes.
     *
     * NOTE: each edge is defined as a source node and a destination node.
     * In the original dgCMatrix each row correspond to the source node
     * and each column correspond to the destination node.
     */
    int to = 0;
    for(int j=0; j<numEdges; j++){
        int from = i[j];

        // every new line in the dgCMatrix is specified by the p vector
        if (to<numNodes-1 && p[to+1] == j) {
            to++;
        }

        graph[from].adj.push_back(to); // edge from source to destination
        graph[from].costs.push_back(x[j]); // x[j] contains the cost of the jth edge
    }


    /**
     * Sometimes nodes don't' have any name associated, so assume that the
     * labels range from 1 to numNodes
     */
    if (nodeLabels.size() == 0){

        for (int t=0; t<numNodes; t++){
            nodeLabels.push_back(to_string(t + 1));
        }
    }

    /**
     * Find the starting node index value as we deal with indexes and
     * not with node labels.
     */
    for (int t=0; t<numNodes; t++ ){
        string label = Rcpp::as<string>(nodeLabels(t));
        if (startNode == label){
            startNodeIndex = t;
            break;
        }
    }

    /**
     * Execute the dijkstra algorithm and return the distance vector as a
     * Named NumeriVector
     */
    distance = dijkstraAlgorithm(graph, startNodeIndex);

    Rcpp::NumericVector v = Rcpp::NumericVector::create();
    for(int t=0; t<numNodes; t++){
        v.push_back(distance[t], Rcpp::as<string>(nodeLabels(t)));
    }


    return v;
}
