
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

const int MAX_NODES = 100;
const int MAX_LINKS = 10000;

struct NODE {
   int count;
   int links [MAX_NODES];
   
   bool visited;

   NODE(void)
      : count(0)
      , visited(false)
   {}

   void addLink(int nodeIdx) {
      links[count]  = nodeIdx;
      ++count;
   }
};

struct LINK {
   int start, end;
   int weight;

   bool operator < (const LINK & p) const {
      return weight < p.weight;
   }
};

vector<LINK> links;
vector<NODE> nodes;
vector<int> path;

bool getLoopPath(int index, int prev = -1)
{
   NODE & cur = nodes[index];
   cur.visited = true;
   path.push_back(index);

   for (int k = 0; k < cur.count; ++k) {
      if (cur.links[k] == prev) {
         continue;
      }

      int nextIdx = cur.links[k];
      NODE & next = nodes[nextIdx];

      if (next.visited) {
         return true;
      }

      if (getLoopPath(nextIdx, index)) {
         return true;
      }
   }

   path.pop_back();
   return false;
}

int main(void)
{
   links.reserve(MAX_LINKS);
   nodes.reserve(MAX_NODES);
   path.reserve(MAX_NODES);

   vector<int> group;
   group.reserve(MAX_NODES);

   for (;;) {
      int nodesCount;
      cin >> nodesCount;
      if (nodesCount == -1) {
         break;
      }

      int linksCount;
      cin >> linksCount;
      
      links.resize(linksCount);

      for (int k = 0; k < linksCount; ++k) {
         LINK & cur = links[k];
         cin >> cur.start >> cur.end >> cur.weight;
         --cur.start;
         --cur.end;
      }

      sort(links.begin(), links.end());

      group.resize(nodesCount);
      for (int k = 0; k < nodesCount; ++k) {
         group[k] = k;
      }

      nodes.clear();
      nodes.resize(nodesCount);

      bool ok = false;

      for (int k = 0; k < linksCount; ++k) {
         LINK & cur = links[k];

         // add link to graph
         nodes[cur.start].addLink(cur.end);
         nodes[cur.end].addLink(cur.start);

         if (group[cur.start] != group[cur.end]) {
            // merge groups
            int srcGroup = group[cur.start];
            int dstGroup = group[cur.end];
            for (int p = 0; p < nodesCount; ++p) {
               if (group[p] == srcGroup) {
                  group[p] = dstGroup;
               }
            }

            continue;
         }

         // found cycle
         bool res = getLoopPath(cur.start);
         assert(res);

         for (int k = 0; k < path.size(); ++k) {
            cout << path[k] + 1 << " ";
         }
         cout << endl;

         ok = true;
         break;
      }

      if (!ok) {
         cout << "No solution." << endl;
      }
   }

   return 0;
}
