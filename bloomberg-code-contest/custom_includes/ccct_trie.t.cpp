#include <ccct_debug.h>
#include <ccct_trie.h>

int main()
{
  std::string line;
  Trie t;
#if 0
  //t.add_string("anchor");
  t.add_string("a");
  t.add_string("an");
  t.add_string("ant");
  t.add_string("antelope");
  t.add_string("antelopes");
  Trie t2;
  t2.add_string("antelopes");
  t2.add_string("antelope");
  t2.add_string("antelopa");
  t2.print(std::cout,true);
  t2.add_string("ant");
  //t2.print(std::cout,true);
  //t2.add_string("an");
  //t1.print(std::cout,true);
  //t2.add_string("a");
#else
  while (std::getline(std::cin, line))
  {
     t.add_string(line); 
  }
#endif
  t.print(std::cout,true);

  std::vector<char> v;
  //t.next_letters(v,"an");
  t.next_letters(v,"Choc");
  DEBUG(v);
}
