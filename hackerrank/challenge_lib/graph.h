#ifndef GRAPH_INCLUDES_GUARD
#define GRAPH_INCLUDES_GUARD
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <queue>
#include <algorithm>

#include <types.h>
#include <debug.h>

template<typename T, typename U=int>
class Graph{
public:
  typedef ull NodeId;
private:
  ull _next_id;
  bool _hasNegativeEdges;
  std::map<NodeId, T> _nodes;
  std::map<NodeId, std::set<std::pair<NodeId,U> > > _nodeEdges;
  template<typename V>
  friend std::ostream& operator<<(std::ostream& os, const Graph<V>& g);
public:
  Graph():
    _next_id(0),
    _hasNegativeEdges(false),
    _nodes(),
    _nodeEdges()
  {}
  int addNode(const T& obj)
  {
    ull id = _next_id++;
    _nodes[id] = obj;
    return id;
  }
  void addEdge(ull id1, ull id2, bool bidir=false)
  {
    addWeightedEdge(id1, id2, 1, bidir);
  }
  void addWeightedEdge(ull id1, ull id2, U weight, bool bidir=false)
  {
    _hasNegativeEdges = weight < 0 || _hasNegativeEdges;
    if(bidir)
    {
      _nodeEdges[id2].insert(std::make_pair(id1,weight));
    }
    _nodeEdges[id1].insert(std::make_pair(id2,weight));
  }

  std::set<NodeId> getConnectedNodes(NodeId starting)
  {
    std::queue<NodeId> nodes;
    std::set<NodeId> visited;
    nodes.push(starting);
    visited.insert(starting);
    while(!nodes.empty())
    {
      NodeId currentNode = nodes.front();
      nodes.pop();
      for(auto next : _nodeEdges[currentNode])
      {
        auto nextnode = std::get<0>(next);
        if(visited.find(nextnode) == visited.end())
        {
          nodes.push(nextnode);
          visited.insert(nextnode);
        }
      }
    }
    return visited;
  }

  /** Dijkstra if all nodes are positive, else Bellman-Ford  */
  bool getShortestPath(
      std::vector<ull>& path,
      U& distance,
      NodeId start,
      NodeId finish
  )
  {
    if(start==finish){
      distance = 0;
      return true;
    }
    if(!_hasNegativeEdges)
    {
      return getShortestPathDijkstra(path,distance,start,finish);
    }
    return getShortestPathBellmanFord(path,distance,start,finish);
  }

  /**Dijkstra*/
  bool getShortestPathDijkstra(
      std::vector<ull>& path,
      U& distance,
      NodeId start,
      NodeId finish
  )
  {
    auto notVisited = getConnectedNodes(start);
    if(notVisited.find(finish) == notVisited.end())
    {
      return false;
    }
    std::map<NodeId, std::unique_ptr<U> > distances;
    auto tryToSetDistance = [&distances] (ull current, std::pair<ull, U> neighbor) {
      auto c = *distances[current];
      auto& d = distances[std::get<0>(neighbor)];
      if(!d.get() || c+std::get<1>(neighbor) < *d)
      {
        d.reset(new U(c+std::get<1>(neighbor)));
      }
    };
    NodeId currentNode = start;
    distances[start] = std::unique_ptr<U>(new U(0));
    while(notVisited.find(finish) != notVisited.end())
    {
      for(auto neighbor : _nodeEdges[currentNode])
      {
        tryToSetDistance(currentNode,neighbor);
      }
      notVisited.erase(notVisited.find(currentNode));
      std::pair<NodeId, U> closest;
      bool first = true;
      //TODO improve linear lookup for shortest next node
      for(auto n : notVisited)
      {
        if(first && distances[n].get())
        {
          first = false;
          closest = std::make_pair(n, *distances[n]);
        }
        else if(distances[n].get() && *distances[n] < std::get<1>(closest))
        {
          closest = std::make_pair(n, *distances[n] );
        }
      }
      currentNode = std::get<0>(closest);
    }
    distance = *distances[finish];
    return true;
  }


  /** Bellman-Ford */
  bool getShortestPathBellmanFord(
      std::vector<ull>& path,
      U& distance,
      NodeId start,
      NodeId finish
  )
  {
    auto connected = getConnectedNodes(start);
    if(connected.find(finish) == connected.end())
    {
      return false;
    }
    return false;
  }

private:
  void _findAllPaths_RecursiveHelper(
      std::vector<std::vector<NodeId> >& paths,
      std::vector<NodeId> currentPath,
      std::set<NodeId> visited,
      NodeId currentNode,
      NodeId finish)
  {
    if(visited.find(currentNode) != visited.end())
    {
      return;
    }
    if(currentNode==finish)
    {
      paths.push_back(currentPath);
    }
    visited.insert(currentNode);
    currentPath.push_back(currentNode);
    for(auto weighted_node: _nodeEdges[currentNode])
    {
      auto nodeid = std::get<0>(weighted_node);
      _findAllPaths_RecursiveHelper(
          paths,
          currentPath,
          visited,
          nodeid,
          finish
      );
    }
  }

public:
  size_t findAllPaths(
      std::vector<std::vector<ull> >& paths,
      NodeId start,
      NodeId finish)
  {
    _findAllPaths_RecursiveHelper(
      paths,
      std::vector<ull>(),
      std::set<NodeId>(),
      start,
      finish
    );
    return paths.size();
  }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Graph<T>& g)
{
  for(auto node_pair : g._nodes)
  {
    auto nodeid = std::get<0>(node_pair);
    auto node = std::get<1>(node_pair);
    os << "(node " << nodeid << ": " << node;
    if(g._nodeEdges.find(nodeid) != g._nodeEdges.end())
    {
      os << ", directed edges: ";
      for(auto edgePair : g._nodeEdges.at(nodeid))
      {
        os << "(node " << g._nodes.at(std::get<0>(edgePair)) << ", weight " << std::get<1>(edgePair) << ")";
      }
    }
    os << ")" << std::endl;
  }
  return os;
}
#endif //GRAPH_INCLUDES_GUARD
