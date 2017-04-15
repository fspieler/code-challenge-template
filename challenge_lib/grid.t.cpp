#include <debug.h>
#include <grid.h>
#include <gtest/gtest.h>
#include <sstream>

TEST(grid,accessing_out_of_bounds_or_unitialized_elements_returns_the_default_value)
{
  int dimx = 4, dimy = 5;
  Grid<char> g(dimx,dimy,'X');
  while(dimx-->0)
    while(dimy-->0)
      ASSERT_EQ('X',g[dimx][dimy]);

  ASSERT_EQ('X',g[-1][-1]);
}

TEST(grid,takes_input_from_inputstringstream)
{
  std::istringstream iss;
  iss.str("0 1 2 3 "
          "4 5 6 7 "
          "8 9 0 1 "
          "2 3 4 5 "
          "6 7 8 9");
  int dimx = 4, dimy = 5;
  Grid<int> g(dimx,dimy,-1);
  iss >> g;
  for(int i = 0; i < dimx; ++i)
    for(int j = 0; j < dimy; ++j)
      EXPECT_EQ((j*dimx+i)%10,g[i][j]);
  g.printWidth = 1;
}

TEST(grid,output_formatted_correctly)
{
  std::istringstream iss;
  std::string input =
          "0 1 2 3 "
          "4 5 6 7 "
          "8 9 0 1 "
          "2 3 4 5 "
          "6 7 8 9";
  iss.str(input);
  int dimx = 4, dimy = 5;
  Grid<int> g(dimx,dimy,-1);
  g.printWidth = 1;
  iss >> g;
  std::ostringstream oss;
  oss << g;
  std::string output =
        "\n   | x\n"
          "   | 0 1 2 3\n"
          "---+----------\n"
          "y 0| 0 1 2 3\n"
          "  1| 4 5 6 7\n"
          "  2| 8 9 0 1\n"
          "  3| 2 3 4 5\n"
          "  4| 6 7 8 9\n";
  ASSERT_EQ(output,oss.str());
}

TEST(grid,find_shortest_path_traversing_odd_cells)
{
  std::istringstream iss;
  std::string input =
          "1 1 1 1 "
          "3 2 6 1 "
          "3 9 3 1 "
          "2 3 4 1 "
          "6 1 1 1";
  iss.str(input);
  int dimx = 4, dimy = 5;
  Grid<int> g(dimx,dimy,-1);
  g.printWidth = 1;
  iss >> g;
  std::map<Point, ull> gridMap;
  auto graph = g.toGraph(gridMap, [] (std::pair<size_t,size_t> p,Grid<int>& g) -> bool {
      return g[std::get<0>(p)][std::get<1>(p)] % 2 == 1;
  });
  std::vector<ull> path;
  int distance;
  ASSERT_TRUE(graph.getShortestPath(
    path,
    distance,
    gridMap[std::make_pair(0,0)],
    gridMap[std::make_pair(1,4)]
  ));
  ASSERT_EQ(5,distance);
  DEBUG(g);
  DEBUG(graph);
}

TEST(grid,find_shortest_path_traversing_odd_ascending_cells)
{
  std::istringstream iss;
  std::string input =
          "1 1 1 1 "
          "3 2 6 3 "
          "3 9 3 5 "
          "2 7 4 7 "
          "6 9 9 7";
  iss.str(input);
  int dimx = 4, dimy = 5;
  Grid<int> g(dimx,dimy,-1);
  g.printWidth = 1;
  iss >> g;
  std::map<Point, ull> gridMap;
  auto graph = g.toGraph
  (
      gridMap,
      [] (Point p,Grid<int>& g) -> bool
      {
        return g[p] % 2 == 1;
      },
      [] (Point p, Point q, Grid<int>& g) -> bool
      {
        return g[q] >= g[p];
      }
  );
  std::vector<ull> path;
  int distance;
  ASSERT_TRUE(graph.getShortestPath(
    path,
    distance,
    gridMap[std::make_pair(0,0)],
    gridMap[std::make_pair(1,4)]
  ));
  ASSERT_EQ(9,distance);
  DEBUG(g);
  DEBUG(graph);
}

TEST(grid,find_all_paths)
{
  std::istringstream iss;
  std::string input =
          "1 1 1 1 "
          "3 2 6 3 "
          "3 9 3 5 "
          "2 7 4 7 "
          "6 9 9 7";
  iss.str(input);
  int dimx = 4, dimy = 5;
  Grid<int> grid(dimx,dimy,-1);
  grid.printWidth = 1;
  iss >> grid;
  std::map<std::pair<size_t,size_t>, ull> gridMap;
  auto graph = grid.toGraph(gridMap);
  auto start = gridMap[std::make_pair(0,0)];
  auto finish = gridMap[std::make_pair(3,4)];
  std::vector<std::vector<ull> > paths;
  ASSERT_EQ(976,graph.findAllPaths(paths, start, finish));
}
