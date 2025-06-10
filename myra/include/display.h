#pragma once
#include <cstdint>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/keysym.h> 
#include <vector>
#include <iostream>
#include "arena.h"


using namespace std;

const int CELL_SIZE = 4;

void display(cairo_t* cr, const vector<vector<uint8_t>> arena_mat, uint16_t mat_len);

int disp_init(const vector<vector<uint8_t>> mat,uint16_t mat_len);

