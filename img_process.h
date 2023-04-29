//
// Created by user on 2023/4/23.
//

#ifndef IMG_PROCESS_H
#define IMG_PROCESS_H

#include "bmp.h"


#define MaxBMPSizeX    1024
#define MaxBMPSizeY    1024

#define a0 0.5765
#define b0 0.2302
#define c0 70.0
#define d0 -0.1597
#define e0 0.9060
#define f0 100.0
#define g0 -0.0006
#define h0 0.0005

#define TH 90
#define TL 65

extern int r[MaxBMPSizeX][MaxBMPSizeY];
extern int g[MaxBMPSizeX][MaxBMPSizeY];
extern int b[MaxBMPSizeX][MaxBMPSizeY];
extern int R[MaxBMPSizeX][MaxBMPSizeY];
extern int G[MaxBMPSizeX][MaxBMPSizeY];
extern int B[MaxBMPSizeX][MaxBMPSizeY];




void Adaptive_median_filtering(int bmp_r[MaxBMPSizeX][MaxBMPSizeY], int &width, int &height, int MAX);

void Perspective_Transformation(int bmp_r[MaxBMPSizeX][MaxBMPSizeY], int bmp_g[MaxBMPSizeX][MaxBMPSizeY],
                                int bmp_b[MaxBMPSizeX][MaxBMPSizeY], int &width, int &height);

void canny_edge_detection(int bmp_r[MaxBMPSizeX][MaxBMPSizeY], int bmp_g[MaxBMPSizeX][MaxBMPSizeY],
                          int bmp_b[MaxBMPSizeX][MaxBMPSizeY], int &width, int &height);

#endif //IMG_PROCESS_H