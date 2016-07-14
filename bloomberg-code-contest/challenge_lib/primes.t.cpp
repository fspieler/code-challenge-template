#include <primes.h>
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

TEST(primes,agree_upto_1million){
  for(unsigned i = 0; i < 1'000'000; ++i)
  {
    bool ipm = isPrimeMemoized(i);
    bool ip = isPrime(i);
    if(ip != ipm)
      EXPECT_EQ(ip, ipm);
  }
}

TEST(primes,arbitrary_small_primes){
  EXPECT_EQ(isPrimeMemoized(25),false);
  EXPECT_EQ(isPrimeMemoized(27),true);
  EXPECT_EQ(isPrimeMemoized(9),false);
  EXPECT_EQ(isPrimeMemoized(1),false);
  EXPECT_EQ(isPrimeMemoized(2),true);
  EXPECT_EQ(isPrimeMemoized(3),true);
  EXPECT_EQ(isPrimeMemoized(4),false);
  EXPECT_EQ(isPrimeMemoized(13),true);
}
#if 0
TEST(primes,arbitrary_large_primes){
  test_isPrime(982'451'653,true);
  test_isPrime(86'028'121,true);
}
#endif
