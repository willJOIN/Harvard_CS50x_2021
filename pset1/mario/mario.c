#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;

    do
    {
        // Prompt height
        h = get_int("Height: ");
    }

    // || = or, && = and
    while (h < 1 || h > 8);

    // Outer loop = rows
    for (int i = 0; i < h; i++)
    {
        // Inner loop = columns
        for (int j = 0; j < h; j++)
        {
            // Pattern
            if (i + j < h - 1)
                printf(" ");
            else
                printf("#");
        }
    printf("\n");
    }
}
