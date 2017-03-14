/************************************************************
 * TASK259.CPP                                     17.03.2008
 *
 * .
 ************************************************************/

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct TASK {
   int index;
   int value;
   int mask[4];
};

const int MAX_TASKS = 100;
int T[MAX_TASKS];
int L[MAX_TASKS];

const int MAX_VALUE = MAX_TASKS * 1000 + 1;
TASK solution[MAX_VALUE];

//#define GEN_TESTS

#ifdef GEN_TESTS
bool FindBetter(int * newSol, int depth, int count, int * mask, int foundRes)
{
   if (depth < count) {
      for (int i=0; i<count; ++i) {
         if (mask[i >> 5] & (1 << (i & 0x1f))) {
            continue;
         }

         mask[i >> 5] |= 1 << (i & 0x1f);
         newSol[depth] = i;
         if (FindBetter(newSol, depth + 1, count, mask, foundRes)) {
            return true;
         }
         mask[i >> 5] &= ~(1 << (i & 0x1f));
      }
      return false;
   }

   int maxVal = 0;
   int cur = 0;
   for (int i=0; i<count; ++i) {
      cur += T[newSol[i]];
      if (maxVal < cur + L[newSol[i]]) {
         maxVal = cur + L[newSol[i]];
      }
   }

   if (maxVal < foundRes) {
      cout << endl;
      for (int i=0; i<count; ++i) {
         cout << newSol[i] << " ";
      }
      cout << endl << maxVal << endl;
      return true;
   }

   return false;
}
#endif

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
#if 0
   istringstream cin("2 2 1 1 4");
#elif 1
//   0 1 3 2
//      102
//Task:
   istringstream cin("4 "
      "38 8 38 8 "
      "34 4 10 46 ");

//Incorrect: 126
#endif
#ifdef GEN_TESTS
   int counter = 0;
one_more:
   cout << string(32, 8) << ++counter;

   int count_ = 1 + rand() % 4;
   ostringstream tmp;
   tmp << count_ << endl;
   for (int i=0; i<count_; ++i) {
      tmp << 1 + rand() % 50 << " " << 1 + rand() % 50 << " ";
   }
   istringstream cin(tmp.str());
#endif

   int n;
   cin >> n;
   int count = 0;
   for (int i=0; i<n; ++i) {
      cin >> T[i];
      count += T[i];
   }
   for (int i=0; i<n; ++i) {
      cin >> L[i];
   }

   memset(solution + 1, 0xff, sizeof(TASK) * count);

   for (int index=0; index<=count; ++index) {
      TASK & cur = solution[index];

      if (cur.index < 0) {
         continue;
      }

      for (int i=0; i<n; ++i) {
         const int newIndex = index + T[i];
         if (newIndex > count || cur.mask[i >> 5] & (1 << (i & 0x1f))) {
            continue;
         }

         TASK t = cur;
         t.index = i;
         t.mask[i >> 5] |= 1 << (i & 0x1f);
         t.value = index + max(cur.value - index, T[i] + L[i]);

         TASK & newSol = solution[newIndex];
         if (newSol.index < 0 || newSol.value > t.value) {
            newSol = t;
         }
      }
   }

#ifndef GEN_TESTS
   cout << solution[count].value << endl;
#else
   int newSol[MAX_TASKS];
   int mask[4];
   memset(mask, 0, sizeof(mask));
   if (FindBetter(newSol, 0, n, mask, solution[count].value)) {
      cout << "Task:" << endl;
      cout << tmp.str() << endl;
      cout << "Incorrect: " << solution[count].value << endl;
      system("pause");
   }
   goto one_more;
#endif

   return 0;
}

//
// End-of-file TASK259.CPP
//
