#include <debug.h>
#include <trie.h>
#include <gtest/gtest.h>

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

int main(int argc, char **argv)
{
  std::string line;
  Trie t;
#if 0
  while (std::getline(std::cin, line))
  {
     t.add_string(line); 
  }
#else
  t.add_string("categorical");
  t.add_string("categories");
  t.add_string("categorically");
  t.add_string("categories");
  t.add_string("categorization");
  t.add_string("categorization");
  t.add_string("categorizations");
  t.add_string("categorization's");
  t.add_string("categorize");
  t.add_string("categorized");
  t.add_string("categorizes");
  t.add_string("categorizing");
  t.add_string("category");
  t.add_string("category's");
  DEBUG(t);


#endif

  int index = 0;
  if(argc > 1)
  {
    DEBUG(t._navigate_to_trie(argv[1],index));
    DEBUG(t._navigate_to_trie("catego",index));
    test_autocomplete(t,argv[1]); 
  }
#if 0
  //t.print(std::cout,true);

  
  test_autocomplete(t,"Spi");
  test_autocomplete(t,"inte");
  //test_autocomplete(t,"ant");
#endif

}
