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
  sobel_matrix = new struct rgb[3][3];
  pixel = new struct rgb;

  // sobel matrix filling with image borders check
  for (int i=0; i<3; i++)
  {
      if ( ((y == 0) && (i == 0)) || ((y == (image.width()-1)) && (i==2)) ) // nullify border pixels if in the 1st row, or the lower row of the picture
        for (int j=0; j<3; j++)
        {
          sobel_matrix[i][j].red = 0;
          sobel_matrix[i][j].green = 0;
          sobel_matrix[i][j].blue = 0;
        }
      else
        for (int j=0; j<3; j++)
        {
          if ( ((x == 0) && (j == 0)) || ((x == (image.height()-1)) && (j == 2)) ) // nulify border pixels if in the 1st or the last column
          {
            sobel_matrix[i][j].red = 0;
            sobel_matrix[i][j].green = 0;
            sobel_matrix[i][j].blue = 0;
          }
          else
          {
            image.get_pixel( (x-1+j),
                             (y-1+i),
                             &(sobel_matrix[i][j].red),
                             &(sobel_matrix[i][j].green),
                             &(sobel_matrix[i][j].blue) );
          }
        }
  }

  //...work with formed sobel's matrix..

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
