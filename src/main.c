#include <gtk/gtk.h>
#include <stdbool.h>

#include "../include/board.h"
#include "../include/bot.h"
#include "../include/control.h"

struct botData
{
    GtkWindow *window;
    int *board;
};

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    int *b = user_data;
    int width = gtk_widget_get_allocated_width(widget);
    int height = gtk_widget_get_allocated_height(widget);
    drawBoard(b, width, height, cr);

    return FALSE;
}

static gboolean bot_play(gpointer user_data)
{
    struct botData *bD = user_data;
    if (possibleMove(bD->board) == 1)
    {
        doMove(bD->board);
        putNewValue(bD->board);
        // printBoard(bD->board);
        GtkWidget *area = gtk_bin_get_child(GTK_BIN(bD->window));
        gtk_widget_queue_draw(area);
        gtk_test_widget_wait_for_draw(area);
        // g_print("+1\n");
        return TRUE;
    }
    return FALSE;
}

gboolean on_key_release(GtkWidget *widget, GdkEventKey *event,
                        gpointer user_data)
{
    int *b = user_data;
    int verif = -1;
    if (event->keyval == GDK_KEY_Left)
    {
        verif = moveLeft(b);
    }
    if (event->keyval == GDK_KEY_Right)
    {
        verif = moveRight(b);
    }
    if (event->keyval == GDK_KEY_Up)
    {
        verif = moveUp(b);
    }
    if (event->keyval == GDK_KEY_Down)
    {
        verif = moveDown(b);
    }
    if (verif != -1)
    {
        putNewValue(b);
        gtk_widget_queue_draw(widget);
    }
    return TRUE;
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        return -1;
    }
    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1],"-h") == 0))
    {
        printf("Here are flags: \"--help\" for help\n");
        printf("                \"--bot\" for bot\n");
        printf("                no arg for playing\n");
        return 0;
    }
    if (argc == 2 && strcmp(argv[1], "--bot") != 0)
    {
        return -1;
    }
    gtk_init(&argc, &argv);

    srand(time(NULL));

    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;
    if (gtk_builder_add_from_file(builder, "template.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        g_object_unref(builder);
        return 1;
    }

    GtkWindow *window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    int width = 900;
    int height = 900;

    gtk_window_set_default_size(window, width, height);
    GtkDrawingArea *area =
        GTK_DRAWING_AREA(gtk_builder_get_object(builder, "drawing_area"));

    int *b = getBoard(SIZE);
    for (int i = 0; i < 2; i++)
    {
        putNewValue(b);
    }

    g_signal_connect(area, "draw", G_CALLBACK(on_draw), b);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    if (argc == 1)
    {
        g_signal_connect(window, "key-release-event", G_CALLBACK(on_key_release), b);
    }
    else
    {
        struct botData bD = { window, b };
        g_timeout_add(500, bot_play, &bD);
    }
    gtk_widget_show_all(GTK_WIDGET(window));

    g_object_unref(builder);

    gtk_main();

    gtk_widget_destroy(GTK_WIDGET(builder));
    gtk_widget_destroy(GTK_WIDGET(area));
    gtk_widget_destroy(GTK_WIDGET(window));
    free(b);

    return 0;
}
