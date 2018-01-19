#include <stdio.h>
#include <cs50.h>

int main (void)
{
    printf("Height: ");
    int height;

    //retrieve the pyramid height from the user until it is an allowed number
    do
    {
        height = get_int();
        if (height == 0)
            return false;
    }
    while (height < 1 || height > 23);

   //determine the number of rows
    for (int i = 0; i < height ; i++)
    {
        //determine the number spaces
        for (int s = 0; s < height - i - 1; s++)
        {
            //prints the spaces
            printf("%s", " ");
        }
        //determines the number of hashtags
        for (int h = 0; h < i + 2 ; h++)
        {
            //prints the hashtags
            printf("#");
        }
        //prints a new line before going on to the next row
        printf("\n");
    }
}



