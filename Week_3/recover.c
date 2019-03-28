#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t  BYTE;
char * make_filename(char *name, int *counter);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover <filename>");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    if(infile == NULL)
    {
        printf("file could not be operned");
        return 2;
    }

    // creat array of bytes to read into
    BYTE data[512];
    // increment file number
    int curJPG = 0;
    // create file name
    // set starting number
    char JPGname[] = "000.jpg\0";
    char *filename = make_filename(JPGname, &curJPG);
    curJPG++;
    // pointer to file
    FILE *JPG = NULL;
    bool open = false;
    int read = 0;
    while(true)
    {
        // read block
        read = fread(data, 1, 512, infile);
        // check that it is the correct size
        if(read != 512)
        {
            // data not the correct size, close all files.
            // exit program
            fclose(infile);
            fclose(JPG);
            // kicks from loop after all files are created
            break;
        }
        else
        {
            // check for end of file
            if(data[0] == 0xff &&
            data[1] == 0xd8 &&
            data[2] == 0xff &&
            (data[3] & 0xf0) == 0xe0){
                // if end of file and a file is open, close it
                if(open)
                {
                    // close file and create new file name
                    fclose(JPG);
                    open = false;
                    filename = make_filename(JPGname, &curJPG);
                    curJPG++;
                }
                // open new file
                JPG = fopen(filename, "w");
                open = true;
            }
            // if a file is open, write to it.
            if (open)
            {
                fwrite(data, 1, 512, JPG);
            }
        }
    }
}

char * make_filename(char *name, int *counter)
{
    char numbers[] = "0123456789";
    name[2] = numbers[*counter % 10];
    name[1] = numbers[(*counter - (*counter % 10)) / 10];
    return name;
}