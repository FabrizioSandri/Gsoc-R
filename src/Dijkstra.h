#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include <vector>

/**
 * The Graph is defined as a vector of Nodes. Each node is composed of
 * - a vector of adjacent nodes id
 * - the cost of the edge from this node to another edge.
 *
 *  Example:
 *      Consider a Node "u" having "n" adjacent nodes. If "i"<n is the ith
 *      adjacent Node to u, then u.adj[i] contains the id of that node
 *      at distance u.costs[i].
 *
 *      In other words, for each adjiacent node the cost to reach that node is
 *      contained in the costs vector
 */
struct Node {
    std::vector<int> adj;
    std::vector<int> costs;
};

/**
 * Comparison class defined in order to implement a Min-Priority queue
 */
class Comparison{
public:
    bool operator() (const std::pair<int,int>& p1, const std::pair<int,int>&p2) const {
        return p1.second > p2.second;
    }
};

/**
 * Dijkstra algorithm function implementation header
 */
std::vector<int> dijkstraAlgorithm(const std::vector<Node>& graph, int startNode);

std::vector<int> dijkstraSparseMatrix(Rcpp::S4 matrix, int startNode);

#endif
