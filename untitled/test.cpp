// #include <iostream>
// #include <cstdint>

// using namespace std;

// int main()
// {   
//     const int sizeY = 5;
//     const int sizeX = 5;

//     uint16_t **ary = new uint16_t*[sizeY];
    
//     for(uint16_t i = 0; i < sizeY; ++i) 
//     {
//         ary[i] = new uint16_t[sizeX];
//         cout<<"mem alloc "<<ary[i]<<endl;
//     }

//     ary[2][3] = 69;
//     for(int i = 0; i < sizeY; ++i)
//     {
//         for(int j = 0; j < sizeX; ++j)
//         {
//             cout << ary[i][j] << " ";
//         }
//         cout << endl;
//     }


//     for(uint16_t i = 0; i < sizeY; ++i) 
//     {
//         delete [] ary[i];
//         cout<<"mem del "<<ary[i]<<endl;
//     }
//     delete [] ary;

//     return 0;
// }

#include <iostream>
#include <cstdint>
#include <bitset>

#define Y_AXIS 8

using namespace std;

int main()
{
    int arry[Y_AXIS];

    for(int i = 0; i<Y_AXIS;i++)
    {
        arry[i] = 0x00;
    }

    arry[Y_AXIS/2] = 0b10101010;

    for(int i = 0; i < Y_AXIS;i++)
    {
        cout << "INDEX :" << " " << i << "- " << bitset<8>(arry[i]) << endl;
    }

}