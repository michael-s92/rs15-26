%option noyywrap
%option noinput
%option nounput


%{
#include <iostream>
#include "parser.h"

using namespace std;

void ispisi(string s)
{
  cout << "Lex:  "<< s << endl;
}

%}



num    [0-9]+


%%

\{{num},?\}           { ispisi("{num,}"); return rep1_token;}
\{{num},{num}\}       { ispisi("{num,num}"); return rep2_token;}


{num}     { ispisi("broj"); return num_token;}

[+]       { ispisi("+"); return plus_token;}
[*]       { ispisi("*"); return star_token;}
[?]       { ispisi("?"); return ques_token;}
[|]       { ispisi("|"); return vert_token;}

\^        { ispisi("^"); return caret_token;}
[$]       { ispisi("$"); return dollar_token;}

[(]       { ispisi("("); return oz_token;}
[)]       { ispisi(")"); return zz_token;}
\[        { ispisi("["); return ou_token;}
\]        { ispisi("]"); return zu_token;}

[-]        { ispisi("-"); return minus_token;}
\\d        { ispisi("\\ d"); return d_token;}
\\D        { ispisi("\\ D"); return no_d_token;}
\\w        { ispisi("\\ w"); return w_token;}
\\W        { ispisi("\\ W"); return no_w_token;}
\\s        { ispisi("\\ s"); return s_token;}
\\S        { ispisi("\\ S"); return no_s_token;}
\\b        { ispisi("\\ b"); return b_token;}
\\n        { ispisi("\\ n"); return n_token;}
\\t        { ispisi("\\ t"); return t_token;}
\\\\       { ispisi("\\ \\ "); return bs_token;}

\\         { ispisi("\\"); return backslash_token;}
\n         { ispisi("kraj"); return 0;}
.          { ispisi("simbol"); return symbol_token;}


%%
