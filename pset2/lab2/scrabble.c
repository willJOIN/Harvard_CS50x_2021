#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Create Function
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
    printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
    printf("Player 2 wins!\n");
    }
    else
    {
    printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Compute and return score for string, non letters = 0 points, case insentive
    // string POINTS[word[i]] "A" = "0", value "1" to "A"; "B" = "1", value "3" to "B"
    //Stores score
    int score = 0;

    // i = each character of a word, n = stores length of characters of a word, loop happens while each character is smaller than a word, and keeps increasing by 1
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isupper(word[i]))
        {
            // "A" ASCII = "65", "65-65" = "0"; "B" ASCII = "66", "66-65" = "1"; Each character has a ASCII decimal value of + "65"; += adds and assigns right operand to left; "A" instead of "65" is cleaner
            score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            // "a" ASCI = "97", "97-97" = "0"; "b" ASCII = "98", "98-97" = "1"; No "else" because else in this case, would deal with non letter values.
            score += POINTS[word[i] - 'a'];
        }
    }
    // Functions need to return a value
    return score;
}
