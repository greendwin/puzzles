/************************************************************
 * TASK231.CPP                                     21.03.2008
 *
 * .
 ************************************************************/

#include <iostream>

using namespace std;

const int MAX_COUNT = 1000001;
char mark[MAX_COUNT];
const int MAX_RES = 10000;
int resVals[MAX_RES];

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
   int n;
   cin >> n;

   mark[0] = true;
   mark[1] = true;

   int res = 0;
   for (int i=2; i<=n; ++i) {
      if (mark[i]) {
         continue;
      }

      if (!mark[i-2]) {
         resVals[res++] = i;
      }

      for (int k=i*2; k<=n; k+=i) {
         mark[k] = true;
      }
   }

   cout << res << endl;
   for (int i=0; i<res; ++i) {
      cout << 2 << " " << resVals[i] - 2 << endl;
   }

   return 0;
}

//
// End-of-file TASK231.CPP
//
