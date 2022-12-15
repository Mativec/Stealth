/**
 * @file Guards.c
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Implémentation du module des gardes
 * @version 0.1
 * @date 2022-11-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../include/Guards.h"

/*essayer de gerer la colision avec les angles de vues et le toucher du garde*/
/*essayer de gerer la colision avec les angles de vues et le toucher du garde*/
int collision(Engine_Obj guard, Engine_Obj player) {
  double d;


  d = distance_between_objects(guard, player);

  if(d < SIGHT_GUARDIAN - SIZE_PLAYER ){
    printf("reussi");
    return 1;
  }
  else if(d < SIZE_PLAYER - SIGHT_GUARDIAN){
    printf("reussi");
    return 1;
  }
  else if(d < SIGHT_GUARDIAN + SIZE_PLAYER){
    return 1;
  }
  else if(d == SIGHT_GUARDIAN + SIZE_PLAYER){
    return 1;
  }
  else{
    return 0;
  }
}