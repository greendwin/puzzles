
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

struct {
   int count;
   const char * msg;
} messages[] = {
   { 1000, "legion" },
   {  500, "zounds" },
   {  250, "swarm"  },
   {  100, "throng" },
   {   50, "horde"  },
   {   20, "lots"   },
   {   10, "pack"   },
   {    5, "several" },
   {    1, "few"    },
};

int main(void)
{
   int count;
   cin >> count;

   for (int k = 0; k < _countof(messages); ++k) {
      if (count >= messages[k].count) {
         cout << messages[k].msg << endl;
         break;
      }
   }

   return 0;
}
