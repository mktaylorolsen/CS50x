#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//MK Olsen
//CS50 PSet3: Caesar

int main (int argc, string argv[])
{

//converts the users "key" number into an integer
int key = atoi(argv[1]);

    //argc should be 2
    if (argc == 2)
    {
        // retrive the plain text user message
        printf("plaintext: ");
        string user_message = get_string ();
        // print the ciphertext
        printf("ciphertext: ");

        // iterate over characters in the string
        for (int n = 0, x = strlen(user_message); n < x; n++)
       {
           //determining if the character is a letter and it's case
            if(isalpha(user_message[n]))
                {
                    if (isupper(user_message[n]))
                    {
                        printf("%c",(((user_message[n] - 65) + key) % 26) + 65);
                    }
                    if (islower(user_message[n]))
                    {
                        printf("%c",(((user_message[n] - 97) + key) % 26) + 97);
                    }
                }
            else
            {
                printf("%c",user_message[n]);
            }
       }
       printf("\n");
       return 0;
    }
    else
    {
        printf("Oh no!\n");
        return 1;
    }
}



