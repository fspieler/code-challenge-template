#ifndef CHALLENGE_INCLUDES_INCLUDES_GUARDS
#define CHALLENGE_INCLUDES_INCLUDES_GUARDS

#include <ccct_debug.h>
#include <ccct_primes.h>

//define quick for-loop macros
#define range(x,n) for(x = 0; x<n; x++)
#define ranged(x,n) for(int x = 0; x<n; x++)

//define types
#define ll long long

#include <vector>
#include <cmath>
#include <algorithm>

template<typename T>
T gcd(T a, T b)
{
    while(b) b ^= a ^= b ^= a %= b;
    return a;
}


#endif //CHALLENGE_INCLUDES_INCLUDES_GUARDS
