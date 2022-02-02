#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t byte;

int main(int argc, char *argv[])
{
    // checking to make sure there is exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // opening file to read from
    FILE *f = fopen(argv[1], "r");

    // checks whether the file is null
    if (f == NULL)
    {
        printf("Coudn't open %s\n", argv[1]);
        return 2;
    }

    // buffer file
    byte buffer[512];
    int count = 0;
    FILE *img = NULL;
    char f_name[8];

    while (fread(&buffer, 512, 1, f) == 1)
    {
        // checking whether the file is JPG
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (count != 0)
            {
                fclose(img);
            }

            sprintf(f_name, "%03i.jpg", count);
            img = fopen(f_name, "w");
            count++;
        }

        if (count != 0)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }

    // closes the files
    fclose(f);
    fclose(img);

    return 0;
}