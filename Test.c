/**
 * @file Test.c
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Implémentation du module de test
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Test.h"

int test_init_case(){
    int x, y;
    int result;
    Case * test;

    x = 5;
    y = 3;

    test = init_case(x, y);
    if (test->x == x && test->y == y)
    {
        result = 1;
    }
    else{
        fprintf(stderr, "case is null\n");
        result = 0;
    }

    free(test);
    return result;
}