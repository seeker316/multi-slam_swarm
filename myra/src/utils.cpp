#pragma once

#include "utils.h"

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


void disp_matrix(const vector<vector<uint8_t>> mat,uint16_t mat_len)
{
    for(int i = 0; i < mat_len; ++i)
    {
        for(int j = 0; j < mat_len; ++j)
        {
            cout << (int)mat[i][j] << " ";
        }
        cout << endl;
    }
}

void num_zero(const vector<vector<uint8_t>> mat,uint16_t mat_len)
{   
    int count = 0;
    for(int i = 0; i < mat_len; ++i)
    {
        for(int j = 0; j < mat_len; ++j)
        {
            if(mat[i][j] == 0)
                count++;
        }
    }
    cout<< "The zero count is" << count << endl;
}

void solid_fill(vector<vector<uint8_t>> &mat,uint16_t mat_len,uint8_t color)
{   
    uint16_t start_point = 0, end_point = 0;

    for(int i = 0; i < mat_len; ++i)
    {   
        for(int j = 0; j < mat_len; ++j)
        {
            if(mat[i][j] != 0)
            {
                start_point = j;
                break;
            }
        }
        for(int j = mat_len-1; j >= 0; --j)
        {
            if(mat[i][j] != 0)
            {
                end_point = j;
                break;
            }
        }

        if (start_point != 0 || end_point != 0)
        {
            for(int j = start_point+1; j <= end_point-1; ++j)
            {
                mat[i][j] = color;
            }
            
            start_point = 0,end_point = 0;
        }
    }
}







