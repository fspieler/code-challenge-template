#include <ccct_debug.h>


int testee(int a)
{
  return 2*a;
}

int testee2(int a, int b, int c, int d, int e, int f)
{
  return a + b + c + d + e + f;
}

int main(int argc, char** argv)
{
  int i = 4;
  DEBUG(i);
  DEBUGF(testee2,1,2,3,i,5,6);
}
