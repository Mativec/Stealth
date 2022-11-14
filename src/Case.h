#ifndef __CASE__
#define __CASE__

#include <stdio.h>
#include <stdlib.h>

#define TAILLE_X 60 
#define TAILLE_Y 45



typedef struct {
    int x, y;
    int test;
}Case;





/*fonction permettant d'initialiser la case*/
Case init_case(int x, int y);





#endif