#include <ccct_debug.h>
#include <ccct_trie.h>
#include <gtest/gtest.h>

#include <algorithm>

namespace test {

TEST(ccct_trie_move_suffix_to_intermediate_node,normal_behavior)
{
  Trie t;
  t.add_string("apple");
  t.add_string("application");
  trie_helper::move_suffix_to_intermediate_node(t,0);
}

TEST(ccct_trie_next_letters,when_single_word_is_input_nextletters_contains_single_next_letter)
{
  Trie t;
  t.add_string("alphabet");
  std::vector<char> nl;
  t.next_letters(nl, "alph");
  ASSERT_EQ(1,nl.size());
  EXPECT_EQ('a',nl[0]);
}

TEST(ccct_trie_next_letters,when_query_hits_common_prefix_single_next_letter_found)
{
  Trie t;
  t.add_string("alphabet");
  t.add_string("alphadog");
  std::vector<char> nl;
  t.next_letters(nl, "alph");
  ASSERT_EQ(1,nl.size());
  EXPECT_EQ('a',nl[0]);
}

TEST(ccct_trie_next_letters,when_trie_forks_twice_both_letters_are_found)
{
  Trie t;
  DEBUG(t);
  t.add_string("alphabet");
  DEBUG(t);
  t.add_string("alphadog");
  DEBUG(t);
  std::vector<char> nl;
  t.next_letters(nl,"alpha");
  DEBUG(t);
  EXPECT_EQ(2,nl.size());
  auto it = std::find(nl.begin(), nl.end(), 'b');
  EXPECT_NE(nl.end(), it) << "b not found.";
  it = std::find(nl.begin(), nl.end(), 'd');
  EXPECT_NE(nl.end(), it) << "d not found.";
}

TEST(ccct_trie_next_letters,querying_after_a_fork_returns_correct_letter)
{
  Trie t;
  t.add_string("alphabet");
  t.add_string("alphadog");
  std::vector<char> nl;
  t.next_letters(nl, "alphab");
  EXPECT_EQ(1,nl.size());
  EXPECT_EQ('e',nl[0]);
  nl.resize(0);
  t.next_letters(nl, "alphad");
  EXPECT_EQ(1,nl.size());
  EXPECT_EQ('o',nl[0]);
}

TEST(ccct_trie_next_letters,categori_bug)
{
  Trie t;
  t.add_string("categorical");
  t.add_string("categorically");
  t.add_string("categories");
  t.add_string("category");
  std::vector<char> next_letters;
  t.next_letters(next_letters,"categor");
  EXPECT_EQ(2, next_letters.size());
  auto it = std::find(next_letters.begin(), next_letters.end(), 'y');
  EXPECT_FALSE(it == next_letters.end()) << "y not found";
  it = std::find(next_letters.begin(), next_letters.end(), 'i');
  EXPECT_FALSE(it == next_letters.end()) << "i not found";
}

#if 0
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

  std::string line;
  Trie t;
  while (std::getline(std::cin, line))
  {
     t.add_string(line); 
  }
  t.add_string("categorical");
  t.add_string("categorically");
  t.add_string("categories");
  t.add_string("category");
  t.print(std::cout,true);
  t.add_string("categorization");
  t.add_string("categorization");
  t.add_string("categorizations");
  t.add_string("categorization's");
  t.add_string("categorize");
  t.add_string("categorized");
  t.add_string("categorizes");
  t.add_string("categorizing");
  t.add_string("category's");



  int index = 0;
  if(argc > 1)
  {
    DEBUG((t._navigate_to_trie(argv[1],index)));
    DEBUG((t._navigate_to_trie("categor",index)));
    test_autocomplete(t,argv[1]); 
  }
  //t.print(std::cout,true);

  
  test_autocomplete(t,"Spi");
  test_autocomplete(t,"inte");
  //test_autocomplete(t,"ant");

}
#endif

} //namspace test


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
