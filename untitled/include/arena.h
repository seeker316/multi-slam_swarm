#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdbool>
#include <math.h>

#define DEG_TO_RAD 3.14159265358979323846 / 180.0

using namespace std;

class arena
{
    public:
        arena();
        arena(string custom_shape,vector<uint16_t> edges,uint16_t num_obstacles);

        ~arena();
    private:
        struct shape
        {   
            string type;
            vector<uint16_t> edges;
            uint16_t wall_thickness;
            float interior_angle = 0;
        };
        
        shape arena_shape;
        
        uint16_t resolution = 10; //set the resolution as how many units make 1 m
        uint16_t buffer = 50; //doubt its existence
        uint16_t num_obstacles;
        
        uint16_t mat_len;
        bool **arena_mat;
        
        int create_arena();
        void disp_arena();
        void draw_wall();



};