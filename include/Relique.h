#ifndef __RELIQUE__
#define __RELIQUE__

#include <assert.h>
#include <stdlib.h>
#include "Object.h"


typedef struct{
    Engine_Obj obj;
    int is_picked_up;
}Engine_Relique;



Engine_Relique *init_reliques(double x, double y);

void add_Relique(Engine_Relique** tab, int* nb_reliques, Engine_Relique relique);



#endif