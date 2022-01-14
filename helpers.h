#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

int average (int r,int g, int b);

void ConvertSepia (BYTE *red,BYTE *green,BYTE *blue);

void blurAverage (int max, RGBTRIPLE *imagens[max]);

int blurCheckCondition(int i, int j, int height, int width);