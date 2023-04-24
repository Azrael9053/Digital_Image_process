//
// Created by user on 2023/4/23.
//
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include<algorithm>

#include "img_process.h"

using namespace std;

extern int r[MaxBMPSizeX][MaxBMPSizeY];


void Adaptive_median_filtering(int bmp_r[MaxBMPSizeX][MaxBMPSizeY], int &width, int &height, int MAX) {
    int value[MAX * MAX];
    int min, max, med, a1, a2, b1, b2, x, y, window, i, j, cnt, flag;
    for (y = height - 1; y >= 0; y--) {
        for (x = 0; x < width; x++) {
            flag = 0;
            for (window = 3; window <= 11; window += 2) {
                cnt = 0;
                for (i = (y + (window >> 1)); i >= (y - (window >> 1)); i--) {
                    for (j = (x - (window >> 1)); j <= (x + (window >> 1)); j++) {
                        if ((i > height) or (j > width) or (i < 0) or (j < 0)) {
                            value[cnt++] = 255;
                        } else {
                            value[cnt++] = bmp_r[j][i];
                        }
                    }
                }
                sort(value, value + (window * window));
                min = value[0];
                max = value[(window * window) - 1];
                med = value[(window * window) >> 1];
                a1 = med - min;
                a2 = med - max;
                if ((a1 > 0) and (a2 < 0)) {
                    b1 = bmp_r[x][y] - min;
                    b2 = bmp_r[x][y] - max;
                    if ((b1 > 0) and (b2 < 0)) {
                        r[x][y] = bmp_r[x][y];
                    } else {
                        r[x][y] = med;
                    }
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                r[x][y] = med;
            }
        }
    }
}

void Perspective_Transformation(int bmp_r[MaxBMPSizeX][MaxBMPSizeY], int bmp_g[MaxBMPSizeX][MaxBMPSizeY],
                                int bmp_b[MaxBMPSizeX][MaxBMPSizeY], int &width, int &height) {

}