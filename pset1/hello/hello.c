#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt user
    string name = get_string("What's your name? \n");
    // Print
    printf("Hello, %s\n", name);
}
