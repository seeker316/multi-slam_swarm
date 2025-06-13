#include "arena.h"
#include "display.h"
#include "robot.h"
#include "object.h"

#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <thread>
#include <mutex>

char getkey()
{
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);

        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        int ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return ch;


};

int main()
{   
/*
//  TESTED & WORKING
    // test("circle");
    // test("odd_polygon");
    // test("even_polygon");
//  ______________________________
    
  visualize DP;    

  arena test("hexagon",6,3,2);
  arena test2 = test;
    
  robot myraI("MYRA",4,5);

  test2.arena_shape = test.arena_shape | myraI.Robot.object_shape;
     
     
  while(true)
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
        //cout<<"char is "<<c<<endl;
        system("clear");
        
        //cout<<"object centre x is "<<myraI.Robot.object_centreX<<endl;
        //cout<<"object centre y is "<<myraI.Robot.object_centreY<<endl;
              
        myraI.Robot.draw_object();
        test2.arena_shape = test.arena_shape | myraI.Robot.object_shape;
        
        disp_matrix(test2.arena_shape.mat,test2.arena_shape.mat_len);
        //disp_init(test2.arena_shape.mat,test2.arena_shape.mat_len);
  }    
    // disp_matrix(test.arena_shape.mat,test.arena_shape.mat_len);
    // disp_init(test.arena_shape.mat,test.arena_shape.mat_len);
*/
////////////////////////////////////////////////////
   bool running = true;
   visualize DP;
 
   arena test("hexagon",6,3,2);
   arena test2 = test;

   robot myraI("MYRA",4,5);

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
        std::cout << "\033[2J\033[1;1H"; 
        //cout<<"object centre x is "<<myraI.Robot.object_centreX<<endl;
        //cout<<"object centre y is "<<myraI.Robot.object_centreY<<endl;
              
        myraI.Robot.draw_object();
        test2.arena_shape = test.arena_shape | myraI.Robot.object_shape;
        
        disp_matrix(test2.arena_shape.mat,test2.arena_shape.mat_len);
     
        running = DP.render(test2.arena_shape.mat);
    }
    return 0;
}

