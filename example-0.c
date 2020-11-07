// https://developer.gnome.org/gtk3/stable/gtk-getting-started.html
// gcc `pkg-config --cflags gtk+-3.0` -o example-0 example-0.c `pkg-config --libs gtk+-3.0`

#include <gtk/gtk.h>
#include <cairo/cairo.h>

void 
print_child(GtkWidget *widget, gpointer data)
{
  int lvl = *((int*)data);
  for (int i = 0; i < lvl; ++i) { printf("."); }
  printf("widget: %s\n", gtk_widget_get_name((GtkWidget*)widget));

  for (int i = 0; i < lvl; ++i) { printf(" "); }
  printf("drawable: %i\n", gtk_widget_is_drawable(widget));
  
  for (int i = 0; i < lvl; ++i) { printf(" "); }
  printf("w/h: %i/%i\n", gtk_widget_get_allocated_width(widget), gtk_widget_get_allocated_height(widget));
  
  fflush(stdout);
  
//  gtk_widget_render_icon_pixbuf()
  ;

  lvl++;
  if (GTK_IS_CONTAINER(widget)) {
    gtk_container_forall(GTK_CONTAINER(widget), &print_child, &lvl);
  }
  
  if (GTK_IS_IMAGE(widget)) {
      cairo_surface_t * srf = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 200, 200);
      cairo_t *cr = cairo_create(srf);
      gtk_widget_draw(widget, cr);
      cairo_surface_write_to_png(srf, "/tmp/image.png");
  }
  
  if (GTK_IS_BUTTON(widget)) {
    cairo_surface_t * srf = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 200, 200);
    cairo_t *cr = cairo_create(srf);
    gtk_widget_draw(widget, cr);
    cairo_surface_write_to_png(srf, "/tmp/button.png");
  }
}

//gboolean
//draw(GtkWidget    *widget, cairo_t *cr, gpointer      user_data)
//{
//  //
//}

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *header;

  window = gtk_application_window_new (app);
//  window = gtk_offscreen_window_new();
  header = gtk_header_bar_new();
  gtk_window_set_titlebar((GtkWindow*)window, header);
  gtk_header_bar_set_show_close_button((GtkHeaderBar*)header, TRUE);

  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 300, 200);
  gtk_widget_show_all (window);

//  GList *children = gtk_container_get_children(GTK_CONTAINER(header));
//  printf("children %i\n", g_list_length(children)); fflush(stdout);
////  while ((children = g_list_next(children)) != NULL) {
////      printf("child %s\n", gtk_widget_get_name((GtkWidget*)children)); fflush(stdout);
////  }

//  gtk_container_forall(GTK_CONTAINER(header), &container_cb, NULL);
  
//  g_signal_connect(header, "draw", G_CALLBACK(draw), NULL);
  
  const int lvl = 0;
  print_child(header, (void*)&lvl);

  // cairo_surface_t * srf = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 200, 200);
  // cairo_t *cr = cairo_create(srf);
  // gtk_widget_draw(header, cr);
  // // gtk_widget_draw(window, cr);
  // cairo_surface_write_to_png(srf, "/tmp/win.png");
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
