/*===========================================================================
  This demonstrative example is provided by the teaching assistant,
  Mr. Shih-Hung Liao (廖世宏), and modified by the instructor, Prof. Lan.

  (1) It can be compiled and executed correctly under the DEV-C++, and Visual C++
      environments.
  (2) In order to run this program, you should also have the "bmp.h" and
      "bmp.cpp" files installed in your current directory or whichever directory
      the C++ compiler is directed to search for.
  (3) The DEV-C++ is a free C++ development environment that is recommended for
      this course. Refer to http://www.bloodshed.net/dev/devcpp.html.

                             Apr. 3, 2006
============================================================================*/
#include <iostream>
#include <stdlib.h>
#include<algorithm>

#include "bmp.h"
#include "img_process.h"

using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];


int main(int argc, char *argv[]) {
    int width, height;
    int i, j;


    open_bmp("./test images/lena_pepper_and_salt_noise10%.bmp", R, R, R, width, height);
    Adaptive_median_filtering(R, width, height, 11);
    save_bmp("./test images/denoise.bmp", r, r, r);
    close_bmp();


    open_bmp("./test images/lena_std.bmp", R, G, B, width, height);
    Perspective_Transformation(R, G, B, width, height);
    save_bmp("./test images/Perspective_Transformation.bmp", r, g, b);
    close_bmp();


    open_bmp("./test images/lighthouse.bmp", R, G, B, width, height);
    canny_edge_detection(R, G, B, width, height);
    for(j = height - 1; j >= 0; j--) {
        for(i = 0; i < width; i++) {
            if(R[i][j] >= TH){
                R[i][j] = 255;
            }
            else if (R[i][j] >= TL and  R[i][j] < TH){
                for (int u = -1; u <= 1; u++) {
                    for (int v = -1; v <= 1; v++) {
                        if(i+u>0 and i+u<width and j+v>0 and j+v<height){
                            if(R[i+u][j+v] == 255){
                                R[i][j] = 255;
                            }
                        }
                    }
                }
            }
        }
    }
    for(j = height - 1; j >= 0; j--) {
        for(i = 0; i < width; i++) {
            if(R[i][j] != 255){
                R[i][j] = 0;
            }
        }
    }
    for(j = height - 1; j >= 0; j--) {
        for(i = 0; i < width; i++) {
            if(i>0 and i<width-1 and j>0 and j<height-1){
                continue;
            } else{
                R[i][j] = 0;
            }
        }
    }
    save_bmp("./test images/canny_edge.bmp", R, R, R);
    close_bmp();


    printf("Job Finished!\n");

//    system("PAUSE"); /* so that the command window holds a while */
    return 0;
}
