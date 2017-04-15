#include <strings.h>
#include <debug.h>
#include <gtest/gtest.h>

TEST(strings,tokenize_simple_test)
{
    auto tokenized = split("this,is,cool",",");
    DEBUG(tokenized);
    EXPECT_EQ(3,tokenized.size());
    ASSERT_EQ("this",tokenized[0]);
    EXPECT_EQ("is",tokenized[1]);
    EXPECT_EQ("cool",tokenized[2]);
}

TEST(strings,tokenize_with_empty_tokens)
{
    auto tokenized = split("this  is     cool");
    DEBUG(tokenized);
    EXPECT_EQ(3,tokenized.size());
    ASSERT_EQ("this",tokenized[0]);
    EXPECT_EQ("is",tokenized[1]);
    EXPECT_EQ("cool",tokenized[2]);
}

TEST(strings,tokenize_ignore_empty_tokens)
{
    auto tokenized = split("this  is     cool",WHITESPACE,true);
    DEBUG(tokenized);
    ASSERT_EQ(8,tokenized.size());
    EXPECT_EQ("this",tokenized[0]);
    EXPECT_EQ("is",tokenized[2]);
    EXPECT_EQ("cool",tokenized[7]);
}

TEST(strings,join_int_vector)
{
    std::vector<int> v {1, 2, 3, 4, 5};
    auto str = join<int>(v);
    ASSERT_EQ("1 2 3 4 5",str);
    str = join<int>(v,":");
    ASSERT_EQ("1:2:3:4:5",str);
}

TEST(strings,join_string_vector)
{
    std::vector<std::string> v{"this","is","awesome","right"};
    auto str = join<std::string>(v,"<=>");
    ASSERT_EQ("this<=>is<=>awesome<=>right",str);
}
