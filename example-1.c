#include <gtk/gtk.h>

static gboolean running;

void
destroy( GtkWidget *widget, gpointer   data )
{
   running = FALSE;
}

void
clicked(GtkButton *button, gpointer   user_data)
{
  printf("clicked\n"); fflush(stdout);
}

int
main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *button;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  g_signal_connect(G_OBJECT(window), "destroy",  G_CALLBACK(destroy), NULL);

  gtk_window_resize(GTK_WINDOW(window), 200, 200);

  button = gtk_check_button_new_with_label ("Hello World");

  g_signal_connect(G_OBJECT(button), "clicked",  G_CALLBACK(clicked), NULL);

  gtk_container_add (GTK_CONTAINER (window), button);
  gtk_widget_show (button);

  gtk_widget_show (window);

  running = TRUE;
  while(running) {
    g_main_context_iteration(NULL, TRUE);
  }

  return 0;
}