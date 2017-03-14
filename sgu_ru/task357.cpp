/************************************************************
 * TASK357.CPP                                     14.03.2008
 *
 * .
 ************************************************************/

#include <iostream>

using namespace std;

const int INF = 1000000;
const int MAX_CHANNEL = 100;
int TABLE[MAX_CHANNEL][MAX_CHANNEL];

/**************************************************************************
* Find()                                                                  *
*                                                                         *
**************************************************************************/
int Find(int x, int y)
{
   int WEIGHT[MAX_CHANNEL];
   int USED[MAX_CHANNEL];
   for (int i=0; i<MAX_CHANNEL; ++i) {
      WEIGHT[i] = INF;
      USED[i]   = false;
   }
   WEIGHT[x] = 0;

   for (;;) {
      int minWeight = INF;
      int index = -1;

      for (int i=0; i<MAX_CHANNEL; ++i) {
         if (!USED[i] && WEIGHT[i] < minWeight) {
            minWeight = WEIGHT[i];
            index = i;
         }
      }

      if (index == -1) {
         break;
      }

      USED[index] = true;
      for (int i=0; i<MAX_CHANNEL; ++i) {
         if (TABLE[index][i] != -1) {
            WEIGHT[i] = min(WEIGHT[i], minWeight + TABLE[index][i]);
         }
      }
   }

   return WEIGHT[y] == INF ? -1 : WEIGHT[y];
}

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
   int b[10];
   int bUp, bDown, bSelect;

   cin >> b[1] >> b[2] >> b[3] >> bUp
       >> b[4] >> b[5] >> b[6] >> bDown
       >> b[7] >> b[8] >> b[9]
       >> bSelect >> b[0];

   int x, y;
   cin >> x >> y;

   for (int i=0; i<MAX_CHANNEL; ++i) {
      for (int j=0; j<MAX_CHANNEL; ++j) {
         TABLE[i][j] = (i == j) ? 0 : -1;
      }
   }

   for (int i=0; i<MAX_CHANNEL; ++i) {
      int d1 = i % 10;
      int d2 = i / 10;

      // single select for 0-9
      if (d2 == 0 && b[d1]) {
         for (int j=0; j<MAX_CHANNEL; ++j) {
            if (j == i) {
               continue;
            }
            TABLE[j][i] = 1;
         }
         continue;
      }

      if (bUp) {
         TABLE[(MAX_CHANNEL + i - 1) % MAX_CHANNEL][i] = 1;
      }
      if (bDown) {
         TABLE[(i + 1) % MAX_CHANNEL][i] = 1;
      }

      if (bSelect && b[d1] && b[d2]) {
         for (int j=0; j<MAX_CHANNEL; ++j) {
            int & val = TABLE[j][i];
            if (val == -1) {
               val = 3;
            }
         }
      }
   }

   int res = Find(x, y);

   cout << res << endl;

   return 0;
}

//
// End-of-file TASK357.CPP
//
