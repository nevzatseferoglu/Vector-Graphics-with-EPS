#include <stdio.h>
#include <math.h>

/* library header */
#include "src/headers/epsLib.h"

int main(void) {

    /* colors of circles */
    Color cx = {.blue=1, .green=0, .red=0};
    Color cy = {.blue=0, .green=1, .red=0};
    Color cz = {.blue=0, .green=0, .red=1};

    /* x and y axis */
    pFigure coord = generateSTD_Figure(WIDTH, HEIGHT, PIXEL_JUMP, THINCKNESS + 1.0);
    
    /* figure initialization without 2D point */
    pFigure circle_x = generateSTD_Figure(WIDTH, HEIGHT, PIXEL_JUMP, THINCKNESS + 0.5);
    circle_x -> color = cx;

    pFigure circle_y = generateSTD_Figure(WIDTH, HEIGHT, PIXEL_JUMP, THINCKNESS + 0.7);
    circle_y -> color = cy;

    pFigure circle_z = generateSTD_Figure(WIDTH, HEIGHT, PIXEL_JUMP, THINCKNESS + 0.9);
    circle_z -> color = cz;


    drawGraphPaper(coord, 2, 2);
    draw_circle(circle_x, newPoint(40.0, 40.0, NULL, false), 20.0);
    draw_circle(circle_y, newPoint(-40.0, 40.0, NULL, false), 10.0);
    draw_circle(circle_z, newPoint(-40.0, -40.0, NULL, false), 20.0);

    append_figures(coord, circle_x);
    append_figures(circle_x, circle_y);
    append_figures(circle_y, circle_z);
    export_eps( coord , "draw_circle.eps" );
    
    return 0;
}