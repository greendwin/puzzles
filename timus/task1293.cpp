
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
   // task 1293
   //int n, a, b;
   //cin >> n >> a >> b;
   //cout << 2 * n * a * b << endl;

   // task1264
   int n, m;
   cin >> n >> m;
   cout << n * (m + 1) << endl;

   return 0;
}
