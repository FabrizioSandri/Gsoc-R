#include <Rcpp.h>
#include <iostream>
#include <vector>

using namespace std;

//' Dijkstra algorithm implementation
//' @param mat the Graph structure representation as output from as_edgelist(G)
//' @param weights a vector containing the weights for each edge(each line) of
//'       the edgelist matrix
// [[Rcpp::export]]
int dijkstra(Rcpp::NumericMatrix mat, std::vector<int> weights){

  for(int i=0; i<mat.nrow(); i++){
    cout << "Edge ";
    for(int j=0; j<mat.ncol(); j++){
      cout << mat(i,j) << " ";
    }
    cout << " with weight " << weights[i] << endl;
  }


  return 1;
}
