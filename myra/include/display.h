#pragma once
#include <cstdint>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>
//#include <X11/keysym.h> 
#include <vector>
#include <iostream>
#include "arena.h"

using namespace std;

class visualize
{
    private:
        const int CELL_SIZE = 4;
        int dim;    
   public:
        Display* dpy;
        XEvent e;
        
        int screen;
        uint16_t vmat_len;
        bool running =  true;

        Window root,win;

        cairo_surface_t *surface;
        cairo_t* cr;

        
        visualize();
        ~visualize();

        void disp_init(uint16_t mat_len);
        bool render(const vector<vector<uint8_t>>& arena_mat);
};


