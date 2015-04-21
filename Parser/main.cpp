#include <iostream>

#include "TreeNodes.hpp"
#include "lexer.h"
#include "parser.h"

using namespace std;


int main(int argc, char *argv[])
{

   while(true)
   {
    if (yyparse()==0)
      cout << "Bravo" << endl;
   }
    return 0;
}


