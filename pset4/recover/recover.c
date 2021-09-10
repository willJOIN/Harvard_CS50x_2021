#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // Try to open file
    FILE *file = fopen(argv[1], "r");
    // Fail to open file
    if (file == NULL)
    {
        printf("Couldn't open the file.\n");
        return 1;
    }
    // Create new type to store a byte of data
    typedef uint8_t BYTE;
    // Number of bytes in JPEG files
    const int JPEG_SIZE = 512;
    BYTE buffer[JPEG_SIZE];
    size_t bytes_read;
    FILE *current_file;
    char current_filename[100];
    int currentfile_count = 0;
    bool imageFound = false;
    bool imageCount = false;
    while (true)
    {
        // Search 512 byte blocks
        bytes_read = fread(buffer, sizeof(BYTE), JPEG_SIZE, file);
        if (bytes_read == 0)
        {
            break;
        }
        // If a 512 byte block contains 4 starting JPEG bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Found JPEG
            imageFound = true;
            // If isn't first JPEG
            if (!imageCount)
            {
                imageCount = true;
            }
            else
            {
                fclose(current_file);
            }
            // %03i == print an integer with 3 numbers to represent it
            sprintf(current_filename, "%03i.jpg", currentfile_count);
            current_file = fopen(current_filename, "w");
            fwrite(buffer, sizeof(BYTE), bytes_read, current_file);
            currentfile_count++;
        }
        else
        {
            // If already found JPEG
            if (imageFound)
            {
                // Keep writing to it
                fwrite(buffer, sizeof(BYTE), bytes_read, current_file);
            }
        }
    }
    // Close any remaining files
    fclose(file);
    fclose(current_file);
    return 0;
}
