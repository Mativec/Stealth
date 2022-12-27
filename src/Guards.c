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



Engine_Guard *init_guard(int x, int y){

  Engine_Guard *new;
  new = (Engine_Guard*) malloc(sizeof(Engine_Guard));

  if (new != NULL) {
    new->obj = init_object(x, y, SPEED_GUARD );
    new->direction = OBJECT_NONE;
    new->cpt = 0;
    }
    return new;


}



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




Engine_Orientation guard_direction(){
  int direction;

  direction = rand() % 4;
  switch(direction){
  case 0:
    return OBJECT_UP;
  case 1:
    return OBJECT_LEFT;
  case 2:
    return OBJECT_DOWN;
  case 3:
    return OBJECT_RIGHT;
  }
  return OBJECT_NONE;
}


void move_guard(Engine_Guard *guard){
  guard->cpt--;

  if(guard->cpt <= 0){
    guard->cpt = FREQ_MOVE_GUARD;
    guard->direction = guard_direction();
  }
  move_object(guard->obj, guard->direction);
  
  if(out_of_bound(guard->obj)){
    move_object(guard->obj, OBJECT_REVERT);
    move_guard(guard);
  }
}