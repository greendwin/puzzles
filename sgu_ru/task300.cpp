/************************************************************
 * TASK300.CPP                                     14.03.2008
 *
 * .
 ************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

const int INF        = 1000000;
const int MAX_POINTS = 4096;
const int X_SHIFT    = 12;

int POS_X[MAX_POINTS];
int POS_Y[MAX_POINTS];

int SORTED_X_IDX[MAX_POINTS];
int SORTED_Y_IDX[MAX_POINTS];

int PACKED_POS_X[MAX_POINTS];
int PACKED_POS_Y[MAX_POINTS];
int SIZE_X[MAX_POINTS];
int SIZE_Y[MAX_POINTS];

#define PPOS_2_I(N) \
   ((PACKED_POS_X[N] << X_SHIFT) + PACKED_POS_Y[N])

#define DIST(PREV, NEXT) \
   (abs(SIZE_X[(NEXT) >> X_SHIFT]          - SIZE_X[(PREV) >> X_SHIFT]) + \
    abs(SIZE_Y[(NEXT) & (MAX_POINTS - 1)]  - SIZE_Y[(PREV) & (MAX_POINTS - 1)]))

struct CompareX {
   bool operator () (int i1, int i2) const {
      return POS_X[i1] < POS_X[i2];
   }
};

struct CompareY {
   bool operator () (int i1, int i2) const {
      return POS_Y[i1] < POS_Y[i2];
   }
};

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
#if 0
   istringstream cin(
      "5 "
      "0 0 "
      "3 0 "
      "3 1 "
      "1 1 "
      "1 -1 ");
#elif 0
   istringstream cin(
      "7 "
      "0 0 "
      "1 0 "
      "1 1 "
      "3 1 "
      "3 0 "
      "1 0 "
      "1 -1 ");
#elif 0
   istringstream cin(
      "10 "
      "0 0 "
      "1 0 "
      "1 2 "
      "0 2 "
      "0 1 "
      "-1 1 "
      "-1 -1 "
      "0 -1 "
      "0 1 "
      "2 1 "
   );
#elif 0
   istringstream cin(
      "10 "
      "0 0 "
      "5 0 "
      "5 6 "
      "2 6 "
      "2 -3 "
      "0 -3 "
      "0 3 "
      "10 3 "
      "10 4 "
      "5 4 "
      );
#elif 0
   istringstream cin(
      "5 "
      "0 0 "
      "1 0 "
      "1 1 "
      "0 1 "
      "0 0 "
      );
#elif 0
   istringstream cin(
      "5 "
      "-1 0 "
      "1 0 "
      "1 1 "
      "0 1 "
      "0 0 "
      );
#endif

   int n;
   cin >> n;

   for (int i=0; i<n; ++i) {
      cin >> POS_X[i] >> POS_Y[i];
      SORTED_X_IDX[i] = SORTED_Y_IDX[i] = i;
   }

   sort(SORTED_X_IDX, SORTED_X_IDX + n, CompareX());
   sort(SORTED_Y_IDX, SORTED_Y_IDX + n, CompareY());

   // pack coords
   int coordX = 0, coordY = 0;
   for (int i=0; i<n; ++i) {
      if (i > 0) {
         if (POS_X[SORTED_X_IDX[i - 1]] != POS_X[SORTED_X_IDX[i]]) {
            ++coordX;
         }
         if (POS_Y[SORTED_Y_IDX[i - 1]] != POS_Y[SORTED_Y_IDX[i]]) {
            ++coordY;
         }
      }
      PACKED_POS_X[SORTED_X_IDX[i]] = coordX;
      SIZE_X[coordX] = POS_X[SORTED_X_IDX[i]];

      PACKED_POS_Y[SORTED_Y_IDX[i]] = coordY;
      SIZE_Y[coordY] = POS_Y[SORTED_Y_IDX[i]];
   }

   int * data = new int[MAX_POINTS * MAX_POINTS];
   memset(data, -1, 4 * MAX_POINTS * MAX_POINTS);

   // initial
   int minLength = INF;
   int length = 0;
   int prev = (PACKED_POS_X[0] << X_SHIFT) + PACKED_POS_Y[0];
   data[prev] = 0;

   for (int i=1; i < n; ++i) {
      const int cur = PPOS_2_I(i);
      
      const int sub  = cur - prev;
      const int sign = sub < 0 ? -1 : 1;
      
      int step = MAX_POINTS * sign;
      if (sub & (MAX_POINTS - 1)) {
         step = sign;
      }

      int iter = prev + step;
      for (;;) {
         length += DIST(iter - step, iter);

         if (data[iter] >= 0 /*&& (iter != cur || i + 1 < n)*/) {
            minLength = min(minLength, length - data[iter]);
         } else {
            data[iter] = length;
         }

         if (iter == cur) {
            break;
         }

         iter += step;
      }

      prev = cur;
   }

   if (minLength == INF) {
      minLength = length;
   }

   cout << minLength << endl;

   return 0;
}

//
// End-of-file TASK300.CPP
//
