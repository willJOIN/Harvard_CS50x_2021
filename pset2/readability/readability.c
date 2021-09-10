#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Create function to count letters
int count_letters(string text);
// Create function to count words
int count_words(string text);
// Create function to count sentences
int count_sentences(string text);

int main(void)
{
    // Get input
    string text = get_string("Text: ");
    // Count letters
    int numberLetters = count_letters(text);
    // Count words
    float numberWords = count_words(text);
    // Count sentences
    int numberSentences = count_sentences(text);
    // Avg letters per 100 words, rule of three
    float L = numberLetters * 100 / numberWords;
    // Avg sentences per 100 words, rule of three
    float S = numberSentences * 100 / numberWords;
    // Coleman Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index <= 15 && index >= 1)
    {
        // Round function
        int grade = round(index);
        printf("Grade %i\n", grade);
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
}

// Count letters function
int count_letters(string text)
{
    int numberLetters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            numberLetters++;
        }
    }
    return numberLetters;
}

// Count words function
int count_words(string text)
{
    float numberWords = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            numberWords++;
        }
    }
    return numberWords;
}

// Count sentences function
int count_sentences(string text)
{
    int numberSentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            numberSentences++;
        }
    }
    return numberSentences;
}