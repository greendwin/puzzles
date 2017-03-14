
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

   vector<int> res(count * count);
   for (int k = 0; k < res.size(); ++k) {
      cin >> res[k];
   }

   int maxX = 2 * count - 1;
   for (int x = 0; x < maxX; ++x) {
      for (int y = 0; y < count; ++y) {
         int x0 = y;
         int y0 = x - y;

         if (x0 >= 0 && x0 < count && y0 >= 0 && y0 < count) {
            cout << res[x0 + y0 * count] << " ";
         }
      }
   }
   cout << endl;

   return 0;
}
