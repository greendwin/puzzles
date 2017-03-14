
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <deque>
#include <queue>
#include <algorithm>
#include <iterator>
#include <cmath>
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
   map<int, int> numbers;
   int res = 0;

   for (int index = 0; index < 3; ++index) {
      int count;
      cin >> count;

      for (int k = 0; k < count; ++k) {
         int val;
         cin >> val;

         int curCount = ++numbers[val];
         if (curCount == 3) {
            ++res;
         }
      }
   }

   cout << res << endl;

   return 0;
}
