#include "arena.h"

using namespace std;


arena::arena()
{
    arena_shape.type = "square";
    arena_shape.edges = {1,1,1,1};

    arena_mat = create_arena();

    // cout<<"ptr val is "<< arena_mat << endl;

}

arena::arena(string custom_shape,vector<uint16_t> edges, uint16_t num_obstacles)
{
    arena_shape.type = custom_shape; 
    arena_shape.edges = edges;

    arena_mat = create_arena();

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

    }
}


uint16_t** arena::create_arena()
{
    uint16_t n = arena_shape.edges.size(); 
    uint16_t **mat_ptr;

    if(n == 1) 
    {   
        mat_len = (arena_shape.edges[0]*2) * resolution;
        
        mat_ptr = new uint16_t*[mat_len];

        for(uint16_t i = 0; i < mat_len; ++i) 
        {
            mat_ptr[i] = new uint16_t[mat_len];
            // cout<<"mem alloc "<<mat_ptr[i]<<endl;
        }
        
        return mat_ptr; 

    }else if(n > 2)
    {
        float interior_angle = 180 - (360 / n);

        mat_len = (n / sin(interior_angle * DEG_TO_RAD)) * resolution;
        
        mat_ptr = new uint16_t*[mat_len];
        
        for(uint16_t i = 0; i < mat_len; ++i) 
        {
            mat_ptr[i] = new uint16_t[mat_len];
            cout<<"mem alloc "<<mat_ptr[i]<<endl;
        }

        cout<<"Interior angle is : "<< interior_angle << "Mat len is :"<< mat_len <<endl;
        return mat_ptr;

    }else 
    {
        cerr<<"INVALID NUMBER OF LENGHTS"<<endl;
        return nullptr;
    }
}

void arena::draw_wall()
{
    if((arena_shape.type == "circle") || (arena_shape.edges.size == 1))
    {
        int center_x,center_y = (mat_len/2) - 1;
        int radius = arena_shape.edges[0];


        for(int i = 0; i < 360; i++)
        {
            int x = cos(i * DEG_TO_RAD) + center_x;
            int y = sin(i * DEG_TO_RAD) + center_y;
            
            arena_mat[y][x] = 1
            
        }





    }

}




int main()
{
    arena test;

    return 0;
}