#include "../include/Guards.h"


int collision(Engine_Obj *guard, Engine_Obj *player){
    if(guard->x == player->x && guard->y == player->y)
        return 1;
    else
        return 0;
}











