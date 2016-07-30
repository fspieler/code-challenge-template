#ifndef PRIMES_INCLUDES_GUARD
#define PRIMES_INCLUDES_GUARD

#include <types.h>
#include <debug.h>
#include <vector>
#include <tuple>
#include <algorithm>

class Prime
{
public:
  virtual bool isPrime(ull n)
  {
    if(n==2)return true;
    if(n%2 == 0 || n ==1){return false;}
    for(ull i = 3; i <= (ull)sqrt(n+1); i+=2)
    {
      if(n % i == 0){return false;}
    }
    return true;
  }
};

bool isPrime(ull n)
{
  Prime p;
  return p.isPrime(n);
}

class MemoizedPrime : public Prime
{
  ull highest_prime = 3;
  std::vector<ull> primes = {2,3};
public:
  bool isPrime(ull n)
  {
    if(n <= 1){return false;}

    if(n < highest_prime)
    {
      return binary_search(primes.begin(),primes.end(),n);
    }
    auto square_root = (ull) sqrt(n+1);

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

    for(ull i = highest_prime+2;
        i <= square_root;
        i+=2)
    {
      if(isPrime(i))
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
  std::vector<std::pair<ull, int> > getPrimeFactors(ull n)
  {
    std::vector<std::pair<ull, int> > ret;
    if(isPrime(n))
    {
      ret.push_back(std::make_pair(n,1));
      return ret;
    }
    for(auto i = 0; n > 1; ++i)
    {
      size_t count = 0;
      while(0 == n % primes[i])
      {
        n /= primes[i];
        count++;
      }
      if(count)
      {
        ret.push_back(std::make_pair(primes[i],count));
      }
    }
    return ret;
  }

};

namespace _MemoizedPrime
{
  MemoizedPrime mp;
}

bool isPrimeMemoized(ull n)
{
  return _MemoizedPrime::mp.isPrime(n);
}
/**
 * Returns a vector of prime factors
 */
std::vector<std::pair<ull, int> > getPrimeFactors(ull n)
{
  return _MemoizedPrime::mp.getPrimeFactors(n);
}

ull gcd(ull a, ull b)
{
  // this impl is not my own... found online a while back, can't find source
  while(b) b ^= a ^= b ^= a %= b;
  return a;
}

ull lcm(ull first, ull second)
{
  return first*second/gcd(first,second);
}
#endif //PRIMES_INCLUDES_GUARD
