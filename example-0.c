// https://developer.gnome.org/gtk3/stable/gtk-getting-started.html
// gcc `pkg-config --cflags gtk+-3.0` -o example-0 example-0.c `pkg-config --libs gtk+-3.0`

#include <gtk/gtk.h>
#include <cairo/cairo.h>


static gboolean
scribble_motion_notify_event (GtkWidget      *widget,
                              GdkEventMotion *event,
                              gpointer        data)
{
//	printf("ev rcv %f,%f\n", event->x, event->y);
	printf("ev rcv %i,%i\n", (int)(event->x), (int)(event->y)); fflush(stdout);

  /* We've handled it, stop processing */
  return TRUE;
}

void 
print_child(GtkWidget *widget, gpointer data)
{
  int lvl = *((int*)data);
  for (int i = 0; i < lvl; ++i) { printf("/"); }
  printf("widget: %s\n", gtk_widget_get_name((GtkWidget*)widget));

  for (int i = 0; i < lvl; ++i) { printf(" "); }
  printf("drawable: %i\n", gtk_widget_is_drawable(widget));
  
  for (int i = 0; i < lvl; ++i) { printf(" "); }
  printf("w/h: %i/%i\n", gtk_widget_get_allocated_width(widget), gtk_widget_get_allocated_height(widget));
  
//  for (int i = 0; i < lvl; ++i) { printf(" "); }
//  printf("name: %s\n", gtk_widget_class_get_css_name(widget));
//  GtkStyleContext* style = gtk_widget_get_style_context(widget);
  
  for (int i = 0; i < lvl; ++i) { printf(" "); }
  printf("widget path: %s\n", gtk_widget_path_to_string(gtk_widget_get_path(widget)));
  
  for (int i = 0; i < lvl; ++i) { printf(" "); }
  printf("style: %s\n", gtk_style_context_to_string(gtk_widget_get_style_context(widget), GTK_STYLE_CONTEXT_PRINT_SHOW_STYLE));
  
  fflush(stdout);
  
//  gtk_widget_set_state_flags(widget, GTK_STATE_FLAG_BACKDROP, FALSE);
  
  gtk_widget_realize(widget);
  
  if (lvl==1) {
      gtk_widget_show(widget);
      GtkAllocation allocation;
      gtk_widget_get_allocation (widget, &allocation);
      allocation.x = 0;
      allocation.y = 0;
      allocation.width = 300;
//      allocation.height = 100;
      
      gint natural_height;
      gtk_widget_get_preferred_height(widget, &allocation.height, &natural_height);
      gtk_widget_size_allocate(widget, &allocation);
      cairo_surface_t * srf = cairo_image_surface_create (
            CAIRO_FORMAT_ARGB32,
            gtk_widget_get_allocated_width(widget),
            gtk_widget_get_allocated_height(widget));
      cairo_t *cr = cairo_create(srf);
      gtk_widget_draw(widget, cr);
      cairo_surface_write_to_png(srf, "/tmp/hdr.png");
    }

  lvl++;
  if (GTK_IS_CONTAINER(widget)) {
    gtk_container_forall(GTK_CONTAINER(widget), &print_child, &lvl);
  }
  
  if (GTK_IS_LABEL(widget) && gtk_widget_get_allocated_width(widget)>1) {
      PangoAttrList *attr = gtk_label_get_attributes(GTK_LABEL(widget));
//      GtkWidget *window = gtk_offscreen_window_new();
////      gtk_container_add(window, widget);
//      gtk_widget_reparent(widget, window);
//      gtk_window_set_default_size (GTK_WINDOW (window), gtk_widget_get_allocated_width(widget), gtk_widget_get_allocated_height(widget));
//      gtk_widget_show_all (window);
//      cairo_surface_t * srf_offscreen = gtk_offscreen_window_get_surface(GTK_OFFSCREEN_WINDOW(window));
//      cairo_surface_write_to_png(srf_offscreen, "/tmp/label.png");
      
//      GtkAllocation allocation;
//      gtk_widget_get_allocation (widget, &allocation);
//      gtk_widget_size_allocate(widget, &allocation);
      
      cairo_surface_t * srf = cairo_image_surface_create (
            CAIRO_FORMAT_ARGB32,
            gtk_widget_get_allocated_width(widget),
            gtk_widget_get_allocated_height(widget));
      cairo_t *cr = cairo_create(srf);
      gtk_widget_draw(widget, cr);
      cairo_surface_write_to_png(srf, "/tmp/label.png");
  }
  
//  if (GTK_IS_IMAGE(widget)) {
//      cairo_surface_t * srf = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 200, 200);
//      cairo_t *cr = cairo_create(srf);
//      gtk_widget_draw(widget, cr);
//      cairo_surface_write_to_png(srf, "/tmp/image.png");
//  }
  
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
////  gtk_widget_draw(widget, cr); // SIGSEGV
//  return TRUE;
//}

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *header;

  window = gtk_application_window_new (app);
//  window = gtk_window_new(GDK_WINDOW_TOPLEVEL);
//  window = gtk_offscreen_window_new();
//  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  header = gtk_header_bar_new();
//  g_signal_connect (window, "motion-notify-event", G_CALLBACK (scribble_motion_notify_event), NULL);
//  GtkWidget *h2 = gtk_header_bar_new();
  gtk_window_set_titlebar((GtkWindow*)window, header);
  gtk_header_bar_set_title(header, "lala");
  gtk_header_bar_set_show_close_button((GtkHeaderBar*)header, TRUE);
  
//  GtkWidget *darea = gtk_drawing_area_new();
//  gtk_container_add(GTK_CONTAINER (window), darea);
//  gtk_widget_set_app_paintable(window, TRUE);
//  gtk_widget_show(darea);
  
  GtkWidget *b = gtk_button_new_with_label("hallo");
//  gtk_container_add(window, b);
//  gtk_widget_show(b);
  
//  gtk_container_add(window, header);
  
  gtk_header_bar_set_title(header, "lala");
  gtk_widget_set_state_flags(window, GTK_STATE_FLAG_BACKDROP, TRUE);
  
//  gtk_widget_add_events(header, GDK_POINTER_MOTION_MASK);
//  gtk_widget_add_events(header, GDK_BUTTON_PRESS_MASK);

//  gtk_window_resize(window, 1920, 1200);


//  gtk_window_set_title (GTK_WINDOW (window), "Window");
//  gtk_window_set_default_size (GTK_WINDOW (window), 300, 200);
//  gtk_window_set_default_size (GTK_WINDOW (window), gtk_widget_get_allocated_width(h2), gtk_widget_get_allocated_height(h2));
//  gtk_widget_show_all (header);
  gtk_widget_show_all (window);
//  gtk_widget_hide(window);
  
//  gtk_window_set_titlebar(window, NULL);
//  g_object_ref(header);
//  gtk_container_remove(window, header);
  
//  gtk_header_bar_set_title(header, "tada");
//  gtk_widget_unmap(header);
  gtk_widget_set_state_flags(window, GTK_STATE_FLAG_BACKDROP, TRUE);
//  gtk_widget_map(header);
//  gtk_widget_show_all (window);
//  gtk_window_set_titlebar((GtkWindow*)window, header);
  
//  while (gtk_events_pending()) {
//    gtk_main_iteration();
//  }
  
//  GtkAllocation clip;
//  gtk_widget_get_allocation(darea, &clip);
  
//  gtk_widget_get_clip(darea, &clip);

//  GList *children = gtk_container_get_children(GTK_CONTAINER(window));
//  printf("children %i\n", g_list_length(children)); fflush(stdout);
//  while ((children = g_list_next(children)) != NULL) {
//      printf("child %s\n", gtk_widget_get_name((GtkWidget*)children)); fflush(stdout);
//  }

//  gtk_container_forall(GTK_CONTAINER(header), &container_cb, NULL);
  
//  g_signal_connect(header, "draw", G_CALLBACK(draw), NULL);
  
//  {
//  const int lvl = 0;
//  print_child(window, (void*)&lvl);
//  }
  
  {
  const int lvl = 1;
  print_child(header, (void*)&lvl);
  }

//  gtk_widget_realize(header);
  
//  gtk_widget_realize(window);
  
//  cairo_surface_t * srf_offscreen = gtk_offscreen_window_get_surface(window);
//  cairo_surface_write_to_png(srf_offscreen, "/tmp/offscreen.png");
  
//  GdkEventButton ev;
//  gtk_main_do_event((GdkEvent*)&ev);
  
//  GtkAllocation allocation;
//  int baseline;
//  gtk_widget_get_allocated_size (window, &allocation, &baseline);
//  gtk_widget_size_allocate_with_baseline (window, &allocation, baseline);
  
  GtkAllocation allocation;
  gtk_widget_get_allocation (window, &allocation);
  allocation.width *= 2;
  gtk_widget_size_allocate(window, &allocation);

   cairo_surface_t * srf = cairo_image_surface_create (
         CAIRO_FORMAT_ARGB32,
         gtk_widget_get_allocated_width(window),
         gtk_widget_get_allocated_height(window));
   cairo_t *cr = cairo_create(srf);
   gtk_widget_draw(window, cr);
//   gtk_widget_hide(window);
   cairo_surface_write_to_png(srf, "/tmp/win.png");
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
