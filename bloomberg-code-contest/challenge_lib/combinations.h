#ifndef COMBINATIONS_INCLUDES_GUARDS
#define COMBINATIONS_INCLUDES_GUARDS
#include <vector>
#include <functional>
#include <debug.h>

namespace _combinations
{
template <typename T, typename U>
void combinationsRecursiveHelper(
  std::vector<std::vector<T> >& combinations,
  std::vector<T> input,
  std::vector<T> currentOutput,
  std::function<U(T,U)> foldfunc,
  std::function<bool(U)> predicate,
  U value
)
{
  if(input.size() == 0)
  {
    if(predicate(value) && currentOutput.size() > 0)
    {
      combinations.push_back(currentOutput);
    }
    return;
  }
  T elem = input.back();
  input.pop_back();
  combinationsRecursiveHelper(
      combinations,
      input,
      currentOutput,
      foldfunc,
      predicate,
      value
  );
  currentOutput.push_back(elem);
  value = foldfunc(elem,value);
  combinationsRecursiveHelper(
      combinations,
      input,
      currentOutput,
      foldfunc,
      predicate,
      value
  );
}
}

template <typename T, typename U>
std::vector<std::vector<T> > combinations
(
  const std::vector<T>& input,
  std::function<U(T,U)> foldfunc,
  U initial,
  std::function<bool(U)> predicate
)
{
  std::vector<std::vector<T> > ret;
  _combinations::combinationsRecursiveHelper(
      ret,
      input,
      std::vector<T>(),
      foldfunc,
      predicate,
      initial
  );
  return ret;
}
#endif // COMBINATIONS_INCLUDES_GUARDS
