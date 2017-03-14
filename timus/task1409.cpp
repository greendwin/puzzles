
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
   int n, m;
   cin >> n >> m;

   cout << m - 1 << " " << n - 1 << endl;

   return 0;
}
