        //Implement a program called recover that recovers JPEGs from a forensic image.

        #include <stdio.h>
        #include <stdlib.h>


        #define BLOCK_SIZE 512

        int main(int argc, char *argv[])
        {
            // ensure proper usage
            if (argc != 2)
            {
                fprintf(stderr, "Usage: ./recover image\n");
                return 1;
            }

        char *mem_card = argv[1];

            // open card file
            FILE *inptr = fopen(mem_card, "r");
            if (inptr == NULL)
            {
                printf("Cannot open file. Please try again.\n");
                return 2;
            }

            // remember filenames
            unsigned char buffer[BLOCK_SIZE];
            // JPEG File Name Counter
            int jpeg_name = 0;
            //file for output
            FILE* outptr = NULL;



            // go through cardfile until there aren't any blocks left
            while (fread(buffer, BLOCK_SIZE, 1, inptr) == 1 )
            {
                //if the image is the start of jpeg
                if (buffer [0] == 0xff && buffer [1] == 0xd8 && buffer [2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
                {
                    if (outptr != NULL)
                    {
                        // close file because there is start to a new JPEG
                        fclose(outptr);
                    }
                    //create a location to store the new jpeg name
                    char new_file[8];
                    sprintf(new_file,"%03d.jpg", jpeg_name);
                    outptr = fopen(new_file, "w");
        	        jpeg_name++;

                }
                if (outptr != NULL)
                {
                    // write 512 bytes
                    fwrite(&buffer, BLOCK_SIZE, 1, outptr);
                }

            }
            // close infile
            fclose(inptr);
            fclose(outptr);

            // victory!
            return 0;

        }







