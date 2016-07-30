#ifndef GRID_INCLUDES_GUARD
#define GRID_INCLUDES_GUARD
#include <types.h>
#include <debug.h>
#include <digits.h>
#include <graph.h>
#include <tuple>
#include <vector>
#include <istream>
#include <iomanip>
#include <ostream>
#include <functional>

typedef std::pair<size_t, size_t> Point;

template<typename T=char>
struct GridElementWrapper
{
  Point point;
  T element;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const GridElementWrapper<T> gew)
{
  os << gew.point << ": " << gew.element;
  return os;
}

template<typename T=char>
class Grid;

template<typename T=char>
class GridRow
{
protected:
  std::vector<T> _elems;
  T _defaultValue;
  friend class Grid<T>;
  template<typename U>
  friend std::ostream& operator<<(std::ostream& os, const Grid<U>& g);
  GridRow(size_t size, T defaultValue) :
    _elems(size,defaultValue),
    _defaultValue(defaultValue)
  {}
public:
  GridRow() = delete;
  virtual ~GridRow() = default;
  virtual T& operator[](size_t y)
  {
    if(y >= 0 && y < _elems.size())
    {
      return _elems[y];
    } else
    {
      return _defaultValue;
    }
  }
};

template<typename T=char>
class BadGridRow : public GridRow<T>
{
  friend class Grid<T>;
  BadGridRow(T badValue) :
    GridRow<T>(1,badValue)
  {}
public:
  T& operator[](size_t)
  {
    return GridRow<T>::_defaultValue;
  }
};

template<typename T>
class Grid
{
  size_t _xdim, _ydim;
  std::vector<GridRow<T> > _grid;
  T _defaultValue;
  BadGridRow<T> _badRow;
  template<typename U>
  friend std::istream& operator>>(std::istream& is, Grid<U>& g);
  template<typename U>
  friend std::ostream& operator<<(std::ostream& os, const Grid<U>& g);
public:
  size_t printWidth;
  Grid() = delete;
  Grid(size_t x_dim, size_t y_dim, T defaultValue) :
    _xdim(x_dim),
    _ydim(y_dim),
    _grid(x_dim, GridRow<T>(y_dim, defaultValue)),
    _badRow(defaultValue),
    printWidth(2)
  {
    _defaultValue = defaultValue;
  }
  GridRow<T>& operator[](size_t x)
  {
    if(x >= 0 && x < _grid.size())
    {
      return _grid[x];
    } else
    {
      return _badRow;
    }
  }
  T& operator[](Point p)
  {
    return (*this)[std::get<0>(p)][std::get<1>(p)];
  }
  Graph<GridElementWrapper<T> > toGraph(
      std::map<Point, ull>& gridMap
    )
  {
    return this->toGraph(
      gridMap,
      [] (Point,Grid<T>&) {return true;},
      [] (Point,Point,Grid<T>&) {return true;}
    );
  }
  Graph<GridElementWrapper<T> > toGraph(
      std::map<Point, ull>& gridMap,
      std::function<bool(Point,Grid<T>&)> predicate
  )
  {
    return this->toGraph(gridMap,predicate, [] (Point, Point, Grid<T>&) {return true;});
  }
  Graph<GridElementWrapper<T> > toGraph(
      std::map<Point, ull>& gridMap,
      std::function<bool(Point,Grid<T>&)> predicate,
      std::function<bool(Point,Point,Grid<T>&)> edgePredicate
  )
  {
    Graph<GridElementWrapper<T> > g;
    for(size_t j = 0; j < _ydim; ++j)
    {
      for(size_t i = 0; i < _xdim; ++i)
      {
        if(predicate(std::make_pair(i,j),*this))
        {
          GridElementWrapper<T> wrapper;
          wrapper.point = std::make_pair(i,j);
          wrapper.element=(*this)[i][j];
          auto temp = g.addNode(wrapper);
          gridMap[wrapper.point] = temp;
          if(i > 0)
          {
            auto left_point = std::make_pair(i-1,j);
            if(predicate(left_point,*this))
            {
              if(edgePredicate(left_point,wrapper.point,*this))
              {
                g.addEdge(
                  gridMap[left_point],
                  gridMap[wrapper.point]
                );
              }
              if(edgePredicate(wrapper.point,left_point,*this))
              {
                g.addEdge(
                  gridMap[wrapper.point],
                  gridMap[left_point]
                );
              }
            }
          }
          if(j > 0)
          {
            auto top_point = std::make_pair(i,j-1);
            if(predicate(top_point,*this))
            {
              if(edgePredicate(top_point,wrapper.point,*this))
              {
                g.addEdge(
                  gridMap[top_point],
                  gridMap[wrapper.point]
                );
              }
              if(edgePredicate(wrapper.point,top_point,*this))
              {
                g.addEdge(
                  gridMap[wrapper.point],
                  gridMap[top_point]
                );
              }
            }
          }
        }
      }
    }
    return g;
  }
};

template<typename T>
std::istream& operator>>(std::istream& is, Grid<T>& g)
{
  for(size_t j = 0; j < g._ydim; ++j)
  {
    for(size_t i = 0; i < g._xdim; ++i)
    {
      is >> g[i][j];
    }
  }
  return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Grid<T>& g)
{
  auto x_width = std::max(g.printWidth, numDigitsDecimal(g._xdim));
  auto y_width = numDigitsDecimal(g._ydim);
  os << std::endl;
  os << "  ";
  for(int i = 0; i < y_width; ++i)
  {
    os << " ";
  }
  os << "| x" << std::endl;
  os << "  ";
  for(int i = 0; i < y_width; ++i)
  {
    os << " ";
  }
  os << "|";
  for(int i = 0; i < g._xdim; i++)
  {
    os << " " << std::setw(x_width) << i;
  }
  os << std::endl;
  os << "--";
  for(int i = 0; i < y_width; ++i)
  {
    os << "-";
  }
  os << "+";
  for(int i = 0; i < (1+x_width) * g._ydim; ++i)
  {
    os << "-";
  }
  os << std::endl;
  for(int j = 0; j < g._ydim; ++j)
  {
    if(j == 0)
    {
      os << "y ";
    }
    else
    {
      os << "  ";
    }
    os << std::setw(y_width) << j << "|";
    for(int i = 0; i < g._xdim; ++i)
    {
      os << ' ' << std::setw(x_width) <<  g._grid.at(i)._elems.at(j);
    }
    os << std::endl;
  }
  return os;
}
#endif // GRID_INCLUDES_GUARD
