#include <stdio.h>
#include <math.h>

/* library header */
#include "src/headers/epsLib.h"

double f(double x) {
    return x*x+1;
}

int main(void) {

    /* x and y coordinate */
    pFigure coord = generateSTD_Figure(WIDTH, HEIGHT, PIXEL_JUMP, THINCKNESS + 1.0);

    /* figure initialization without 2D point */
    pFigure funct = generateSTD_Figure(WIDTH, HEIGHT, PIXEL_JUMP, THINCKNESS);


    drawGraphPaper(coord, 2, 2);
    draw_fx(funct, f, -30, 30);

    append_figures(coord, funct);
    export_eps( coord , "draw_fx.eps" );
    
    return 0;
}