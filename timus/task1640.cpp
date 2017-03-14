
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
#include <cassert>
#include <cmath>

#pragma warning(disable : 4018)

#ifdef ONLINE_JUDGE
typedef long long          INT64;
typedef unsigned long long UINT64;
#else
typedef __int64            INT64;
typedef unsigned __int64   UINT64;
#endif

using namespace std;

double sqr(double x)
{
   return x * x;
}

int main(void)
{
   int count;
   cin >> count;

   vector<int> posX(count);
   vector<int> posY(count);

   int minX = 0;
   int minY = 0;

   for (int k = 0; k < count; ++k) {
      cin >> posX[k] >> posY[k];

      if (k == 0 || minX > posX[k]) {
         minX = posX[k];
      }
      if (k == 0 || minY > posY[k]) {
         minY = posY[k];
      }
   }

   minX -= 1;
   minY -= 1;

   double maxDist = 0;

   for (int k = 0; k < count; ++k) {
      double dist = sqrt(sqr(posX[k] - minX) + sqr(posY[k] - minY));

      if (dist > maxDist) {
         maxDist = dist;
      }
   }

   cout << minX << " " << minY << " " << fixed << setprecision(10) << maxDist;

   return 0;
}
