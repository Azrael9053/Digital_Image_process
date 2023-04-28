//
// Created by user on 2023/4/23.
//
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include<algorithm>

#include "img_process.h"
#include "matrix_calculate.h"

using namespace std;


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
    int i, j, u, v, x, y;
    double H[ROW][COL] = {0};
    double H_inv[ROW][COL];
    double p_uv[COL];
    double p_xy[COL];

    for (j = height - 1; j >= 0; j--) {
        for (i = 0; i < width; i++) {
            r[i][j] = 0;
            g[i][j] = 0;
            b[i][j] = 0;
        }
    }

    for (v = height - 1; v >= 0; v--) {
        for (u = 0; u < width; u++) {
            H[0][0] = a0 - g0 * u;
            H[0][1] = b0 - h0 * u;
            H[0][2] = c0;
            H[1][0] = d0 - g0 * v;
            H[1][1] = e0 - h0 * v;
            H[1][2] = f0;
            H[2][2] = 1;
            p_uv[0] = u;
            p_uv[1] = v;
            p_uv[2] = 1;
            if (!inverse(H, H_inv)) {
                cout << "inverse failed" << endl;
                return;
            }
            for (i = 0; i < 3; i++) {
                p_xy[i] = 0;
            }
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    p_xy[i] += H_inv[i][j] * p_uv[j];
                }
            }
            x = p_xy[0];
            y = p_xy[1];
            if (x >= 0 && x < width && y >= 0 && y < height) {
                r[u][v] = bmp_r[x][y];
                g[u][v] = bmp_g[x][y];
                b[u][v] = bmp_b[x][y];
            }
        }
    }
}