
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>
#include <cassert>

#ifdef ONLINE_JUDGE
   typedef long long          INT64;
   typedef unsigned long long UINT64;
#else
   typedef __int64            INT64;
   typedef unsigned __int64   UINT64;
#endif

using namespace std;

enum PART_CMP {
   PC_FIRST,
   PC_LAST,
};

struct PART {
   int first;
   int last;
   int odd;

   PART_CMP cmp;

   bool operator < (const PART & p) const {
      if (cmp == PC_FIRST) {
         return first < p.first;
      } 
      if (cmp == PC_LAST) {
         return last < p.last;
      }
      return false;
   }

   bool operator == (const PART & p) const {
      return first == p.first && last == p.last;
   }
};

ostream & operator << (ostream & output, const PART & p)
{
   return output << p.first << " " << p.last << (p.odd ? " odd" : " even");
}

map<PART, int> leftParts;
map<PART, int> rightParts;
typedef map<PART, int>::iterator part_iterator;

void remove_both(PART & p)
{
   p.cmp = PC_FIRST;
   size_t res = leftParts.erase(p);
   assert(res == 1);

   p.cmp = PC_LAST;
   res = rightParts.erase(p);
   assert(res == 1);
}

bool try_push(PART p)
{
   queue<PART> toProcess;
   toProcess.push(p);

   while (!toProcess.empty()) {
      PART cur = toProcess.front();
      toProcess.pop();

      cur.cmp = PC_FIRST;
      part_iterator left = leftParts.find(cur);
      if (left != leftParts.end() && left->first == cur) {
         if (left->first.odd != cur.odd) {
            return false;
         }
         continue;
      }

      if (left != leftParts.end()) {
         PART next = left->first;
         remove_both(next);

         if (cur.last > next.last) {
            swap(cur, next);
         }

         next.first = cur.last + 1;
         next.odd   ^= cur.odd;

         toProcess.push(cur);
         toProcess.push(next);
         continue;
      }

      cur.cmp = PC_LAST;
      part_iterator right = rightParts.find(cur);
      if (right != rightParts.end()) {
         PART next = right->first;
         remove_both(next);

         if (cur.first > next.first) {
            swap(cur, next);
         }

         cur.last = next.first - 1;
         cur.odd  ^= next.odd;

         toProcess.push(cur);
         toProcess.push(next);
         continue;
      }

      cur.cmp = PC_FIRST;
      leftParts.insert(make_pair(cur, 0));

      cur.cmp = PC_LAST;
      rightParts.insert(make_pair(cur, 0));
   }

   return true;
}

void main(void)
{
   for (;;) {
      int bitsCount  = 0;
      cin >> bitsCount;
      if (bitsCount == -1) {
         break;
      }

      int count = 0;
      cin >> count;

      bool failed = false;
      int correct = count;
      leftParts.clear();
      rightParts.clear();

      for (int k = 0; k < count; ++k) {
         int first, last;
         string res;
         cin >> first >> last >> res;

         PART p;
         p.first = first;
         p.last  = last;
         p.odd   = res == "odd";

         if (!failed && !try_push(p)) {
            correct = k;
            failed  = true;
         }
      }

      for (part_iterator iter = leftParts.begin(); iter != leftParts.end(); ++iter) {
         cout << "> " << iter->first << endl;
      }

      cout << correct << endl;
   }
}
