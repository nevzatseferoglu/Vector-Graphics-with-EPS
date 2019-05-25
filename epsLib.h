#ifndef _EPSLIB_
#define _EPSLIB_

typedef struct{
	/* Colors */
	double red;
	double green;
	double blue;
}Color;

typedef struct Point2D{
	double x; /* To take under the control of x axis of my each point */
	double y; /* To take under the control of y axis of my each point */
	struct Point2D* next;
}Point2D;

typedef struct Tree{
	struct Tree* rightChild;
	double data;
	struct Tree* leftChild;
}Tree;

typedef struct Text{
	struct Text* next; 
	double x; /* X axis of text */
	double y; /* Y axis of text */
	int number; /*number in the binary Tree*/
}Text;

typedef struct Figure{
	double urx, ury, llx, lly; /*The four arguments of the bounding box comment correspond to the lower-
	left (llx, lly) and upper-right (urx, ury) corners of the bounding box.*/
	double thickness;
	double resolution;
	Color c;
	Point2D* point;
	Text* textPoint;
	struct Figure* next;
}Figure;

/* Start figure : create a new figure and arranging bounding box of the canvas */
Figure* start_figure(double width, double height);
/* Setting the thickness and resolution */
void set_thickness_resolution(Figure *fig,double thickness,double resolution);
/* Setting the color of the figure */
void set_color(Figure  * fig, Color c);
/* Drawing a function with help of math */
void draw_fx(Figure  * fig, double f(double x),double start_x,double end_x);
void draw_polyline(Figure * fig,Point2D *poly_line, int n);
/* Drawing Polyline */
void draw_circle(Figure * fig,Point2D *center, double radius);
/* Drawing Circle  */
void draw_ellipse(Figure * fig, Point2D * center,double axis_x,double axis_y);
/* Drawing Ellipse */
void scale_figure(Figure * fig,double scale_x,double scale_y);
/* Scaling Figure */
void resize_figure(Figure * fig,Point2D start_roi,Point2D end_roi);
/* Resizing */
void append_figures(Figure * fig_1,Figure* fig_2);
/* Appending figures with each other */
void export_eps(Figure * fig, char * file_name);
/* Exporting Eps */
void export_svg(Figure * fig, char * file_name);
/* Drawing Binary Tree */
void draw_binary_tree(Figure* fig,Tree* root);
/* Make Memory Free */
void free_all_allocated_memory(Figure * fig);
#endif