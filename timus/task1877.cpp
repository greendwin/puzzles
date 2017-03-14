
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <deque>
#include <queue>
#include <algorithm>
#include <iterator>
#include <cassert>

#pragma warning(disable : 4018)

#ifdef ONLINE_JUDGE
typedef long long          INT64;
typedef unsigned long long UINT64;
#else
typedef __int64            INT64;
typedef unsigned __int64   UINT64;
#endif

using namespace std;

int main(void)
{
   int n, m;
   cin >> n >> m;

   // task 1877
   //if (n % 2 == 0 || m % 2 == 1) {
   //   cout << "yes" << endl;
   //} else {
   //   cout << "no" << endl;
   //}

   // task 1820
   int res = 0;
   int a = n; // both sides raw
   int b = 0; // one side is cooked

   while (a + b > 0) {
      int subA = min(a, m);
      int subB = min(b, m - subA);

      a -= subA;
      b += subA - subB;
      ++res;
   }

   cout << res << endl;

   return 0;
}
