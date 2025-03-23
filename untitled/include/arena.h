#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdbool>
#include <cmath>

#define DEG_TO_RAD (M_PI/ 180)

using namespace std;

struct shape
{   
    string type;
    uint16_t num_sides = 0;
    float side_len = 0;
    uint16_t wall_thickness = 1;
    float interior_angle = 0;
    uint16_t mat_len;
    bool **mat;
};

class arena
{
    public:
        arena();
        arena(string custom_shape,uint16_t num_sides,float side_len,u_int wall_thickness=1, uint16_t num_obstacles=0);
        ~arena();

        shape arena_shape;

    private:

        
        uint16_t resolution = 10; //set the resolution as how many units make 1 m
        uint16_t buffer = 5; //doubt its existence
        uint16_t scaled_len = 0;
        uint16_t num_obstacles;
        
        
        int create_arena();
        void draw_wall();
        bool test();


};

void disp_matrix(bool **mat,uint16_t mat_len);

arena::arena()
{
    arena_shape.type = "square";
    arena_shape.num_sides = 4;
    arena_shape.side_len = 1;
    arena_shape.wall_thickness = 1;

    scaled_len = (arena_shape.side_len*resolution) + arena_shape.wall_thickness + 1;

    create_arena();
    draw_wall();
    disp_matrix(arena_shape.mat,arena_shape.mat_len);
}

arena::arena(string custom_shape,uint16_t num_sides,float side_len, u_int wall_thickness,uint16_t num_obstacles)
{
    arena_shape.type = custom_shape; 
    arena_shape.num_sides = num_sides;
    arena_shape.side_len = side_len;
    arena_shape.wall_thickness = wall_thickness;

    scaled_len = (arena_shape.side_len*resolution) + arena_shape.wall_thickness + 1;

    create_arena();
    draw_wall();
    disp_matrix(arena_shape.mat,arena_shape.mat_len);

}

arena::~arena()
{
    if(arena_shape.mat)
    {
        for(uint16_t i = 0; i < arena_shape.mat_len; ++i) 
        {
            delete [] arena_shape.mat[i];
        }
        delete [] arena_shape.mat;
        arena_shape.mat = nullptr;

    }
}


int arena::create_arena()
{
    uint16_t n = arena_shape.num_sides; 

    if((arena_shape.type == "circle") || (n == 1)) 
    {   
        arena_shape.mat_len = (scaled_len*2) + resolution;
        
        arena_shape.mat = new bool*[arena_shape.mat_len];

        for(uint16_t i = 0; i < arena_shape.mat_len; ++i) 
        {
            arena_shape.mat[i] = new bool[arena_shape.mat_len];

            cout<<"mat_len "<<arena_shape.mat_len<<endl;
        }
        
        return 0; 

    }else if(n > 2)
    {   
        arena_shape.interior_angle = 180 - (360 / n);

        arena_shape.mat_len = (2 * scaled_len / (2 * sin(M_PI / n))) + resolution;

        arena_shape.mat = new bool*[arena_shape.mat_len]();
        
        for(uint16_t i = 0; i < arena_shape.mat_len; ++i) 
        {
            arena_shape.mat[i] = new bool[arena_shape.mat_len];
        }


        return 0;

    }else 
    {
        cerr<<"INVALID NUMBER OF LENGHTS"<<endl;
        return -1;
    }
}


// void arena::disp_arena()
// {
//     for(int i = 0; i < mat_len; ++i)
//     {
//         for(int j = 0; j < mat_len; ++j)
//         {
//             cout << arena_mat[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

void arena::draw_wall()
{   
    float cos_comp,sin_comp;

    if((arena_shape.type == "circle") || (arena_shape.num_sides == 1))
    {
        int center_x = (arena_shape.mat_len/2);
        int center_y = (arena_shape.mat_len/2);
        int radius = scaled_len;


        for(int i = 0; i < 360; i++)
        {   
            int x = 0,y = 0,a = 0, b = 0;

            sin_comp = std::round((sin(i * DEG_TO_RAD)) * 100000) / 100000;
            cos_comp = std::round((cos(i * DEG_TO_RAD)) * 100000) / 100000; 

            x = (radius*cos_comp) + center_x;
            y = (radius*sin_comp) + center_y;
            

            for(int i = -arena_shape.wall_thickness;i < (arena_shape.wall_thickness);i++)
            {
                for(int j = -arena_shape.wall_thickness;j < (arena_shape.wall_thickness);j++)
                {
                    a = y+i, b = x+j;
                    if(a >= 0 && a < arena_shape.mat_len && b >= 0 && b < arena_shape.mat_len) // Prevent out-of-bounds access
                    arena_shape.mat[a][b] = true;
                }   
            }
            
        }
       
    
        
        

    }else if(arena_shape.num_sides > 2)
    {   

        int side_start_x = (arena_shape.mat_len/2) - (scaled_len)/2;
        float apothem = scaled_len / (2*tan(DEG_TO_RAD*(180/arena_shape.num_sides)));
        int side_start_y = ((arena_shape.mat_len/2) + apothem) - 1;
        
        int angle_step = 0;
        int exterior_angle =  180 - arena_shape.interior_angle;
        for(int i = 0;i < arena_shape.num_sides;i++)
        {   
            int y = 0,x = 0,a = 0, b = 0;

            for(int j = 0;j < scaled_len;j++)
            {   
                sin_comp = std::round((sin(angle_step * DEG_TO_RAD)) * 100000) / 100000;
                cos_comp = std::round((cos(angle_step * DEG_TO_RAD)) * 100000) / 100000; 
    
                y = side_start_y - round(j*sin_comp);
                x = side_start_x + round(j*cos_comp);
                
                for(int i = -arena_shape.wall_thickness;i < (arena_shape.wall_thickness);i++)
                {
                    for(int j = -arena_shape.wall_thickness;j < (arena_shape.wall_thickness);j++)
                    {
                        a = y+i, b = x+j;
                        if(a >= 0 && a < arena_shape.mat_len && b >= 0 && b < arena_shape.mat_len) // Prevent out-of-bounds access
                        arena_shape.mat[a][b] = true;
                    }   
                }
            }

            side_start_y = y;
            side_start_x = x;
            angle_step += exterior_angle;

        }        
    
    }
    
}


bool arena::test()
{
    // arena hexagon("hexagon",6,3,0);
    arena dodecagon("dodecagon",12,5,0);
    // arena circle("circle",3,1,0);
    // arena square;

    return true;
}

void disp_matrix(bool **mat,uint16_t mat_len)
{
    for(int i = 0; i < mat_len; ++i)
    {
        for(int j = 0; j < mat_len; ++j)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}
