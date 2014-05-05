#include <stdio.h>
#include <stdlib.h>
#include "../headers/bitmap_image.hpp"

class rgb
{
  public:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

rgb sobel_operator(int x,int y, bitmap_image image)
{
  rgb sobel_matrix[3][3];
  rgb pixel;
  rgb Gx;
  rgb Gy;

  // Sobel matrix filling with image borders check
  for (int i=0; i<3; i++)
  {
    if ( ((y == 0) && (i == 0)) || ((y == (image.width()-1)) && (i==2)) ) // nullify border pixels if in the 1st row, or the lower row of the picture
    {
      for (int j=0; j<3; j++)
      {
        sobel_matrix[i][j].red = 0;
        sobel_matrix[i][j].green = 0;
        sobel_matrix[i][j].blue = 0;
      }
    }
    else
    {
      for (int j=0; j<3; j++)
      {
        if ( ((x == 0) && (j == 0)) || ((x == (image.height()-1)) && (j == 2)) ) // nullify border pixels if in the 1st or the last column
        {
          sobel_matrix[i][j].red = 0;
          sobel_matrix[i][j].green = 0;
          sobel_matrix[i][j].blue = 0;
        }
        else
        {
          image.get_pixel( (x-1+j),
                           (y-1+i),
                           sobel_matrix[i][j].red,
                           sobel_matrix[i][j].green,
                           sobel_matrix[i][j].blue );
        }
      }
    }
  }

  // Grayscale, all the values in channels are the same
  for (int i=0; i<3; i++)
	for (int j=0; j<3; j++)
	{
	  sobel_matrix[i][j].red = sobel_matrix[i][j].red * 0.3 + sobel_matrix[i][j].green * 0.59 + sobel_matrix[i][j].blue * 0.11;
	}

  // Now, we'll be working only with red channel, as in green and blue channels values are the same.
  int Gx_matrix[3][3];
  int Gy_matrix[3][3];
  // Sobel operator for X axis
  Gx_matrix[0][0] = -1; Gx_matrix[0][1] = 0; Gx_matrix[0][2] = 1;
  Gx_matrix[1][0] = -2; Gx_matrix[1][1] = 0; Gx_matrix[1][2] = 2;
  Gx_matrix[2][0] = -1; Gx_matrix[2][1] = 0; Gx_matrix[2][2] = 1;
  // Sobel operator for Y axis
  Gy_matrix[0][0] =  -1; Gy_matrix[0][1] = -2;  Gy_matrix[0][2] = -1;
  Gy_matrix[1][0] =  0;  Gy_matrix[1][1] = 0;   Gy_matrix[1][2] = 0;
  Gy_matrix[2][0] = 1;   Gy_matrix[2][1] = 2;   Gy_matrix[2][2] = 1;


  for (int i=0; i<3; i++)
  	for (int j=0; j<3; j++)
  	{
  	  Gx_matrix[i][j] = Gx_matrix[i][j] * sobel_matrix[i][j].red;
  	  Gy_matrix[i][j] = Gy_matrix[i][j] * sobel_matrix[i][j].red;
  	}

  int Gx_red = 0;
  int Gy_red = 0;
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
    {
      Gx_red = Gx_red + Gx_matrix[i][j];
      Gy_red = Gy_red + Gy_matrix[i][j];
    }
  double result = sqrt(pow(Gx_red,2) + pow(Gy_red,2));

  if (result > 255)
	result = 255;
  if (result < 0)
	result = 0;

  pixel.red = (unsigned char)result;
  pixel.green = pixel.red;
  pixel.blue = pixel.red;

  return pixel;
}

int main(void)
{
  rgb pixel;
  bitmap_image image("lena.bmp");
  if (!image)
    {
      printf("Error - Failed to open lena.bmp \n");
      return 1;
    }

  bitmap_image result(image.height(),image.width());

  for (int y=0; y < image.width(); y++)
    for (int x=0; x < image.height(); x++)
      {
        pixel = sobel_operator(x, y, image);
        result.set_pixel(x, y, pixel.red, pixel.green, pixel.blue);
        printf("X and Y %d : %d \n", x, y);
      }

  result.save_image("sobel.bmp");
  return 0;
}
