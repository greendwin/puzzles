/************************************************************
 * TASK344.CPP                                     14.03.2008
 *
 * .
 ************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

const int MAX_SIZE = 1024;
const int X_SHIFT  = 10;

const int OFFSET[] = { -1, MAX_SIZE, 1, -MAX_SIZE };

enum {
   MARK_USED         = 0x0001,
   MARK_QUEUED       = 0x0002,
};

using namespace std;

/**************************************************************************
* Mark()                                                                  *
*                                                                         *
**************************************************************************/
void Mark(int * data, int start, int n, int m, int & count)
{
   queue<int> q;
   q.push(start);

   while (!q.empty()) {
      int cur = q.front();
      q.pop();

      data[cur] &= ~MARK_QUEUED;

      // check neighbors
      int n_cnt = 0;
      for (int i=0; i<4; ++i) {
         const int neighbor = cur + OFFSET[i];
         if (neighbor >= 0 && data[neighbor] & MARK_USED) {
            ++n_cnt;
         }
      }

      if (n_cnt > 1) {
         data[cur] |= MARK_USED;
         ++count;

         for (int i=0; i<4; ++i) {
            const int neighbor = cur + OFFSET[i];
            if (neighbor >= 0
            &&  data[neighbor] == 0
            && (neighbor & (MAX_SIZE - 1)) < m
            && (neighbor >> X_SHIFT) < n) {
               q.push(neighbor);
               data[neighbor] |= MARK_QUEUED;
            }
         }
      }
   }
}

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
   int * data = new int[MAX_SIZE * MAX_SIZE];
   memset(data, 0, MAX_SIZE * MAX_SIZE);

#if 0
   istringstream cin(
      "3 3\n"
      "x..\n"
      ".x.\n"
      ".x.\n"
   );
#elif 0
   istringstream cin(
      "3 4 "
      "X..X"
      ".X.."
      ".X.."
   );
#endif

   int n, m;
   cin >> n >> m;

   int count = 0;

   for (int i=0; i<n; ++i) {
      const int i_off = i << X_SHIFT;
      for (int j=0; j<m; ++j) {
         char ch;
         cin >> ch;
         if (ch != '.') {
            data[i_off + j] = MARK_USED;
            ++count;
         }
      }
   }

   for (int i=0; i<n; ++i) {
      const int i_off = i << X_SHIFT;
      for (int j=0; j<m; ++j) {
         if (data[i_off + j] == 0) {
            Mark(data, (i << X_SHIFT) + j, n, m, count);
         }
      }
   }

   cout << count << endl;

   return 0;
}

//
// End-of-file TASK344.CPP
//
