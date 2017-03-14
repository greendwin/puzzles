
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
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

struct PART {
   int first;
   int last;
   int odd;

   bool operator < (const PART & p) const {
      return first < p.first || first == p.first && last < p.last;
   }
};

enum {
   STATE_UNKNOWN,
   STATE_ODD,
   STATE_EVEN,
};

bool check(vector<PART> & parts)
{
   sort(parts.begin(), parts.end());

   map<int, int> states;
   typedef map<int, int>::iterator state_iterator;

   for (int k = 0; k < parts.size(); ++k) {
      const PART & cur = parts[k];

      state_iterator iter = states.find(cur.first - 1);
      if (iter != states.end()) {
         int odd = iter->second ^ cur.odd;

         iter = states.find(cur.last);
         if (iter == states.end()) {
            states.insert(make_pair(cur.last, odd));
         } else if (iter->second != odd) {
            return false;
         }

         continue;
      }

      if (k > 0 && parts[k - 1].first == cur.first || k + 1 < parts.size() && parts[k + 1].first == cur.first) {
         states.insert(make_pair(cur.first - 1, 0));
         --k;
      }
   }

   return true;
}

int main(void)
{
   bool stop = false;
   PART p;
   string res;

   vector<PART> parts;
   parts.reserve(5000);

   vector<PART> tmp;
   tmp.reserve(5000);

   for (;;) {
      parts.clear();

      int bitsCount  = 0;
      cin >> bitsCount;
      if (bitsCount == -1) {
         break;
      }

      int count = 0;
      cin >> count;

      for (int k = 0; k < count; ++k) {
         cin >> p.first >> p.last >> res;
         p.odd = (res == "odd");

         parts.push_back(p);
      }

      int lo     = 1;
      int hi     = count;

      tmp.clear();
      copy(parts.begin(), parts.end(), back_inserter(tmp));

      if (check(tmp)) {
         cout << count << endl;
         continue;
      }

      while (hi - lo > 1) {
         int mid = (hi + lo) / 2;
         
         tmp.clear();
         copy(parts.begin(), parts.begin() + mid, back_inserter(tmp));

         if (check(tmp)) {
            lo       = mid;
         } else {
            hi       = mid;
         }
      }

      cout << lo << endl;
   }

   return 0;
}
