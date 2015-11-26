#include <ccct_debug.h>
#include <ccct_trie.h>

int main()
{
  Trie t;
  t.add_string("edward");
  t.add_string("fred");
  t.add_string("frank");
  t.add_string("frankfurter");
  t.add_string("frankenstein");
  t.print(std::cout, true);
  std::cout << sizeof(Trie) << std::endl;
}
