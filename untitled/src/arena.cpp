#include "arena.h"
#include "display.h"
#include "robot.h"


int main()
{   
//  TESTED & WORKING
        // test("circle");
    // test("odd_polygon");
    // test("even_polygon");
//  ______________________________
    

    arena test("hexagon",6,3,2);
    robot myraI("MYRA",1,5);

    test.arena_shape | myraI.robot_shape;
    
    disp_matrix(test.arena_shape.mat,test.arena_shape.mat_len);
    disp_init(test.arena_shape.mat,test.arena_shape.mat_len);

    return 0;
}