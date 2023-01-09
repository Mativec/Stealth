#include "../include/Relique.h"



Engine_Relique *init_relique(double x, double y){
    Engine_Relique *tmp = (Engine_Relique*)malloc(sizeof(Engine_Relique));
    if(tmp != NULL){
        tmp->obj = *init_object(x, y);
        tmp->is_picked_up = 0;
    }
    return tmp;
}

/*pointeur vers un tableau **tab*/
void add_Relique(Engine_Relique** tab, int* nb_reliques, Engine_Relique relique){
    static int buffer = 0;

    assert(tab != NULL);
    assert(nb_reliques != NULL);


    if (buffer == 0) {
        buffer = 1;
        *tab = (Engine_Relique*)malloc(sizeof(Engine_Relique) * buffer);
    }
    /*if we have necessary memory to avoid the segfault*/
    if (*nb_reliques >= buffer) {
        while ((*nb_reliques) >= buffer) {
            buffer *= 2;
        }
        *tab = realloc(*tab, sizeof(Engine_Relique) * buffer);
    }
    if ((*tab) == NULL) {
        fprintf(stderr, "failed to create a relique...");
        exit(EXIT_FAILURE);
    }

    (*tab)[(*nb_reliques)] = relique;
    (*nb_reliques)++;
}

void genere_relique(Engine_Relique **tab, int *nb_reliques, Engine_Walls walls, int nb_walls){
    int i, x , y;
    Engine_Relique *tmp;
    

    for(i = 0; i < 3; i++){
        do{
            x =  rand() % SIZE_X;
            y =  rand() % SIZE_Y;
            tmp = init_relique((double)x,(double)y);
        }while (wall_collision(tmp->obj, walls, nb_walls ));
        
        add_Relique(tab, nb_reliques, *tmp );
    }

}


void test_coord_reliques_joueurs(Engine_Relique *reliques, Engine_Player player, int nb_reliques){
    int i;
    for(i = 0; i < nb_reliques; i++){
        printf("pos joueur %f %f\n pos relique %f %f", player.obj.x, player.obj.y , reliques[i].obj.x, reliques[i].obj.y);
    }
}



void free_reliques(Engine_Relique **tab){
    free(tab);
}




