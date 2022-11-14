/**
 * @file Plateau.h
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Module de gestion du plateau de jeu
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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