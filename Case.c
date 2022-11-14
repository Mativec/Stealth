/**
 * @file Case.c
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Implementation du module de gestion des cases du plateau de jeu.
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Case.h"


Case * init_case(int x, int y){
  Case *tmp = (Case*)malloc(sizeof(Case));
  if(tmp != NULL){
    tmp->x = x;
    tmp->y = y;
  }
  return tmp;
}



