#include "../include/Relique.h"



Engine_Relique *init_reliques(double x, double y){
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



void generate_relique(){

}



