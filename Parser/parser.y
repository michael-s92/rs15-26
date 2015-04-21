%{

#include <iostream>
#include <string>
#include "TreeNodes.hpp"

using namespace std;

extern int yylex();

void yyerror(const string s)
{
  cerr << s << endl;
}

void ispisi(string l, string d)
{
   cout << endl << l << "  ->  " << d << endl << endl;
}

%}



%left caret_token dollar_token
%left vert_token
%left concat d_token no_d_token s_token no_s_token w_token no_w_token b_token n_token t_token bs_token rep1_token rep2_token symbol_token num_token oz_token minus_token ou_token zz_token zu_token
%left plus_token star_token ques_token
%left backslash_token




%%


RegExp :
         //konkatenacija
        RegExp RegExp %prec concat  {ispisi("RegExp","Konkatenacija");}

         // Reg | Reg
       | RegExp vert_token RegExp   {ispisi("RegExp","Ili");}

         // Reg *
       | RegExp star_token  {ispisi("RegExp","Zvezdica");}

        // Reg +
       | RegExp plus_token  {ispisi("RegExp","Plus");}

        //Reg ?
       | RegExp ques_token  {ispisi("RegExp","Upitnik");}

         // Reg{2,3}
       | Repetition      {ispisi("RegExp","Repetition");}

        // ( Reg )
       | oz_token RegExp zz_token {ispisi("RegExp","Zagrade");}

        // [a-z]
       | CharacterClass {ispisi("RegExp","Karakterska Klasa");}

        // ^Reg
      | caret_token RegExp {ispisi("RegExp","Pocetak Reda");}

         // Reg $
       | RegExp dollar_token {ispisi("RegExp","Kraj Reda");}

        //  /+
       | BackslashReg   {ispisi("RegExp","Backslash");}

        // svi nespecijalni simboli
       | symbol_token   {ispisi("RegExp","Nespecijalni simbol");}

        // svi brojevi
       | num_token  {ispisi("RegExp","Broj");}

        // minus (kao nespecijalni simbol)
       | minus_token

        //] kao nespecijalni simbol
       | zu_token
;

    //Ovo je uradjeno preko leksera da prepoznaje
    // da bi se izbegli s-r konflikti
    // lakse ih je ovako eliminisati
Repetition : rep1_token {ispisi("Repetition","{num,} ili {num}");}
           | rep2_token {ispisi("Repetition","{num,num}");}
;


CharacterClass : ou_token ArraySym zu_token
                     {ispisi("CharacterClass","[ ArraySym ]");}


;

ArraySym : ArraySym CharPart           {ispisi("ArraySym","ArraySym CharPart");}
         | CharPart                    {ispisi("ArraySym","CharPart");}
         | caret_token ArraySym        {ispisi("ArraySym","^ArraySym");}
;

CharPart : SymbolChar minus_token SymbolChar    {ispisi("CharPart","SymbolChar - SymbolChar");}
         | SymbolChar                           {ispisi("CharPart","SymbolChar");}
;

// Izdvojeno je sve cemu moze da prethodi backslash
// s tim da su razdvojeni delovi koji sa backslashom imaju specijalno znacenje
// od onih koji nemaju
BackslashReg : d_token                  {ispisi("BackslashReg","\\ d");}
             | no_d_token               {ispisi("BackslashReg","\\ D");}
             | w_token                  {ispisi("BackslashReg","\\ w");}
             | no_w_token               {ispisi("BackslashReg","\\ W");}
             | s_token                  {ispisi("BackslashReg","\\ s");}
             | no_s_token               {ispisi("BackslashReg","\\ S");}
             | b_token                  {ispisi("BackslashReg","\\ b");}
             | backslash_token Symbol   {ispisi("BackslashReg","\\ Symbol");}
             | n_token                  {ispisi("BackslashReg","\\ n");}
             | bs_token                 {ispisi("BackslashReg","\\ \\");}
             | t_token                  {ispisi("BackslashReg","\\ t");}
;


// kako symbol_token predstavlja samo nespecijalne simbole,
// Symbol je nesto sto grupise sve specijalne i nespecijalne simbole

Symbol : symbol_token   {ispisi("Symbol","nespecijalni simbol");}
       | num_token      {ispisi("Symbol","broj");}
       | plus_token     {ispisi("Symbol","+");}
       | star_token     {ispisi("Symbol","*");}
       | ques_token     {ispisi("Symbol","?");}
       | vert_token     {ispisi("Symbol","|");}
       | caret_token    {ispisi("Symbol","^");}
       | dollar_token   {ispisi("Symbol","$");}
       | oz_token       {ispisi("Symbol","(");}
       | zz_token       {ispisi("Symbol",")");}
       | ou_token       {ispisi("Symbol","[");}
       | zu_token       {ispisi("Symbol","]");}
;


// SymbolChar predstavlja sve simbole koji se mogu naci unutar karakterske
// klase

SymbolChar : symbol_token   {ispisi("SymbolChar","nespecijalni simbol");}
           | num_token      {ispisi("SymbolChar","broj");}
           | BackslashReg   {ispisi("SymbolChar","\\");}
           | plus_token     {ispisi("SymbolChar","+");}
           | star_token     {ispisi("SymbolChar","*");}
           | ques_token     {ispisi("SymbolChar","?");}
           | vert_token     {ispisi("SymbolChar","|");}
           | dollar_token   {ispisi("SymbolChar","$");}
           | oz_token       {ispisi("SymbolChar","(");}
           | zz_token       {ispisi("SymbolChar",")");}
           | ou_token       {ispisi("SymbolChar","[");}
;

%%
