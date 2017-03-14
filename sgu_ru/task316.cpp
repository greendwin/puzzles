/************************************************************
 * TASK316.CPP                                     14.03.2008
 *
 * .
 ************************************************************/

#include <iostream>

using namespace std;

const int MAX_TANKS = 6;

int HITPOINTS[MAX_TANKS];
int SCOREPOINTS[MAX_TANKS];

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
   int n, count;
   cin >> n >> count;

   for (int i=0; i<n; ++i) {
      HITPOINTS[i] = 100;
   }

   for (int i=0; i<count; ++i) {
      int a, b;
      cin >> a >> b;
      --a;
      --b;

      if (HITPOINTS[a] < 0) {
         continue;
      }

      if (HITPOINTS[b] > 0) {
         SCOREPOINTS[a] += 3;
      }
      HITPOINTS[b] -= 8;
   }

   for (int i=0; i<n; ++i) {
      int score = SCOREPOINTS[i];
      if (HITPOINTS[i] > 0) {
         score += HITPOINTS[i] >> 1;
      }
      cout << HITPOINTS[i] << " " << score << endl;
   }

   return 0;
}

//
// End-of-file TASK316.CPP
//
