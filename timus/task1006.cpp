
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <deque>
#include <queue>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <cassert>

#pragma warning(disable : 4018)

#ifdef ONLINE_JUDGE
typedef long long          INT64;
typedef unsigned long long UINT64;
#else
typedef __int64            INT64;
typedef unsigned __int64   UINT64;
#endif

using namespace std;

const char LT     = (char)218;
const char RT     = (char)191;
const char LB     = (char)192;
const char RB     = (char)217;
const char VERT   = (char)179;
const char HOR    = (char)196;
const char ANY    = 'x';

const int WIDTH  = 50;
const int HEIGHT = 20;
vector<string> data;

void Print(const vector<string> & data)
{
   for (int k = 0; k < data.size(); ++k) {
      cout << data[k] << endl;
   }
}

struct RECT {
   int x, y;
   int width, height;
   int count;

   RECT(void)
      : x(0), y(0)
      , width(0), height(0)
      , count(0)
   {}

   bool operator < (const RECT & p) const {
      if (count != p.count) {
         return count < p.count;
      }
      return width + height < p.width + p.height;
   }
};

struct PAIR {
   int x, y;
   char type;

   PAIR(int x, int y, char type)
      : x(x), y(y), type(type)
   {}
};

void GetCoords(const RECT & rect, vector<PAIR> & coords)
{
   coords.clear();
   coords.reserve(2 * (rect.width + rect.height - 2));
   for (int k = 0; k < rect.width; ++k) {
      coords.push_back(PAIR(rect.x + k, rect.y, (
         k == 0 ? LT : k + 1 == rect.width ? RT : HOR)));

      coords.push_back(PAIR(rect.x + k, rect.y + rect.height - 1, (
         k == 0 ? LB : k + 1 == rect.width ? RB : HOR)));
   }

   for (int k = 1; k + 1 < rect.height; ++k) {
      coords.push_back(PAIR(rect.x, rect.y + k, VERT));
      coords.push_back(PAIR(rect.x + rect.width - 1, rect.y + k, VERT));
   }
}

enum {
   SEARCH_RIGHT,
   SEARCH_DOWN,
   SEARCH_LEFT,
   SEARCH_UP,
};

bool SearchLeft(const vector<string> & data, int x0, int y0, int x1, int y1, RECT & res)
{
   const string & y1_line = data[y1];
   for (int x = x0; x < x1; ++x) {
      char val = y1_line[x];
      if (val == ANY) {
         continue;
      }

      if (x == x0 && val == LB || x != x0 && val == HOR) {
         continue;
      }

      return false;
   }

   for (int y = y0 + 1; y < y1; ++y) {
      char val = data[y][x0];
      if (val != ANY && val != VERT) {
         return false;
      }
   }

   res.x = x0;
   res.y = y0;
   res.width  = x1 - x0 + 1;
   res.height = y1 - y0 + 1;

   return true;
}

bool Check(const vector<string> & data, RECT & rect)
{
   if (rect.x + rect.width >= WIDTH) {
      return false;
   }
   if (rect.y + rect.height >= HEIGHT) {
      return false;
   }

   static vector<PAIR> coords;
   GetCoords(rect, coords);

   rect.count = 0;

   for (int k = 0; k < coords.size(); ++k) {
      PAIR & cur = coords[k];
      char val = data[cur.y][cur.x];

      if (val != ANY && val != cur.type) {
         return false;
      }

      if (val == cur.type) {
         ++rect.count;
      }
   }

   return rect.count != 0;
}

bool SearchDown(const vector<string> & data, int x0, int y0, int x1, RECT & res)
{
   bool first = true;
   RECT r;
   r.x = x0;
   r.y = y0;
   r.width = x1 - x0 + 1;

   for (int y = y0 + 1; y < HEIGHT; ++y) {
      char val = data[y][x1];

      if (val == VERT) {
         continue;
      }

      if (val != ANY && val != RB) {
         return !first;
      }

      r.height = y - y0 + 1;

      if (!Check(data, r)) {
         if (val == RB) {
            return !first;
         }
      } else if (first || res < r) {
         res = r;
         first = false;
      }
   }

   return !first;
}

bool SearchRight(const vector<string> & data, int x0, int y0, RECT & res)
{
   char val = data[y0][x0];
   if (val != ANY && val != LT) {
      return false;
   }

   const string & y0_line = data[y0];

   bool first = true;
   RECT r;
   r.x = x0;
   r.y = y0;

   for (int x = x0 + 1; x < WIDTH; ++x) {
      char val = y0_line[x];
      if (val == HOR) {
         continue;
      }

      if (val != ANY && val != RT) {
         return !first;
      }

      r.width = r.height = x - x0 + 1;
      if (!Check(data, r)) {
         if (val == RB) {
            return !first;
         }
      } else if (first || res < r) {
         res = r;
         first = false;
      }

      //if (!SearchDown(data, x0, y0, x, r)) {
      //   if (val == RT) {
      //      return !first;
      //   }
      //} else if (first || res < r) {
      //   res = r;
      //   first = false;
      //}
   }

   return !first;
}

bool FindNext(const vector<string> & data, RECT & res)
{
   const int count = WIDTH * HEIGHT;

   bool first = true;
   RECT r;

   for (int k = 0; k < count; ++k) {
      int x = k % WIDTH;
      int y = k / WIDTH;

      if (!SearchRight(data, x, y, r)) {
         continue;
      }

      if (first || res < r) {
         first = false;
         res = r;
      }
   }

   return !first;
}

int main(void)
{
   string line;
   for (int k = 0; k < HEIGHT; ++k) {
      getline(cin, line);
      assert(line.size() == WIDTH);
      data.push_back(line);
   }

   RECT rect;
   //rect.x = 0;
   //rect.y = 0;
   //rect.width = 3;
   //rect.height = 3;
   vector<PAIR> coords;
   //GetCoords(rect, coords);
   //for (int k = 0; k < coords.size(); ++k) {
   //   PAIR & cur = coords[k];
   //   data[cur.y][cur.x] = cur.type;
   //}

   vector<RECT> rects;

   for (;;) {
      if (!FindNext(data, rect)) {
         break;
      }

      rects.push_back(rect);

      GetCoords(rect, coords);
      for (int k = 0; k < coords.size(); ++k) {
         PAIR & cur = coords[k];
         data[cur.y][cur.x] = ANY;
      }
   }

   //Print(data);
   cout << rects.size() << endl;
   for (int k = (int)rects.size() - 1; k >= 0; --k) {
      const RECT & cur = rects[k];
      cout << cur.x << " " << cur.y << " " << cur.width << endl;
   }

   return 0;
}
