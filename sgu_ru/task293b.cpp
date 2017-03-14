/************************************************************
* TASK293.CPP                                     20.03.2008
*
* .
************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

const int MAX_COUNT = 2005;
const int MAX_SEQ = 2 * MAX_COUNT;

int seq[MAX_SEQ];
int answL[MAX_SEQ];
int answR[MAX_SEQ];

/*#define MY_DEBUG /*

#define GEN_TESTS
/**/

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
#ifdef MY_DEBUG
   string test = "6 CQCCCQQQCCQ";
   cout << test << endl;
   istringstream cin(test);
#endif
#ifdef GEN_TESTS
   int counter_ = 0;
   vector<int> arr;

one_more:
   cout << string(32, 8) << ++counter_;

   ostringstream tmp;

   int n_ = 1 + rand() % 6;
   tmp << n_ << endl;

   int count_ = (n_ << 1) - 1;
   arr.resize(count_);
   for (int i=0; i<count_; ++i) {
      arr[i] = rand() % 2 ? 'Q' : 'C';
      tmp << (char)arr[i];
   }

   istringstream cin(tmp.str());
#endif

   int n;
   cin >> n;

   const int count = (n << 1) - 1;
   for (int i=0; i<count; ++i) {
      char ch;
      cin >> ch;
      seq[i] = ch;
   }

#ifdef GEN_TESTS
   memset(answL, 0, sizeof(answL));
   memset(answR, 0, sizeof(answR));
#endif

   int answ = 1;

   const int A = 'Q';

   int As = (seq[0] == A);
   int pos = 1;

   for (int step=2; step<=n; ++step) {
      const int step_2 = (step << 1) - 1;

#ifdef MY_DEBUG
      cout << "+" << (char)seq[pos] << (char)seq[pos + 1] << endl;
      for (int i=0; i<step_2; ++i) {
         cout << (char)seq[i];
      }
      cout << endl;
#endif

      As += seq[pos++] == A;
      As += seq[pos++] == A;

      const int Bs = step_2 - As;

      int answRem = 2;

      // check center
      int CCC = A;
      const int center = step_2 >> 1;
      if (Bs & 1) {
         CCC = (A == 'Q') ? 'C' : 'Q';
      }

      if (seq[center] != CCC) {
         int leftWeight = 0;
         int rightWeight = 0;
         int lastLeft;
         int lastRight;

         for (int left = 0, right = step_2 - 1; left < right; ++left, --right) {
            if (seq[left] != seq[right]) {
               if (seq[left] == CCC) {
                  ++leftWeight;
                  lastLeft = left;
               } else {
                  ++rightWeight;
                  lastRight = right;
               }
            }
         }

         if (leftWeight > rightWeight) {
            answL[answ] = lastLeft;
            answR[answ] = center;
            ++answ;
            --answRem;
            swap(seq[lastLeft], seq[center]);
         } else {
            answL[answ] = center;
            answR[answ] = lastRight;
            ++answ;
            --answRem;
            swap(seq[center], seq[lastRight]);
         }

#ifdef MY_DEBUG
         cout << 1 + answL[answ - 1] << " " << 1 + answR[answ - 1] << endl;

         for (int i=0; i<step_2; ++i) {
            cout << (char)seq[i];
         }
         cout << endl;
#endif
      }

      // swap if needed
      int left = 0;
      int right = step_2 - 1;
      while (left < right) {
         if (seq[left] != seq[right]) {
            if (answRem <= 0) {
#ifndef GEN_TESTS
               cout << "He" << endl;
               return 0;
#else
               cout << endl << "He" << endl << tmp.str() << endl;
               //system("pause");
               goto one_more;
#endif
            }

            const int l0 = left;
            const int r0 = right;

            do {
               ++left;
               --right;
            } while (left < right && seq[left] == seq[right]);

            if (seq[l0] != seq[left]) {
               answL[answ] = l0;
               answR[answ] = left;
               swap(seq[l0], seq[left]);
               ++answ;
               --answRem;
            } else {
               answL[answ] = l0;
               answR[answ] = right;
               swap(seq[l0], seq[right]);
               ++answ;
               --answRem;
            }

            // restore left & right
            left  = l0;
            right = r0;

#ifdef MY_DEBUG
            for (int i=0; i<step_2; ++i) {
               cout << (char)seq[i];
            }
            cout << endl;
#endif
         }

         ++left;
         --right;
      }

      // correct swaps
      answ += answRem;
      if (answR[answ-2] == step_2 - 1) {
         swap(answL[answ-2], answL[answ-1]);
         swap(answR[answ-2], answR[answ-1]);
      }
   }

#ifndef GEN_TESTS
   cout << "Qc" << endl;
   for (int i=0; i<count; ++i) {
      if (answL[i] == answR[i]) {
         cout << "0 0" << endl;
         continue;
      }

      cout << 1 + answL[i] << " " << 1 + answR[i] << endl;
   }
#else
   for (int i=0; i<count_; ++i) {
      if (i % 2 == 1) {
         int left = 0;
         int right = i - 1;
         while (left < right && arr[left] == arr[right]) {
            ++left;
            --right;
         }

         if (left < right) {
            cout << endl << "Incorrect" << endl;
            goto error;
         }
      }

      if (answL[i] == answR[i]) {
         if (answL[i] != 0) {
            cout << endl << "Mismatch" << endl;
            goto error;
         }
         continue;
      }

      swap(arr[answL[i]], arr[answR[i]]);
   }

   int left = 0;
   int right = count_ - 1;
   while (left < right && arr[left] == arr[right]) {
      ++left;
      --right;
   }

   if (left < right) {
      cout << endl << "Incorrect" << endl;
      goto error;
   }

   goto one_more;

error:
   cout << tmp.str() << endl;
   system("pause");
   goto one_more;
#endif

   return 0;
}

//
// End-of-file TASK293.CPP
//
