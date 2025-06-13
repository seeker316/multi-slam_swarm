#pragma once
#include <iostream>
#include <cstdint>
#include <vector>

#include <termios.h>
#include <unistd.h>
#include <cstdlib>


using namespace std;

struct shape
{   
    string type;
    uint16_t num_sides = 0;
    float side_len = 0;
    uint16_t wall_thickness = 1;
    float interior_angle = 0;
    uint16_t mat_len;
    vector<vector<uint8_t>> mat;

    uint offsetX = 0,offsetY = 0;

    shape() = default;

    shape(uint16_t len) : mat_len(len), mat(len, vector<uint8_t>(len,0)) {}

    void resize_mat(uint16_t len)
    {
        mat_len = len;
        mat.assign(len, std::vector<uint8_t>(len,0));
    }
};

void disp_matrix(const vector<vector<uint8_t>> mat,uint16_t mat_len);

void num_zero(const vector<vector<uint8_t>> mat,uint16_t mat_len);

void solid_fill(vector<vector<uint8_t>> &mat,uint16_t mat_len,uint8_t color);

char getkey();
