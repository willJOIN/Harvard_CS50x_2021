#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Command line: argc = int number of words, argv = string array of words
int main(int argc, string argv[])
{
    // if number of words different than 2
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        // Return 1 = return exit code error
        return 1;
    }
    else
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            // argv[0] = ./caesar, argv[1] = second word, argv[1][i] = each character of second word, argv[1][i] > 0 = positive
            if (isdigit(argv[1][i]) && argv[1][i] > 0)
            {
                // Cast string argv[1] to int and assign to key
                int key = atoi(argv[1]);
                string plaintext = get_string("plaintext: ");
                // Call function
                string ciphertext = plaintext;
                for (int j = 0, m = strlen(plaintext); j < m; j++)
                {
                    if (isalpha(plaintext[j]))
                    {
                        if (isupper(plaintext[j]))
                        {
                            ciphertext[j] = (plaintext[j] - 'A' + key) % 26;
                            ciphertext[j] += 'A';
                        }
                        else if (islower(plaintext[j]))
                        {
                            ciphertext[j] = (plaintext[j] - 'a' + key) % 26;
                            ciphertext[j] += 'a';
                        }
                    }
                }
                printf("ciphertext: %s\n", ciphertext);
                // Return 0 = no error
                return 0;
            }
            else
            {
                printf("Usage: ./caesar key\n");
                // Return 1 = return exit code error
                return 1;
            }
        }
    }
}

