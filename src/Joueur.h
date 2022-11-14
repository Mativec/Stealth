#ifndef __JOUEUR__
#define __JOUEUR__

#include "Case.h"


typedef struct joueur{
  char* nom;
  Case position;
  int inventaire;
  int mana;
  double vitesse;
  
}Joueur;


#endif