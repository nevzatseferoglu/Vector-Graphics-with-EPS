#include <stdio.h>
#include "src/headers/epsLib.h"

int main(void) {

    /* x and y axis */
    pFigure coord = generateSTD_Figure(WIDTH, HEIGHT, PIXEL_JUMP, THINCKNESS - 0.09);
    
    drawGraphPaper(coord, 50, 50);

    export_eps(coord , "draw_grid.eps" );
    
    return 0;
}