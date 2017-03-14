/************************************************************
 * TASK302.CPP                                     14.03.2008
 *
 * .
 ************************************************************/

#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

/**************************************************************************
* main()                                                                  *
*                                                                         *
**************************************************************************/
int main(void)
{
   //istringstream cin("Thi<UP>sIs<DOWN>EaSY</DOWN>Pr<DOWN>O</DOWN>ble</UP>m");

   enum MOD_STATE {
      MST_DEFAULT,
      MST_UP,
      MST_DOWN,
   };

   stack<MOD_STATE> mod_state;
   mod_state.push(MST_DEFAULT);

   enum STATE {
      ST_DEFAULT,
      ST_TAG,
   } state = ST_DEFAULT;
   
   string line;
   getline(cin, line);
   istringstream input(line);

   string tag;
   char ch;
   while (input >> ch) {
      switch (state) {
         case ST_DEFAULT:
            if (ch == '<') {
               tag.clear();
               state = ST_TAG;
               break;
            }

            switch (mod_state.top()) {
               case MST_UP:
                  ch = char_traits<char>::to_char_type(toupper(char_traits<char>::to_int_type(ch)));
                  break;
               case MST_DOWN:
                  ch = char_traits<char>::to_char_type(tolower(char_traits<char>::to_int_type(ch)));
                  break;
            }
            cout << ch;
            break;

         case ST_TAG:
            if (ch == '>') {
               if (tag == "UP") {
                  mod_state.push(MST_UP);
               } else if (tag == "DOWN") {
                  mod_state.push(MST_DOWN);
               } else {
                  mod_state.pop();
               }
               state = ST_DEFAULT;
               break;
            }

            if (!isspace(char_traits<char>::to_int_type(ch))) {
               tag += ch;
            }
            break;
      }
   }

   return 0;
}

//
// End-of-file TASK302.CPP
//
