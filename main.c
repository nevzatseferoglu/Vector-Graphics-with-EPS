#include <stdio.h> /* Standart Library */
#include <stdlib.h> /* For Dynamic Memory Allocation ex. malloc */
#include  <math.h> /* For mathematical equation and calculation */
#include "headers/epsLib.h" /* Project Main Lib.*/
double f(double x);
int main()
{
	Figure *fig_1=NULL,*fig_2=NULL,*fig_3=NULL,*fig_4=NULL,*fig_5=NULL;
	/* I have five different figure , We can draw each one as alone or together */

	int i=0,size;
	double width=100,height=100; /* Arranging Bounding Box */
	double thickness=0.1,resolution=0.02,radius,axis_x,axis_y;
	/* My figures have several own properties like radius , thickness, resolution .. */
	
	Color c; /* Color Arranging */
	Tree* root;  /* Binary Tree */
	Point2D* poly_line; /* PolyLine Figure ,  I filled in its own function with dynamic memory allocation */

	/* Sample Binary Tree Implementation */
	root=(Tree*)malloc(sizeof(Tree));
	root->data=10;
	root->rightChild=NULL,root->leftChild=NULL;
	root->rightChild=(Tree*)malloc(sizeof(Tree));
	root->rightChild->data=89;
	root->rightChild->rightChild=NULL,root->rightChild->leftChild=NULL;
	root->leftChild=(Tree*)malloc(sizeof(Tree));
	root->leftChild->data=100;
	root->leftChild->rightChild=NULL,root->leftChild->leftChild=NULL;
	root->rightChild->rightChild=(Tree*)malloc(sizeof(Tree));
	root->rightChild->rightChild->data=54;
	root->rightChild->rightChild->rightChild=NULL,root->rightChild->rightChild->leftChild=NULL;
	root->leftChild->leftChild=(Tree*)malloc(sizeof(Tree));
	root->leftChild->leftChild->data=4;
	root->leftChild->leftChild->rightChild=NULL,root->leftChild->leftChild->leftChild=NULL;
	root->leftChild->rightChild=(Tree*)malloc(sizeof(Tree));
	root->leftChild->rightChild->data=11;
	root->leftChild->rightChild->rightChild=NULL,root->leftChild->rightChild->leftChild=NULL;
	/*------End------------------------------------------*/


	/* to fill center , ı need to allocate from the memory */
	Point2D* center=(Point2D*)malloc(sizeof(Point2D));

	/*It is test for resizing operation */
	/*
		Point2D testA;
		Point2D testB;
		testA.x=-50;
		testA.y=-50;
		testB.x=100;
		testB.y=100;
	*/

	/*Creating fig_1 for using in asd*/
	fig_1=start_figure(width,height);
	set_thickness_resolution(fig_1,thickness,resolution);
	c.red=1,c.green=0,c.blue=0;
	set_color(fig_1,c);
	draw_fx(fig_1,f,-30,30);
	/*------End----------------------*/

	/*Creating fig_2 for using in asd*/
	fig_2=start_figure(width,height);
	set_thickness_resolution(fig_2,thickness,resolution);
	c.red=0,c.green=1,c.blue=0;
	set_color(fig_2,c);
	center->x=-30.0;
	center->y=20.0;
	radius=7.0;
	draw_circle(fig_2,center,radius);
	/*-----------End--------------------*/

	/*Creating fig_3 for using in asd*/
	fig_3=start_figure(width,height);
	set_thickness_resolution(fig_3,thickness,resolution);
	c.red=0,c.green=0,c.blue=1;
	set_color(fig_3,c);
	center->x=20.0;
	center->y=20.0;
	axis_x=5;
	axis_y=8;
	draw_ellipse(fig_3,center,axis_x,axis_y);
	/*-----------End--------------------*/

	/*Creating fig_4 for using in asd*/
	fig_4=start_figure(width,height);
	c.red=0,c.green=0,c.blue=1;
	set_thickness_resolution(fig_4,thickness,resolution);
	set_color(fig_4,c);
	draw_polyline(fig_4,poly_line,5);
	/*-----------End--------------------*/

	/*Creating fig_5 for using in asd*/
	fig_5=start_figure(width,height);
	c.red=0,c.green=0,c.blue=0;
	set_thickness_resolution(fig_5,thickness,resolution);
	set_color(fig_5,c);
	draw_binary_tree(fig_5,root);
	/*-----------End--------------------*/

	/*resize_figure(fig_1,testA,testB);*/
	
	/* Appending figures with each other */
	append_figures(fig_1,fig_2);
	append_figures(fig_2,fig_3);
	append_figures(fig_3,fig_4);
	append_figures(fig_4,fig_5);
	/*--------End------------------------*/


	export_eps(fig_1,"mix.eps");
	
	/* I added this function to the library because of purpose of using in main function */
	free_all_allocated_memory(fig_1); 

	return 0;
}
/* Math Function for sending to teh draw-fx function */
double f(double x)
{
	return cos(x);
}