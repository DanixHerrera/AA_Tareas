/* displayChart.h - header of display chart module
 * 
 * Vector defined in main.c
 * Stores the colors selected by the user
 * Draws the bars in the GtkDrawingArea 
*/


#ifndef DISPLAYCHART_H
#define DISPLAYCHART_H

#include <gtk/gtk.h>

extern int vector[301];

void F_saveColors(GdkRGBA color1, GdkRGBA color2);

gboolean F_displayBars(GtkWidget *widget, cairo_t *cr, gpointer data);



#endif
