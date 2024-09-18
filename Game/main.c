#include <gtk/gtk.h>
#include <cairo.h>
#include <stdbool.h>
#include "board.h"
#include "control.h"
#include "bot.h"

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	int* b = user_data;
	drawBoard(b, 900, 900, cr);

	return FALSE;
}


gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
	int* b = user_data;
	int verif = -1;
	if(event->keyval == GDK_KEY_Left)
	{
		verif = moveLeft(b);
	}
	if(event->keyval == GDK_KEY_Right)
	{
		verif = moveRight(b);
	}
	if(event->keyval == GDK_KEY_Up)
	{
		verif = moveUp(b);
	}
	if(event->keyval == GDK_KEY_Down)
	{
		verif = moveDown(b);
	}
	if(verif != -1)
	{
		putNewValue(b);
		gtk_widget_queue_draw(widget);
	}
	return TRUE;
}



int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);

	srand(time(NULL));

	GtkBuilder* builder = gtk_builder_new();
	GError* error = NULL;
	if(gtk_builder_add_from_file(builder, "template.glade", &error) == 0)
	{
		g_printerr("Error loading file: %s\n", error->message);
		g_clear_error(&error);
		g_object_unref(builder);
		return 1;
	}

	GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder,"window"));

	int width = 900;
	int height = 900;

	gtk_window_set_default_size(window, width, height);
	GtkDrawingArea* area = GTK_DRAWING_AREA(gtk_builder_get_object(builder,"drawing_area"));

	int* b = getBoard(SIZE);
	putNewValue(b);
	putNewValue(b);

	g_signal_connect(area, "draw", G_CALLBACK(on_draw), b);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(window, "key-release-event", G_CALLBACK(on_key_release), b);
	gtk_widget_show_all(GTK_WIDGET(window));

	g_object_unref(builder);

	gtk_main();

	gtk_widget_destroy(GTK_WIDGET(builder));
	gtk_widget_destroy(GTK_WIDGET(area));
	gtk_widget_destroy(GTK_WIDGET(window));
	free(b);

	return 0;
}
