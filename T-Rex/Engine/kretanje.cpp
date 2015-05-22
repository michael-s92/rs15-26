#include "kretanje.h"

Kretanje::Kretanje()
{

}

Kretanje::Kretanje(int br_stanja)
{
   nodes.resize(br_stanja);
   prelazi.resize(br_stanja);
   for (int i=0; i< prelazi.length(); i++)
       prelazi[i].resize(br_stanja);
}
