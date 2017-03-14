
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

INT64 GetVal(INT64 n)
{
   return n * (n - 1) / 2;
}

int main(void)
{
   int count;
   cin >> count;

   for (int k = 0; k < count; ++k) {
      int index;
      cin >> index;
      --index;

      int lo = 1;
      int hi = 100000;

      bool ok = false;

      while (hi - lo > 1) {
         int mid = (hi + lo) / 2;

         INT64 sum = GetVal(mid);
         if (sum == index) {
            ok = true;
            break;
         }

         if (sum < index) {
            lo = mid;
         } else {
            hi = mid;
         }
      }

      if (!ok) {
         ok = GetVal(lo) == index || GetVal(hi) == index;
      }

      cout << (ok ? 1 : 0) << " ";
   }

   cout << endl;

   return 0;
}
