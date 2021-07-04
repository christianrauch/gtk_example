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

//  button = gtk_check_button_new_with_label ("Hello World");

//  g_signal_connect(G_OBJECT(button), "clicked",  G_CALLBACK(clicked), NULL);

//  gtk_container_add (GTK_CONTAINER (window), button);
//  gtk_widget_show (button);

  gtk_widget_show (window);

  GdkDisplay* gdkdisplay = gdk_display_get_default();
  GdkDeviceManager* device_manager = gdk_display_get_device_manager(gdkdisplay);

  int i = 0;
  running = TRUE;
  while(running) {
    GdkEventButton *ev = (GdkEventButton *)gdk_event_new(GDK_BUTTON_PRESS);
    ev->window = gtk_widget_get_window(GTK_WIDGET(window));
    ev->x = 100;
    ev->y = 100;
    ev->send_event = TRUE;
    ev->device = gdk_device_manager_get_client_pointer(device_manager);
    ev->state = GDK_BUTTON1_MASK;
    ev->time = GDK_CURRENT_TIME;
    ev->button = 1;

//    gboolean handled = gtk_widget_event(window, (GdkEvent*)ev);
//    printf("motion handled? %i\n", handled); fflush(stdout);

//    g_usleep(1000);
//    i++;
//    if (i%10 == 0) {
//      printf("clicked?\n"); fflush(stdout);
//      gdk_event_put(ev);
//      gdk_test_simulate_button(gtk_widget_get_window(GTK_WIDGET(window)),
//                               100, 100, 1, 0, GDK_BUTTON_PRESS);
//    }

//    gtk_main_do_event(ev);
    g_main_context_iteration(NULL, TRUE);
  }

  return 0;
}