/************************************************************
 * TASK299.CPP                                     18.03.2008
 *
 * .
 ************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_DIGS = 500;

struct NUMBER {
   int digs[MAX_DIGS + 1];
   int count;

   void Read(istream & input) {
      count = 0;

      for (;;) {
         int ich = input.get();
         if (!isdigit(ich)) {
            if (count > 0) {
               break;
            }
            continue;
         }
         digs[count++] = char_traits<char>::to_char_type(ich) - '0';
      }

      reverse(digs, digs + count);
   }

   int Compare(const NUMBER & p) const {
      if (count != p.count) {
         return count - p.count;
      }

      for (int i=count - 1; i>=0; --i) {
         if (digs[i] != p.digs[i]) {
            return digs[i] - p.digs[i];
         }
      }

      return 0;
   }

   void Add(const NUMBER & p, NUMBER & sum) const {
      int m = min(count, p.count);

      memset(&sum, 0, sizeof(sum));

      int add = 0;
      for (int i=0; i<m; ++i) {
         int & val = sum.digs[i];
         val = digs[i] + p.digs[i] + add;
         
         if (val >= 10) {
            add = 1;
            val -= 10;
         } else {
            add = 0;
         }
      }

      if (count < p.count) {
         for (int i=m; i<p.count; ++i) {
            int & val = sum.digs[i];

            val += add + p.digs[i];
            if (val > 10) {
               val -= 10;
               add = 1;
            } else {
               add = 0;
            }
         }
         sum.count = p.count + add;
      } else if (count > p.count) {
         for (int i=m; i<count; ++i) {
            int & val = sum.digs[i];

            val += add + digs[i];
            if (val > 10) {
               val -= 10;
               add = 1;
            } else {
               add = 0;
            }
         }
         sum.count = count + add;
      } else {
         sum.digs[m] = add;
         sum.count = m + add;
      }
   }
};

/**************************************************************************
* operator <<()                                                           *
*                                                                         *
**************************************************************************/
ostream & operator << (ostream & output, const NUMBER & p)
{
   for (int i=p.count - 1; i >= 0; --i) {
      output << p.digs[i];
   }
   return output;
}

const int MAX_COUNT = 1000;
NUMBER nums[MAX_COUNT];
int indices[MAX_COUNT];

struct IndLess {
   bool operator () (int a, int b) const {
      return nums[a].Compare(nums[b]) < 0;
   }
};

//#define GEN_TESTS

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
#if 0
   istringstream cin("7 1 2 6 4 8 100 73");
#endif
#ifdef GEN_TESTS
   int counter_ = 0;
one_more:
   cout << string(32, 8) << ++counter_;

   vector<int> arr;
   ostringstream tmp;
   int n_ = 3 + rand() % 950;
   tmp << n_ << endl;
   for (int i=0; i<n_; ++i) {
      arr.push_back(1 + rand() % 10);
      tmp << arr[i] << endl;
   }
   istringstream cin(tmp.str());
#endif

   int n;
   cin >> n;

   for (int i=0; i<n; ++i) {
      nums[i].Read(cin);

      indices[i] = i;
   }

   sort(indices, indices + n, IndLess());

   for (int i=2; i<n; ++i) {
      NUMBER & a = nums[indices[i-2]];
      NUMBER & b = nums[indices[i-1]];
      NUMBER & c = nums[indices[i]];

      NUMBER sum;
      a.Add(b, sum);

      if (sum.Compare(c) > 0) {
#ifndef GEN_TESTS
         cout << nums[indices[i-2]] << " " << nums[indices[i-1]] << " " << nums[indices[i]] << endl;
#else
         if (arr[indices[i-2]] + arr[indices[i-1]] <= arr[indices[i]]
         || arr[indices[i-2]] > arr[indices[i-1]]
         || arr[indices[i-1]] > arr[indices[i]]) {
            cout << endl << tmp.str();
            cout << "Wrong: " << i << ": " << indices[i-2] << " " << indices[i-1] << " " << indices[i] << endl;
            system("pause");
         }
         goto one_more;
#endif
         return 0;
      }
   }

#ifdef GEN_TESTS
   for (int i=0; i<n; ++i) {
      for (int j=0; j<n; ++j) {
         for (int k=0; k<n; ++k) {
            if (i == j || j == k || i == k) {
               continue;
            }
            if (arr[i] <= arr[k] && arr[j] <= arr[k] && arr[i] + arr[j] > arr[k]) {
               cout << endl << tmp.str();
               cout << "Wrong: 0 0 0" << endl;
               cout << "Should: " << i << " " << j << " " << k << endl;
               system("pause");
            }
         }
      }
   }

   goto one_more;
#endif

   cout << "0 0 0" << endl;

   return 0;
}

//
// End-of-file TASK299.CPP
//
