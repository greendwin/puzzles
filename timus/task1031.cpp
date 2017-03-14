
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>
#include <iterator>
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

template <class T>
void read_list(vector<T> & arr, int count)
{
   for (int k = 0; k < count; ++k) {
      T val;
      cin >> val;
      arr.push_back(val);
   }
}

vector<int> len;
vector<int> cost;
vector<int> dist;

struct STATION {
   int dist;
   int price;

   STATION(void)
      : dist(0)
      , price(-1)
   {}

   bool           operator < (const STATION & p) const         { return dist   < p.dist; }
   bool           operator < (int p_dist) const                { return dist   < p_dist; }
   friend bool    operator < (int p_dist, const STATION & p)   { return p_dist < p.dist; }
};

typedef vector<STATION>::iterator station_iterator;

/******************************************************************************/
/* process
/*
/******************************************************************************/
void process(vector<STATION> & list)
{
   int count = list.size();
   
   for (int index = 0; index < count; ++index) {
      STATION & cur = list[index];
      if (cur.price == -1) {
         continue;
      }

      int offset = index + 1;
      for (int k = 0; k < len.size(); ++k) {
         int curLen  = len[k];
         int curCost = cost[k];
         int newPrice = cur.price + curCost;

         station_iterator endStation = lower_bound(list.begin() + offset, list.end(), cur.dist + curLen + 1);

         for (station_iterator iter = list.begin() + offset; iter != endStation; ++iter) {
            if (iter->price == -1) {
               iter->price = newPrice;
            } else {
               iter->price = min(iter->price, newPrice);
            }
         }

         offset = endStation - list.begin();
      }
   }
}

int main(void)
{
   read_list(len,  3);
   read_list(cost, 3);

   int count;
   cin >> count;

   int start, finish;
   cin >> start >> finish;
   --start;    // to range [0, N-1]
   --finish;
   if (start > finish) {
      swap(start, finish);
   }

   vector<STATION> stations(count);

   for (int k = 1; k < count; ++k) {
      cin >> stations[k].dist;
   }

   stations[start].price = 0;

   // first pass: init values in range [0, start]
   // travel from start to beginning
   if (start > 0) {
      int maxDist = stations[start].dist;

      vector<STATION> prepare(start + 1);
      for (int k = 0; k <= start; ++k) {
         prepare[k].dist = maxDist - stations[start - k].dist;
      }

      prepare[0].price = 0;
      process(prepare);

      for (int k = 0; k < start; ++k) {
         stations[k].price = prepare[start - k].price;
      }
   }

   process(stations);

   int postCount = count - finish;
   vector<STATION> post(postCount);
   for (int k = 0; k < postCount; ++k) {
      post[k].dist  = stations[finish + k].dist;
      post[k].price = (k == 0) ? 0 : -1;
   }

   process(post);

   int bestPrice = stations[finish].price;
   for (int k = 1; k < postCount; ++k) {
      if (post[k].price != -1) {
         bestPrice = min(bestPrice, stations[finish + k].price + post[k].price);
      }
   }

   cout << bestPrice << endl;

   return 0;
}
