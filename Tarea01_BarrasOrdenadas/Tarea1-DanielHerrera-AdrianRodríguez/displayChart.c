/* displayChart.c - Bar Chart module with Cairo
 *
 * This header saves the colors chosen by the user, draw 301 bars proportional to their 
  *  values and mix the colors based on the height of each bar
*/


#include <gtk/gtk.h>
#include "displayChart.h"

static GdkRGBA minColor;   // value 5  (min) 
static GdkRGBA maxColor;  // value 305 (max)
static int colorsAreReady = 0; // 0=false

/*  F_saveColors()
 * Call from main.c when the user clicks “Generate Chart”.
   Saves the colors to use when drawing
 */
void F_saveColors(GdkRGBA color1, GdkRGBA color2) {
    minColor = color1;
    maxColor  = color2;
    colorsAreReady = 1; // 1=true
}

/* mixColor()
 * Calculate the intermediate color between minimum color and maximum color
   based on a factor t between 0.0 and 1.0.
 * t is a factor between 0.0 y 1.0.
     t = 0.0 -> min color ( 5)
     t = 0.5 ->  intermediate
     t = 1.0 ->  max color (305)
 * Parameters: cairo_t *cr, double t
 */
static void mixColor(cairo_t *cr, double t) {
    double r = minColor.red   + t * (maxColor.red - minColor.red);
    double g = minColor.green + t * (maxColor.green - minColor.green);
    double b = minColor.blue  + t * (maxColor.blue - minColor.blue);

    cairo_set_source_rgb(cr, r, g, b);
}

/*    F_displayBars()
 * Callback for the GtkDrawingArea draw signal.
 * GTK calls it automatically when it needs to redraw
 * Parameters: GtkWidget *widget, cairo_t *cr, gpointer data
 */
gboolean F_displayBars(GtkWidget *widget, cairo_t *cr, gpointer data) {

    int widthArea = gtk_widget_get_allocated_width(widget);
    int heightArea  = gtk_widget_get_allocated_height(widget);


    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);

 
    if (!colorsAreReady) 
    {
        cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
        cairo_move_to(cr, widthArea / 2 - 100, heightArea / 2);
        cairo_show_text(cr, "Press 'Generate chart' to display bars");
        return FALSE;
    }

    // Bars dimensions 

    double barWidth = (double)(widthArea - 300) / 301.0;

    int maxHeight = heightArea - 5;

    int minValue = 5;
    int maxValue = 305;
    
    int valueRange = maxValue - minValue;

	// Draw each bar
	
    for (int i = 0; i < 301; i++) {

        int value = vector[i];

        double t = (double)(value - minValue) / valueRange;
        double barHeight = t * maxHeight;

        double x = i * (barWidth + 1.0); //px separation

        double y = heightArea - barHeight;

        mixColor(cr, t);

        cairo_rectangle(cr, x, y, barWidth , barHeight);
        cairo_fill(cr);
    }

    return FALSE;
}
