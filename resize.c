//Implement a program called resize that resizes (i.e., enlarges) 24-bit uncompressed BMPs by a factor of n.

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage: three commanda line arguments + the program
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    //ensure n is the proper size.
   int n = atoi(argv[1]);

    if (n < 1 || n > 100)
    {
        fprintf(stderr, "Usage: n must be positive and less than or equal to 100\n");
        return 2;
    }
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

 // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    //change height and width
    int pre_height = bi.biHeight;
    bi.biHeight *= n;
    int pre_width = bi.biWidth;
    bi.biWidth *= n;

    // determine padding for scanlines and keep track of infile's padding (dependent upon height and width)
    int in_padding = (4 - (pre_width * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //update size of image (dependent upon padding)
    bi.biSizeImage = (((sizeof(RGBTRIPLE))*bi.biWidth) + out_padding) * abs(bi.biHeight);

     //update size of file (dependent upon image size)
     bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //make room for the array
    RGBTRIPLE *holding = malloc((sizeof(RGBTRIPLE)) * (bi.biWidth));

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(pre_height); i < biHeight; i++)
    {
        //create a counter
            int count = 0;

        // iterate over pixels in scanline
        for (int j = 0; j < pre_width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read triple from the infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write pixel into triple
            for (int x = 0; x < n; x++)
                {
                *(holding + count) = triple;
                count++;
                }

        }

        // skip over padding, if any
        fseek(inptr, in_padding, SEEK_CUR);

            // write triple to the outfile
           for(int z = 0; z < n; z++)
           {
                fwrite((holding), sizeof(RGBTRIPLE), bi.biWidth, outptr);

                // add padding back to outfile
                for (int k = 0; k < out_padding; k++)
                {
                    fputc(0x00, outptr);
                }
           }
    }

    //free memory since malloc was used
    free(holding);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

