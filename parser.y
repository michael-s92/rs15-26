%{

#include <iostream>
#include <string>

using namespace std;

extern int yylex();

void yyerror(const string s)
{
  cerr << s << endl;
}

%}



%token symbol_token
%token num_token
%token backslash_token
%token oz_token zz_token ov_token zv_token ou_token zu_token


%left vert_token
%left concat
%left plus_token star_token ques_token
%right backslash_token

%token comma_token caret_token dollar_token
%token minus_token

%%


RegExp :
        //konkatenacija
        RegExp RegExp %prec concat
        // Reg | Reg
       | RegExp vert_token RegExp
        // Reg *
       | RegExp star_token
        // Reg +
       | RegExp plus_token
        //Reg?
       | RegExp ques_token
        // Reg{2,3}
       | Repetition
        // ( Reg )
       | oz_token RegExp zz_token
        // [a-z]
       | CharacterClass
        // ^Reg
       | caret_token RegExp
        // Reg $
       | RegExp dollar_token
        //  /+
       | backslash_token Symbol
        // svi nespecijalni simboli
       | symbol_token
        // svi brojevi
       | num_token
;

Repetition : RegExp ov_token ArrayNum zv_token
;

CharacterClass : ou_token ArraySym zu_token
;

ArrayNum : num_token comma_token num_token
         | num_token comma_token
         | num_token
;

ArraySym : ArraySym CharPart
         | CharPart
         | caret_token ArraySym
;

CharPart : Symbol minus_token Symbol
         | Symbol
;

Symbol : symbol_token
       | plus_token
       | star_token
       | ques_token
       | vert_token
       | backslash_token
       | num_token
       | comma_token
       | caret_token
       | dollar_token
       | oz_token
       | zz_token
       | ov_token
       | zv_token
       | ou_token
       | zu_token
;

%%
