// Implements a dictionary's functionality
#include <stdbool.h>
#include "dictionary.h"
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int word_count = 0;

// Number of buckets in hash table
const unsigned int N = 100000; //(LENGTH * 'z');

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain a hash value
    int index = hash(word);
    // Access linked list at that index in the hash table
    node *cursor = table[index];
    // Traverse linked list
    while (cursor != NULL)
    {
        // Check if is in the dictionary
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // Cursor goes to next word
        cursor = cursor->next;
    }
    // Not on dictionary
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned int hash = 5381;
    int c;
    while ((c = *word++))
    {
        c = tolower(c);
        // hash * 33 + c
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Try to open dictionary file
    FILE *file = fopen(dictionary, "r");
    // Fail to open dictionary file
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH];
    // Read strings from dictionary one at a time
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node
        node *node_1 = malloc(sizeof(node));
        if (node_1 == NULL)
        {
            return false;
        }
        // Copy word into node
        strcpy(node_1->word, word);
        // Set to null for now
        node_1->next = NULL;
        // Hash word to obtain a hash value
        int cursor = hash(word);
        // Insert node into hash table at that location
        if (table[cursor] == NULL)
        {
            table[cursor] = node_1;
        }
        else
        {
            node_1->next = table[cursor];
            table[cursor] = node_1;
        }
        word_count++;
    }
    // Close the file
    fclose(file);
    // If EOF
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
