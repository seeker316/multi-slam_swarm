#pragma once

#include "arena.h"

arena::arena()
{
    arena_shape.type = "square";
    arena_shape.num_sides = 4;
    arena_shape.side_len = 1;
    arena_shape.wall_thickness = 1;

    scaled_len = arena_shape.side_len*resolution;

    create_arena();
    draw_wall();

}

arena::arena(string custom_shape,uint16_t num_sides,float side_len, u_int wall_thickness,uint16_t num_obstacles)
{
    arena_shape.type = custom_shape; 
    arena_shape.num_sides = num_sides;
    arena_shape.side_len = side_len;
    arena_shape.wall_thickness = wall_thickness;

    scaled_len = arena_shape.side_len*resolution;

    create_arena();
    draw_wall();
}

arena::~arena()
{
    /*
    if(arena_shape.mat)
    {
        for(uint16_t i = 0; i < arena_shape.mat_len; ++i) 
            delete [] arena_shape.mat[i];

        delete [] arena_shape.mat;
        arena_shape.mat = nullptr;

    }
    */
}


int arena::create_arena()
{
    uint16_t n = arena_shape.num_sides; 

    if((arena_shape.type == "circle") || (n == 1)) 
    {   
        arena_shape.mat_len = (scaled_len + (arena_shape.wall_thickness+1))*2 - 1;

        //arena_shape.mat = new uint8_t *[arena_shape.mat_len];

      //for(uint16_t i = 0; i < arena_shape.mat_len; ++i) 
        //arena_shape.mat[i] = new uint8_t[arena_shape.mat_len];
        
        arena_shape.resize_mat(arena_shape.mat_len);

        return 0; 

    }else if(n > 2)
    {   
        arena_shape.interior_angle = 180 - (360 / n);

        arena_shape.mat_len = (scaled_len / sin(M_PI / n)) + 2*arena_shape.wall_thickness + 1;
        
        //arena_shape.mat = new uint8_t *[arena_shape.mat_len]();
        
        //for(uint16_t i = 0; i < arena_shape.mat_len; ++i)
        //    arena_shape.mat[i] = new uint8_t[arena_shape.mat_len];

        arena_shape.resize_mat(arena_shape.mat_len);
        
        return 0;

    }else 
    {
        cerr<<"INVALID NUMBER OF LENGHTS"<<endl;
        return -1;
    }
}


void arena::draw_wall()
{   
    float cos_comp,sin_comp;

    if((arena_shape.type == "circle") || (arena_shape.num_sides == 1))
    {
        int center_x = (arena_shape.mat_len/2);
        int center_y = (arena_shape.mat_len/2);
        int radius = scaled_len;

        //arena_shape.mat[center_y][center_x] = 2;


        for(int i = 0; i < 360; i++)
        {   
            int x = 0,y = 0,a = 0, b = 0;

            sin_comp = std::round((sin(i * DEG_TO_RAD)) * 100000) / 100000;
            cos_comp = std::round((cos(i * DEG_TO_RAD)) * 100000) / 100000; 

            x = (radius*cos_comp) + center_x;
            y = (radius*sin_comp) + center_y;
            

            for(int i = 0;i < (arena_shape.wall_thickness);i++)
            {
                for(int j = 0;j < (arena_shape.wall_thickness);j++)
                {                       
                    if(y > (arena_shape.mat_len/2))
                        a = y-i;
                    else
                        a = y+i;

                    if(x > (arena_shape.mat_len/2))
                        b = x-j;
                    else
                        b = x+j;

                    if(a >= 0 && a < arena_shape.mat_len && b >= 0 && b < arena_shape.mat_len) // Prevent out-of-bounds access
                    arena_shape.mat[a][b] = 1;
                }   
            }

            
        }
       
    
    }else if(arena_shape.num_sides > 2)
    {   
        float dum_length = scaled_len + arena_shape.wall_thickness;

        float side_start_x = (float(arena_shape.mat_len)/2) - ((dum_length)/2);

        float apothem = arena_shape.num_sides%2 ? (dum_length / (2 * tan(M_PI / arena_shape.num_sides))) : (dum_length / (2 * tan(M_PI / arena_shape.num_sides))) - 1;

        float side_start_y = ((float(arena_shape.mat_len)/2) + apothem);
        
        int angle_step = 0;
        int exterior_angle =  180 - arena_shape.interior_angle;


        for(int i = 0;i < arena_shape.num_sides;i++)
        {   
            int y = 0,x = 0,a = 0, b = 0;

            for(int j = 0;j < dum_length;j++)
            {   
                sin_comp = std::round((sin(angle_step * DEG_TO_RAD)) * 100000) / 100000;
                cos_comp = std::round((cos(angle_step * DEG_TO_RAD)) * 100000) / 100000; 
    
                y = round(side_start_y - round(j*sin_comp));
                x = round(side_start_x + round(j*cos_comp));
                

                if(y >= 0 && y < arena_shape.mat_len && x >= 0 && x < arena_shape.mat_len) // Prevent out-of-bounds access
                arena_shape.mat[y][x] = 1;

                for(int i = 0;i < (arena_shape.wall_thickness);i++)
                {
                    for(int j = 0;j < (arena_shape.wall_thickness);j++)
                    {                           
                        if(y > (arena_shape.mat_len/2))
                            a = y-i;
                        else
                            a = y+i;
    
                        if(x > (arena_shape.mat_len/2))
                            b = x-j;
                        else
                            b = x+j;
    
                        if(a >= 0 && a < arena_shape.mat_len && b >= 0 && b < arena_shape.mat_len) // Prevent out-of-bounds access
                            arena_shape.mat[a][b] = 1;
                    }   
                }

            }

            side_start_y = y;
            side_start_x = x;
            angle_step += exterior_angle;

        }        

    }
    
}

bool test( string testfor)
{
    if(testfor == "circle")
    {
        cout<<"test "<<testfor<<endl;

        arena test1a("circle",1,1,4);
        cout<<test1a.arena_shape.type<<endl;       
        cout<<"side_len "<<test1a.arena_shape.side_len<<endl; 
        cout<<"mat_len "<<test1a.arena_shape.mat_len<<endl;
        cout<<"thickness "<<test1a.arena_shape.wall_thickness<<endl;

        arena test1b("circle",1,2,3);
        cout<<test1b.arena_shape.type<<endl;
        cout<<"side_len "<<test1b.arena_shape.side_len<<endl;
        cout<<"mat_len "<<test1b.arena_shape.mat_len<<endl;
        cout<<"thickness "<<test1b.arena_shape.wall_thickness<<endl;

        arena test1c("circle",1,3,6);
        cout<<test1c.arena_shape.type<<endl;
        cout<<"side_len "<<test1a.arena_shape.side_len<<endl; 
        cout<<"mat_len "<<test1c.arena_shape.mat_len<<endl;
        cout<<"thickness "<<test1c.arena_shape.wall_thickness<<endl;        
        
        return true;
    }
    else if(testfor == "even_polygon")
    {   
        cout<<"test "<<testfor<<endl;

        arena test2a("square",4,1);
        cout<<test2a.arena_shape.type<<endl;
        cout<<"side_len "<<test2a.arena_shape.side_len<<endl;
        cout<<"mat_len "<<test2a.arena_shape.mat_len<<endl;
        cout<<"thickness "<<test2a.arena_shape.wall_thickness<<endl;

        arena test2b("hexagon",6,1);
        cout<<test2b.arena_shape.type<<endl;
        cout<<"side_len "<<test2b.arena_shape.side_len<<endl;
        cout<<"mat_len "<<test2b.arena_shape.mat_len<<endl;
        cout<<"thickness "<<test2b.arena_shape.wall_thickness<<endl;

        arena test2c("hexagon",6,3,3);
        cout<<test2c.arena_shape.type<<endl;
        cout<<"side_len "<<test2c.arena_shape.side_len<<endl;
        cout<<"mat_len "<<test2c.arena_shape.mat_len<<endl;
        cout<<"thickness "<<test2c.arena_shape.wall_thickness<<endl;

        arena test2d("octagon",8,1,2);
        cout<<test2d.arena_shape.type<<endl;
        cout<<"side_len "<<test2d.arena_shape.side_len<<endl;
        cout<<"mat_len "<<test2d.arena_shape.mat_len<<endl;
        cout<<"thickness "<<test2d.arena_shape.wall_thickness<<endl;


        return true;
    }
    else if(testfor == "odd_polygon")
    {
        cout<<"test "<<testfor<<endl;
        
        arena test3a("Triangle",3,1);
        cout<<test3a.arena_shape.type<<endl;
        cout<<"side_len "<<test3a.arena_shape.side_len<<endl;
        cout<<"mat_len "<<test3a.arena_shape.mat_len<<endl;
        cout<<"thickness "<<test3a.arena_shape.wall_thickness<<endl;
        
        arena test3b("Pentgon",5,1,4);
        cout<<test3b.arena_shape.type<<endl;
        cout<<"side_len "<<test3b.arena_shape.side_len<<endl;
        cout<<"mat_len "<<test3b.arena_shape.mat_len<<endl;
        cout<<"thickness "<<test3b.arena_shape.wall_thickness<<endl;
        
        arena test3c("9 side",9,3,2);
        cout<<test3c.arena_shape.type<<endl;
        cout<<"side_len "<<test3c.arena_shape.side_len<<endl;
        cout<<"mat_len "<<test3c.arena_shape.mat_len<<endl;
        cout<<"thickness "<<test3c.arena_shape.wall_thickness<<endl;
        
        arena test3d("Heptagon",7,2,3);
        cout<<test3d.arena_shape.type<<endl;
        cout<<"side_len "<<test3d.arena_shape.side_len<<endl;
        cout<<"mat_len "<<test3d.arena_shape.mat_len<<endl;
        cout<<"thickness "<<test3d.arena_shape.wall_thickness<<endl;

        return true;
    }

    return false;
}
