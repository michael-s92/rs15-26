%{

#include <iostream>
#include <string>

#include "TreeNodes.hpp"
#include "lexer.h"


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

%union {
   char sym;
   reg_node *reg;
}

%left <sym> caret_token dollar_token
%left <sym> vert_token
%left <sym> concat d_token
      no_d_token s_token no_s_token w_token no_w_token
      b_token n_token t_token bs_token
      rep1_token rep2_token
      symbol_token num_token
      oz_token minus_token ou_token zz_token zu_token
%left <sym> plus_token star_token ques_token
%left <sym> backslash_token

%type <sym> Symbol
%type <reg> RegExp Reg BackslashReg

%%

Reg : RegExp        {
                    cout << *$1 << endl;
                    }
;

RegExp :
         //konkatenacija
        RegExp RegExp %prec concat  {
                                    $$ = new concat_reg_node($1,$2);
                                    //ispisi("RegExp","Konkatenacija");
                                    }

         // Reg | Reg
       | RegExp vert_token RegExp       {
                                        $$ = new union_reg_node($1,$3);
                                     //   ispisi("RegExp","Ili");
                                        }

         // Reg *
       | RegExp star_token              {
                                        $$ = new star_reg_node($1);
                                     //   ispisi("RegExp","Zvezdica");
                                        }

        // Reg +
       | RegExp plus_token              {
                                        $$ = new plus_reg_node($1);
                                     //   ispisi("RegExp","Plus");
                                        }

        //Reg ?
       | RegExp ques_token              {
                                        $$ = new ques_reg_node($1);
                                     //   ispisi("RegExp","Upitnik");
                                        }

         // Reg{2,3}
       | Repetition                      {
                                     //    ispisi("RegExp","Repetition");
                                         }

        // ( Reg )
       | oz_token RegExp zz_token       {
                                        $$ = $2;
                                     //   ispisi("RegExp","Zagrade");
                                        }

        // [a-z]
       | CharacterClass                 {
                                     //   ispisi("RegExp","Karakterska Klasa");
                                        }

        // ^Reg
      | caret_token RegExp               {
                                      //   ispisi("RegExp","Pocetak Reda");
                                         }

         // Reg $
       | RegExp dollar_token              {
                                      //    ispisi("RegExp","Kraj Reda");
                                          }

        //  /+
       | BackslashReg                      {
                                             $$=$1;
                                      //     ispisi("RegExp","Backslash");
                                           }

        // svi nespecijalni simboli
       | symbol_token                       {
                                              $$ = new normal_symbol_reg_node($1);
                                       //     ispisi("RegExp","Nespecijalni simbol");
                                            }

        // svi brojevi
       | num_token                          {
                                              $$ = new normal_symbol_reg_node($1);
                                        //    ispisi("RegExp","Broj");
                                            }

        // minus (kao nespecijalni simbol)
       | minus_token                          {
                                              $$ = new normal_symbol_reg_node('-');
                                         //     ispisi("RegExp","-");
                                              }

        //] kao nespecijalni simbol
       | zu_token                           {
                                             $$ = new normal_symbol_reg_node(']');
                                         //   ispisi("RegExp","[");
                                            }
;

    //Ovo je uradjeno preko leksera da prepoznaje
    // da bi se izbegli s-r konflikti
    // lakse ih je ovako eliminisati
Repetition : rep1_token         {
                                //ispisi("Repetition","{num,} ili {num}");
                                }
           | rep2_token         {
                                //ispisi("Repetition","{num,num}");
                                }
;


CharacterClass : ou_token ArraySym zu_token
                                {
                                //ispisi("CharacterClass","[ ArraySym ]");
                                }

;

ArraySym : ArraySym CharPart           {
                                        //ispisi("ArraySym","ArraySym CharPart");
                                       }
         | CharPart                    {
                                        //ispisi("ArraySym","CharPart");
                                       }
         | caret_token ArraySym        {
                                        //ispisi("ArraySym","^ArraySym");
                                       }
;

CharPart : SymbolChar minus_token SymbolChar    {
                                              //  ispisi("CharPart","SymbolChar - SymbolChar");
                                                }
         | SymbolChar                           {
                                              //  ispisi("CharPart","SymbolChar");
                                                }
;

// Izdvojeno je sve cemu moze da prethodi backslash
// s tim da su razdvojeni delovi koji sa backslashom imaju specijalno znacenje
// od onih koji nemaju
BackslashReg : d_token                  {
                                        $$ = new backslash_symbol_reg_node($1);
                                        //ispisi("BackslashReg","\\ d");
                                      //    cout << *$$ << endl;
                                        }
             | no_d_token               {
                                        $$ = new backslash_symbol_reg_node('D');
                                        //ispisi("BackslashReg","\\ D");
                                        }
             | w_token                  {
                                        $$ = new backslash_symbol_reg_node('w');
                                        //ispisi("BackslashReg","\\ w");
                                        }
             | no_w_token               {
                                        $$ = new backslash_symbol_reg_node('W');
                                        //ispisi("BackslashReg","\\ W");
                                        }
             | s_token                  {
                                        $$ = new backslash_symbol_reg_node('s');
                                        //ispisi("BackslashReg","\\ s");
                                        }
             | no_s_token               {
                                        $$ = new backslash_symbol_reg_node('S');
                                        //ispisi("BackslashReg","\\ S");
                                        }
             | b_token                  {
                                        $$ = new backslash_symbol_reg_node('b');
                                        //ispisi("BackslashReg","\\ b");
                                        }
             | backslash_token Symbol   {
                                        $$ = new backslash_symbol_reg_node($2);
                                        //ispisi("BackslashReg","\\ Symbol");
                                        }
             | n_token                  {
                                        $$ = new backslash_symbol_reg_node('n');
                                        //ispisi("BackslashReg","\\ n");
                                        }
             | bs_token                 {
                                        $$ = new backslash_symbol_reg_node('\\');
                                        //ispisi("BackslashReg","\\ \\");
                                        }
             | t_token                  {
                                         $$ = new backslash_symbol_reg_node('t');
                                        //ispisi("BackslashReg","\\ t");
                                        //cout << *$$ << endl;
                                        }
;


// kako symbol_token predstavlja samo nespecijalne simbole,
// Symbol je nesto sto grupise sve specijalne i nespecijalne simbole

Symbol : symbol_token   {
                       // ispisi("Symbol","nespecijalni simbol");
                        $$ = $1;
                        }
       | num_token      {
                       // ispisi("Symbol","broj");
                        $$ = $1;
                        }
       | plus_token     {
                       // ispisi("Symbol","+");
                        $$ = $1;
                        }
       | star_token     {
                      // ispisi("Symbol","*");
                        $$ = $1;
                        }
       | ques_token     {
                      // ispisi("Symbol","?");
                        $$ = $1;
                        }
       | vert_token     {
                      // ispisi("Symbol","|");
                        $$ = $1;
                        }
       | caret_token    {
                       // ispisi("Symbol","^");
                        $$ = $1;
                        }
       | dollar_token   {
                       // ispisi("Symbol","$");
                        $$ = $1;
                        }
       | oz_token       {
                      //  ispisi("Symbol","(");
                        $$ = $1;
                        }
       | zz_token       {
                      //  ispisi("Symbol",")");
                        $$ = $1;
                        }
       | ou_token       {
                      //  ispisi("Symbol","[");
                        $$ = $1;
                        }
       | zu_token       {
                        //ispisi("Symbol","]");
                        $$ = $1;
                        }
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

