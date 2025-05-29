#pragma once
#include "object.h"

void operator|(shape& shape1, const shape& shape2) 
{
    u_int16_t start_col = ((shape1.mat_len-1) / 2) - ((shape2.mat_len-1) / 2);
    u_int16_t start_row = (shape1.mat_len / 2) - (shape2.mat_len / 2);

    for (int i = 0; i < shape2.mat_len; i++) 
    {
        for (int j = 0; j < shape2.mat_len; j++) 
            shape1.mat[start_row + i][start_col + j] |= shape2.mat[i][j];
    }
}

object::object()
{
    this->object_type = "default";
    object_shape.type = "triangle";
    object_shape.num_sides = 3;
    object_shape.side_len = 3;

    create_object();
    draw_object();
    color = grey;
    // disp_matrix(object_shape.mat,object_shape.mat_len);

}

object::object(string object_type, string shape_type,uint16_t num_sides,float side_len)
{
    this->object_type = object_type;

    object_shape.type = shape_type;
    object_shape.num_sides = num_sides;
    object_shape.side_len = side_len;
    
    if(object_type == "robot")
        color = red;
    else if(object_type == "obstacle")
        color = blue;
    else
        color = grey;
    

    create_object();
    draw_object();
    // disp_matrix(object_shape.mat,object_shape.mat_len);
}

object::~object()
{
    if(object_shape.mat)
    {
        for(uint16_t i = 0; i < object_shape.mat_len; ++i) 
            delete [] object_shape.mat[i];

        delete [] object_shape.mat;
        object_shape.mat = nullptr;

    }
}

int object::create_object()
{
    uint16_t n = object_shape.num_sides;

    if(n == 1) 
    {   
        object_shape.mat_len = (object_shape.side_len*2) + 1;
        
        object_shape.mat = new uint8_t*[object_shape.mat_len];

        for(uint16_t i = 0; i < object_shape.mat_len; ++i) 
            object_shape.mat[i] = new uint8_t[object_shape.mat_len];
        
        return 0; 

    }else if(n > 2)
    {   
        object_shape.interior_angle = 180 - (360 / n);

        object_shape.mat_len = (2 * object_shape.side_len / (2 * sin(M_PI / n)));

        object_shape.mat = new uint8_t*[object_shape.mat_len]();
        
        for(uint16_t i = 0; i < object_shape.mat_len; ++i) 
            object_shape.mat[i] = new uint8_t[object_shape.mat_len];


        return 0;

    }else 
    {
        cerr<<"INVALID NUMBER OF LENGHTS"<<endl;
        return -1;
    }
}

void object::draw_object()
{   
    float cos_comp,sin_comp;

    object_centreX = (object_shape.mat_len/2);
    object_centreY = (object_shape.mat_len/2);

    if(object_shape.num_sides == 1)
    {
        int radius = object_shape.side_len;


        for(int i = 0; i < 360; i++)
        {   
            int x = 0,y = 0;

            sin_comp = std::round((sin(i * DEG_TO_RAD)) * 100000) / 100000;
            cos_comp = std::round((cos(i * DEG_TO_RAD)) * 100000) / 100000; 

            x = (radius*cos_comp) + object_centreX;
            y = (radius*sin_comp) + object_centreY;
            
            /////debug
            object_shape.mat[object_centreY][object_centreX] = true;
            
            if(x >= 0 && x < object_shape.mat_len && y >= 0 && y < object_shape.mat_len) // Prevent out-of-bounds access
                    object_shape.mat[y][x] = color;
            
        }


    }else if(object_shape.num_sides > 2)
    {   
        int side_start_x = (float(object_shape.mat_len)/2 - (object_shape.side_len)/2);
        float apothem = object_shape.side_len / (2*tan(DEG_TO_RAD*(180/object_shape.num_sides)));
        int side_start_y = (float(object_shape.mat_len/2) + apothem);


        int angle_step = 0;
        int exterior_angle =  180 - object_shape.interior_angle;

        for(int i = 0;i < object_shape.num_sides;i++)
        {   
            int y = 0,x = 0,a = 0, b = 0;

            for(int j = 0;j < object_shape.side_len;j++)
            {   
                sin_comp = std::round((sin(angle_step * DEG_TO_RAD)) * 100000) / 100000;
                cos_comp = std::round((cos(angle_step * DEG_TO_RAD)) * 100000) / 100000; 
    
                y = side_start_y - round(j*sin_comp);
                x = side_start_x + round(j*cos_comp);

                if(y >= 0 && y < object_shape.mat_len && x >= 0 && x < object_shape.mat_len) // Prevent out-of-bounds access
                        object_shape.mat[y][x] = color;
                
            }

            side_start_y = y;
            side_start_x = x;
            angle_step += exterior_angle;

        }
               
    }

    solid_fill(object_shape.mat,object_shape.mat_len,color);
    
}
