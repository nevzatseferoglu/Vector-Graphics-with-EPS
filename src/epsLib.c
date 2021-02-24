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
 *                  OS : VERSION="18.04.4 LTS (Bionic Beaver)"              *
 *                                                                          *
 *    Date :  24/05/2019													*
 * 	  Update : 				                                                *
 ****************************************************************************/

/* Project Main Lib.*/
#include "headers/epsLib.h"
#include "headers/bst.h"

void free_all_allocated_memory(Figure* fig);

bool setPoint( pPoint2D* point , double x , double y , bool isMoveto )
{
	if( *point == NULL )
		return false;

	(*point) -> x = x;
	(*point) -> y = y;
	(*point) -> isMoveto = isMoveto;

	return true;
}

pPoint2D newPoint( double x , double y  , pPoint2D next , bool isMoveto )
{
	pPoint2D newPoint = NULL;

	newPoint = (pPoint2D) malloc( sizeof( Point2D ) * 1 );
	if( newPoint == NULL )
	{
		fprintf(stderr,"Allocation failed, Error: newPoint().\n");
		exit( -1 );
	}

	newPoint -> x = x;
	newPoint -> y = y;
	newPoint -> next = next;
	newPoint -> isMoveto = isMoveto;

	return newPoint;
}

pFigure start_figure( double width , double height )
{
	/* defined new figure */
	pFigure fig = (pFigure) malloc( sizeof( Figure ) ); 

	if( fig == NULL )
	{
		fprintf(stderr ,"Error in allocation process in start_figure(int,int)\n");
		exit(EXIT_FAILURE);
	}

	/*Arranging boundingBox */
	fig -> urx = width;
	fig -> ury = height;
	
	fig -> llx = (-1) * width;
	fig -> lly = (-1) * height;

	/* no text at all */
	fig -> text = NULL;

	/* Ensuring that each pointer variable of figure is not allocated in memory yet. */
	fig -> next = NULL;
	fig -> point = NULL;

	return fig;
}

void set_thickness_resolution( pFigure fig ,double thickness,double resolution)
{
	/* Thickness and resolution are communicated with figure */
	fig -> thickness = thickness;
	fig -> resolution = resolution;
}

void set_color( pFigure fig , Color color )
{
	/* Setting Color */
	(fig -> color).red		= color.red;
	(fig -> color).green	= color.green;
	(fig -> color).blue		= color.blue;
}

pFigure generateSTD_Figure( double width , double height ,double resolution
 , double thickness )
{
	pFigure newFigure = NULL;
  	newFigure = start_figure( width , height );
	set_thickness_resolution( newFigure , thickness , resolution );

	/* Default color is black. */
	Color newColor = { 0 , 0 , 0 };
	set_color( newFigure , newColor );

	return newFigure;
}

void draw_fx(pFigure fig, double f(double x), double start_x, double end_x)
{
	pPoint2D initialPoint, nextPoint = NULL;

	if( fig == NULL )
	{
		fprintf(stderr,"Parameter that takes figure cannot be NULL, Error: draw_fx()\n");
		exit(EXIT_FAILURE);
	}

	fig -> point = NULL;
	initialPoint = fig -> point = newPoint(start_x, f(start_x), NULL, true);
	nextPoint = NULL;

	for( double x = start_x + fig -> resolution ; x <= end_x ; x += fig->resolution )
	{
		nextPoint = newPoint(x, f(x), NULL, false);
		initialPoint -> next = nextPoint;
		initialPoint = nextPoint;
	}
}

void draw_polyline( pFigure fig, pPoint2D pointArray, int n)
{
	if( fig == NULL )
	{
		fprintf(stderr,"Given figure cannot be NULL, Error: draw_polyline().");
		exit(EXIT_FAILURE);
	}

	if( n <= 1 || pointArray == NULL )
	{
		fprintf(stderr, "Invalid array size or NULL point reference, Error: draw_polyline().");
		exit(EXIT_FAILURE);
	}

	pPoint2D initialPoint = newPoint(pointArray->x, pointArray->y, pointArray->next,pointArray->isMoveto);
	pPoint2D head = initialPoint;
	pPoint2D nextPoint = NULL;

	for( size_t i = 1 ; i < n ; ++i )
	{
		nextPoint = newPoint((pointArray+i)->x, (pointArray+i)->y
		, (pointArray+i)->next,(pointArray+i)->isMoveto);

		initialPoint -> next = nextPoint;
		initialPoint = initialPoint -> next;
	}
	initialPoint -> next = NULL;

	fig -> point = head;
}

/*void draw_fx(pFigure fig, double f(double x), double start_x, double end_x)
{	
	pPoint2D head = NULL;

	head = newPoint( 0 , 0 , NULL , true );
	fig -> point = head;

	for( double  i = start_x ; i < end_x ;  i += fig -> resolution )
	{
		if( i == start_x )
		{
			if( !setPoint( &head , i , f( i ) , true ) )
			{
				fprintf( stderr ,"Null dereference cannot be setted !\n" );
				exit( -1 );
			}
		}
		else
		{
			if( !setPoint( &head , i , f( i ) , false ) )
			{
				fprintf( stderr ,"Null dereference cannot be setted !\n" );
				exit( -1 );
			}
		}

		if( i + (fig -> resolution ) < end_x )
		{
			head -> next = newPoint( 0 , 0 , NULL , false );
			head = head -> next;
		}
	}
}*/

void drawGraphPaper( pFigure fig , int xSquareNumber , int ySquareNumber )
{
	pPoint2D head = NULL;
	if (xSquareNumber == 1 || ySquareNumber == 1) {
		fprintf(stderr, "Sqare numbers argument canno be 1, Error: drawGraphPaper()\n");
		exit(EXIT_FAILURE);
	}

	head = newPoint( 0 , 0 , NULL , false );

	fig -> point = head;

	for( double ySpace = (fig -> lly + (( fig -> ury) * 2 / ySquareNumber)) ; ySpace < fig -> ury ; ySpace +=  ( fig -> ury) * 2 / ySquareNumber )
	{
		for( double xSpace = fig -> llx + 1 ; xSpace < fig -> urx ; xSpace += 1  )
		{
			if( xSpace == fig -> llx + 1 )
			{
				if( !setPoint( &head , xSpace , ySpace , true ) )
				{
					fprintf( stderr ,"Null dereference cannot be setted !\n" );
					exit( -1 );
				}
			}
			else
			{
				if( !setPoint( &head , xSpace , ySpace , false ) )
				{
					fprintf( stderr ,"Null dereference cannot be setted !\n" );
					exit( -1 );
				}
			}

			if( ( xSpace + 1 ) < fig -> urx )
			{
				head -> next = newPoint( 0 , 0 , NULL , false );
				head = head -> next;
			}
		}
	}

	for( double xSpace = (fig -> llx + (( fig -> urx) * 2 / xSquareNumber)) ; xSpace < fig -> urx ; xSpace +=  ( fig -> urx) * 2 / xSquareNumber )
	{
		for( double ySpace = fig -> lly + 1 ; ySpace < fig -> ury ; ySpace += 1  )
		{
			if( ySpace == fig -> lly + 1 )
			{
				if( !setPoint( &head , xSpace , ySpace , true ) )
				{
					fprintf( stderr ,"Null dereference cannot be setted !\n" );
					exit( -1 );
				}
			}
			else
			{
				setPoint( &head , xSpace , ySpace , false );
			}

			if( ( ySpace + 1 ) < fig -> ury )
			{
				head -> next = newPoint( 0 , 0 , NULL , false );
				head = head -> next;
			}
		}
	}
}

void draw_ellipse( pFigure fig , pPoint2D center , double majorAxis , double minorAxis  )
{
	pPoint2D head = NULL;
	head = newPoint( 0 , 0 , NULL , false );
	
	fig -> point = head;

	for( double degree = 0 ; degree < 360 ; degree += fig -> resolution )
	{
		if( !setPoint( &head , ( majorAxis * cos( degree * PI / 180 ) ) + center -> x , ( minorAxis *  sin( degree * PI / 180 ) ) + center -> y , false  ) )
		{
			fprintf( stderr ,"Null dereference cannot be setted, Error: draw_ellipse().\n" );
			exit( -1 );
		}

		if( ( degree + ( fig -> resolution) ) < 360 )
		{
			head -> next = newPoint( 0 , 0 , NULL , false );
			head = head -> next;
		}
	}
}

void draw_circle( pFigure fig , pPoint2D center , double radius )
{
	draw_ellipse( fig , center , radius , radius );
}

void addPoint(pFigure fig, pPoint2D newPoint) {

	pPoint2D move = NULL;

	if (fig == NULL || fig -> point == NULL) {
		fprintf(stderr, "First figure or figure's point cannot be NULL, addPoint()!\n");
		exit(EXIT_FAILURE);
	}

	move = fig -> point;

	while( move -> next !=  NULL ) {
		move = move -> next;
	}

	move -> next = newPoint;
}

int get_digit(int num) {
	int digit = 1;

	if (num < 0)
		++digit;

	while((num = num / 10) !=  0)
		++digit;

	
	return digit;
}
void render_text(pFigure fig, pPoint2D center, unsigned int num, double radius) {

	fig -> text = (Text*)malloc(sizeof(Text));
	fig -> text -> num = num;
	fig -> text -> size = radius - radius / 2;

	fig -> text -> x = (center -> x) - get_digit(num);
	fig -> text -> y = (center -> y);

}

void append_figures(pFigure first, pFigure second) {
	
	pFigure head = first;

	if (first == NULL) {
		fprintf(stderr, "First figure cannot be NULL, append_figures()!\n");
		exit(EXIT_FAILURE);
	}

	while( head -> next !=  NULL ) {
		head = head -> next;
	}

	head -> next = second;
}

void draw_line(pFigure fig, pPoint2D center, int r, int depth, bool isLeft) {

	pFigure line = generateSTD_Figure(WIDTH, HEIGHT, PIXEL_JUMP, THINCKNESS);
	line -> point = newPoint(0, 0, NULL, false);
	

	if (isLeft == true) {
		line -> point -> x = center -> x - r * cos(45);
		line -> point -> y = center -> y - r * sin(45);
	
		line -> point -> next = newPoint(0, 0, NULL, false);
		line -> point -> next -> x = center -> x - (1.5) * r * pow( 2, (depth - 2));
		center -> x = line -> point -> next -> x;
	}
	else {
		line -> point -> x = center -> x + r * cos(45);
		line -> point -> y = center -> y - r * sin(45);

		line -> point -> next = newPoint(0, 0, NULL, false);
		line -> point -> next -> x = center -> x + (1.5) * r * pow( 2, (depth - 2));
		center -> x = line -> point -> next -> x;
	}

	line -> point -> next -> y = center -> y - 2 * (r + 1) + r;
	center -> y = line -> point -> next -> y;

	append_figures(fig, line);
}

void draw_binary_tree_helper(pFigure fig, pTree root, pPoint2D center, unsigned int depth, int r) {

	pFigure circle_left = NULL;
	pFigure circle_right = NULL;

	double cSaveX = center -> x;
	double cSaveY = center -> y;


	if (root == NULL || depth <= 1) {
		return;
	}

	if (root->left != NULL) {
		draw_line(fig, center, r, depth, true);
		center -> y -= r;
		circle_left = generateSTD_Figure(WIDTH, HEIGHT, PIXEL_JUMP, THINCKNESS);
		draw_circle(circle_left, center, r);
		render_text(circle_left, center, root-> left -> num, r);
		append_figures(fig, circle_left);
		draw_binary_tree_helper(fig, root->left, center, depth - 1, r);
	}

	if (root->right != NULL) {
		center -> x = cSaveX;
		center -> y = cSaveY;

		draw_line(fig, center, r, depth, false);
		center -> y -= r;
		circle_right = generateSTD_Figure(WIDTH, HEIGHT, PIXEL_JUMP, THINCKNESS);
		draw_circle(circle_right, center, r);
		render_text(circle_right, center, root-> right -> num, r);
		append_figures(fig, circle_right);
		draw_binary_tree_helper(fig, root->right, center, depth - 1, r);
	}
}

void draw_binary_tree(pFigure fig, pTree root) {
	pPoint2D center = newPoint(0, HEIGHT - 10, NULL, true);
	unsigned int r = 7;

	if (root != NULL) {
		draw_circle(fig, center, r);
		render_text(fig, center, root -> num, r);
	}

	draw_binary_tree_helper(fig, root, center, findDepth(root), r);
	free(center);
}

void export_eps( pFigure actualFig , const char* file_name )
{
	pFigure fig = NULL;
	pPoint2D printerPoint = NULL;
	FILE *fp = NULL;

	fig = actualFig;

	if( fig == NULL )
	{
		/* Checking the Figure whether it is empty or not */
		fprintf( stderr , "Error , fig is empty ! " );
		exit( EXIT_FAILURE );
	}
	else
	{
		fp = fopen( file_name , "w" );
		if( fp == NULL )
		{
			fprintf(stderr , "File could not be opened !\n");
			exit( -1 );
		}

		fprintf( fp , "%%!!PS-Adobe-3.0 EPSF-3.0\n" );
		fprintf( fp , "%%%%BoundingBox: %.3lf %.3lf %.3lf %.3lf\n" , fig -> llx , fig -> lly , fig -> urx , fig -> ury );
		fprintf( fp , "%%Title: (ARTWORK.EPS)\n" );
		fprintf( fp , "%%CreationDate: (25/09/2020)(Initial Date)\n" );
		fprintf( fp , "%%EndComments\n" );

		//fprintf( fp , "%.3lf setlinewidth\n" , fig -> thickness);
		//fprintf( fp , "\n/Times-Roman findfont\n%.2lf scalefont\nsetfont ", 11 * fig -> thickness ); /* configurations */

		while( fig != NULL )
		{
			/* Setting width and color of each figure */

			fprintf( fp , "%.3lf setlinewidth\n" , fig -> thickness );
			fprintf( fp , "%.3lf %.3lf %.3lf setrgbcolor\n" , (fig -> color).red , (fig -> color).green , (fig -> color).blue );

			/* -------End---------------------------- */
			if(fig -> text != NULL)
			{
				fprintf(fp,"/Times-Roman findfont %.3lf scalefont setfont\n", fig -> text -> size);
				fprintf(fp,"%.3lf %.3lf moveto\n", fig -> text -> x, fig -> text -> y);
				fprintf(fp,"(%d) show\n", fig -> text -> num);
			}

			if( fig -> point != NULL )
			{
				printerPoint = fig -> point;
				fprintf( fp , "%.3lf %.3lf moveto\n" , printerPoint -> x , printerPoint -> y );

				while( printerPoint != NULL )
				{
					if( printerPoint -> isMoveto == true )
					{
						fprintf( fp , "%.3lf %.3lf moveto\n" , printerPoint -> x , printerPoint -> y );
					}
					else
					{
						fprintf(fp, "%.3lf %.3lf lineto\n" , printerPoint -> x , printerPoint -> y );
					}
					printerPoint = printerPoint -> next;				
				}

				fprintf( fp , "stroke\n" );
			}

			/* Proceed to next figure */
			fig = fig -> next;
		}

		fclose( fp );
	}

	free_all_allocated_memory(actualFig);
}

/*---Make all allocated memory free----*/
void free_all_allocated_memory( pFigure fig )
{
	pFigure freeFigure = NULL;
	pPoint2D freePoint = NULL;

	while( fig != NULL)
	{
		freeFigure = fig;

		while ( fig -> point != NULL )
		{
			freePoint = fig -> point;
			fig -> point = fig -> point -> next;
			
			free( freePoint );
			freePoint = NULL;
		}

		if ( freeFigure -> text != NULL ) {
			free(freeFigure -> text);
			freeFigure -> text = NULL;
		}
		
		fig = fig -> next;

		free( freeFigure );	
		freeFigure = NULL;	
	}
}