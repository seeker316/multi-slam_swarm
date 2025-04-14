#pragma once
#include "arena.h"

class robot
{
private:
    int create_robot();
    void draw_robot();


public:
    shape robot_shape;
    uint16_t robot_centreX,robot_centreY;
    
    robot();
    robot(string robot_type,uint16_t num_sides,float side_len);
    ~robot();

};


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

robot::robot()
{
    robot_shape.type = "MYRA";
    robot_shape.num_sides = 3;
    robot_shape.side_len = 3;

    create_robot();
    draw_robot();
    // disp_matrix(robot_shape.mat,robot_shape.mat_len);

}

robot::robot(string robot_type,uint16_t num_sides,float side_len)
{
    robot_shape.type = robot_type;
    robot_shape.num_sides = num_sides;
    robot_shape.side_len = side_len;

    create_robot();
    draw_robot();
    // disp_matrix(robot_shape.mat,robot_shape.mat_len);
}

robot::~robot()
{
    if(robot_shape.mat)
    {
        for(uint16_t i = 0; i < robot_shape.mat_len; ++i) 
            delete [] robot_shape.mat[i];

        delete [] robot_shape.mat;
        robot_shape.mat = nullptr;

    }
}

int robot::create_robot()
{
    uint16_t n = robot_shape.num_sides;

    if(n == 1) 
    {   
        robot_shape.mat_len = (robot_shape.side_len*2) + 1;
        
        robot_shape.mat = new uint8_t*[robot_shape.mat_len];

        for(uint16_t i = 0; i < robot_shape.mat_len; ++i) 
            robot_shape.mat[i] = new uint8_t[robot_shape.mat_len];
        
        return 0; 

    }else if(n > 2)
    {   
        robot_shape.interior_angle = 180 - (360 / n);

        robot_shape.mat_len = (2 * robot_shape.side_len / (2 * sin(M_PI / n)));

        robot_shape.mat = new uint8_t*[robot_shape.mat_len]();
        
        for(uint16_t i = 0; i < robot_shape.mat_len; ++i) 
            robot_shape.mat[i] = new uint8_t[robot_shape.mat_len];


        return 0;

    }else 
    {
        cerr<<"INVALID NUMBER OF LENGHTS"<<endl;
        return -1;
    }
}

void robot::draw_robot()
{   
    float cos_comp,sin_comp;

    robot_centreX = (robot_shape.mat_len/2);
    robot_centreY = (robot_shape.mat_len/2);

    if(robot_shape.num_sides == 1)
    {
        int radius = robot_shape.side_len;


        for(int i = 0; i < 360; i++)
        {   
            int x = 0,y = 0;

            sin_comp = std::round((sin(i * DEG_TO_RAD)) * 100000) / 100000;
            cos_comp = std::round((cos(i * DEG_TO_RAD)) * 100000) / 100000; 

            x = (radius*cos_comp) + robot_centreX;
            y = (radius*sin_comp) + robot_centreY;
            
            /////debug
            robot_shape.mat[robot_centreY][robot_centreX] = true;
            
            if(x >= 0 && x < robot_shape.mat_len && y >= 0 && y < robot_shape.mat_len) // Prevent out-of-bounds access
                    robot_shape.mat[y][x] = red;
            
        }


    }else if(robot_shape.num_sides > 2)
    {   
        int side_start_x = (float(robot_shape.mat_len)/2 - (robot_shape.side_len)/2);
        float apothem = robot_shape.side_len / (2*tan(DEG_TO_RAD*(180/robot_shape.num_sides)));
        int side_start_y = (float(robot_shape.mat_len/2) + apothem);


        int angle_step = 0;
        int exterior_angle =  180 - robot_shape.interior_angle;

        for(int i = 0;i < robot_shape.num_sides;i++)
        {   
            int y = 0,x = 0,a = 0, b = 0;

            for(int j = 0;j < robot_shape.side_len;j++)
            {   
                sin_comp = std::round((sin(angle_step * DEG_TO_RAD)) * 100000) / 100000;
                cos_comp = std::round((cos(angle_step * DEG_TO_RAD)) * 100000) / 100000; 
    
                y = side_start_y - round(j*sin_comp);
                x = side_start_x + round(j*cos_comp);

                if(y >= 0 && y < robot_shape.mat_len && x >= 0 && x < robot_shape.mat_len) // Prevent out-of-bounds access
                        robot_shape.mat[y][x] = red;
                
            }

            side_start_y = y;
            side_start_x = x;
            angle_step += exterior_angle;

        }
               
    }

    solid_fill(robot_shape.mat,robot_shape.mat_len,red);
    
}

