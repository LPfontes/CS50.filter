#include "helpers.h"


int average (int r,int g, int b){
    int a;
    
    return a = (r + g+ b)/3;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height ; i++){
        for(int j = 0; j < width ; j++){
            BYTE *red = &image[i][j].rgbtRed;
            BYTE *green= &image[i][j].rgbtGreen;
            BYTE *blue = &image[i][j].rgbtBlue;
           int scale = average(*red,*green,*blue);
           *red = *green = *blue = scale;
           
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
