library(igraph)

test_that(
    "Sample graph 1",
    {
        result = TRUE

        gl <- graph_from_literal(a-+c-+b-+d+-e-+f, a-+b, c-+d, d-+f, b-+e)
        E(gl)$weight <- c(2,1,1,3,5,2,1,1,3)

        distanceVector <- dijkstraSparseMatrix(as_adj(gl, attr = "weight"), "a")
        correctVector <- setNames(c(0,1,2,4,3,5),c("a", "b", "c", "d", "e", "f"))
        plot(gl, edge.label=E(gl)$weight)

        for(name in names(distanceVector)) {
            result = result && (distanceVector[name] == correctVector[name])
        }

        expect_true(result)

    }
)
