#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollar;
    int i = 0, cents = 0;
    
    do
    {
        // Prompt change
        dollar = get_float("What's the change? ");
    }
    while (dollar < 0);

    // Calculate fewest number of coins
    cents = round(dollar * 100);

    // Quarter
    while (cents >= 25)
    {
        cents = cents - 25;
        i++;
    }

    // Dime
    while (cents < 25 && cents >= 10)
    {
        cents = cents - 10;
        i++;
    }

    // Nickel
    while (cents < 10 && cents >= 5)
    {
        cents = cents - 5;
        i++;
    }

    // Penny
    while (cents < 5 && cents >= 1)
    {
        cents = cents - 1;
        i++;
    }

    // Print fewest number of coins
    printf("Total coins: %i\n", i);
}
