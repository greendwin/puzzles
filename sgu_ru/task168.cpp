/************************************************************
 * TASK168.CPP                                     24.03.2008
 *
 * .
 ************************************************************/

#include <iostream>
#include <sstream>

using namespace std;

const int MAX_COUNT = 1000;
int arr[MAX_COUNT * 2][MAX_COUNT];

const int INF = 0x64646464;

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
#if 1
   istringstream cin("3 3 \
      1 2 3 \
      4 5 6 \
      7 8 9"
      );
#endif

   int n, m;
   cin >> n >> m;

   memset(arr, 0x64, sizeof(arr));

   for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
         cin >> arr[x + y][y];
      }
   }

   for (int x = n-1; x >= 0; --x) {
      for (int y=m-1; y>=0; --y) {
         if (y > 0) {
            arr[x+y][y] = min(arr[x+y][y], min(arr[x+y+1][y+1], arr[x+y][y-1]));
         } else {
            arr[x+y][y] = min(arr[x+y][y], arr[x+y+1][y+1]);
         }
      }
   }

   for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
         cout << arr[x+y][y] << " ";
      }
      cout << endl;
   }

   return 0;
}

//
// End-of-file TASK168.CPP
//
