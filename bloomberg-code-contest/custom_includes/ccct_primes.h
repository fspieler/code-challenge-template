#ifndef CCCT_PRIMES_INCLUDES_GUARD
#define CCCT_PRIMES_INCLUDES_GUARD

#include <ccct_debug.h>
#include <vector>
#include <algorithm>

bool isPrime(unsigned long long n)
{
  if(n==2)return true;
  if(n%2 == 0 || n ==1){return false;}
  for(unsigned long long i = 3; i <= (unsigned long long)sqrt(n+1); i+=2)
  {
    if(n % i == 0){return false;}
  }
  return true;
}

namespace _isPrimeMemoized {
  unsigned long long highest_prime = 3;
  std::vector<unsigned long long> primes = {2,3};
};

bool isPrimeMemoized(unsigned long long n)
{
  if(n <= 1){return false;}

  auto &highest_prime = _isPrimeMemoized::highest_prime;
  auto &primes = _isPrimeMemoized::primes;

  if(n < highest_prime)
  {
      return binary_search(primes.begin(),primes.end(),n);
  }
  auto square_root = (unsigned long long) sqrt(n+1);
  
  for
  (
   auto prime = begin(primes);
   prime != end(primes) && *prime <= square_root;
   ++prime
  )
  {
    if(n % *prime == 0)
    {
      return false;
    }
  }

  for(unsigned long long i = highest_prime+2;
          i <= square_root;
          i+=2)
  {
    if(isPrimeMemoized(i))
    {
      primes.push_back(i);
      highest_prime = i;
    }
    if(n % i == 0)
    {
      return false;
    }
  }
  return true;
}

#endif //CCCT_PRIMES_INCLUDES_GUARD
