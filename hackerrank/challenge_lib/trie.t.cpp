#include <debug.h>
#include <trie.h>
#include <gtest/gtest.h>

#include <algorithm>

TEST(trie,simple_example)
{
  Trie t;
  t.addWord("cat");
  t.addWord("caterpillar");
  t.addWord("category");
  t.addWord("car");
  t.addWord("dog");
  auto words = t.findCompletions("cat");
  DEBUG(words);
  ASSERT_EQ(3,words.size());
  words = t.findCompletions("cate");
  ASSERT_EQ(2,words.size());
  ASSERT_EQ(1,t.findCompletions("d").size());

}
