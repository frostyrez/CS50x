#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int Gx[3][3];
    int Gy[3][3];
}
kern;

//////////////////////////
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    int* ptr;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // printf("Blue: %i Green: %i Red: %i\n",image[i][j].rgbtBlue,image[i][j].rgbtGreen,image[i][j].rgbtRed);
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3);

        // OPTION 2
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;

            // printf("Blue: %i Green: %i Red: %i\n",image[i][j].rgbtBlue,image[i][j].rgbtGreen,image[i][j].rgbtRed);
        }
    }
    return;
}

//////////////////////////
// Reflect image horizontally
void swap(RGBTRIPLE *a, RGBTRIPLE *b);

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < round(width/2); j++)
        {
            swap(&image[i][j],&image[i][width-j]);
        }
    }
    return;
}

//////////////////////////
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // printf("\n");
    int ii_limit[2] = {0,0};
    int jj_limit[2] = {0,0};
    int rnd = 0;
    RGBCOUNTER temp_pixel = {0,0,0};
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each pixel of each row
        for (int j = 0; j < width; j++)
        {
            // Set ii limits
            if (i == 0)
            {
                ii_limit[0] = 0;
                ii_limit[1] = 2;
            }
            else if (i == height - 1)
            {
                ii_limit[0] = -1;
                ii_limit[1] = 1;
            }
            else
            {
                ii_limit[0] = -1;
                ii_limit[1] = 2;
            }
            // Set jj limits
            if (j == 0)
            {
                jj_limit[0] = 0;
                jj_limit[1] = 2;
            }
            else if (j == width - 1)
            {
                jj_limit[0] = -1;
                jj_limit[1] = 1;
            }
            else
            {
                jj_limit[0] = -1;
                jj_limit[1] = 2;
            }
            rnd = (ii_limit[1]-ii_limit[0])*(jj_limit[1]-jj_limit[0]);
            // For each row around that pixel
            for (int ii = ii_limit[0]; ii < ii_limit[1]; ii++)
            {
                // For each pixel within that row
                for (int jj = jj_limit[0]; jj < jj_limit[1]; jj++)
                {
                    temp_pixel.rgbtBlue = temp_pixel.rgbtBlue + image[i+ii][j+jj].rgbtBlue;
                    temp_pixel.rgbtGreen = temp_pixel.rgbtGreen + image[i+ii][j+jj].rgbtGreen;
                    temp_pixel.rgbtRed = temp_pixel.rgbtRed + image[i+ii][j+jj].rgbtRed;
                }
            }
            image[i][j].rgbtBlue = round(temp_pixel.rgbtBlue/rnd);
            image[i][j].rgbtGreen = round(temp_pixel.rgbtGreen/rnd);
            image[i][j].rgbtRed = round(temp_pixel.rgbtRed/rnd);
            temp_pixel.rgbtBlue = 0;
            temp_pixel.rgbtGreen = 0;
            temp_pixel.rgbtRed = 0;
        }
    }
    return;
}

//////////////////////////
// Detect edges
kern make_kernels(void);
int capnrnd(int Gx, int Gy);

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    kern kernel = make_kernels();
    RGBCOUNTER temp_Gx = {0,0,0};
    RGBCOUNTER temp_Gy = {0,0,0};
    int ii_limit[2] = {0,0};
    int jj_limit[2] = {0,0};

    // For each row
    for (int i = 0; i < height; i++) {
        // For each pixel of each row
        for (int j = 0; j < width; j++) {
            // printf("Pixel at %i,%i has blue value of %i\n",i,j,image[i][j].rgbtBlue);
            // Set ii limits
            if (i == 0)
            {
                ii_limit[0] = 0;
                ii_limit[1] = 2;
            }
            else if (i == height - 1)
            {
                ii_limit[0] = -1;
                ii_limit[1] = 1;
            }
            else
            {
                ii_limit[0] = -1;
                ii_limit[1] = 2;
            }
            // Set jj limits
            if (j == 0)
            {
                jj_limit[0] = 0;
                jj_limit[1] = 2;
            }
            else if (j == width - 1)
            {
                jj_limit[0] = -1;
                jj_limit[1] = 1;
            }
            else
            {
                jj_limit[0] = -1;
                jj_limit[1] = 2;
            }
            // For each row around that pixel
            for (int ii = ii_limit[0]; ii < ii_limit[1]; ii++) {
                // For each pixel within that row
                for (int jj = jj_limit[0]; jj < jj_limit[1]; jj++) {
                    // printf("temp_Gx.Blue = %i\n",temp_Gx.rgbtBlue);
                    // printf("ii = %i, jj = %i\n",ii,jj);
                    // Print kernel
                    // for (int k1 = 0; k1 < 3; k1++) {
                    //     printf("%i %i %i\n",kernel.Gx[k1][0],kernel.Gx[k1][1],kernel.Gx[k1][2]);
                    // }
                    // printf("Equation about to be done: %i = %i + %i * %i\n",temp_Gx.rgbtBlue,temp_Gx.rgbtBlue,kernel.Gx[ii+1][jj+1],image[i+ii][j+jj].rgbtBlue);
                    temp_Gx.rgbtBlue = temp_Gx.rgbtBlue + kernel.Gx[ii+1][jj+1]*image[i+ii][j+jj].rgbtBlue;
                    // printf("temp_Gx.Blue = %i after ii = %i and jj = %i\n",temp_Gx.rgbtBlue,ii,jj);
                    temp_Gx.rgbtGreen = temp_Gx.rgbtGreen + kernel.Gx[ii+1][jj+1]*image[i+ii][j+jj].rgbtGreen;
                    temp_Gx.rgbtRed = temp_Gx.rgbtRed + kernel.Gx[ii+1][jj+1]*image[i+ii][j+jj].rgbtRed;
                    temp_Gy.rgbtBlue = temp_Gy.rgbtBlue + kernel.Gy[ii+1][jj+1]*image[i+ii][j+jj].rgbtBlue;
                    temp_Gy.rgbtGreen = temp_Gy.rgbtGreen + kernel.Gy[ii+1][jj+1]*image[i+ii][j+jj].rgbtGreen;
                    temp_Gy.rgbtRed = temp_Gy.rgbtRed + kernel.Gy[ii+1][jj+1]*image[i+ii][j+jj].rgbtRed;
                }
            }
            // printf("Pixel %i %i blue value is %i\n",i,j,image[i][j].rgbtBlue);
            image[i][j].rgbtBlue = capnrnd(temp_Gx.rgbtBlue,temp_Gy.rgbtBlue);
            image[i][j].rgbtGreen = capnrnd(temp_Gx.rgbtGreen,temp_Gy.rgbtGreen);
            image[i][j].rgbtRed = capnrnd(temp_Gx.rgbtRed,temp_Gy.rgbtRed);
            // printf("New pixel %i %i blue value is %i\n",i,j,image[i][j].rgbtBlue);
            temp_Gx.rgbtBlue = 0;
            temp_Gx.rgbtGreen = 0;
            temp_Gx.rgbtRed = 0;
            temp_Gy.rgbtBlue = 0;
            temp_Gy.rgbtGreen = 0;
            temp_Gy.rgbtRed = 0;
            }
    }
    // printf("Pixel 2,2 now has blue value of %i\n",image[2][2].rgbtBlue);
    return;
}

//////////////////////////

void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp_pixel = *a;
    *a = *b;
    *b = temp_pixel;
}

kern make_kernels(void)
{
    kern kernel;
    for (int j = -1; j < 2; j++) {
        kernel.Gx[0][j+1] = j;
        kernel.Gx[1][j+1] = 2*j;
        kernel.Gx[2][j+1] = j;
    }
    for (int i = -1; i < 2; i++) {
        kernel.Gy[i+1][0] = i;
        kernel.Gy[i+1][1] = 2*i;
        kernel.Gy[i+1][2] = i;
    }
    return kernel;
}

int capnrnd(int Gx, int Gy)
{
    // printf("Gx = %i, Gy = %i, ",Gx,Gy);
    int rounded = round(sqrt(Gx*Gx + Gy*Gy));
    if (rounded > 255) {
        rounded = 255;
        //printf("Pixel rounded!\n");
    }
    return rounded;
}