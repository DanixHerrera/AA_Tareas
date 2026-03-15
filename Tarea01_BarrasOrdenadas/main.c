#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
	
    GtkBuilder *builder;
    GtkWidget  *window;

    gtk_init(&argc, &argv);


    builder = gtk_builder_new_from_file("ventana.glade"); //upload .glade file

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main")); //to obtain main window by an ID 

    gtk_builder_connect_signals(builder, NULL); //autoconnect signals like buttons, labels, etc

    g_object_unref(builder);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
