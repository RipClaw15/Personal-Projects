#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            avg = roundf((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            sepiaRed = roundf(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if(sepiaRed > 255) sepiaRed = 255;
            sepiaGreen = roundf(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if(sepiaGreen > 255) sepiaGreen = 255;
            sepiaBlue = roundf(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if(sepiaBlue > 255) sepiaBlue = 255;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int a;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width / 2 ; j++)
        {

            a = image[i][j].rgbtRed; image[i][j].rgbtRed = image[i][width - (j + 1)].rgbtRed; image[i][width - (j + 1)].rgbtRed = a;
            a = image[i][j].rgbtGreen; image[i][j].rgbtGreen = image[i][width - (j + 1)].rgbtGreen; image[i][width - (j + 1)].rgbtGreen = a;
            a = image[i][j].rgbtBlue; image[i][j].rgbtBlue = image[i][width - (j + 1)].rgbtBlue; image[i][width - (j + 1)].rgbtBlue = a;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;

        }
    }
    float avg;




    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(i == 0 && j == 0)
            {
            avg = roundf((copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed) / 4.0);
            image[i][j].rgbtRed = avg;
            avg = roundf((copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen  + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 4.0);
            image[i][j].rgbtGreen = avg;
            avg = roundf((copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 4.0);
            image[i][j].rgbtBlue = avg;
            }
            else if(i == 0 && j == width - 1)
            {
            avg = roundf((copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed) / 4.0);
            image[i][j].rgbtRed = avg;
            avg = roundf((copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen  + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen) / 4.0);
            image[i][j].rgbtGreen = avg;
            avg = roundf((copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue) / 4.0);
            image[i][j].rgbtBlue = avg;
            }
            else if(i == height - 1 && j == 0)
            {
            avg = roundf((copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed) / 4.0);
            image[i][j].rgbtRed = avg;
            avg = roundf((copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen  + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen) / 4.0);
            image[i][j].rgbtGreen = avg;
            avg = roundf((copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue) / 4.0);
            image[i][j].rgbtBlue = avg;
            }
            else if(i == height - 1 && j == width - 1)
            {
            avg = roundf((copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j].rgbtRed) / 4.0);
            image[i][j].rgbtRed = avg;
            avg = roundf((copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen  + copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen) / 4.0);
            image[i][j].rgbtGreen = avg;
            avg = roundf((copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue) / 4.0);
            image[i][j].rgbtBlue = avg;
            }
            else if(i == 0)
            {
            avg = roundf((copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed) / 6.0);
            image[i][j].rgbtRed = avg;
            avg = roundf((copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen  + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 6.0);
            image[i][j].rgbtGreen = avg;
            avg = roundf((copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 6.0);
            image[i][j].rgbtBlue = avg;
            }

            else if(j == 0)
            {
            avg = roundf((copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed) / 6.0);
            image[i][j].rgbtRed = avg;
            avg = roundf((copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j].rgbtGreen  + copy[i][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 6.0);
            image[i][j].rgbtGreen = avg;
            avg = roundf((copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 6.0);
            image[i][j].rgbtBlue = avg;
            }

            else if(i == height - 1)
            {
            avg = roundf((copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed) / 6.0);
            image[i][j].rgbtRed = avg;
            avg = roundf((copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen  + copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen) / 6.0);
            image[i][j].rgbtGreen = avg;
            avg = roundf((copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue) / 6.0);
            image[i][j].rgbtBlue = avg;
            }

            else if(j == width - 1)
            {
            avg = roundf((copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed) / 6.0);
            image[i][j].rgbtRed = avg;
            avg = roundf((copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i][j-1].rgbtGreen  + copy[i][j].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen) / 6.0);
            image[i][j].rgbtGreen = avg;
            avg = roundf((copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue) / 6.0);
            image[i][j].rgbtBlue = avg;
            }

            else

            {
            avg = roundf((copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed) / 9.0);
            image[i][j].rgbtRed = avg;
            avg = roundf((copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 9.0);
            image[i][j].rgbtGreen = avg;
            avg = roundf((copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 9.0);
            image[i][j].rgbtBlue = avg;
            }
        }
    }

    return;
}
