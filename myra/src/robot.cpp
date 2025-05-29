#pragma once
#include "robot.h"

robot::robot()
{
   object Robot; 

}

robot::robot(string robot_shape_type,uint16_t num_sides,float side_len)
     : Robot("robot",robot_shape_type, num_sides, side_len)
{
     
}

robot::~robot()
{

}


