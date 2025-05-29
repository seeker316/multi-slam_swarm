#pragma once
#include "arena.h"

const uint8_t black = 0;
const uint8_t white  = 1;
const uint8_t red = 2;
const uint8_t blue = 3;
const uint8_t green = 4;
const uint8_t grey = 5;

class object
{
private:
    int create_object();
    void draw_object();


public:
    shape object_shape;
    string object_type;
    uint8_t color;
    uint16_t object_centreX,object_centreY;
    
    object();
    object(string object_type,string shape_type,uint16_t num_sides,float side_len);
    ~object();

};


void operator|(shape& shape1, const shape& shape2); 

