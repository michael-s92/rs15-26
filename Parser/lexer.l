%option noyywrap
%option noinput
%option nounput


%{
#include <iostream>
#include "parser.h"

using namespace std;

%}

num    [0-9]


%%

{num}      {return num_token;}
[+]        {return plus_token;}
[-]        {return minus_token;}
[*]        {return star_token;}
[?]        {return ques_token;}
[|]        {return vert_token;}
,          {return comma_token;}
\^         {return caret_token;}
[$]        {return dollar_token;}
\          {return backslash_token;}
[(]        {return oz_token;}
[)]        {return zz_token;}
[{]        {return ov_token;}
[}]        {return zv_token;}
\[         {return ou_token;}
\]         {return zu_token;}
.          {return symbol_token;}

%%
