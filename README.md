# *Vector Graphics with SVG and EPS*
*Two-dimensional (2D) vector graphics is an essential tool for many documenting and computer graphics applications. In this project, you will explore two portable vector graphics file formats EPS and SVG. You will write a C library that can generate vector graphics in EPS and SVG or convert between these two formats. Your library will handle only a subset of functionalities possible with EPS and SVG.*

___*For more information click the links below :*___
- EPS: See [More Info For EPS][EPS_Link] for a specification of EPS format.
- SVG: See [More Info For SVG][SVG_Link] for an introduction to SVG format.

## Project Purpose
Libraries would be able to draw vector graphics and export EPS or SVG formatted files including your graphics.

___Library Functions :___ 
- *Figure * start_figure(double width, double height)*
- *void set_thickness_resolution(Figure resolution)*
- *void set_color(Figure * fig, Color c)*
- *void draw_fx(Figure * fig, double f(double x), double start_x, double end_x)*
- *void draw_polyline(Point2D * poly_line, int n)*
- *void draw_circle(Point2D * center, double r)*
- *void draw_ellipse(...)*
- *void draw_binary_tree(Tree * root)*
- *void scale_figure(double scale_x, double scale_y)*
- *void resize_figure(Point2D start_roi, Point2D end_roi)*
- *void append_figures(Figure * fig1, Figure * fig2)*
- *void export_eps(Figure * fig, char * file_name)*
- *void export_svg(Figure * fig, char * file_name)*
- *void import_svg(char * file_name, Figure * fig)*


[EPS_Link]: https://www-cdf.fnal.gov/offline/PostScript/5002.PDF
[SVG_Link]: https://www.w3schools.com/graphics/svg_intro.asp
