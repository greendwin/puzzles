/************************************************************
 * TASK181.CPP                                     18.03.2008
 *
 * .
 ************************************************************/

#include <iostream>
#include <sstream>
#include <string>

const int MAX_VALUE = 1000;
int mark[MAX_VALUE + 1];
int seq[MAX_VALUE + 1];

using namespace std;

//#define GEN_TESTS

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
   int A, alpha, beta, gamma, M, k;
#ifndef GEN_TESTS
   cin >> A >> alpha >> beta >> gamma >> M >> k;
#else
   int counter = 0;
one_more:
   cout << string(32, 8) << ++counter;

   A = rand() % 10000;
   alpha = rand() % 100;
   beta = rand() % 100;
   gamma = rand() % 100;
   M = 1 + rand() % 1000;
   k = 1 + rand() % 10000;
#endif

   if (k == 0) {
      cout << A << endl;
      return 0;
   }

   memset(mark, 0xff, sizeof(mark));

   int cur = A % M;
   seq[0] = cur;
   mark[cur] = 0;

   int count = 1;

   int start;
   for (;;) {
      int next = (alpha * cur * cur + beta * cur + gamma) % M;
      if (mark[next] != -1) {
         start = mark[next];
         break;
      }

      mark[next] = count;
      seq[count++] = next;
      cur = next;
   }

   int res;
   if (k < start) {
      res = seq[k];
   } else {
      res = seq[start + (k - start) % (count - start)];
   }
#ifndef GEN_TESTS
   cout << res << endl;
#else
   
   cur = A % M;
   for (int i=1; i<=k; ++i) {
      cur = (cur * cur * alpha + cur * beta + gamma) % M;
   }

   if (res != cur) {
      cout << endl;
      cout << A << " " << alpha << " " << beta << " " << gamma << " " << M << " " << k << endl;
      cout << "res: " << res << endl;
      cout << "cor: " << cur << endl;
      system("pause");
   }
   goto one_more;
#endif

   return 0;
}

//
// End-of-file TASK181.CPP
//
