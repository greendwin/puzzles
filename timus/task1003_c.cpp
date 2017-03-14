
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
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

map<int, bool> exists;
map<int, bool> odd;
map<int, int>  nextVal;

bool add(int a, int b, bool curOdd)
{
   if (!exists[a]) {
      exists[a] = true;
      odd[a] = curOdd;
      nextVal[a] = b;
      return true;
   }

   int prevB = nextVal[a];

   if (b == prevB) {
      return odd[a] == curOdd;
   }

   if (b > prevB) {
      return add(prevB + 1, b, curOdd ^ odd[a]);
   }

   bool prevOdd = odd[a];
   nextVal[a] = b;
   odd[a]  = curOdd;
   return add(b + 1, prevB, prevOdd ^ curOdd);
}

int main(void)
{
   for (;;) {
      int numBits;
      cin >> numBits;

      if (numBits == -1) {
         break;
      }

      int count;
      cin >> count;

      exists.clear();
      odd.clear();
      nextVal.clear();

      int last = -1;
      for (int k = 0; k < count; ++k) {
         int a, b ;
         string res;
         cin >> a >> b >> res;
         if (last != -1) {
            continue;
         }

         if (!add(a, b, res == "odd")) {
            last = k;
         }
      }

      cout << (last == -1 ? count : last) << endl;
   }

   return 0;
}
