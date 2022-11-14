#ifndef __PLATEAU__
#define __PLATEAU__

#include "Case.h"





typedef struct plateau{
    Case* joueur;

    Case* mur;
    int nb_murs;

    Case* relique;
    int nb_reliques;
    
    Case* gardien;
}*Plateau;






#endif