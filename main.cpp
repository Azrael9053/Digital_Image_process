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

    open_bmp("./test images/lena_pepper_and_salt_noise10%.bmp", R, R, R, width, height); // for gray images
    Adaptive_median_filtering(R, width, height, 11);
    save_bmp("./test images/denoise.bmp", r, r, r); // for gray images

    open_bmp("./test images/lena_std.bmp", R, G, B, width, height); // for gray images
    Perspective_Transformation(R, G, B, width, height);
    save_bmp("./test images/Perspective_Transformation.bmp", r, g, b); // for gray images

    printf("Job Finished!\n");

    // 關閉 bmp 影像圖檔
    close_bmp();

//    system("PAUSE"); /* so that the command window holds a while */
    return 0;
}
