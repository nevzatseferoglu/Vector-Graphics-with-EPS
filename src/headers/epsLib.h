#ifndef _EPSLIB_
#define _EPSLIB_

#include <stdio.h> 		/* Standart Library */
#include <stdlib.h> 	/* For dynamic memory allocation */
#include <math.h> 		/* For mathematical equation and calculation */
#include <stdbool.h>	/* Standart C library to get bool effect */
#include "bst.h"

/* Size are equivalent to sample A4 */
#define WIDTH 200
#define HEIGHT 200

#define THINCKNESS 0.1
#define RESOLUTION 20

/* Pi number */
#define PI 3.14159265358979323846

/* Number of the pixel per some physical unit */
#define PIXEL_JUMP  ((double) ((1.0000) / (RESOLUTION)))

typedef struct Figure 	Figure;
typedef struct Color 	Color;
typedef struct Text 	Text;
typedef struct Point2D 	Point2D;


typedef Figure* 	pFigure;
typedef Point2D* 	pPoint2D;

struct Color {

	double red;
	double green;
	double blue;

};

struct Text {

	double size;
	double x;
	double y;
	int num;

};

struct Point2D {

	/* To take under the control of coordinates of my each point */
	double x; 
	double y;

	struct Point2D* next;
	bool isMoveto;
};


struct Figure{

	/* The four arguments of the bounding box comment correspond to the lower-
		left (llx, lly) and upper-right (urx, ury) corners of the bounding box. */
	double urx, ury, llx, lly;

	double thickness;
	double resolution;
	Color color;
	Text* text;
	pPoint2D point;
	struct Figure* next;

};

/* Create a point */
pPoint2D newPoint(double x , double y  , pPoint2D next , bool isMoveto);

/* Create a new figure and arranging bounding box of the canvas */
pFigure start_figure(double width, double height);

/* Setting the thickness and resolution */
void set_thickness_resolution(pFigure fig, double thickness, double resolution);

/* Setting the color of the figure */
void set_color(pFigure fig, Color c);

/* Generate a standart figure */
pFigure generateSTD_Figure(double width, double height, double resolution, double thickness);

/* Drawing a function with help of math */
void draw_fx(pFigure fig, double f(double x),double start_x,double end_x);

/* Drawing polylines functions */
void draw_polyline(pFigure fig, pPoint2D pointArray, int n);

/* Draw a graph-paper according to given xSize and ySize */
void drawGraphPaper(pFigure fig , int xSquareNumber , int ySquareNumber);

/* Draw a circle */
void draw_circle(pFigure fig , pPoint2D center , double radius);

/* Draw an ellipse */
void draw_ellipse(pFigure fig , pPoint2D center , double majorAxis , double minorAxis);

/* Draw a binary tree */
void draw_binary_tree(pFigure fig, pTree root);

/* Append two figures */
void append_figures(pFigure first, pFigure second);

/* Export as eps file */
void export_eps(pFigure fig, const char * file_name);

/* Make allocated memory free */
void free_all_allocated_memory(pFigure fig);

#endif