#include "arena.h"

using namespace std;


arena::arena()
{
    arena_shape.type = "square";
    arena_shape.edges = {1,1,1,1};

    create_arena();
    arena_mat[2][3] = 1;
    disp_arena();
    // cout<<"ptr val is "<< arena_mat << endl;

}

arena::arena(string custom_shape,vector<uint16_t> edges, uint16_t num_obstacles)
{
    arena_shape.type = custom_shape; 
    arena_shape.edges = edges;

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
            // cout<<"mem del "<<arena_mat[i]<<endl;
        }
        delete [] arena_mat;
        arena_mat = nullptr;

    }
}


int arena::create_arena()
{
    uint16_t n = arena_shape.edges.size(); 

    if(n == 1) 
    {   
        mat_len = (arena_shape.edges[0]*2) * resolution;
        
        arena_mat = new bool*[mat_len]();

        for(uint16_t i = 0; i < mat_len; ++i) 
        {
            arena_mat[i] = new bool[mat_len];
            // cout<<"mem alloc "<<mat_ptr[i]<<endl;
        }
        
        return 0; 

    }else if(n > 2)
    {
        arena_shape.interior_angle = 180 - (360 / n);

        mat_len = (n / sin(arena_shape.interior_angle * DEG_TO_RAD)) * resolution;
        
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
    if((arena_shape.type == "circle") || (arena_shape.edges.size() == 1))
    {
        int center_x = (mat_len/2);
        int center_y = (mat_len/2);
        int radius = arena_shape.edges[0]*resolution;


        for(int i = 0; i < 360; i++)
        {
            int x = (radius*cos(i * DEG_TO_RAD)) + center_x;
            int y = (radius*sin(i * DEG_TO_RAD)) + center_y;
            
            if(x >= 0 && x < mat_len && y >= 0 && y < mat_len) // Prevent out-of-bounds access
                arena_mat[y][x] = true;
            
        }

    }else if (arena_shape.edges.size() > 2)
    {
        cout<<"interior angle is "<< arena_shape.interior_angle << endl;
        cout << "number of sides are" << arena_shape.edges.size()<<endl;
        
    }
    


}




int main()
{   
    vector<uint16_t> test_dim = {2,2,2};
    arena test("triangle",test_dim,0);
    
    // arena test;

    return 0;
}