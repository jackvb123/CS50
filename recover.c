   
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];


    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    FILE * outptr = NULL;
    unsigned char* buffer = malloc(512);
    int i=0;
    while(fread(buffer,512,1,inptr)!=0){
        if(buffer[0] == 0xff &&
           buffer[1] == 0xd8 &&
           buffer[2] == 0xff &&
           (buffer[3] & 0xf0) == 0xe0){
               if(outptr != NULL) fclose(outptr);
               char  name[10] ;
               if(i< 10 )
               sprintf(name, "00%d.jpg",i);
               else
               sprintf(name, "0%d.jpg",i);
               i++;
               
               outptr = fopen(name, "w");
               if(outptr == NULL){
                   fprintf(stderr, "Couldnt create output file\n");
                   fclose(outptr);
                   return 3;
               }
               
           }
           if(outptr!= NULL)
           fwrite(buffer,512,1,outptr);
    }
    


    // close infile
    fclose(inptr);

    
    // success
    return 0;
}
