
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

struct SEGMENT {
   int id;
   int x;
   int y;

   int contained;
   int prev;
   vector<int> subSegments;

   SEGMENT(void)
      : id(-1), x(0), y(0)
      , contained(0)
      , prev(-1)
   {}

   bool operator < (const SEGMENT & p) const {
      if (x != p.x) {
         return x < p.x;
      }

      return y > p.y;
   }
};

void ProcessSegments(vector<SEGMENT> & data, int & bestIdx, int & bestDepth)
{
   bestDepth = -1;
   bestIdx   = -1;

   for (int k = 0; k < data.size(); ++k) {
      SEGMENT & cur = data[k];

      if (bestDepth < cur.contained) {
         bestIdx   = k;
         bestDepth = cur.contained;
      }

      for (int index = k + 1; index < data.size(); ++index) {
         SEGMENT & next = data[index];
         if (next.x >= cur.y) {
            break;
         }

         if (cur.x >= next.x || cur.y <= next.y) {
            continue;
         }

         if (next.contained < cur.contained + 1) {
            next.contained = cur.contained + 1;
            next.prev      = k;
         }
      }
   }
}

int main(void)
{
   int count;
   cin >> count;

   vector<SEGMENT> data(count);
   for (int k = 0; k < count; ++k) {
      SEGMENT & cur = data[k];
      cur.id = k + 1;
      cin >> cur.x >> cur.y;
   }

   sort(data.begin(), data.end());

   int index, depth;
   ProcessSegments(data, index, depth);

   cout << depth + 1 << endl;
   while (index != -1) {
      const SEGMENT & cur = data[index];
      cout << cur.id << " ";
      index = cur.prev;
   }
   cout << endl;

   return 0;
}
