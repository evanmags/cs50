#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "bmp.h"

bool varify_number(char *num);
int calc_padding(int width);
void write_row(int width, int padding,FILE *file, RGBTRIPLE row[]);

int main(int argc, char *argv[])
{
    // check for correct argument lengths
    // check that the second argument is a numeric value.
    if (argc != 4 || !varify_number(argv[1]))
    {
        printf("usage: ./resize factor copyfile printfile");
        return 1;
    }


    // set variables
    float copies = atof(argv[1]);
    if (copies > 100)
    {
        printf("usage: ./resize factor copyfile printfile");
        return 1;
    }
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    // n file is the file we are reading from. "r" means we have read permissions
    FILE *inptr = fopen(infile, "r");
    // make sure file was opened correctly and it exists.
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    // outfile is the writing to file, "w" means that we have write permissions.
    FILE *outptr = fopen(outfile, "w");
    // double check that it exists adn that is was oepned.
    if (outptr == NULL)
    {
        // if no out put file we still need to close the input since it was opened
        // we did not need to do this for the input file because that file was opened
        // before this one and we would have exited the program before opening this one.
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADEr (first 14 bytes)
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER (next 20 bytes)
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // store old height and width.
    int readWidth = bi.biWidth;
    int readHeight = bi.biHeight;

    // set new height and width properties
    bi.biWidth *= copies;
    bi.biHeight *= copies;

    // determine padding for scanlines
    // need old to know what to skip at the end of each line.
    int oldPadding = calc_padding(readWidth);
    // need new to determine how much to pad on resized image. tripling an image
    // with 2 bytes of padding would give a full 6 BYTES or two tripples.
    // in shich case we can take out all padding as it woule line up correctly.
    int newPadding = calc_padding(bi.biWidth);

    // set new biSize
    bi.biSizeImage  = ((sizeof(RGBTRIPLE) * bi.biWidth) + newPadding) * abs(bi.biHeight);
    // write new bfSize
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // create 'holder' array for each row that is read
    RGBTRIPLE row[bi.biWidth + newPadding];


    // iterate over infile's scanlines
    int heightLine = 0;
    for (int i = 0; i <  abs(readHeight); i++)
    {
        int index = 0;
        for (int j = 0; j < readWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            if (copies > 1)
            {
                // write RGB triple to array
                for (int l = 0; l < copies; l++)
                {
                    // this is were the width magic happens.
                    // adding each tripple copies number of times
                    // to widen each row
                    row[index] = triple;
                    index++;
                }
            }
            else
            {
                if (j % (int)(1/copies) == 0)
                {
                    row[index] = triple;
                    index++;
                }
            }
        }



        // skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);

        // this is were the rows are written and
        // the height magic happens
        if(copies > 1)
        {
            // each row is iterated over copies number of times
            // first writing the row, then writing the padding (if any)
            // every run through this iterator adds another row of height to the new file.
            for (int m = 0; m < copies; m++)
            {
                write_row(bi.biWidth, newPadding, outptr, row);
            }
        }
        else
        {
            // only print if multiple of inverse of copies
            if (i % (int)(1/copies) == 0)
            {
                write_row(bi.biWidth, newPadding, outptr, row);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

bool varify_number(char *num)
{
    for (int i = 0, n = strlen(num); i < n; i++)
    {
        if (isdigit(num[i]) == 0 && strstr(&num[i], ".") == NULL)
        {
            return false;
        }
    }
    return true;
}

int calc_padding(int width)
{
   return (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
}

void write_row(int width, int padding,FILE *file, RGBTRIPLE row[])
{
    for (int n = 0; n < width; n++)
    {
        fwrite(&row[n], sizeof(RGBTRIPLE), 1, file);
    }
    for (int k = 0; k < padding; k++)
    {
        fputc(0x00, file);
    }
}