#pragma once

#include <iostream>
#include <cmath>
#include <cstdint>
#include "utils.h"

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
    uint8_t **mat;
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


};

bool test( string testfor);


