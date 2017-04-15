#ifndef DIGITS_INCLUDES_GUARD
#define DIGITS_INCLUDES_GUARD
#include <types.h>
#include <debug.h>
size_t numDigitsDecimal(ll x)
{
    if(x < 0) x = x * -1;
    size_t ret = 0;
    for(;x > 0;x/=10)
    {
        ret++;
    }
    return ret;
}

size_t numDigitsBinary(ll x)
{
    if(x < 0) x = x * -1;
    size_t ret = 0;
    for(;x > 0;x/=2)
    {
        ret++;
    }
    return ret;
}
#endif //DIGITS_INCLUDES_GUARD

