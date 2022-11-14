#include "Case.h"



Case * init_case(int x, int y){
  Case *tmp = (Case*)malloc(sizeof(Case));
  if(tmp != NULL){
    tmp->x = x;
    tmp->y = y;
  }
  return tmp;
}



