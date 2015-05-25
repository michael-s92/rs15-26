%{

#include <iostream>
#include <string>
#include <vector>
#include "AutomatParser/TreeNodes.hpp"
#include <QString>
#include <QDebug>

using namespace std;

extern int yylex();

void yyerror(const string s)
{

}

void ispisi(string l, string d)
{
   cout << endl << l << "  ->  " << d << endl << endl;
}

void add_vector(vector<Symbol_reg_node*> & elem_l, const vector<Symbol_reg_node*> & elem_r)
{
   vector<Symbol_reg_node *>::const_iterator i = elem_r.begin();
   for (; i!=elem_r.end(); i++)
     elem_l.push_back(*i);
}


Reg_node * reg;

Reg_node * parse(const char* s);

extern void set_text(const char *s);


%}

%union {
   char sym;
   Reg_node *reg;
   vector<Symbol_reg_node *> *vec;
   Char_class_reg_node * char_class;
   Symbol_reg_node * sym_reg;
   numbers *num;

}

%left <sym> dollar_token caret_token
%left <sym> vert_token
%left <sym> concat d_token
      no_d_token s_token no_s_token w_token no_w_token
      b_token n_token t_token bs_token

      symbol_token num_token
      oz_token minus_token ou_token zz_token zu_token
%left <sym> plus_token star_token ques_token
%left <num> rep1_token rep2_token rep3_token
%left <sym> backslash_token

%type <num> Repetition

%type <reg> RegExp RegSimple RegLasy Reg
%type <char_class> CharacterClass
%type <vec> ArraySym CharPart
%type <sym_reg> SymbolChar BackslashReg Symbol SpecSymbol

%%

// pravilo potrebno samo za ispisivanje cvora
Reg : RegExp                {
                              reg = $1;
                          //     cout << *$1 << endl;
                            }
;

// ovim pravilom obezbedjujemo da se kad imamo izraze ^^^^ reg_izraz $$$
// uzimamo u obzir samo reg_izraz


RegExp :
         // konkatenacija
        RegExp RegExp %prec concat  	{
                                        $$ = new Concat_reg_node($1,$2);
                                  //       ispisi("RegExp","Konkatenacija");
                                        }

         // unija
       | RegExp vert_token RegExp       {
                                        $$ = new Union_reg_node($1,$3);
                                  //       ispisi("RegExp","Ili");
                                        }

         // Reg *
         // Ne koristimo neterminal RegExp, vec RegSimle
         // da bi zabranili izraze reg++, reg+*, reg?{1} ...
       | RegSimple star_token           {
                                        $$ = new Star_reg_node($1);
                                  //       ispisi("RegExp","RegSimple star_token");
                                        }

        // Reg +
       | RegSimple plus_token           {
                                        $$ = new Plus_reg_node($1);
                                  //       ispisi("RegExp","RegSimple plus_token");
                                        }

        //Reg ?
       | RegSimple ques_token           {
                                        $$ = new Ques_reg_node($1);
                                  //       ispisi("RegExp","RegSimple ques_token");
                                        }

        // Reg{m,n}
       | RegSimple Repetition           {
                                         $$  = new Repetition_reg_node($1,$2->a,$2->b);
                                  //       ispisi("RegExp","RegSimple Repetition");
                                        }
        // Reg+? - za lenjo izracunavanje
        // izdvajamo posebno, jer bi u rekurziji dozvolili izraze a+????
       | RegLasy ques_token		{
                                        $$ = new Ques_reg_node($1);
                                  //       ispisi("RegExp","RegLasy ques_token");
                                        }

       | RegSimple			{
                                        $$ = $1;
                                  //       ispisi("RegExp","RegSimple");
                                        }
;

RegSimple
            // ( Reg )
          :oz_token RegExp zz_token       {
                                           $$ = $2;
                                    //        ispisi("RegSimple","( RegExp )");
                                           }

            // [a-z]
          | CharacterClass                 {
                                            $$ = $1;
                                     //        ispisi("RegSimple","Karakterska Klasa");
                                           }

            //  / slovo - skidamo specijalnu funkciju odredjenim znakovima
          | BackslashReg                   {
                                            $$=$1;
                                      //       ispisi("RegSimple","Backslash");
                                           }
          | backslash_token num_token      {
                                            $$ = new Backslash_symbol_reg_node($2);
                                      //       ispisi("RegSimple","\\ num_token");
                                           }
            // svi nespecijalni simboli
          | symbol_token                    {
                                             $$ = new Normal_symbol_reg_node($1);
                                     //         ispisi("RegSimple","Nespecijalni simbol");
                                            }
            // ovo je za one simbole koji nisu operatori, ai su opet negde specijalni
          | SpecSymbol                      {
                                             $$ = $1;
                                    //          ispisi("RegSimple","Specijalni simbol negde");
                                            }
;

RegLasy
        // Reg *
       : RegSimple star_token           {
                                        $$ = new Star_reg_node($1);
                                 //        ispisi("RegLasy","RegSimple star_token");
                                        }

        // Reg +
       | RegSimple plus_token           {
                                        $$ = new Plus_reg_node($1);
                                 //        ispisi("RegLasy","RegSimple plus_token");
                                        }

        //Reg ?
       | RegSimple ques_token           {
                                        $$ = new Ques_reg_node($1);
                                //         ispisi("RegLasy","RegSimple ques_token");
                                        }

        // Reg{2,3}
       | RegSimple Repetition           {
                                         $$  = new Repetition_reg_node($1,$2->a,$2->b);
                              //            ispisi("RegLasy","RegSimple Repetition");
                                        }
;


Repetition : rep1_token         {
                                $$ = $1;
                                }
           | rep2_token         {
                                $$ = $1;
                           //      ispisi("Repetition","{num}");
                                }
           | rep3_token         {
                                $$ = $1;
                            //     ispisi("Repetition","{num,num}");
                                }
;


CharacterClass : ou_token ArraySym zu_token
                                            {
                                            $$ = new Char_class_reg_node(*$2,true);
                                     //        ispisi("CharacterClass","[ ArraySym ]");
                                            }
               | ou_token caret_token ArraySym zu_token
                                                          {
                                                          $$ = new Char_class_reg_node(*$3,false);
                                     //                      ispisi("CharacterClass","^  [ ArraySym ]");
                                                          }

;

ArraySym : ArraySym CharPart           { $$ = $1; add_vector(*$1,*$2);
                                  //       ispisi("ArraySym","ArraySym CharPart");
                                       }
         | CharPart                    {
                                        $$ = $1;
                                  //       ispisi("ArraySym","CharPart");
                                       }
;

CharPart : SymbolChar minus_token SymbolChar    {
                                                char c1=$1->getValue();
                                                char c2=$3->getValue();
                                                if (c1 > c2)
                                                  yyerror("Syntax error: Karakterska klasa - neodgovarajuci redoled");
                                                $$ = new vector<Symbol_reg_node *>;
                                                for (char c=c1; c<=c2; c++)
                                                $$->push_back(new Normal_symbol_reg_node(c));
                                       //          ispisi("CharPart","SymbolChar - SymbolChar");

                                                }
         | SymbolChar                           {
                                                 $$ = new vector<Symbol_reg_node *>;
                                                 $$->push_back($1->clone());
                                    //              ispisi("CharPart","SymbolChar");
                                                }
;

// Izdvojeno je sve cemu moze da prethodi backslash
// s tim da su razdvojeni delovi koji sa backslashom imaju specijalno znacenje
// od onih koji nemaju
BackslashReg : d_token                  {
                                        $$ = new Backslash_symbol_reg_node('d');
                                 //        ispisi("BackslashReg","\\ d");
                                        }
             | no_d_token               {
                                        $$ = new Backslash_symbol_reg_node('D');
                                 //        ispisi("BackslashReg","\\ D");
                                        }
             | w_token                  {
                                        $$ = new Backslash_symbol_reg_node('w');
                                 //        ispisi("BackslashReg","\\ w");
                                        }
             | no_w_token               {
                                        $$ = new Backslash_symbol_reg_node('W');
                                  //       ispisi("BackslashReg","\\ W");
                                        }
             | s_token                  {
                                        $$ = new Backslash_symbol_reg_node('s');
                                  //       ispisi("BackslashReg","\\ s");
                                        }
             | no_s_token               {
                                        $$ = new Backslash_symbol_reg_node('S');
                                  //       ispisi("BackslashReg","\\ S");
                                        }
             | b_token                  {
                                        $$ = new Backslash_symbol_reg_node('b');
                                  //       ispisi("BackslashReg","\\ b");
                                        }
             | backslash_token Symbol   {
                                        $$ = new Backslash_symbol_reg_node($2->getValue());
                                  //       ispisi("BackslashReg","\\ Symbol");
                                        }
             | n_token                  {
                                        $$ = new Backslash_symbol_reg_node('n');
                                  //       ispisi("BackslashReg","\\ n");
                                        }
             | bs_token                 {
                                        $$ = new Backslash_symbol_reg_node('\\');
                                  //       ispisi("BackslashReg","\\ \\");
                                        }
             | t_token                  {
                                        $$ = new Backslash_symbol_reg_node('t');
                                  //       ispisi("BackslashReg","\\ t");
                                        }
;


// kako symbol_token predstavlja samo nespecijalne simbole,
// Symbol je nesto sto grupise sve specijalne i nespecijalne simbole

Symbol : symbol_token   {
                        $$ = new Normal_symbol_reg_node($1);
                    //     ispisi("Symbol","nespecijalni simbol");
                        }

       | SpecSymbol     {
                        $$ = $1;
                    //     ispisi("Symbol","\\ SpecSymbol");
                        }
       | plus_token     {
                        $$ = new Normal_symbol_reg_node($1);
                   //      ispisi("Symbol","+");
                        }
       | star_token     {
                        $$ = new Normal_symbol_reg_node($1);
                     //    ispisi("Symbol","*");
                        }
       | ques_token     {
                        $$ = new Normal_symbol_reg_node($1);
                     //    ispisi("Symbol","?");
                        }
       | vert_token     {
                        $$ = new Normal_symbol_reg_node($1);
                     //    ispisi("Symbol","|");
                        }
       | oz_token       {
                        $$ = new Normal_symbol_reg_node($1);
                    //     ispisi("Symbol","(");
                        }
       | zz_token       {
                        $$ = new Normal_symbol_reg_node($1);
                    //     ispisi("Symbol",")");
                        }
       | ou_token       {
                        $$ = new Normal_symbol_reg_node($1);
                    //     ispisi("Symbol","[");
                        }
;

SpecSymbol : minus_token		{
                                        $$ = new Normal_symbol_reg_node('-');
                                  //       ispisi("SpecSymbol","-");
                                        }
           | zu_token			{
                                        $$ = new Normal_symbol_reg_node(']');
                                 //        ispisi("SpecSymbol","]");
                                        }
           | caret_token		{
                                        $$ = new Normal_symbol_reg_node('^');
                               //          ispisi("SpecSymbol","^");
                                        }
           | dollar_token		{
                                        $$ = new Normal_symbol_reg_node('$');
                            //             ispisi("SpecSymbol","$");
                                        }


// SymbolChar predstavlja sve simbole koji se mogu naci unutar karakterske
// klase

SymbolChar : symbol_token   {
                            $$ = new Normal_symbol_reg_node($1);
                         //    ispisi("SymbolChar","nespecijalni simbol");
                            }
           | num_token      {
                            $$ = new Normal_symbol_reg_node($1);
                         //    ispisi("SymbolChar","broj");
                            }
           | BackslashReg   {
                             $$ = $1;
                        //     ispisi("SymbolChar","\\");
                            }
           | backslash_token num_token   {
                                         $$ = new Backslash_symbol_reg_node($2);
                                //          ispisi("BackslashReg","\\ num_token");
                                         }
           | plus_token     {
                            $$ = new Normal_symbol_reg_node($1);
                          //   ispisi("SymbolChar","+");
                            }
           | star_token     {
                            $$ = new Normal_symbol_reg_node($1);
                          //   ispisi("SymbolChar","*");
                            }
           | ques_token     {
                            $$ = new Normal_symbol_reg_node($1);
                         //    ispisi("SymbolChar","?");
                            }
           | vert_token     {
                             $$ = new Normal_symbol_reg_node($1);
                          //   ispisi("SymbolChar","|");
                            }
           | dollar_token   {
                            $$ = new Normal_symbol_reg_node($1);
                           //  ispisi("SymbolChar","$");
                            }
           | oz_token       {
                            $$ = new Normal_symbol_reg_node($1);
                           //  ispisi("SymbolChar","(");
                            }
           | zz_token       {
                            $$ = new Normal_symbol_reg_node($1);
                           //  ispisi("SymbolChar",")");
                            }
           | ou_token       {
                            $$ = new Normal_symbol_reg_node($1);
                           // ispisi("SymbolChar","[");
                            }
;

%%

Reg_node * parse(const char *s)
{
  reg = 0;
  set_text(s);
  if (yyparse()==0)
    return reg;
  else
    return 0;
}


