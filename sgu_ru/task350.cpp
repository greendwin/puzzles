/************************************************************
 * TASK350.CPP                                     17.03.2008
 *
 * .
 ************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

struct ITEM;

ITEM * root;

struct ITEM {
   int val;

   ITEM * prev;
   ITEM * next;

   bool operator < (const ITEM & p) const {
      return val < p.val;
   }

   bool IsRemoved(void) const {
      return prev == NULL && next == NULL && root != this;
   }

   void Remove(void) {
      if (prev == NULL) {
         if (root == this) {
            root = next;
         }
      } else {
         prev->next = next;
      }
      if (next != NULL) {
         next->prev = prev;
      }

      prev = next = NULL;
   }
};

int COUNT;
const int MAX_COUNT = 100;
ITEM items[MAX_COUNT + 1];

/**************************************************************************
* Lookup()                                                                *
*                                                                         *
**************************************************************************/
ITEM * Lookup(int val)
{
   int lo = 0, hi = COUNT - 1;
   while (hi - lo > 1) {
      int mid = (lo + hi) >> 1;

      if (val < items[mid].val) {
         hi = mid;
      } else if (val > items[mid].val) {
         lo = mid;
      } else {
         return items + mid;
      }
   }

   if (items[lo].val == val) {
      return items + lo;
   }
   return items + hi;
}

ITEM * res[MAX_COUNT];

/**************************************************************************
* Clean()                                                                 *
*                                                                         *
**************************************************************************/
void Clean(int count, int & rem)
{
   for (int i=0; i < count - 1; ++i) {
      const int xor = res[i]->val ^ res[count-1]->val;
      
      ITEM * tmp = Lookup(xor);
      if (tmp->IsRemoved()) {
         continue;
      }

      tmp->Remove();
      --rem;

      ITEM * pending[MAX_COUNT];
      int to_remove = 0;

      for (ITEM * it1 = root; it1 != NULL; it1 = it1->next) {
         for (ITEM * it2 = it1->next; it2 != NULL; it2 = it2->next) {
            if ((it1->val ^ it2->val) == xor) {
               pending[to_remove++] = it1;
               it2->Remove();
               rem -= 2;
               break;
            }
         }
      }

      for (int k=0; k<to_remove; ++k) {
         pending[k]->Remove();
      }
   }
}

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
#ifndef ONLINE_JUDGE
#if 0
   istringstream cin(
      "6 "
      "30 19 66 13 92 81");
#elif 0
   istringstream cin(
      "3 "
      "15 2 13");
#elif 0
   string test;
   const int test_count = 30;
   {
      ostringstream tmp;

      int count = test_count;
      tmp << count * (count - 1) / 2 << endl;
      cout << count * (count - 1) / 2 << endl;
      for (int i=0; i<count; ++i) {
         for (int j=i+1; j<count; ++j) {
            tmp << ((1 << i) | (1 << j)) << " ";
            cout << ((1 << i) | (1 << j)) << " ";
         }
      }
      cout << endl;
      test = tmp.str();
   }
   istringstream cin(test);
#endif
#endif

   cin >> COUNT;
   for (int i=0; i<COUNT; ++i) {
      cin >> items[i].val;
   }
   sort(items, items + COUNT);

   for (int i=0; i<COUNT; ++i) {
      if (i > 0) {
         items[i].prev = items + i - 1;
      }
      if (i + 1 < COUNT) {
         items[i].next = items + i + 1;
      }
   }

   int rem = COUNT;
   root = items;

   if (rem <= 1) {
      cout << "0 " << root->val << endl;
      return 0;
   }

   // select a, b
   int count = 0;

   res[count++] = root;
   root->Remove();
   --rem;

   for (ITEM * cur = root; cur != NULL; cur = cur->next) {
      const int xor = res[0]->val ^ cur->val;
      ITEM * tmp = Lookup(xor);
      if (tmp->val == xor) {
         res[count++] = cur;
         cur->Remove();
         --rem;
         break;
      }
   }

   Clean(count, rem);

   while (rem > 1) {
      // find ax
      for (ITEM * cur = root; cur != NULL; cur = cur->next) {
         const int xor = res[0]->val ^ cur->val;
         ITEM * tmp = Lookup(xor);
         if (xor == tmp->val) {
            res[count++] = cur;
            cur->Remove();
            --rem;
            break;
         }
      }

      Clean(count, rem);
   }

   if (rem == 1) {
      res[count++] = root;
   }

   cout << "0 ";
   for (int i=0; i<count; ++i) {
      cout << res[i]->val << " ";
   }

#if 0 //ndef ONLINE_JUDGE
   if (count + 1 != test_count) {
      int a = 0;
   }
   for (int i=0; i<count + 1; ++i) {
      const int a = res[i] ? res[i]->val : 0;

      for (int j=i+1; j<count + 1; ++j) {
         const int b = res[j] ? res[j]->val : 0;
         const int xor = a ^ b;

         if (Lookup(xor)->val != xor) {
            int a = 0;
         }
      }
   }
   cout << "Done." << endl;
   system("pause");
#endif
}

//
// End-of-file TASK350.CPP
//
