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

  // sobel matrix filling with image borders check
  image.get_pixel()

  for (int i=0; i<3; i++)
  {
    if (y == 0)
      for (int j=0; j<3; j++)
    	sobel_atrix[i][]
  }


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
