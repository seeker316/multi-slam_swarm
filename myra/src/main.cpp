#pragma once

#include "arena.h"
#include "display.h"
#include "robot.h"
#include "object.h"
#include "utils.h"

#define CONSOLE_CLEAR "\033[2J\033[1;1H"

int main()
{   
//  TESTED & WORKING
    // test("circle");
    // test("odd_polygon");
    // test("even_polygon");
//  ______________________________

   bool running = true;
   visualize DP;
 
   arena test("square",4,6,2);
   arena test2 = test;

   robot myraI("MYRA",1,5);

   test2.arena_shape = test.arena_shape | myraI.Robot.object_shape;

   DP.disp_init(test2.arena_shape.mat_len);
   
   while(running)
   {
        char c = getkey();   
        switch(c)
        {
            case 'w':
                myraI.Robot.object_shape.offsetY--;
                break;
            case 'a':
                myraI.Robot.object_shape.offsetX--;
                break;
            case 's':
                myraI.Robot.object_shape.offsetY++;
                break;
            case 'd':
                myraI.Robot.object_shape.offsetX++; 
                break;
            case 'q':
                return 0;
        }
        std::cout << CONSOLE_CLEAR; 
        //cout<<"object centre x is "<<myraI.Robot.object_centreX<<endl;
        //cout<<"object centre y is "<<myraI.Robot.object_centreY<<endl;
              
        myraI.Robot.draw_object();
        test2.arena_shape = test.arena_shape | myraI.Robot.object_shape;
        
        disp_matrix(test2.arena_shape.mat,test2.arena_shape.mat_len);
     
        running = DP.render(test2.arena_shape.mat);
    }
    return 0;
}

