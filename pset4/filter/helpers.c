#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 3.0 because is a float
            average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed = 0;
    int sepiaGreen = 0;
    int sepiaBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            // Operator ?; that can short if else statements, if greater than 255 cap at 255 and assign to sepiaBlue, (CONDITION) ? (TRUE) : (FALSE);
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        int currentPosition = 0;
        // Reading backwards
        for (int j = width - 1; j >= 0; j--, currentPosition++)
        {
            // Temporary buffer to modify a copy of the matrix
            temp[i][currentPosition] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Assigning buffer to final image
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int rows = 0; rows < height; rows++)
    {
        for (int columns = 0; columns < width; columns++)
        {
            int count = 0;
            // Row coords array
            int rowsCoords[] = {rows - 1, rows, rows + 1};
            // Column coords array
            int columnsCoords[] = {columns - 1, columns, columns + 1};
            float totalRed = 0;
            float totalGreen = 0;
            float totalBlue = 0;
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    // Rows
                    int currentRows = rowsCoords[r];
                    // Columns
                    int currentColumns = columnsCoords[c];
                    // 3x3, including center
                    if (currentRows >= 0 && currentRows < height && currentColumns >= 0 && currentColumns < width)
                    {
                        RGBTRIPLE pixel = image[currentRows][currentColumns];
                        totalRed += pixel.rgbtRed;
                        totalGreen += pixel.rgbtGreen;
                        totalBlue += pixel.rgbtBlue;
                        count++;
                    }
                }
            }
            // Updating RGB values
            temp[rows][columns].rgbtRed = round(totalRed / count);
            temp[rows][columns].rgbtGreen = round(totalGreen / count);
            temp[rows][columns].rgbtBlue = round(totalBlue / count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // New pixel is average from old pixels that were on 3x3, including center
            image[i][j] = temp[i][j];
        }
    }
    return;
}
