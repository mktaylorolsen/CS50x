#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
//MK Olsen
//CS50 PSet2: Initials

int main(void)
    {
        //Get the name
        printf("Hi there! What is your full name?\n");
        string given_name = get_string ();

        //Make sure the name is viable
        if (given_name != NULL);

        //Go ahead and print the first initial
        printf("%c",toupper(given_name[0]));

        //Print out the 1st letter after the space in the name.
        for (int n = 0, s = strlen(given_name); n < s; n++)
            {
                if (given_name[n]==' ')
                    {
                        printf("%c",toupper(given_name[n+1]));
                    }
            }

        //Print new line.
        printf("\n");
    }



