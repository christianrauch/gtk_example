#include <stdio.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>

int x_root = 0;
int y_root = 0;

static gboolean running;

gboolean simulate_left_button(gpointer user_data) {
  GdkWindow* gdkwindow = gtk_widget_get_window(user_data);
  GdkDisplay* gdkdisplay = gdk_display_get_default();
  GdkDeviceManager* device_manager = gdk_display_get_device_manager(gdkdisplay);
//  Display *display = GDK_WINDOW_XDISPLAY(gdkwindow);
//  Window window = GDK_WINDOW_XID(gdkwindow);
//  Window root = DefaultRootWindow(display);
//  Window subwindow = None;
  GdkEvent* event = NULL;
  GdkEventButton* event_button = NULL;
  int x = 0, y = 0;

//  XTranslateCoordinates(display, root, window, x_root, y_root, &x, &y,
//    &subwindow);

  x = x_root = 164;
  y = y_root = 152;

//  printf("XID: 0x%08lx\n", window);
  printf("x_root = %d, y_root = %d\n", x_root, y_root);
  printf("x = %d, y = %d\n", x, y);
  fflush(stdout);

  event = gdk_event_new(GDK_BUTTON_PRESS);
  event_button = &event->button;
  event_button->type = GDK_BUTTON_PRESS;
  event_button->window = gdkwindow;
  event_button->send_event = 1;
  event_button->time = GDK_CURRENT_TIME;
  event_button->x = x;
  event_button->y = y;
  event_button->state = GDK_BUTTON1_MASK;
  event_button->button = 1;
  event_button->device = gdk_device_manager_get_client_pointer(device_manager);
  event_button->x_root = x_root;
  event_button->y_root = y_root;

  gdk_event_put(event);
//  gtk_main_do_event(event);
  gdk_event_free(event);
  return FALSE;
}

gboolean on_button_press (GtkWidget* widget, GdkEventButton* event,
    GdkWindowEdge edge) {
  if (event->type != GDK_BUTTON_PRESS)
    return TRUE;

  if (event->button == 3) {
//    printf("Right XID: 0x%08lx\n", GDK_WINDOW_XID(gtk_widget_get_window(widget)));
    printf("Right x = %f, y = %f\n", event->x_root, event->y_root);

    x_root = event->x_root;
    y_root = event->y_root;
    g_timeout_add(500, simulate_left_button, widget);
  } else if (event->button == 1) {
//    printf("Left XID: 0x%08lx\n", GDK_WINDOW_XID(gtk_widget_get_window(widget)));
    printf("Left x = %f, y = %f\n", event->x_root, event->y_root);
  } else {
    printf("Unknown x = %f, y = %f\n", event->x_root, event->y_root);
  }
  fflush(stdout);
  return FALSE;
}

gboolean on_button_all_press (GtkWidget* widget, GdkEventButton* event,
    GdkWindowEdge edge) {
  if (event->type != GDK_BUTTON_PRESS)
    return TRUE;

  printf("%s Button %i x = %f, y = %f\n", gtk_widget_get_name(widget), event->button, event->x_root, event->y_root);
   fflush(stdout);
  return FALSE;
}

gboolean on_key_press (GtkWidget* widget, GdkEventKey* event,
    GdkWindowEdge edge) {
  printf("Key %i\n", event->keyval); fflush(stdout);
  g_timeout_add(500, simulate_left_button, widget);
  return FALSE;
}

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

int main(int argc, char* argv[]) {
  GtkWidget* window = NULL;
  GtkWidget *button;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
  gtk_window_set_title(GTK_WINDOW(window), "Simulate Left button");
//  gtk_window_set_decorated(GTK_WINDOW (window), FALSE);
  gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

  button = gtk_check_button_new_with_label ("Hello World");

  gtk_container_add (GTK_CONTAINER (window), button);

//  g_signal_connect(G_OBJECT(window), "button-press-event",
//      G_CALLBACK(on_button_press), NULL);
  
//  g_signal_connect(G_OBJECT(window), "button-press-event",
//      G_CALLBACK(on_button_press), NULL);

  g_signal_connect(G_OBJECT(button), "button-press-event", G_CALLBACK(on_button_all_press), NULL);

  g_signal_connect(G_OBJECT(window), "button-press-event", G_CALLBACK(on_button_all_press), NULL);

  g_signal_connect(G_OBJECT(window), "key-press-event", G_CALLBACK(on_key_press), NULL);

  g_signal_connect(G_OBJECT(button), "clicked",  G_CALLBACK(clicked), NULL);

//  g_signal_connect_swapped(G_OBJECT(window), "destroy",
//      G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  g_signal_connect(G_OBJECT(window), "destroy",  G_CALLBACK(destroy), NULL);

//  gtk_widget_add_events(button, GDK_ALL_EVENTS_MASK);

  gtk_widget_show(button);
  gtk_widget_show(window);

  gtk_main();
//  running = TRUE;
//  while(running) {
////    g_timeout_add(1000, simulate_left_button, button);
//    g_main_context_iteration(NULL, TRUE);
////    g_usleep(1e3);
////    simulate_left_button(button);
//  }

  return 0;
}