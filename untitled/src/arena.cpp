#include "arena.h"
#include "display.h"
#include "robot.h"


int main()
{   
    arena test("square",4,2);
    // // arena test("octagon",8,1,1);
    // arena test("circle",1,1,1);
    // // // arena test;
    // disp_matrix(test.arena_shape.mat,test.arena_shape.mat_len);
    // int i = disp_init(test);

    
    robot myraI("MYRA",4,5);

    test | myraI;
    disp_matrix(test.arena_shape.mat,test.arena_shape.mat_len);
    // robot myraII("MYRA",6,6);
    // robot myraIII("MYRA",6,7);
    // robot myraIV("MYRA",6,8);
    // robot myraV("MYRA",6,9);
    // robot myraVI("MYRA",6,10);
    // robot myraVII("MYRA",6,11);
    // robot myraVIII("MYRA",6,12);
    // robot myraIX("MYRA",6,13);
    // robot myraX("MYRA",6,14);
    // robot myraXI("MYRA",6,15);
    // robot myraXII("MYRA",6,25);

    return 0;
}