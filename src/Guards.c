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
  double x1, x2, y1, y2, r1, r2;

  x1 = guard.x;
  x2 = player.x;
  y1 = guard.y;
  y2 = player.y;
  r1 = 40;
  r2 = 5;


  d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

  if(d <= r1 - r2 ){
    printf("reussi");
    return 1;
  }
  else if(d <= r2 - r1){
    printf("reussi");
    return 1;
  }
  else if(d < r1 + r2){
    return 1;
  }
  else if(d == r1 + r2){
    return 1;
  }
  else{
    return 0;
  }
}