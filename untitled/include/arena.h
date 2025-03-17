#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdbool>
#include <cmath>

#define DEG_TO_RAD (M_PI/ 180)

using namespace std;

class arena
{
    public:
        arena();
        arena(string custom_shape,uint16_t num_sides,float side_len,uint16_t num_obstacles);
        ~arena();

        uint16_t mat_len;
        bool **arena_mat;

    private:
        struct shape
        {   
            string type;
            uint16_t num_sides = 0;
            float side_len = 0;
            uint16_t wall_thickness = 2;
            float interior_angle = 0;
            
        };
        
        shape arena_shape;
        
        uint16_t resolution = 10; //set the resolution as how many units make 1 m
        uint16_t buffer = 5; //doubt its existence
        uint16_t scaled_len = 0;
        uint16_t num_obstacles;
        
        
        int create_arena();
        void disp_arena();
        void draw_wall();
        
        bool test();


};

arena::arena()
{
    arena_shape.type = "square";
    arena_shape.num_sides = 4;
    arena_shape.side_len = 1;

    scaled_len = arena_shape.side_len*resolution;

    create_arena();
    draw_wall();
    // disp_arena();
}

arena::arena(string custom_shape,uint16_t num_sides,float side_len, uint16_t num_obstacles)
{
    arena_shape.type = custom_shape; 
    arena_shape.num_sides = num_sides;
    arena_shape.side_len = side_len;

    scaled_len = arena_shape.side_len*resolution;

    create_arena();
    draw_wall();
    // disp_arena();

}

arena::~arena()
{
    if(arena_mat)
    {
        for(uint16_t i = 0; i < mat_len; ++i) 
        {
            delete [] arena_mat[i];
        }
        delete [] arena_mat;
        arena_mat = nullptr;

    }
}


int arena::create_arena()
{
    uint16_t n = arena_shape.num_sides; 

    if((arena_shape.type == "circle") || (n == 1)) 
    {   
        mat_len = (arena_shape.side_len*2) * resolution;
        
        arena_mat = new bool*[mat_len]();

        for(uint16_t i = 0; i < mat_len; ++i) 
        {
            arena_mat[i] = new bool[mat_len];

            cout<<"mat_len "<<mat_len<<endl;
        }
        
        return 0; 

    }else if(n > 2)
    {   
        arena_shape.interior_angle = 180 - (360 / n);

        mat_len = 2 * scaled_len / (2 * sin(M_PI / n));

        arena_mat = new bool*[mat_len]();
        
        for(uint16_t i = 0; i < mat_len; ++i) 
        {
            arena_mat[i] = new bool[mat_len];
        }


        return 0;

    }else 
    {
        cerr<<"INVALID NUMBER OF LENGHTS"<<endl;
        return -1;
    }
}


void arena::disp_arena()
{
    for(int i = 0; i < mat_len; ++i)
    {
        for(int j = 0; j < mat_len; ++j)
        {
            cout << arena_mat[i][j] << " ";
        }
        cout << endl;
    }
}

void arena::draw_wall()
{   
    float cos_comp,sin_comp;

    if((arena_shape.type == "circle") || (arena_shape.num_sides == 1))
    {
        int center_x = (mat_len/2);
        int center_y = (mat_len/2);
        int radius = scaled_len;


        for(int i = 0; i < 360; i++)
        {   
            sin_comp = std::round((sin(i * DEG_TO_RAD)) * 100000) / 100000;
            cos_comp = std::round((cos(i * DEG_TO_RAD)) * 100000) / 100000; 

            int x = (radius*cos_comp) + center_x;
            int y = (radius*sin_comp) + center_y;
            
            if(x >= 0 && x < mat_len && y >= 0 && y < mat_len) // Prevent out-of-bounds access
                arena_mat[y][x] = true;
            
        }

    }else if(arena_shape.num_sides > 2)
    {   
        int side_start_x = (mat_len/2) - (scaled_len)/2;
        float apothem = scaled_len / (2*tan(DEG_TO_RAD*(180/arena_shape.num_sides)));
        int side_start_y = ((mat_len/2) + apothem) - 1;
        

        int angle_step = 0;
        int exterior_angle =  180 - arena_shape.interior_angle;
        for(int i = 0;i < arena_shape.num_sides;i++)
        {   
            int y_point = 0,x_point = 0;

            for(int j = 0;j < scaled_len;j++)
            {   
                sin_comp = std::round((sin(angle_step * DEG_TO_RAD)) * 100000) / 100000;
                cos_comp = std::round((cos(angle_step * DEG_TO_RAD)) * 100000) / 100000; 
    
                y_point = side_start_y - round(j*sin_comp);
                x_point = side_start_x + round(j*cos_comp);
                
                if(x_point >= 0 && x_point < mat_len && y_point >= 0 && y_point < mat_len)
                {
                    arena_mat[y_point][x_point] = true;
                }

            }

            side_start_y = y_point;
            side_start_x = x_point;
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