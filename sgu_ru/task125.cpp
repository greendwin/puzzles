/************************************************************
 * TASK125.CPP                                     18.03.2008
 *
 * .
 ************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define NO_SOLUTION "NO SOLUTION"

const int MAX_COUNT = 3;
int initial[MAX_COUNT][MAX_COUNT];
int isMax[MAX_COUNT][MAX_COUNT];
const int MAX_TABLE = 7;
int table[MAX_TABLE][MAX_TABLE];

enum SIGN {
   SIGN_0 = 1,
   SIGN_LS = SIGN_0,
   SIGN_EQ,
   SIGN_GR,
   SIGN_MAX,
};

const int MAX_OFFSET = 4;
const int offX[MAX_OFFSET]    = { 0, 1,  0, -1 };
const int offY[MAX_OFFSET]    = { 1, 0, -1,  0 };
const int offInv[MAX_OFFSET]  = { 1, 0,  0,  1 };

const int MAX_SIGN = 12;
struct POS {
   int x, y;
};
POS signs[MAX_SIGN];

//#define GEN_TESTS

#ifdef GEN_TESTS
int initial_0[MAX_COUNT][MAX_COUNT];
#endif

#if 1
/**************************************************************************
* DbgDump()                                                               *
*                                                                         *
**************************************************************************/
void DbgDump(int n)
{
   for (int y=0; y<=(n << 1); ++y) {
      for (int x=0; x<=(n << 1); ++x) {
         if (x % 2 == 1 && y % 2 == 1) {
            cout << table[x][y];
            continue;
         }
         if (x % 2 == 0 && y % 2 == 0) {
            cout << " ";
            continue;
         }
         switch (table[x][y]) {
            case SIGN_LS: cout << '<'; break;
            case SIGN_GR: cout << '>'; break;
            case SIGN_EQ: cout << '='; break;
            default: cout << '?'; break;
         }
      }
      cout << endl;
   }
   cout << endl;
}
#endif

struct STACK_ITEM {
   int x, y;
   int index;
};

const int MAX_STACK = 12 * 9 * 9;
STACK_ITEM stack[MAX_STACK];

/**************************************************************************
* Update()                                                                *
*                                                                         *
**************************************************************************/
bool Update(int x0, int y0, int n)
{
   int index = 0;
   stack[index].x = (x0 << 1) + 1;
   stack[index].y = (y0 << 1) + 1;
   stack[index].index = 0;

   while (index >= 0) {
      STACK_ITEM * st = stack + index;

      for (int i=st->index; i<MAX_OFFSET; ++i) {
         int x1 = st->x + offX[i];
         int y1 = st->y + offY[i];
         if (x1 <= 0 || y1 <= 0 || x1 >= (n << 1) || y1 >= (n << 1)) {
            continue;
         }

         int sign = table[x1][y1];
         if (offInv[i]) {
            sign = SIGN_MAX - sign;
         }

         if (sign == SIGN_LS) {
            continue;
         }

         int newVal = table[st->x][st->y];
         if (sign == SIGN_GR) {
            --newVal;
         }

         if (newVal <= 0) {
            return false;
         }

         int x2 = x1 + offX[i];
         int y2 = y1 + offY[i];
         if (table[x2][y2] > newVal) {
            table[x2][y2] = newVal;
            st->index = i + 1;

#if 0
            DbgDump(n);
#endif

            ++index;
            stack[index].x = x2;
            stack[index].y = y2;
            stack[index].index = 0;
            goto stack_push;
         }
      }

      --index;

stack_push: ;
   }

   return true;
}

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
#ifndef GEN_TESTS
#if 0
   istringstream cin("3 "
      "1 2 1 "
      "1 2 1 "
      "1 1 0 "
      );
#elif 0
   istringstream cin(
      "2 "
      "2 0 "
      "0 1 ");
#endif
#else
   int _counter = 0;
one_more:
   cout << string(32, 8) << ++_counter;

   string test;
   vector<vector<int> > arr;
   {
      int n = 2 + rand() % 2;
      ostringstream tmp;
      tmp << n << endl;

      arr.clear();
      arr.resize(n, vector<int>(n));

      for (int i=0; i<n; ++i) {
         for (int j=0; j<n; ++j) {
            arr[i][j] = rand() % 10;
         }
      }

      for (int y=0; y<n; ++y) {
         for (int x=0; x<n; ++x) {
            int weight = 0;

            for (int i=0; i<MAX_OFFSET; ++i) {
               int x1 = x + offX[i];
               int y1 = y + offY[i];

               if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n) {
                  continue;
               }

               if (arr[x1][y1] > arr[x][y]) {
                  ++weight;
               }
            }

            tmp << weight << " ";
         }
         tmp << endl;
      }

      test = tmp.str();
   }

   istringstream cin(test);
#endif

   int n;
   cin >> n;

   for (int y=0; y<n; ++y) {
      for (int x=0; x<n; ++x) {
         cin >> initial[x][y];
      }
   }

#ifdef GEN_TESTS
   memcpy(initial_0, initial, sizeof(initial));
#endif

   // collect signs
   int sign_count = 0;
   for (int y=0; y<n; ++y) {
      for (int x=0; x < n; ++x) {
         const int x0 = (x << 1) + 1;
         const int y0 = (y << 1) + 1;

         POS pos;
         if (x + 1 < n) {
            pos.x = x0 + 1;
            pos.y = y0;
            signs[sign_count++] = pos;
         }

         if (y + 1 < n) {
            pos.x = x0;
            pos.y = y0 + 1;
            signs[sign_count++] = pos;
         }
      }
   }

   // move fixed signs to the end
   bool maxFound = false;
   int varSignCount = sign_count;
   for (int y=0; y<n; ++y) {
      for (int x=0; x<n; ++x) {
         if (initial[x][y] != 0) {
            continue;
         }

         maxFound = true;
         isMax[x][y] = true;

#if 0 // incorrect!!!
         int x0 = (x << 1) + 1;
         int y0 = (y << 1) + 1;
         for (int i=0; i<MAX_OFFSET; ++i) {
            int signX = x0 + offX[i];
            int signY = y0 + offY[i];

            if (signX <= 0 || signX >= (n << 1)
            ||  signY <= 0 || signY >= (n << 1)) {
               continue;
            }

            if (initial[(signX + offX[i]) >> 1][(signY + offY[i]) >> 1] == 0) {
               table[signX][signY] = SIGN_EQ;
            } else {
               table[signX][signY] = !offInv[i] ? SIGN_GR : SIGN_LS;
            }

            for (int k=0; k<varSignCount; ++k) {
               if (signs[k].x == signX && signs[k].y == signY) {
                  swap(signs[k], signs[varSignCount - 1]);
                  --varSignCount;
                  break;
               }
            }
         }
#endif
      }
   }

   // fill border signs
   for (int x=0; x<MAX_TABLE; ++x) {
      table[x][0]       = SIGN_LS;
      table[x][n << 1]  = SIGN_GR;
   }
   for (int y=0; y<MAX_TABLE; ++y) {
      table[0][y]       = SIGN_GR;
      table[n << 1][y]  = SIGN_LS;
   }

#if 0
   for (int x=0; x<n; ++x) {
      for (int y=0; y<n; ++y) {
         table[(x << 1) + 1][(y << 1) + 1] = initial[x][y];
      }
   }
   DbgDump(n);
#endif

   if (!maxFound) {
      cout << NO_SOLUTION << endl;
      return 0;
   }

   // update initials
   for (int x=0; x<n; ++x) {
      for (int y=0; y<n; ++y) {
         initial[x][y] += (x == 0) + (x + 1 == n) + (y == 0) + (y + 1 == n);
      }
   }

#if 0
   for (int x=0; x<n; ++x) {
      for (int y=0; y<n; ++y) {
         table[(x << 1) + 1][(y << 1) + 1] = initial[x][y];
      }
   }
   DbgDump(n);
#endif

   // prepare signs
   int count = 1;
   for (int index=0; index<varSignCount; ++index) {
      table[signs[index].x][signs[index].y] = SIGN_MAX - 1;
      count *= 3;
   }

   for (int counter = 0; counter < count; ++counter) {
      // increment signs
      for (int i = 0; i < varSignCount; ++i) {
         POS p = signs[i];
         int & val = table[p.x][p.y];
         ++val;
         if (val < SIGN_MAX) {
            break;
         }

         val = SIGN_0;
      }

#if 0
      for (int x=0; x<n; ++x) {
         for (int y=0; y<n; ++y) {
            table[(x << 1) + 1][(y << 1) + 1] = initial[x][y];
         }
      }
      DbgDump(n);
      system("pause");
#endif

      // check correctness
      bool correct = true;
      for (int x=0; x<n; ++x) {
         for (int y=0; y<n; ++y) {
            const int x0 = (x << 1) + 1;
            const int y0 = (y << 1) + 1;

            int weight = 0;
            for (int i=0; i<MAX_OFFSET; ++i) {
               int sign = table[x0 + offX[i]][y0 + offY[i]];
               if (offInv[i]) {
                  sign = SIGN_MAX - sign;
               }

               weight += (sign == SIGN_LS);
            }

            if (weight != initial[x][y]) {
               correct = false;
               goto stop_verification;
            }
         }
      }
stop_verification:
      if (!correct) {
         continue;
      }

#if 0
      for (int x=0; x<n; ++x) {
         for (int y=0; y<n; ++y) {
            table[(x << 1) + 1][(y << 1) + 1] = initial[x][y];
         }
      }
      DbgDump(n);
#endif

      // prepare update
      int max = n * n;
      for (int x=0; x<n; ++x) {
         for (int y=0; y<n; ++y) {
            int x0 = (x << 1) + 1;
            int y0 = (y << 1) + 1;

            table[x0][y0] = max;
         }
      }

      // run updates
      correct = true;
      for (int x=0; x<n; ++x) {
         for (int y=0; y<n; ++y) {
            if (!isMax[x][y]) {
               continue;
            }

            if (!Update(x, y, n)) {
               correct = false;
               goto stop_update;
            }
         }
      }
stop_update:
      if (!correct) {
         continue;
      }

#ifndef GEN_TESTS
      // print result
      for (int y=0; y<n; ++y) {
         for (int x=0; x<n; ++x) {
            cout << table[(x << 1) + 1][(y << 1) + 1] << " ";
         }
         cout << endl;
      }
#else
      for (int y=0; y<n; ++y) {
         for (int x=0; x<n; ++x) {
            int weight = 0;

            for (int i=0; i<MAX_OFFSET; ++i) {
               int x1 = x + offX[i];
               int y1 = y + offY[i];

               if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n) {
                  continue;
               }

               if (table[(x1 << 1) + 1][(y1 << 1) + 1] > table[(x << 1) + 1][(y << 1) + 1]) {
                  ++weight;
               }
            }

            if (weight != initial_0[x][y]) {
               cout << endl << "Incorrect:" << endl;
               // print result
               for (int y=0; y<n; ++y) {
                  for (int x=0; x<n; ++x) {
                     cout << table[(x << 1) + 1][(y << 1) + 1] << " ";
                  }
                  cout << endl;
               }
               cout << "Task:" << endl;
               cout << test;
               system("pause");
               goto one_more;
            }
         }
      }
      goto one_more;
#endif
      return 0;
   }

#ifdef GEN_TESTS
   cout << endl << test << endl;
   for (int y=0; y<n; ++y) {
      for (int x=0; x<n; ++x) {
         cout << arr[x][y] << " ";
      }
      cout << endl;
   }
   cout << endl;
#endif

   cout << NO_SOLUTION << endl;

#ifdef GEN_TESTS
   system("pause");
   goto one_more;
#endif
   
   return 0;
};

//
// End-of-file TASK125.CPP
//
