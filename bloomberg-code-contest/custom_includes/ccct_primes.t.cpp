#include <ccct_primes.h>
#include <iostream>

using namespace std;

void test_isPrime(long long n, bool expected)
{
  cout << n << (expected ? " is" : " is not" )
    << " prime, returns:" << (isPrimeMemoized(n) ? " prime." : " not prime.") << endl;
}

int main()
{
  for(unsigned i = 0; i < 1'000'000'000; ++i)
  {
    bool ipm = isPrimeMemoized(i);
    bool ip = isPrime(i);
    if(ip != ipm)
      std::cout << "Disagreement about " << i << ", " << "isPrimeMemoized says " << (ipm ? "prime." : "not prime.") << std::endl;  
  }
  test_isPrime(25,false);
  DEBUG(_isPrimeMemoized::primes);
#if 0
  test_isPrime(982'451'653,true);
  test_isPrime(9,false);
  test_isPrime(86'028'121,true);
  test_isPrime(1,false);
  test_isPrime(2,true);
  test_isPrime(3,true);
  test_isPrime(4,false);
  test_isPrime(13,true);
#endif
}
