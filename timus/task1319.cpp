
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
   int count;
   cin >> count;

   int index = 0;
   vector<int> res(count * count);
   for (int x = 0; x < 2 * count - 1; ++x) {
      for (int y = 0; y < 2 * count - 1; ++y) {
         int x0 = count - x - 1 + y;
         int y0 = y;

         if (x0 >= 0 && x0 < count && y0 >= 0 && y0 < count) {
            res[x0 + y0 * count] = ++index;
         }
      }
   }

   for (int k = 0; k < count; ++k) {
      for (int p = 0; p < count; ++p) {
         cout << res[p + k * count] << " ";
      }
      cout << endl;
   }

   return 0;
}
