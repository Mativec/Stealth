#include "../include/Relique.h"



Engine_Relique *init_relique(double x, double y){
    Engine_Relique *tmp = (Engine_Relique*)malloc(sizeof(Engine_Relique));
    if(tmp != NULL){
        tmp->obj = *init_object(x, y);
        tmp->is_picked_up = 0;
    }
    return tmp;
}

void generate_relique(Engine_Relique **tab, Engine_Obj spawn, Engine_Walls walls, int nb_walls){
    int i, x , y;
    Engine_Relique *tmp;
    
    *tab = (Engine_Relique*)malloc(sizeof(Engine_Relique) * NB_RELIQUES);

    for(i = 0; i < NB_RELIQUES; i++){
        do{
            x =  rand() % SIZE_X;
            y =  rand() % SIZE_Y;
            tmp = init_relique((double)x,(double)y);
        }while (distance_between_objects(spawn, tmp->obj) < 20 && wall_collision(tmp->obj, walls, nb_walls ));
        
        (*tab)[i] = *tmp;
    }

}


void test_coord_reliques_joueurs(Engine_Relique *reliques, Engine_Player player){
    int i;
    for(i = 0; i < NB_RELIQUES; i++){
        printf("pos joueur : %s\n pos relique : %s", object_to_string(player.obj) , object_to_string(reliques[i].obj));
    }
}
