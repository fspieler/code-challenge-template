#include <debug.h>
#define private public
#include <trie.h>
#include <gtest/gtest.h>

#include <algorithm>

namespace test {

TEST(trie_add_string,add_to_empty_node)
{
  Trie t;
  std::string s = "teststring";
  t._is_empty_word = false;
  t._empty_count = 0;
  t.add_string(s);
  ASSERT_EQ(s,t._str);
  ASSERT_TRUE(t._is_full_word);
  ASSERT_FALSE(t._is_empty_word);
  ASSERT_EQ(0, t._map.size());
}

TEST(trie_add_string,add_to_empty_node_2)
{
  Trie t;
  std::string s = "teststring";
  t._is_empty_word = true;
  t._empty_count = 457;
  t.add_string(s);
  ASSERT_EQ(s,t._str);
  ASSERT_TRUE(t._is_full_word);
  ASSERT_TRUE(t._is_empty_word);
  ASSERT_EQ(457, t._empty_count);
  ASSERT_EQ(0, t._map.size());
}

TEST(trie_add_string,adding_sub_string_creates_two_full_nodes)
{
  Trie t;
  t.add_string("abcd");
  t.add_string("ab");
  ASSERT_EQ("ab",t._str);
  ASSERT_EQ(1,t._map.size());
  ASSERT_NO_THROW(t._map.at('c'));
  ASSERT_TRUE(t._is_full_word);
  ASSERT_EQ(1,t._full_count);
  ASSERT_FALSE(t._is_empty_word);
  Trie& t2 = t._map['c'];
  ASSERT_EQ("d",t2._str);
  ASSERT_EQ(0,t2._map.size());
  ASSERT_TRUE(t2._is_full_word);
  ASSERT_EQ(1,t2._full_count);
  ASSERT_FALSE(t2._is_empty_word);
}

TEST(trie_add_string,adding_sub_string_creates_two_full_nodes_two)
{
  Trie t;
  t.add_string("ab");
  t.add_string("abcd");
  ASSERT_EQ("ab",t._str);
  ASSERT_EQ(1,t._map.size());
  ASSERT_NO_THROW(t._map.at('c'));
  ASSERT_TRUE(t._is_full_word);
  ASSERT_EQ(1,t._full_count);
  ASSERT_FALSE(t._is_empty_word);
  Trie& t2 = t._map['c'];
  ASSERT_EQ("d",t2._str);
  ASSERT_EQ(0,t2._map.size());
  ASSERT_TRUE(t2._is_full_word);
  ASSERT_EQ(1,t2._full_count);
  ASSERT_FALSE(t2._is_empty_word);
}
} //namespace test

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
