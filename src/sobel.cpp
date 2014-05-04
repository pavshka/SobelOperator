/* *
 * Copyright 1993-2012 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 */
#include <stdio.h>
#include <stdlib.h>
#include "bitmap_image.hpp"

struct rgb
{
  char red;
  char green;
  char blue;
};

struct rgb sobel_operator(int x, int y, bitmap_image image)
{
  pixel = new struct rgb;
  sobel_matrix = new int[3][3];

  // image borders check
  if (x == 0)
	for (int i=0; i<3; i++)
;


  return pixel;
}

int main(void)
{
	pixel = new struct rgb;
    bitmap_image image("lena.bmp");
    if (!image)
	  {
	    printf("Error - Failed to open lena.bmp \n");
	    return 1;
	  }

	for (int y=0; y < image.width(); y++)
      for (x=0; x < image.height(); x++)
	    {
    	  pixel = sobel_operator(x, y, image);
	      image.set_pixel(x, y, pixel.red, pixel.green, pixel.blue);
		}

	image.save_image("sobelized.bmp");
	return 0;
}
