/* main.c 
*	HOMEWORK 1: RANDOM BARS
*
* Students:
*   Daniel Josué Herrera Córdoba - 2024082732
*   Adrian Rodríguez Quirós - 2024071785
*  
* Costa Rica Institute of Technology
* Teacher: Francisco Torres Rojas
* */


#include <gtk/gtk.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "displayChart.h"

int vector[301];
int vsize = 0;

GtkWidget *mainWindow;
GtkWidget *drwChart;
GtkWidget *btnGenerateBarChart;
GtkWidget *btnExit;
GtkWidget *cbtnColor1;
GtkWidget *cbtnColor2;


typedef struct {
    int* actual;
} ArrayList;

void initConstructor(ArrayList *list) {
    list->actual = (int*)calloc(301, sizeof(int));
}

/*  checkIfThere()
 * Checks if there is repeated numbers in the array
 * Parameters: ArrayList *list, int pos
 */
int checkIfThere(ArrayList *list, int pos) {
    if(pos > 301) {
        return 2;
    }
    return list->actual[pos];
}

/* generateNumbers()
 * Fills the array with 301 unique numbers between 5 and 305.
 */
void generateNumbers() {
    ArrayList list;
    
    initConstructor(&list);
    int allow = 0;
    int number;
    srand(time(NULL));
    
    for(int i = 0; i < 301; i++) {
		allow = 0;
		
        while (allow == 0) {
			
            number = rand() % 301;
            
            if (checkIfThere(&list,number) == 0) {
                list.actual[number] = 1;
                vector[vsize] = number + 5;
                vsize++;
                allow = 1;
            }
        }
    }
    free(list.actual);
}


// GKT-GLADE CALLBACKS #########

/* Callback on_mainWindow_destroy
 * runs when the user closes the window using the X button.
 */
void on_mainWindow_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

/* on_btnGenerateBarChart_clicked()
 *  This function is called when the user clicks “Expand”. Retrieves the selected colors 
 * and instructs the GtkDrawingArea to redraw itself.
 */
void on_btnGenerateBarChart_clicked(GtkWidget *widget, gpointer user_data) {
	
	GdkRGBA color1, color2;
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(cbtnColor1), &color1);
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(cbtnColor2), &color2);
    
    F_saveColors(color1, color2);
	
	gtk_widget_queue_draw(drwChart);
	
} 

/* Callback on_btnExit_clicked
 * runs if the user presses "Exit" button
 */
void on_btnExit_clicked(GtkWidget *widget, gpointer user_data) {
    gtk_main_quit(); 
}

/*loadWidgets()
 * Get each widget of the .glade file using ID
 */
void loadWidgets(GtkBuilder *builder) {
	mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
	btnGenerateBarChart   = GTK_WIDGET(gtk_builder_get_object(builder, "btnGenerateBarChart"));
	
    drwChart  = GTK_WIDGET(gtk_builder_get_object(builder, "drwChart"));
    btnExit       = GTK_WIDGET(gtk_builder_get_object(builder, "btnExit"));
    cbtnColor1  = GTK_WIDGET(gtk_builder_get_object(builder, "cbtnColor1"));
    cbtnColor2  = GTK_WIDGET(gtk_builder_get_object(builder, "cbtnColor2"));
} 

/* connectSignals()
 *  Connect each widget to its callback function.
 */
void connectSignals() { 
    g_signal_connect(mainWindow, "destroy", G_CALLBACK(on_mainWindow_destroy), NULL);
    g_signal_connect(btnGenerateBarChart, "clicked", G_CALLBACK(on_btnGenerateBarChart_clicked), NULL);
    g_signal_connect(btnExit,  "clicked", G_CALLBACK(on_btnExit_clicked),   NULL);

   g_signal_connect(drwChart, "draw", G_CALLBACK(F_displayBars), NULL);
}


int main(int argc, char *argv[]) {

	 generateNumbers();

    GtkBuilder *builder;
    GtkWidget  *window;

    gtk_init(&argc, &argv);


    builder = gtk_builder_new_from_file("window.glade"); //upload .glade file
    if (builder == NULL) {
        g_printerr("Error: cannot load window.glade\n");
        return 1;
    }
    
    loadWidgets(builder);

    connectSignals();
    
    g_object_unref(builder);

    gtk_widget_show_all(mainWindow);
    
    gtk_main(); 
    
    
	
    

    return 0;
}

