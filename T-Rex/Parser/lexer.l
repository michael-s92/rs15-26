%option noyywrap
%option noinput
%option nounput



%{
#include <iostream>
#include "Parser/TreeNodes.hpp"
#include <string>
#include "parser.h"
#include <string>

using namespace std;

void ispisi(string s)
{
  cout << "Lex:  "<< s << endl;
}

void set_text(char *s)
{
   yy_scan_string(s);
}


%}



digit    [0-9]+


%%



\{{digit}+,\}           {
                         string s(yytext);
                         size_t index = s.find(',');
                         s = s.substr(1,index);
                         yylval.num =new numbers(stoi(s,0,10),-1);
                         return rep1_token;
                        }
\{{digit}+\}            {
                        string s(yytext);
                        size_t index = s.find('}');
                        s= s.substr(1,index);
                        yylval.num = new numbers(stoi(s,0,10),stoi(s,0,10));
                        return rep2_token;
                        }
\{{digit}+,{digit}+\}    {
                        string s(yytext);
                        size_t index1 = s.find(',');
                        string s1 = s.substr(1,index1);
                        size_t index2 = s.find('}');
                        string s2 = s.substr(index1+1,index2);
                        yylval.num =new numbers(stoi(s1,0,10),stoi(s2,0,10));
                        return rep3_token;
                         }


{digit}             {
                //  ispisi("broj");
                    yylval.sym = *yytext;
                    return num_token;
                    }

[+]             {
               // ispisi("+");
                yylval.sym = *yytext;
                return plus_token;
                }
[*]             {
               // ispisi("*");
                yylval.sym = *yytext;
                return star_token;
                }
[?]             {
                //ispisi("?");
                yylval.sym = *yytext;
                return ques_token;
                }
[|]             {
                //ispisi("|");
                yylval.sym = *yytext;
                return vert_token;
                }

\^               {
                 //ispisi("^");
                 yylval.sym = *yytext;
                 return caret_token;
                 }
[$]              {
                 //ispisi("$");
                 yylval.sym = *yytext;
                 return dollar_token;
                 }

[(]             {
                //ispisi("(");
                yylval.sym = *yytext;
                return oz_token;
                }
[)]             {
                //ispisi(")");
                yylval.sym = *yytext;
                return zz_token;
                }
\[              {
                //ispisi("[");
                yylval.sym = *yytext;
                return ou_token;
                }
\]              {
               // ispisi("]");
                yylval.sym = *yytext;
                return zu_token;
                }

[-]             {
                //ispisi("-");
                yylval.sym = *yytext;
                return minus_token;
                }

\\d             {
                //ispisi("\\ d");
                yylval.sym = yytext[1];
                return d_token;
                }
\\D             {
                //ispisi("\\ D");
                yylval.sym = yytext[1];
                return no_d_token;
                }
\\w             {
                //ispisi("\\ w");
                yylval.sym = yytext[1];
                return w_token;
                }
\\W             {
                //ispisi("\\ W");
                yylval.sym = yytext[1];
                return no_w_token;
                }
\\s             {
                //ispisi("\\ s");
                yylval.sym = yytext[1];
                return s_token;
                }
\\S             {
               // ispisi("\\ S");
                yylval.sym = yytext[1];
                return no_s_token;
                }
\\b             {
               // ispisi("\\ b");
                yylval.sym = yytext[1];
                return b_token;
                }
\\n             {
               // ispisi("\\ n");
                yylval.sym = yytext[1];
                return n_token;
                }
\\t             {
              //  ispisi("\\ t");
                yylval.sym = yytext[1];
                return t_token;
                }
\\\\            {
              //  ispisi("\\ \\ ");
                yylval.sym = yytext[1];
                return bs_token;
                }

\\              {
              //  ispisi("\\");
                yylval.sym = *yytext;
                return backslash_token;
                }
\n              {
              //  ispisi("kraj");
                return 0;
                }
.               {
              //  ispisi("simbol");
                yylval.sym = *yytext;
                return symbol_token;
                }

%%
