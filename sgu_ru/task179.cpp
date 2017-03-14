/************************************************************
 * TASK179.CPP                                     19.03.2008
 *
 * .
 ************************************************************/

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//#define GEN_TESTS

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
#ifdef GEN_TESTS
   string initial = "((()))";
   istringstream cin(initial);
   cout << initial << endl;
one_more: ;
#endif

   string str;
   cin >> str;

   int last = -1;
   int lastOpened;

   for (int i=0, opened = 0; i<(int)str.size(); ++i) {
      switch (str[i]) {
         case '(':
            if (opened > 0) {
               last = i;
               lastOpened = opened - 1;
            }
            ++opened;
            break;

         case ')':
            --opened;
            break;
      }
   }

   if (last == -1) {
      cout << "No solution" << endl;
      return 0;
   }

   str[last] = 0;
   int rem = ((int)str.size() - last - lastOpened) / 2;

   cout << str.c_str() << ')' << string(rem, '(') << string(rem + lastOpened, ')');

#ifdef GEN_TESTS
   cout << endl;
   string res = str.c_str() + string(")") + string(rem, '(') + string(rem + lastOpened, ')');
   cin.~istringstream();
   new (&cin) istringstream(res);
   goto one_more;
#endif

   return 0;
}

//
// End-of-file TASK179.CPP
//
