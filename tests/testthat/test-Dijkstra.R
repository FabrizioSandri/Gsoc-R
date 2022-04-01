library(igraph)

test_that(
    "Sample graph 1",
    {
        result = TRUE

        gl <- graph_from_literal(a-+c-+b-+d+-e-+f, a-+b, c-+d, d-+f, b-+e)
        E(gl)$weight <- c(2,1,1,3,5,2,1,1,3)

        distanceVector <- dijkstraSparseMatrix(as_adj(gl, attr = "weight"), "a")
        correctVector <- setNames(c(0,1,2,4,3,5),c("a", "b", "c", "d", "e", "f"))

        for(name in names(distanceVector)) {
            result = result && (distanceVector[name] == correctVector[name])
        }

        expect_true(result)

    }
)

test_that(
    "Sample graph 2 (Zachary)",
    {
        result = TRUE

        G <-  graph("Zachary")      # sample graph

        distanceVector <- dijkstraSparseMatrix(as_adj(G), "1")
        correctVector <- setNames(
            c(0,1,1,1,1,1,1,1,1,2,1,1,1,1,3,3,2,1,3,1,3,1,3,3,2,2,3,2,2,3,2,1,2,2),
            1:34
        )


        for(name in names(distanceVector)) {
            result = result && (distanceVector[[name]] == correctVector[[name]])
        }

        expect_true(result)

    }
)

test_that(
    "Sample graph 3 (ring)",
    {
        result = TRUE

        G <- make_ring(20)
        E(G)$weight <- c(2,1,1,3,5,2,1,1,4,3,5,2,1,1,3,2,1,1,3,8)

        distanceVector <- dijkstraSparseMatrix(as_adj(G, attr = "weight"), "1")
        correctVector <- setNames(
            c(0,2,3,4,7,12,14,15,16,20,23,22,20,19,18,15,13,12,11,8),
            1:20
        )


        for(name in names(distanceVector)) {
            result = result && (distanceVector[[name]] == correctVector[[name]])
        }

        expect_true(result)

    }
)
