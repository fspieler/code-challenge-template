#include <functional.h>
#include <debug.h>
#include <gtest/gtest.h>

TEST(functional,filter_vector)
{
    std::vector<int> v{1,2,3,4,5,6,7,8,9};
    auto filtered = filter<int>(v,[](int x){return x%2==0;});
    ASSERT_EQ(4,std::get<0>(filtered).size());
    ASSERT_EQ(5,std::get<1>(filtered).size());
    ASSERT_EQ(std::vector<int>({2,4,6,8}), std::get<0>(filtered));
    ASSERT_EQ(std::vector<int>({1,3,5,7,9}), std::get<1>(filtered));
}

TEST(functional,filter_set)
{
    std::set<int> v{1,2,3,4,5,6,7,8,9};
    auto filtered = filter<int>(v,[](int x){return x%2==0;});
    ASSERT_EQ(4,std::get<0>(filtered).size());
    ASSERT_EQ(5,std::get<1>(filtered).size());
    ASSERT_EQ(std::set<int>({2,4,6,8}), std::get<0>(filtered));
    ASSERT_EQ(std::set<int>({1,3,5,7,9}), std::get<1>(filtered));
}

TEST(functional,each_vector)
{
    std::vector<int> v{1,2,3,4,5,6,7,8,9};
    auto doubled = each<int,int>(v,[](int x){return x*2;});
    ASSERT_EQ(9,doubled.size());
    ASSERT_EQ(std::vector<int>({2,4,6,8,10,12,14,16,18}), doubled);
}

TEST(functional,foldleft_vector)
{
    std::vector<int> v{1,2,3,4,5,6,7,8,9};
    int sum = foldleft<int,int>(v,[](int x,int sum){return x + sum;},0);
    ASSERT_EQ(45,sum);
}

TEST(functional,productall)
{
    std::vector<int> v{1,2,3,4,5};
    int product = productall(v);
    ASSERT_EQ(120,product);
}
