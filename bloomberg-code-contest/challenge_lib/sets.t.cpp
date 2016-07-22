#include <sets.h>
#include <debug.h>
#include <gtest/gtest.h>

TEST(sets,see_if_union_works)
{
    std::set<int> a, b;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);
    a.insert(5);
    b.insert(2);
    b.insert(4);
    b.insert(6);
    b.insert(8);
    ASSERT_EQ(7,set_union(a,b).size());
}

TEST(sets,see_if_intersection_works)
{
    std::set<int> a, b;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);
    a.insert(5);
    b.insert(2);
    b.insert(4);
    b.insert(6);
    b.insert(8);
    ASSERT_EQ(2,set_intersection(a,b).size());
}
