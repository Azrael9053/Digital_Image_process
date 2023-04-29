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

double Gradient_Angle[512][512] = {0};
int max_gradient = 0;

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

void gray_scale(int bmp_r[MaxBMPSizeX][MaxBMPSizeY], int bmp_g[MaxBMPSizeX][MaxBMPSizeY],
                int bmp_b[MaxBMPSizeX][MaxBMPSizeY], int &width, int &height) {
    int i, j;
    for (j = height - 1; j >= 0; j--) {
        for (i = 0; i < width; i++) {
            r[i][j] = (bmp_r[i][j] * 0.299 + bmp_g[i][j] * 0.587 + bmp_b[i][j] * 0.114);
        }
    }
}

void Gaussian_LPF(int bmp_r[MaxBMPSizeX][MaxBMPSizeY], int &width, int &height, double sigma, int MAX) {
    int i, j, x, y, u, v;
    double sum = 0;
    double filter[MAX][MAX];

    for (i = 0; i < MAX; i++) {
        x = -((MAX) >> 1) + i;
        for (j = 0; j < MAX; j++) {
            y = -((MAX) >> 1) + j;
            filter[i][j] = exp(-(x * x + y * y) / (2 * sigma * sigma));
            sum += filter[i][j];
        }
    }
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            filter[i][j] /= sum;
        }
    }
    for (j = height - 1; j >= 0; j--) {
        for (i = 0; i < width; i++) {
            sum = 0;
            for (y = j + (MAX >> 1); y >= j - (MAX >> 1); y--) {
                for (x = i - (MAX >> 1); x <= i + (MAX >> 1); x++) {
                    if (x >= 0 and x < width and y >= 0 and y < height) {
                        sum += bmp_r[x][y] * filter[x - i + (MAX >> 1)][y - j - (MAX >> 1)];
                    } else {
                        sum += bmp_r[i][j] * filter[x - i + (MAX >> 1)][y - j - (MAX >> 1)];
                    }
                }
            }
            R[i][j] = sum;
        }
    }
}

void sobel(int bmp_r[MaxBMPSizeX][MaxBMPSizeY], int &width, int &height) {
    const double Sobel_mask[2][3][3] = {{{-1, 0,  1},  {-2, 0, 2}, {-1, 0, 1}},
                                        {{-1, -2, -1}, {0,  0, 0}, {1,  2, 1}}};
    int i, j, x, y, u, v;

    for (j = height - 1; j >= 0; j--) {
        for (i = 0; i < width; i++) {
            x = 0;
            y = 0;
            for (v = -1; v <= 1; v++) {
                for (u = -1; u <= 1; u++) {
                    if (i + u >= 0 and i + u < width and j + v >= 0 and j + v < height) {
                        x += bmp_r[i + u][j + v] * Sobel_mask[0][u + 1][v + 1];
                        y += bmp_r[i + u][j + v] * Sobel_mask[1][u + 1][v + 1];
                    }
                }
            }
            r[i][j] = abs(x) + abs(y);
            if (max_gradient < r[i][j]) {
                max_gradient = r[i][j];
            }
            Gradient_Angle[i][j] = atan2(x, y) * 180.0 / M_PI;
            Gradient_Angle[i][j] += 180.0 * (Gradient_Angle[i][j] < 0);
        }
    }
}

void Non_maximum_suppression(int bmp_r[MaxBMPSizeX][MaxBMPSizeY], int &width, int &height) {
    int i, j, x, y;
    double nearpoint[2];
    for(i = 0; i < width; i++) {
        for(j = 0; j < height; j++) {
            R[i][j] = bmp_r[i][j];
        }
    }
    for (j = height - 1; j >= 0; j--) {
        for(i = 0; i < width; i++) {
            if(bmp_r[i][j] > 0){
                if(Gradient_Angle[i][j] < 22.5 or Gradient_Angle[i][j] > 157.5){
                    if(i-1>0){
                        nearpoint[0] = bmp_r[i-1][j];
                    } else{
                        nearpoint[0] = -1;
                    }
                    if(i+1<width){
                        nearpoint[1] = bmp_r[i+1][j];
                    } else{
                        nearpoint[1] = -1;
                    }
                }
                else if(Gradient_Angle[i][j] < 67.5 and Gradient_Angle[i][j] >= 22.5){
                    if(i-1>0 and j-1>0){
                        nearpoint[0] = bmp_r[i-1][j-1];
                    } else{
                        nearpoint[0] = -1;
                    }
                    if(i+1<width and j+1<height){
                        nearpoint[1] = bmp_r[i+1][j+1];
                    } else{
                        nearpoint[1] = -1;
                    }
                }
                else if(Gradient_Angle[i][j] < 112.5 and Gradient_Angle[i][j] >= 67.5){
                    if(j-1>0){
                        nearpoint[0] = bmp_r[i][j-1];
                    } else{
                        nearpoint[0] = -1;
                    }
                    if(j+1<height){
                        nearpoint[1] = bmp_r[i][j+1];
                    } else{
                        nearpoint[1] = -1;
                    }
                }
                else if(Gradient_Angle[i][j] < 157.5 and Gradient_Angle[i][j] >= 112.5){
                    if(i-1>0 and j+1<height){
                        nearpoint[0] = bmp_r[i-1][j+1];
                    } else{
                        nearpoint[0] = -1;
                    }
                    if(i+1<width and j-1>0){
                        nearpoint[1] = bmp_r[i+1][j-1];
                    } else{
                        nearpoint[1] = -1;
                    }
                }
                if(bmp_r[i][j] < nearpoint[0] or bmp_r[i][j] < nearpoint[1]){
                    R[i][j] = 0;
                }
            }
        }
    }
}

void canny_edge_detection(int bmp_r[MaxBMPSizeX][MaxBMPSizeY], int bmp_g[MaxBMPSizeX][MaxBMPSizeY],
                          int bmp_b[MaxBMPSizeX][MaxBMPSizeY], int &width, int &height) {

    gray_scale(bmp_r, bmp_g, bmp_b, width, height);
    Gaussian_LPF(r, width, height, 1.5, 3);
    sobel(R, width, height);
    Non_maximum_suppression(r, width, height);

}