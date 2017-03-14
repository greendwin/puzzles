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

/**************************************************************************
* GetPosA()                                                               *
*                                                                         *
**************************************************************************/
int GetPosA(int index, int As, int Bs)
{
   const int As_2 = As >> 1;
   if (index < As_2) {
      return index;
   }
   
   const int As_odd = As & 1;
   if (As_odd && index == As_2) {
      return (As + Bs) >> 1;
   }

   return Bs + index;
}

/**************************************************************************
* GetPosB()                                                               *
*                                                                         *
**************************************************************************/
int GetPosB(int index, int As, int Bs)
{
   const int As_2 = As >> 1;
   const int Bs_2 = Bs >> 1;
   if (index < Bs_2) {
      return As_2 + index;
   }

   const int Bs_odd = Bs & 1;
   if (Bs_odd && index == Bs_2) {
      return As_2 + Bs_2;
   }

   return As_2 + (As & 1) + index;
}

const int MAX_COUNT = 2005;
const int MAX_SEQ = 2 * MAX_COUNT;

int seq[MAX_SEQ];

#define MY_DEBUG /*

#define GEN_TESTS
/**/

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
#ifdef MY_DEBUG
   string test = "6 QQCCCQCCQQQ";
   cout << test << endl;
   istringstream cin(test);
#endif
#ifdef GEN_TESTS
   int counter_ = 0;
   vector<int> arr;
   vector<int> answLeft, answRight;

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

   answLeft.clear();
   answLeft.resize(count_ - 1, 0);
   answRight.clear();
   answRight.resize(count_ - 1, 0);

   istringstream cin(tmp.str());
#endif

   int n;
   cin >> n;

   const int count = (n << 1) - 1;
   int Qs = 0, Cs = 0;
   for (int i=0; i<count; ++i) {
      char ch;
      cin >> ch;
      seq[i] = ch;
      Qs += seq[i] == 'Q';
      Cs += seq[i] == 'C';
   }

   const int A_0 = Qs < Cs ? 'Q' : 'C';

#ifndef GEN_TESTS
   cout << "Qc" << endl;
   cout << "0 0" << endl;
#endif
   
   int As = seq[0] == A_0;
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

      As += seq[pos++] == A_0;
      As += seq[pos++] == A_0;
      
      const int Bs = step_2 - As;

      int answL[2] = { 0, 0 };
      int answR[2] = { 0, 0 };
      int answ = 0;

      int A_i = 0;
      int B_i = 0;
      for (int i=0; i<step_2 && answ < 2; ++i) {
         if (seq[i] == A_0) {
            int pos = GetPosA(A_i, As, Bs);
            if (pos == i) {
               ++A_i;
               continue;
            }

            int A_i_tmp = A_i;
            while (seq[pos] == A_0) {
               ++A_i_tmp;
               pos = GetPosA(A_i_tmp, As, Bs);
            }
            answL[answ] = i;
            answR[answ] = pos;
            
            ++answ;
            swap(seq[i], seq[pos]);
            ++B_i;
            
            continue;
         }

         int pos = GetPosB(B_i, As, Bs);
         if (pos == i) {
            ++B_i;
            continue;
         }

         int B_i_tmp = B_i;
         while (seq[pos] != A_0) {
            ++B_i_tmp;
            pos = GetPosB(B_i_tmp, As, Bs);
         }
         answL[answ] = i;
         answR[answ] = pos;
         ++answ;
         swap(seq[i], seq[pos]);

         ++A_i;
      }

      while (answ < 2) {
         answL[answ] = answR[answ] = 0;
         ++answ;
      }

      if (answR[answ] == step_2) {
         swap(answL[0], answL[1]);
         swap(answR[0], answR[1]);
      }

      for (int i=0; i<2; ++i) {
#ifndef GEN_TESTS
         if (answL[i] == answR[i]) {
            cout << "0 0" << endl;
            continue;
         }

         cout << 1 + answL[i] << " " << 1 + answR[i] << endl;
#else
         answLeft [(step - 2) * 2 + i] = answL[i];
         answRight[(step - 2) * 2 + i] = answR[i];
#endif
      }

#ifdef MY_DEBUG
      for (int i=0; i<step_2; ++i) {
         cout << (char)seq[i];
      }
      cout << endl;
#endif
   }

#ifdef GEN_TESTS
   for (int i=0; i<count_ - 1; ++i) {
      if (i % 2 == 0) {
         int left = 0;
         int right = i;
         while (left < right && arr[left] == arr[right]) {
            ++left;
            --right;
         }

         if (left < right) {
            cout << endl << "Incorrect" << endl;
            goto error;
         }
      }

      if (answLeft[i] == answRight[i]) {
         if (answLeft[i] != 0) {
            cout << endl << "Mismatch" << endl;
            goto error;
         }
         continue;
      }

      swap(arr[answLeft[i]], arr[answRight[i]]);
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
