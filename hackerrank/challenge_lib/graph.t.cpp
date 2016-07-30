#include <debug.h>
#include <graph.h>
#include <gtest/gtest.h>

TEST(graphConnectedNodes,finds_connected_nodes)
{
    Graph<int> g;
    auto n1 = g.addNode(1);
    auto n2 = g.addNode(2);
    auto n3 = g.addNode(3);
    auto n4 = g.addNode(4);
    auto n5 = g.addNode(5);
    auto n6 = g.addNode(6);
    g.addEdge(n1,n2);
    g.addEdge(n4,n1);
    g.addEdge(n4,n3);
    g.addEdge(n2,n4);
    g.addEdge(n5,n6);
    auto connectedNodes = g.getConnectedNodes(n1);
    ASSERT_EQ(4,connectedNodes.size());
    ASSERT_TRUE(connectedNodes.find(n1) != connectedNodes.end());
    ASSERT_TRUE(connectedNodes.find(n2) != connectedNodes.end());
    ASSERT_TRUE(connectedNodes.find(n3) != connectedNodes.end());
    ASSERT_TRUE(connectedNodes.find(n4) != connectedNodes.end());
}
TEST(graphGetShortestPath,same_node_twice_returns_true_and_results_in_empty_path)
{
    Graph<int> g;
    auto n1 = g.addNode(1);
    auto n2 = g.addNode(2);
    g.addEdge(n1,n2);
    std::vector<ull> path;
    int distance;
    ASSERT_TRUE(g.getShortestPath(path,distance,n1,n1));
    ASSERT_EQ(0,path.size());
}
TEST(graphGetShortestPath,disconnected_neighbors_return_false)
{
    Graph<int> g;
    auto n1 = g.addNode(1);
    auto n2 = g.addNode(2);
    std::vector<ull> path;
    int distance;
    ASSERT_FALSE(g.getShortestPath(path,distance,n1,n2));
}

#if 1
TEST(graphGetShortestPath,find_trivial_path)
{
    Graph<int> g;
    auto n1 = g.addNode(1);
    auto n2 = g.addNode(2);
    auto n3 = g.addNode(3);
    g.addEdge(n1,n2);
    g.addEdge(n2,n3);
    std::vector<ull> path;
    int distance;
    ASSERT_TRUE(g.getShortestPath(path, distance, n1, n3));
    DEBUG(path);
    ASSERT_EQ(2,distance);
    //TODO test path
}

TEST(graphGetShortestPath,find_tricky_path)
{
    Graph<int> g;
    auto n1 = g.addNode(1);
    auto n2 = g.addNode(2);
    auto n3 = g.addNode(3);
    auto n4 = g.addNode(4);
    auto n5 = g.addNode(5);
    g.addWeightedEdge(n1,n2,5);
    g.addWeightedEdge(n1,n3,4);
    g.addWeightedEdge(n2,n4,3);
    g.addWeightedEdge(n3,n4,7);
    g.addWeightedEdge(n4,n5,4);
    g.addWeightedEdge(n3,n5,14);
    std::vector<ull> path;
    int distance;
    ASSERT_TRUE(g.getShortestPath(path,distance,n1,n5));
    ASSERT_EQ(12,distance);
}

TEST(graph_findAllPaths,find_all_paths)
{
    Graph<int> g;
    auto n1 = g.addNode(1);
    auto n2 = g.addNode(2);
    auto n3 = g.addNode(3);
    auto n4 = g.addNode(4);
    auto n5 = g.addNode(5);
    g.addWeightedEdge(n1,n2,5);
    g.addWeightedEdge(n1,n3,4);
    g.addWeightedEdge(n2,n4,3);
    g.addWeightedEdge(n3,n4,7);
    g.addWeightedEdge(n4,n5,4);
    g.addWeightedEdge(n3,n5,14);
    std::vector<std::vector<ull> > paths;
    ASSERT_EQ(3,g.findAllPaths(paths,n1,n5));
}
#endif
