#include "helpers.h"
#include <stdio.h>
static const int rgb = 3;
int average (int r,int g, int b){

    int a;

    return a = (r + g+ b)/rgb;
}
int blurCheckCondition(int i, int j, int height, int width){
    if(i == 0 && j == 0){ 
        return 1;
    }
    if(i == 0 && j == width - 1 ){ 
       return 2;  
        
    }
    if(i == height - 1 && j == 0){ 
        return 3;
    }
    if(i == height - 1 && j == width - 1 ){ 
        return 4;
    }
    if(i == 0 ){ 
        return 5;
    }
    if(j == 0){ 
        return 6;
    }
    
    if(i == height - 1 || j == width - 1 ){
        return 7; 
    }
    return 8; 
}
void blurAverage(int max, RGBTRIPLE *imagens[max])
{
    int RGB[] = {0,0,0};

   for(int i = 0; i < max; i++){
       for(int j = 0; j < rgb; j++){
           switch(j){
               case 0:
               RGB[j] += imagens[i]->rgbtRed;
               break;
               case 1:
               RGB[j] += imagens[i]->rgbtGreen;
               break;
               case 2:
               RGB[j] += imagens[i]->rgbtBlue;
               break;
           }
       }

   }
    for(int i = 0; i < rgb; i++){
     RGB[i] = RGB[i] / max;
    }

    imagens[0]->rgbtRed   = RGB[0];
    imagens[0]->rgbtGreen = RGB[1];
    imagens[0]->rgbtBlue  = RGB[2];
}

void ConvertSepia (BYTE *red,BYTE *green,BYTE *blue){

    BYTE *RGB[]={red,green,blue};
    int intColor[]       = {*red,*green,*blue};
    int sepiaColor[]     = {0,0,0};
    double nConvert[3][3] = {{0.393,0.769,0.189},
                                 {0.349,0.686,0.168},
                                 {0.272,0.534,0.131}};

    for(int i = 0; i < rgb; i++){
        for(int j = 0; j < rgb; j++){
            sepiaColor[i] += intColor[j] * nConvert[i][j];

        }
        if(sepiaColor[i] >= 255){
            sepiaColor[i] = 255;
        }
        if(sepiaColor[i] < 0){
            sepiaColor[i] = 0;
        }

    }
    for(int i = 0; i < rgb; i++){
     *RGB[i] = sepiaColor[i];
    }

}


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for(int i = 0; i < height ; i++){
        for(int j = 0; j < width ; j++){
            BYTE *red    = &image[i][j].rgbtRed;
            BYTE *green  = &image[i][j].rgbtGreen;
            BYTE *blue   = &image[i][j].rgbtBlue;
           int scale     = average(*red,*green,*blue);
           *red = *green = *blue = scale;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height ; i++){
        for(int j = 0; j < width ; j++){
             BYTE *red   = &image[i][j].rgbtRed;
             BYTE *green = &image[i][j].rgbtGreen;
             BYTE *blue  = &image[i][j].rgbtBlue;

            ConvertSepia (red,green,blue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int w;
     for(int i = 0; i < height ; i++){
        w =  width - 1;
        for(int j = 0; j < width/2 ; j++,w--){
             BYTE *red       = &image[i][j].rgbtRed;
             BYTE *green     = &image[i][j].rgbtGreen;
             BYTE *blue      = &image[i][j].rgbtBlue;
             BYTE *color[]   = {red,green,blue};
             BYTE *red2      = &image[i][w].rgbtRed;
             BYTE *green2    = &image[i][w].rgbtGreen;
             BYTE *blue2     = &image[i][w].rgbtBlue;
             BYTE *color2[]  = {red2,green2, blue2};
             BYTE aux[]      = {*red,*green,*blue};

             for(int c = 0; c < rgb; c++){
                 *color[c]  = *color2[c];
                 *color2[c] = aux[c];

             }
        }
     }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int t = 0;
    int max;
    RGBTRIPLE *imagens[9];
    for(int i = 0; i < height ; i++){
        for(int j = 0; j < width ; j++){
            max = blurCheckCondition( i, j, height , width) ;
            switch(max){
                case 1:
                    imagens[0] = &image[i]    [j];
                    imagens[1] = &image[i]    [j + 1];
                    imagens[2] = &image[i + 1][j + 1];
                    imagens[3] = &image[i + 1][j];
                    max = 4;
                break;
                case 2:
                    imagens[0] = &image[i]    [j - 1];
                    imagens[1] = &image[i]    [j];
                    imagens[2] = &image[i + 1][j -1];
                    imagens[3] = &image[i + 1][j];
                    max = 4;
                break;
                case 3:
                    imagens[0] = &image[i- 1] [j];
                    imagens[1] = &image[i - 1][j + 1];
                    imagens[2] = &image[i]    [j];
                    imagens[3] = &image[i]    [j + 1];
                    max = 4;
                break;
                case 4:
                    imagens[0] = &image[i-1][j-1];
                    imagens[1] = &image[i-1][j];
                    imagens[2] = &image[i]  [j - 1];
                    imagens[3] = &image[i]  [j];
                    max = 4;
                break;
                case 5:
                    imagens[0] = &image[i]    [j-1];
                    imagens[1] = &image[i]    [j];
                    imagens[2] = &image[i]    [j + 1];
                    imagens[3] = &image[i + 1][j + 1];
                    imagens[4] = &image[i + 1][j];
                    imagens[5] = &image[i + 1][j - 1];
                    max = 6;
                break;
                case 6:
                    imagens[0] = &image[i - 1][j];
                    imagens[1] = &image[i - 1][j + 1];
                    imagens[2] = &image[i]    [j];
                    imagens[3] = &image[i]    [j + 1];
                    imagens[4] = &image[i + 1][j];
                    imagens[5] = &image[i+ 1] [j + 1];
                    max = 6;
                break;
                case 7:
                    imagens[0] = &image[i - 1][j - 1];
                    imagens[1] = &image[i - 1][j];
                    imagens[2] = &image[i][j - 1];
                    imagens[3] = &image[i - 1][j + 1];
                    imagens[4] = &image[i]    [j];
                    imagens[5] = &image[i]    [j + 1];
                    max = 6;
                break;
                case 8:
                    imagens[0] = &image[i -1] [j-1];
                    imagens[1] = &image[i-1]  [j];
                    imagens[2] = &image[i-1]  [j + 1];
                    imagens[3] = &image[i]    [j - 1];
                    imagens[4] = &image[i]    [j];
                    imagens[5] = &image[i]    [j + 1];
                    imagens[6] = &image[i + 1][j - 1];
                    imagens[7] = &image[i + 1][j];
                    imagens[8] = &image[i + 1][j + 1];
                    max = 9;
                break;
               
            }
            blurAverage(max, imagens);
        }
    }
    return;
}
