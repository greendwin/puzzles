
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
   int limit, count;
   cin >> limit >> count;

   int waiting = 0;
   for (int k = 0; k < count; ++k) {
      int val;
      cin >> val;

      waiting += val;
      waiting -= min(waiting, limit);
   }

   cout << waiting << endl;

   return 0;
}
