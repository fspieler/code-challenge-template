#include <combinations.h>
#include <gtest/gtest.h>
#include <debug.h>

TEST(combinations,even_sums)
{
    std::vector<int> v {1,2,3,4,5,6};
    auto combs = combinations<int,int>(
            v,
            [] (int x, int y) { return x+y;},
            0,
            [] (int x) {return x%2 == 0;}
    );
    DEBUG(combs);
    ASSERT_EQ(31,combs.size());
}
