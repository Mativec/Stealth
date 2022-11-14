/**
 * @file Case.h
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Module de gestion des cases du plateua de jeu.
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __CASE__
#define __CASE__

#include <stdio.h>
#include <stdlib.h>

#define TAILLE_X 60 
#define TAILLE_Y 45



typedef struct {
    int x, y;
    int test;
}Case;





/*fonction permettant d'initialiser la case*/
Case * init_case(int x, int y);





#endif