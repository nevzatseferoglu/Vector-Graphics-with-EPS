#include <stdio.h>
#include <time.h>
#include "src/headers/epsLib.h"

#define RANDOM_LIMIT 1000

int main(void) {
    
    srand(time(NULL));   // Initialization, should only be called once.
    int random; 

    /* x and y axis */
    //pFigure coord = generateSTD_Figure(WIDTH, HEIGHT, PIXEL_JUMP, THINCKNESS - 0.09);
    
    pTree root = NULL;
    pFigure fig = generateSTD_Figure(WIDTH, HEIGHT, PIXEL_JUMP, THINCKNESS);

    for(int i = 0 ; i < 12 ; ++i) {
        random = rand() % RANDOM_LIMIT;
        insert(&root, random);
    }

    //drawGraphPaper(coord, 3, 3);
    draw_binary_tree(fig, root);
    tearUp(root);

    //append_figures(coord, fig);
    export_eps(fig , "draw_bst.eps" );
    
    return 0;
}