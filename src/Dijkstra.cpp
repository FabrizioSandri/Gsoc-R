#include <Rcpp.h>
#include <iostream>
#include <vector>

using namespace std;


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
