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
    private:
        struct shape
        {   
            string type;
            uint16_t num_sides = 0;
            float side_len = 0;
            uint16_t wall_thickness;
            float interior_angle = 0;
            
        };
        
        shape arena_shape;
        
        uint16_t resolution = 10; //set the resolution as how many units make 1 m
        uint16_t buffer = 5; //doubt its existence
        uint16_t scaled_len = 0;
        uint16_t num_obstacles;
        
        uint16_t mat_len;
        bool **arena_mat;
        
        int create_arena();
        void disp_arena();
        void draw_wall();



};