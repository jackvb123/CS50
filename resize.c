/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // taking factor value
    int n = atoi(argv[1]);
    
    
    
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        return 4;
    }

    BITMAPFILEHEADER bf_output;
    BITMAPINFOHEADER bi_output;
    bf_output = bf;
    bi_output = bi;
    bi_output.biWidth=bi.biWidth * n;
    bi_output.biHeight=bi.biHeight * n;
    
    
    // determine padding for scanlines
    int pad_input = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int pad_output = (4-(bi_output.biWidth *sizeof(RGBTRIPLE))%4)%4;

    //bfSize and biSizeImage Calculation
    //Followed the discussion at https://cs50.stackexchange.com/questions/14016/pset4-resize-c-bfsize-bisizeimage-formulas
    
    bf_output.bfSize = 54+bi_output.biWidth*abs(bi_output.biHeight)*3+abs(bi_output.biHeight)*pad_output;
    bi_output.biSizeImage = ((((bi_output.biWidth*bi_output.biBitCount)+31)& ~31)/8)*abs(bi_output.biHeight);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_output, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_output, sizeof(BITMAPINFOHEADER), 1, outptr);

    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline n times vertically 
        for(int p=0;p<n;p++){
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile n times horizontally
            for(int k=0;k<n;k++)
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, pad_input, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < pad_output; k++)
        {
            fputc(0x00, outptr);
        }
        
        fseek(inptr, -(bi.biWidth*3+pad_input),SEEK_CUR);
        }
        fseek(inptr,bi.biWidth*3+pad_input,SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
