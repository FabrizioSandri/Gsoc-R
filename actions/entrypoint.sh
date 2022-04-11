#!/bin/bash

### Dependencies installation
Rscript -e 'install.packages("devtools", repos="https://cloud.r-project.org")'
Rscript -e 'install.packages("igraph", repos="https://cloud.r-project.org")'

### Install the Dijkstra package 
cat <<EOF >install.R
require("devtools")
devtools::install_github("FabrizioSandri/Gsoc-R")
EOF

Rscript "install.R"

### Run the test of the cities graph
cat <<EOF >main.R
require(igraph)
require(Dijkstra)

G <- graph_from_literal(Rome-Berlin-Paris-Madrid, Paris-London-Berlin, Rome-Madrid)
E(G)\$weight <- c(1,5,2,3,1,4)

distanceVector <- dijkstraSparseMatrix(as_adj(G, attr = "weight"), "${INPUT_SOURCE_NODE}")

print(distanceVector)
EOF

Rscript "main.R"


