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
int collision(Engine_Obj guard, Engine_Obj player) {
    if (((guard.x == player.x && guard.y == player.y) || (player.x == guard.x - 5 || player.x == guard.x + 5)) && ((player.y == guard.x - 5 || player.x == guard.x + 5))) {
        return 1;
    } else {
        return 0;
    }
}
