#include <Rcpp.h>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include "Dijkstra.h"

#define inf INT_MAX

using namespace std;


//' Dijkstra algorithm implementation
//' @param edgeList the Graph structure representation as output from as_edgelist(G)
//' @param weights a vector containing the weights for each edge(each line) of
//'         the edgelist matrix
//' @param numNodes the number of nodes of the graph
//' @param startNode the starting node which we are interested in calculating
//'         the shortest paths
//' @param isDirected boolean value stating that each edge into the edge matrix
//'         should be trated or not as a directed edge
// [[Rcpp::export]]
std::vector<int> dijkstra(Rcpp::NumericMatrix edgeList, std::vector<int> weights, int numNodes,
             int startNode, bool isDirected){

    vector<Node> graph(numNodes + 1);
    vector<int> distance(numNodes + 1, inf);

    /**
     * Min-Priority queue as a queue of pairs, where each pair is defined as a
     * pair of a node id and its priority (the distance). Comparison is a custom
     * comparison way to make the priority queue a Min-Priority queue.
     */
    priority_queue<pair<int,int>, vector<pair<int,int>>, Comparison> minPQueue;

    /**
     * Parse the edge matrix into a Graph (represented as a vector of Nodes)
     * paying attention to the case that the graph is directed.
     */
    for(int i=0; i<edgeList.nrow(); i++){

        int from = edgeList(i, 0);
        int to = edgeList(i, 1);

        // add each directed edge to the graph
        graph[from].adj.push_back(to);
        graph[from].costs.push_back(weights[i]);

        // add also each edge in the reverse order if the graph is not directed
        if (!isDirected){
            graph[to].adj.push_back(from);
            graph[to].costs.push_back(weights[i]);
        }

    }


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

    vector<int> distanceSliced = vector<int>(distance.begin() + 1, distance.end());

    return distanceSliced;
}
