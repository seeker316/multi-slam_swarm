#pragma once

#include "display.h"


void display(cairo_t* cr,uint8_t **arena_mat,uint16_t mat_len)
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

int disp_init(uint8_t **mat,uint16_t mat_len)
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
