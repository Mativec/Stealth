/**
 * @file Joueur.h
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Module de gestion du joueur
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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