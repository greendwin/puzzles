
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <deque>
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

istringstream nextLine(istream & input = cin)
{
   string line;
   getline(input, line);

   return istringstream(line);
}

int totalSize  = 0;
int subLen = 1;

int bestPos = -1;
int bestSum = 0;

int curSum  = 0;
int curPos  = 0;
deque<int> part;

void Push(char ch)
{
   ++curPos;

   if (ch == '*') {
      part.clear();
      curSum = 0;
      return ;
   }

   if (part.size() == subLen) {
      int val = part.front();
      part.pop_front();

      curSum -= val;
   }

   int val = ch - '0';
   part.push_back(val);
   curSum += val;

   if (part.size() == subLen) {
      if (bestPos == -1 || bestSum > curSum) {
         bestPos = curPos - subLen + 1;
         bestSum = curSum;
      }
   }
}

int main(void)
{
   nextLine() >> totalSize >> subLen;

   string line;
   while (totalSize > 0) {
      getline(cin, line);
      for (int k = 0; k < line.size(); ++k) {
         Push(line[k]);
      }
      totalSize -= line.size();
   }

   cout << (bestPos != -1 ? bestPos : 0) << endl;

   return 0;
}
