
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

int sum(int val)
{
   int res = val % 10;
   val /= 10;
   res += val % 10;
   val /= 10;
   res += val % 10;
   return res;
}

int main(void)
{
   int num;
   cin >> num;

   int left  = sum(num / 1000);
   int right = sum(num % 1000);

   if (left > right) {
      ++num;
   } else {
      --num;
   }

   left  = sum(num / 1000);
   right = sum(num % 1000);
   if (left == right) {
      cout << "Yes" << endl;
   } else {
      cout << "No" << endl;
   }

   return 0;
}
