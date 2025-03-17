#include "arena.h"

using namespace std;

arena::arena()
{
    arena_shape.type = "square";
    arena_shape.num_sides = 4;
    arena_shape.side_len = 1;

    scaled_len = arena_shape.side_len*resolution;

    create_arena();
    draw_wall();
    disp_arena();
    // cout<<"ptr val is "<< arena_mat << endl;

}

arena::arena(string custom_shape,uint16_t num_sides,float side_len, uint16_t num_obstacles)
{
    arena_shape.type = custom_shape; 
    arena_shape.num_sides = num_sides;
    arena_shape.side_len = side_len;

    scaled_len = arena_shape.side_len*resolution;

    create_arena();
    draw_wall();
    disp_arena();

    // cout<<"ptr val is "<< arena_mat << endl;
}

arena::~arena()
{
    if(arena_mat)
    {
        for(uint16_t i = 0; i < mat_len; ++i) 
        {
            delete [] arena_mat[i];
            // cout<<"mem pos "<<i<<endl;
            // cout<<"mem del "<<arena_mat[i]<<endl;
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
            // cout<<"mem alloc "<<mat_ptr[i]<<endl;
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
    cout<<"shape is "<<arena_shape.type<<" / Side len is "<<scaled_len<<endl;
    cout << "matrix length is " << mat_len <<endl;
    // cout<<"interior angle is "<< arena_shape.interior_angle << endl;
    // cout << "number of sides are " << arena_shape.num_sides <<endl;

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
        int side_start_y = ((mat_len/2) + apothem);
        
                
        // for(int i = side_start_x;i<(side_start_x + (scaled_len));i++)
        // {
        //     arena_mat[mat_len-1][i] = true;
        // }

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
                
                // cout << " j is " << j <<" /side_start_y is "<<side_start_y<<endl;
                // cout << " y is " << y_point <<" /x is "<<x_point<<endl;
                // cout << sin_comp << " --> ###RED FLAG" <<endl;
                if(x_point >= 0 && x_point < mat_len && y_point >= 0 && y_point < mat_len)
                {
                    arena_mat[y_point][x_point] = true;
                    // cout << " y is " << y_point <<" /x is "<<x_point<<endl;
                    if(i == arena_shape.num_sides - 1)
                    {
                        cout << " y is " << y_point <<" /x is "<<x_point<<endl;
                        // cout << " j is " << j <<" /side_start_y is "<<side_start_y<<endl;
                        // cout << " y is " << y_point <<" /x is "<<x_point<<endl;
                        cout << apothem << " --> ###RED FLAG" <<endl;
                    }

                }



            }


               

            side_start_y = y_point;
            side_start_x = x_point;

            angle_step += exterior_angle;

            // cout<<"step angle "<<angle_step<<endl;
            // cout << " start y is " << side_start_y <<"  start x is "<<side_start_x<<endl;
        }
    
    }
    


}


bool test()
{
    arena hexagon("hexagon",6,3,0);
    arena dodecagon("dodecagon",12,5,0);
    arena circle("circle",3,1,0);
    arena square;

    return true;
}

int main()
{   
    if(!test()) return -1;

    return 0;
}