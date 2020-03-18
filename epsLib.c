/****************************************************************************
 *     Term Project                                   						*
 *     NEVZAT SEFEROGLU                                						*
 *	   171044024    														*
 *	   This program was writen by citizen of th GORA 					    *
 *     ---------------------                                                *
 *     This program implements a vector graphics library that can draw      *
 *     vector graphics and exports EPS formatted files including graphics.  *
 *     You can append figures in different thickness and color.             *
 *     These functions could not completed yet in this version:             *
 *     --------------------------------------------------------				*
 *     ->draw_koch_snowflake	                                            *
 *     ->draw_fractal_tree,                              				    *
 *     ->draw_fractal_atree.                                                *
 *     Environment Info :													*
 *                  Compiler : gcc version 8.3.0 (Ubuntu 8.3.0-6ubuntu1)    *
 *                  OS : Kubuntu (Debian Based) Linux                       *
 *                                                                          *
 *    Date :  24/05/2019                                                    *
 ****************************************************************************/
#include <stdio.h> /* Standart Library */
#include <stdlib.h> /* For Dynamic Memory Allocation ex. malloc */
#include  <math.h> /* For mathematical equation and calculation */
#include "headers/epsLib.h" /* Project Main Lib.*/
#define PI 3.14159 /* Pi Number */

enum bool{false,true}; /* Boolean Operation */

/*Function that I use */
int calculatNodeAmount(Tree* root);
void drawTrees(Tree* root,Point2D *center,int horizonal,int vertical,int radius,Figure* fig);
void free_all_allocated_memory(Figure * fig);
Figure* createFigure(Figure* fig);
void resize_figure(Figure* fig,Point2D start_roi,Point2D end_roi);

Figure * start_figure(double width, double height)
{
	Figure *fig=(Figure*)malloc(sizeof(Figure)); /* defined new figure */
	/*Arranging BoundingBox */
	fig->urx=width/2.0;
	fig->ury=height/2.0;
	
	fig->llx=-width/2.0; 
	fig->lly=-height/2.0;

	/* Returning Figure Struct */
	return fig;
}
void set_thickness_resolution(Figure *fig,double thickness,double resolution)
{
	/* Setting Thinkness */
	fig->thickness=thickness;
	fig->resolution=resolution;
}
void set_color(Figure* fig, Color c)
{
	/* Setting Color */
	fig->c.red=c.red;
	fig->c.green=c.green;
	fig->c.blue=c.blue;
}
void draw_fx(Figure* fig, double f(double x), double start_x, double end_x)
{
	Point2D *head=(Point2D*)malloc(sizeof(Point2D));

	fig->point=head;

		while(start_x<end_x)
		{
			/* incrementation with resolution till te end of the function range */
			head->x=15+start_x;
			head->y=f(start_x);
			head->next=(Point2D*)malloc(sizeof(Point2D));
			head=head->next;
			head->next=NULL;
			start_x=start_x+(fig->resolution);
		}
		head->x=15+end_x;
		head->y=f(end_x);
}
void draw_binary_tree(Figure* fig,Tree* root)
{
	/*Valiable Arrenging before sending drawTrees() function */
	Point2D* center=(Point2D*)malloc(sizeof(Point2D));
	/*Default Radius : 2 */
	double radius=2,x,y;
	int nodeAmount=0;
	int horizonal;
	int vertical;

	center->x=-25.0;
	center->y=-15.0;

	draw_circle(fig,center,radius);
	fig->textPoint=(Text*)malloc(sizeof(Text));
	fig->textPoint->x=center->x;
	fig->textPoint->y=center->y;
	fig->textPoint->number=(int)root->data;

	nodeAmount=calculatNodeAmount(root);
	horizonal=((radius)*(nodeAmount)/2)+1;
	vertical=horizonal;

	drawTrees(root,center,horizonal,vertical,radius,fig);
}
int calculatNodeAmount(Tree* root)
{
	int count=0;
	/* Calculating amount of node in binary tree */
	if(root==NULL)
		return count;
	else
	{
		++count; /* Incrementation of count beacause of the first node */
		if(root->rightChild!=NULL)
		{
			count+=calculatNodeAmount(root->rightChild);
		}
		if(root->leftChild!=NULL)
		{
			count+=calculatNodeAmount(root->leftChild);
		}
	}
	return count;
}
void drawTrees(Tree* root,Point2D *center,int horizonal,int vertical,int radius,Figure* fig)
{
	/*Purpose : Drawing Circle*/
	double x,y,a,b;
	Figure *newFig,*newLineRight,*newLineLeft;
	
	a=1.2;
	b=sqrt(radius*radius-a*a);
	x=center->x;
	y=center->y;
	/* Center of my main circle */
	/* I use recursion method to draw a binary tree */
	/* Because I need to do many jobs at the same time (open to comment */
	if(root!=NULL)
	{
		/* After controlling each node whether it is NULL or not , if it is not go ahead */
		newFig=createFigure(fig);
		draw_circle(newFig,center,radius);

		/* Appending each circle with eac other */
		append_figures(fig,newFig);

		if(root->rightChild != NULL)
		{
			/*Inside of this condition , I arranged the center of each circle and its text included */
			newLineRight=createFigure(fig);
			newLineRight->point=(Point2D*)malloc(sizeof(Point2D));
			newLineRight->point->x=center->x+a;
			newLineRight->point->y=center->y-b;
			center->x+=horizonal;
			center->y-=vertical;
			/* Changing center->x and center->y */

			newLineRight->textPoint=(Text*)malloc(sizeof(Text));
			newLineRight->textPoint->x=center->x;
			newLineRight->textPoint->y=center->y;
			newLineRight->textPoint->number=(int)root->rightChild->data;

			newLineRight->point->next=(Point2D*)malloc(sizeof(Point2D));
			newLineRight->point->next->x=center->x;
			newLineRight->point->next->y=center->y+radius;
			newLineRight->point->next->next=NULL;

			/* Apending a last figure */

			append_figures(fig,newLineRight);
			drawTrees(root->rightChild,center,--horizonal,vertical,radius,fig);
		}
		if(root->leftChild != NULL)
		{
			center->x=x;
			center->y=y;
			/*Inside of this condition , I arranged the center of each circle and its text included */
			newLineLeft=createFigure(fig);
			newLineLeft->point=(Point2D*)malloc(sizeof(Point2D));
			newLineLeft->point->x=center->x-a;
			newLineLeft->point->y=center->y-b;
			center->x-=horizonal;
			center->y-=vertical;

			newLineLeft->textPoint=(Text*)malloc(sizeof(Text));
			newLineLeft->textPoint->x=center->x;
			newLineLeft->textPoint->y=center->y;
			newLineLeft->textPoint->number=(int)root->leftChild->data;


			newLineLeft->point->next=(Point2D*)malloc(sizeof(Point2D));
			newLineLeft->point->next->x=center->x;
			newLineLeft->point->next->y=center->y+radius;
			newLineLeft->point->next->next=NULL;

			/* Apending a last figure */
			append_figures(fig,newLineLeft);
			drawTrees(root->leftChild,center,--horizonal,vertical,radius,fig);
		}
	}
	/*-----------------------End------------------------------------------*/
}
void draw_polyline(Figure * fig,Point2D* poly_line,int n)
{
	/* This function purpose is constitute a figure which include many polylines */
	int i=0;
	poly_line=(Point2D*)malloc((sizeof(Point2D))*(n+1));
	fig->point=&poly_line[0];
	poly_line[0].x=0; /*Initial coordinate which will be started to draw */
	poly_line[0].y=0;
	poly_line[0].next=&poly_line[1];

	for(i=1 ; i<n ; ++i)
	{
		poly_line[i].x=poly_line[i-1].x+i*(i-1);
		poly_line[i].y=poly_line[i-1].y-i;
		poly_line[i].next=&poly_line[i+1];
	}
	
	poly_line[n].x=poly_line[n-1].x+(n-1)*(n-1);
	poly_line[n].y=poly_line[n-1].y-(n-1);
	poly_line[n].next=NULL;
}
void draw_circle(Figure * fig,Point2D* center, double radius)
{
	/*I draw the circle thanks to math science ,  I used trigonometric function and its own value */
	/*My x axis was = cos(x) , my y axis was = sin(x) */
	/* Resolution was directly related to the my point amount till the end */
	double degree=0,center_x,center_y;
	Point2D *head=(Point2D*)malloc(sizeof(Point2D));

	center_x=center->x;
	center_y=center->y;

	fig->point=head;
	/*This loop is main loop for drawing circle*/
	/* While constricting this function , I realize that ,my figure actually is  not a circle , it is a polygon which has hundreds of edge */
	/* It was awesome */
	for(degree=0 ; degree<=360 ; degree=degree+fig->resolution)
	{
		head->x=center_x+cos(degree * PI / 180.0)*radius; /*Arraging */
		head->y=center_y+sin(degree * PI / 180.0)*radius;
		head->next=(Point2D*)malloc(sizeof(Point2D));
		head=head->next;
		head->next=NULL;
	}
	head->x=center_x+cos(360 * PI / 180.0)*radius; /*Arraging */
	head->y=center_y+sin(360 * PI / 180.0)*radius;
}
void draw_ellipse(Figure* fig,Point2D* center,double axis_x,double axis_y)
{
	/* I used the same method of the drawing circle to draw ellipse */
	/* Differences is  that there are two different variable as a and b instead of radius */
	double degree=0;
	double center_x,center_y;
	Point2D *head=(Point2D*)malloc(sizeof(Point2D));

	center_x=center->x;
	center_y=center->y;
	fig->point=head;

	for(degree=0 ; degree<=360 ; degree=degree+fig->resolution)
	{
		head->x=center_x+cos(degree * PI / 180.0)*axis_x; 
		head->y=center_y+sin(degree * PI / 180.0)*axis_y;

		head->next=(Point2D*)malloc(sizeof(Point2D));
		head=head->next;
		head->next=NULL;
	}
	head->x=center_x+cos(360 * PI / 180.0)*axis_x;
	head->y=center_y+sin(360 * PI / 180.0)*axis_y;
}
void scale_figure(Figure* fig,double scale_x,double scale_y)
{

}
void resize_figure(Figure* fig,Point2D start_roi,Point2D end_roi)
{
	fig->llx=start_roi.x; /*Changing the lower coordinate of BoundingBox */
	fig->lly=start_roi.y; 

	fig->urx=end_roi.x;		/*Changing the upper coordinate of BoundingBox */
	fig->ury=end_roi.y;
}
void append_figures(Figure* fig_1,Figure* fig_2)
{
	/* I append two figure with going through the end of the first figure which is fig_1*/
	/* And I add another fig to the next of first one */
	while(fig_1->next != NULL)
		fig_1=fig_1->next;
	fig_1->next=fig_2;
}
void export_eps(Figure* fig, char * file_name)
{
	FILE *fp;
	if(fig==NULL)
	{
		/* Checking the Figure whether it is empty or not */
		fprintf(stderr,"Error , fig is empty ! ");
		exit(1);
	}
	else
	{
		fp=fopen(file_name,"w");
		fprintf(fp,"%%!!PS-Adobe-3.0 EPSF-3.0\n");
		fprintf(fp,"%%%%BoundingBox: %.3lf %.3lf %.3lf %.3lf\n",fig->llx,fig->lly,fig->urx,fig->ury);
		fprintf(fp,"%.3lf setlinewidth\n",fig->thickness);
		fprintf(fp,"\n/Times-Roman findfont\n%.2lf scalefont\nsetfont ",11*fig->thickness); /* configurations */

		if(!fig->textPoint)
		{
			/* for drawing x and y axis on the canvas */
			fprintf(fp,"0.000 0.000 0.000 setrgbcolor\n");
			fprintf(fp,"%.3lf 0.000 moveto\n",fig->llx);
			fprintf(fp,"%.3lf 0.000 lineto\n",fig->urx);
			fprintf(fp,"0.000  %.3lf moveto\n",fig->ury);
			fprintf(fp,"0.000  %.3lf lineto\n",fig->llx);
			fprintf(fp,"stroke\n");
		}
		while(fig!=NULL)
		{
			/* Setting width and color of each figure */
			fprintf(fp,"%.3lf setlinewidth\n",fig->thickness);
			fprintf(fp,"%.3lf %.3lf %.3lf setrgbcolor\n",fig->c.red,fig->c.green,fig->c.blue);
			fprintf(fp,"stroke\n");
			/* -------End---------------------------- */
			if(fig->textPoint!=NULL)
			{
				while(fig->textPoint!=NULL)
				{
					fprintf(fp,"%d %d moveto\n",(int)fig->textPoint->x,(int)fig->textPoint->y);
					fprintf(fp,"(%d) show\n",fig->textPoint->number);
					fig->textPoint=fig->textPoint->next;
				}
			}
			if(fig->point!=NULL)
			{
				/* Drawing the point of each figure seperately */
				fprintf(fp,"%.3lf %.3lf moveto\n",fig->point->x,fig->point->y);
				while(fig->point!=NULL)
				{
					fprintf(fp, "%.3lf %.3lf lineto\n",fig->point->x,fig->point->y);
					fig->point=fig->point->next; 					
				}
				fprintf(fp,"stroke\n");
			}
			fig=fig->next;
			/* Going to the new figure */
		}
		fprintf(fp,"stroke\n");
		fclose(fp);
	}
}
/* Creating an new figure , and returning it ! */
Figure* createFigure(Figure* fig)
{
	Figure* newFig;
	Color c; /* Arranging Color */
	newFig=start_figure(2*(fig->urx),2*(fig->ury));
	c.red=0,c.green=0,c.blue=0;
	set_thickness_resolution(newFig,fig->thickness,fig->resolution);
	set_color(newFig,c);
	return newFig;
}
/*---Make all allocated memory free----*/
void free_all_allocated_memory(Figure * fig)
{
	Point2D * temp;
	Text* tmpText;
	Figure * tmpFig;
	do
	{
		temp = fig->point;
		while(temp)
		{
			free(temp);
			fig->point = fig->point->next;
			temp = fig->point;
		}
		tmpText = fig->textPoint;
		while(tmpText)
		{
			free(tmpText);
			fig->textPoint = fig->textPoint->next;
			tmpText = fig->textPoint;
		}
		tmpFig = fig; 
		fig = fig->next;
		free(tmpFig);
	} while(fig);
	free(fig);
}