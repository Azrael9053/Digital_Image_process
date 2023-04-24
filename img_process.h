//
// Created by user on 2023/4/23.
//
#include "bmp.h"


#define MaxBMPSizeX    1024
#define MaxBMPSizeY    1024


void Adaptive_median_filtering(int bmp_r[MaxBMPSizeX][MaxBMPSizeY], int &width, int &height, int MAX);
void Perspective_Transformation(int bmp_r[MaxBMPSizeX][MaxBMPSizeY], int bmp_g[MaxBMPSizeX][MaxBMPSizeY], int bmp_b[MaxBMPSizeX][MaxBMPSizeY], int &width, int &height);