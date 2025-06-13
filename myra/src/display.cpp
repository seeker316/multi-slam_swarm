#pragma once

#include "display.h"

visualize::visualize()
{
   dpy = XOpenDisplay(nullptr);
   if(!dpy)
   {
        cerr<<"cannot open display\n";
   }
   
   screen =  DefaultScreen(dpy);
   root = RootWindow(dpy,screen);
}

visualize::~visualize()
{
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
}

void visualize::disp_init(uint16_t mat_len)
{
    vmat_len = mat_len;
    dim = vmat_len*CELL_SIZE;

    win = XCreateSimpleWindow(dpy,root,10,10,dim,dim,1,BlackPixel(dpy,screen),WhitePixel(dpy,screen));
    
    //XSelectInput(dpy,win,ExposureMask | KeyPressMask);
    XSelectInput(dpy,win,ExposureMask);
    XMapWindow(dpy,win);

    surface = cairo_xlib_surface_create(dpy,win,DefaultVisual(dpy,screen), dim,dim);
    
    cr = cairo_create(surface);
}

bool visualize::render(const vector<vector<uint8_t>>& arena_mat)
{
  while(XPending(dpy))
    XNextEvent(dpy, &e);

    //cairo_set_source_rgb(cr ,1,1,1);
    //cairo_paint(cr);

  for(int i = 0; i < vmat_len; i++)
  {
        for(int j = 0; j < vmat_len; j++)
        {
          switch(arena_mat[i][j])
          {
             case 0: cairo_set_source_rgb(cr,1,1,1); break;
             case 1: cairo_set_source_rgb(cr,0,0,0); break;
             case 2: cairo_set_source_rgb(cr,1,0,0); break;
             case 3: cairo_set_source_rgb(cr,0,0,1); break;
             case 4: cairo_set_source_rgb(cr,0,1,0); break;
             case 5: cairo_set_source_rgb(cr,0.5,0.5,0.5); break;
          }
          
          cairo_rectangle(cr,j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
          cairo_fill(cr);
        
        // // Draw grid outline
        // (cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
        // cairo_rectangle(cr, j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
        // cairo_stroke(cr);
        }
  }

  cairo_surface_flush(surface);
  XFlush(dpy);
  
  return true;

}



//////////////////////////////////////////////////////////////////
/*
void display(cairo_t* cr,const vector<vector<uint8_t>> arena_mat,uint16_t mat_len)
{

    for(int i = 0; i < mat_len; i++)
    {
        for(int j = 0; j < mat_len; j++)
        {
            if(arena_mat[i][j] == 0)
                cairo_set_source_rgb(cr,1,1,1);
            else if (arena_mat[i][j] == 1)
                cairo_set_source_rgb(cr,0,0,0);
            else if (arena_mat[i][j] == 2)
                cairo_set_source_rgb(cr,1,0,0);
            else if (arena_mat[i][j] == 3)
                cairo_set_source_rgb(cr,0,0,1);
            else if (arena_mat[i][j] == 4)
                cairo_set_source_rgb(cr,0,1,0);
            else if (arena_mat[i][j] == 5)
                cairo_set_source_rgb(cr,0.5,0.5,0.5);


            cairo_rectangle(cr,j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            cairo_fill(cr);

            // // Draw grid outline
            // (cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
            // cairo_rectangle(cr, j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            // cairo_stroke(cr);
        }
    }
}
*/
/*
int disp_init(const vector<vector<uint8_t>> mat,uint16_t mat_len)
{   
    int dim = mat_len*CELL_SIZE;

    Display* dpy = XOpenDisplay(nullptr);
    if(!dpy)
    {
        cerr<<"cannot open display\n";
        return 1;
    }

    int screen = DefaultScreen(dpy);
    Window root = RootWindow(dpy,screen);

    Window win = XCreateSimpleWindow(dpy,root,10,10,dim,dim,1,BlackPixel(dpy,screen),WhitePixel(dpy,screen));
    
    XSelectInput(dpy,win,ExposureMask | KeyPressMask);
    XMapWindow(dpy,win);

    cairo_surface_t* surface = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy,screen), dim,dim);

    cairo_t* cr = cairo_create(surface);

    bool running = true;
    XEvent e;

    while(running)
    {
        XNextEvent(dpy, &e);

        if(e.type == Expose)
        {
            display(cr,mat,mat_len);
        }
        else if (e.type == KeyPress)
        {
            if (XLookupKeysym(&e.xkey, 0) == XK_q)
            {
                running = false;  // Exit only on 'q'
            }
        }

    }

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);

    return 0;
}

*/
