/************************************************************
 * TASK186.CPP                                     19.03.2008
 *
 * .
 ************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//#define GEN_TESTS

/**************************************************************************
* Calc()                                                                  *
*                                                                         *
**************************************************************************/
int Calc(int n, int ones)
{
   if (n <= 1) {
      return 0;
   }
   if (ones == 0) {
      return n - 1;
   }

   return Calc(n - 2, ones - 1) + 1;
}

#ifdef GEN_TESTS
int seq[100];
int used[100];

/**************************************************************************
* FindMin()                                                               *
*                                                                         *
**************************************************************************/
int FindMin(vector<int> & arr, int left, int right)
{
   if (right - left + 1 <= 1) {
      return 0;
   }

   int minVal = 10000000;
   
   for (int i=left + 1; i<right; ++i) {
      int item = arr[seq[i]];
      
      int val = 1;
      if (item == 1) {
         val += FindMin(arr, left, i - 1);
         val += FindMin(arr, i + 1, right);
      } else {
         val += FindMin(arr, left, i);
         val += FindMin(arr, i + 1, right);

         int newVal = 1;
         newVal += FindMin(arr, left, i - 1);
         newVal += FindMin(arr, i, right);

         val = min(val, newVal);
      }

      if (minVal > val) {
         minVal = val;
      }
   }

   return minVal;
}

/**************************************************************************
* FindBetter()                                                            *
*                                                                         *
**************************************************************************/
bool FindBetter(int depth, vector<int> & arr, int res)
{
   if (depth != (int)arr.size()) {
      for (int i=0; i<(int)arr.size(); ++i) {
         if (used[i]) {
            continue;
         }

         used[i] = true;
         seq[depth] = i;
         if (FindBetter(depth + 1, arr, res)) {
            used[i] = false;
            return true;
         }
         used[i] = false;
      }

      return false;
   }

   int min = FindMin(arr, 0, (int)arr.size() - 1);
   if (min < res) {
      cout << endl << min << " < " << res << endl;
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
#ifdef GEN_TESTS
   int counter = 0;
   vector<int> arr;
one_more:
   cout << string(32, 8) << ++counter;
   int num = rand() % 9;
   arr.resize(num);
   ostringstream tmp;
   tmp << num << endl;
   for (int i=0; i<num; ++i) {
      arr[i] = 1 + rand() % 2;
      tmp << arr[i] << " ";
   }
   tmp << endl;
   istringstream cin(tmp.str());
#endif

   int n;
   cin >> n;

   int ones = 0;
   for (int i=0; i<n; ++i) {
      int val;
      cin >> val;
      if (val == 1) {
         ++ones;
      }
   }

   int res = Calc(n, ones);
#ifndef GEN_TESTS
   cout << res << endl;
#else
   //if (counter == 117) {
   //   int a = 0;
   //}

   if (FindBetter(0, arr, res)) {
      cout << tmp.str() << endl;
      system("pause");
   }
   goto one_more;
#endif

   return 0;
}

//
// End-of-file TASK186.CPP
//
