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
  EXPECT_EQ(false, isPrimeMemoized(25));
  EXPECT_EQ(true, isPrimeMemoized(29));
  EXPECT_EQ(false, isPrimeMemoized(9));
  EXPECT_EQ(false, isPrimeMemoized(1));
  EXPECT_EQ(true, isPrimeMemoized(2));
  EXPECT_EQ(true, isPrimeMemoized(3));
  EXPECT_EQ(false, isPrimeMemoized(4));
  EXPECT_EQ(true, isPrimeMemoized(13));
}

TEST(primes,arbitrary_large_primes){
  EXPECT_EQ(true, isPrimeMemoized(982'451'653));
  EXPECT_EQ(true, isPrimeMemoized(86'028'121));
}

TEST(primefactors,prime_number_is_factored_properly_with_correct_order){
  auto facs = getPrimeFactors(101);
  EXPECT_EQ(1,facs.size());
  EXPECT_EQ(101,std::get<0>(facs[0]));
  EXPECT_EQ(1,std::get<1>(facs[0]));
}

TEST(primefactors,360_is_factored_properly_with_correct_order){
  auto facs = getPrimeFactors(360);
  EXPECT_EQ(3,facs.size());
  EXPECT_EQ(2,std::get<0>(facs[0]));
  EXPECT_EQ(3,std::get<1>(facs[0]));
  EXPECT_EQ(3,std::get<0>(facs[1]));
  EXPECT_EQ(2,std::get<1>(facs[1]));
  EXPECT_EQ(5,std::get<0>(facs[2]));
  EXPECT_EQ(1,std::get<1>(facs[2]));
}

TEST(primefactors,1000_is_factored_properly_with_correct_order){
  auto facs = getPrimeFactors(1000);
  EXPECT_EQ(2,facs.size());
  EXPECT_EQ(2,std::get<0>(facs[0]));
  EXPECT_EQ(3,std::get<1>(facs[0]));
  EXPECT_EQ(5,std::get<0>(facs[1]));
  EXPECT_EQ(3,std::get<1>(facs[1]));
}

TEST(gcd,return_gcd_with_two_inputs){
  EXPECT_EQ(12,gcd(72,84));
}

TEST(lcm,return_lcm_with_two_inputs){
  EXPECT_EQ(75,lcm(15,25));
  EXPECT_EQ(4061,lcm(131,31));
}
