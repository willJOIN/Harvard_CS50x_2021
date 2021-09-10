#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int s, e, y = 0;

    do
    {
        // Prompt start size
        s = get_int("Start size: \n");
    }
    while (s < 9);

    do
    {
        // Prompt end size
        e = get_int("End size: \n");
    }
    while (e < s);

    do
    {
        // Calculate years
        s = s + (s / 3) - (s / 4);
        y++;
    }
    while (e > s);

    // Print years
    printf("Years: %i\n", y);
}
