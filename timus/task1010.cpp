
#include <iostream>

#ifdef ONLINE_JUDGE
   typedef long long          INT64;
   typedef unsigned long long UINT64;
#else
   typedef __int64            INT64;
   typedef unsigned __int64   UINT64;
#endif

using namespace std;

void main(void)
{
   int count = 0;
   cin >> count;

   int cur, next;
   cin >> cur >> next;

   int bestN = 1;
   INT64 bestDiff = abs((INT64)cur - (INT64)next);

   for (int k = 2; k < count; ++k) {
      cur = next;
      cin >> next;

      INT64 diff = abs((INT64)cur - (INT64)next);
      if (bestDiff < diff) {
         bestDiff = diff;
         bestN    = k;
      }
   }

   cout << bestN << " " << bestN + 1 << endl;
}
