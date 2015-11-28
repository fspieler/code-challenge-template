#include <ccct_debug.h>
#include <ccct_trie.h>

void test_next_letters(const Trie& t, const std::string& s)
{
  std::vector<char> v;
  t.next_letters(v,s);
  std::cout << s << ": " << v << std::endl;
}

void test_autocomplete(const Trie& t, const std::string& s)
{
  std::vector<std::string> v;
  t.autocomplete_words(v,s);
  std::cout << s << ": " << v << std::endl;
}

int main()
{
  std::string line;
  Trie t;
  while (std::getline(std::cin, line))
  {
     t.add_string(line); 
  }
  t.add_string("Spieler");
  t.print(std::cout,true);

  test_next_letters(t,"Choc");
  test_next_letters(t,"choc");
  test_next_letters(t,"ant");

  test_autocomplete(t,"Spi");
  test_autocomplete(t,"inte");
  //test_autocomplete(t,"ant");

}
