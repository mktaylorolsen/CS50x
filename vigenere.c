#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//MK Olsen
//CS50 PSet3: Vigenere

int main (int argc, string argv[])
{
string key = argv[1];
int key_length = strlen(argv[1]);
    //iterate over the key
    for (int j = 0; j < key_length; j++)
    {
        //argc (argument count) should be 2 and the entered text (argv[1]) should be alphabetized
        if (argc != 2)
        {
            printf("Enter in a keyword.\n");
            return 1;
        }
        if (!isalpha(argv[1][j]))
        {
            printf("Please enter in a keyword with all letters.\n");
            return 1;
        }
    }
    // retrive the plain text user message
    printf("plaintext: ");
    string user_message = get_string ();
    // print the ciphertext
    printf("ciphertext: ");

    // iterate over characters in the plain text string
  for (int n = 0, position = 0, x = strlen(user_message); n < x; n++)
        {
            int movement = toupper(key[position % key_length]) - 65;
           //determining if the character is a letter and it's case
             if(isalpha(user_message[n]))
                 {
                     // determine which character in key the user message assigns to
                         if (isupper(user_message[n]))
                         {
                             printf("%c",(((user_message[n] - 65) + movement) % 26) + 65);
                             position++;
                         }
                         if (islower(user_message[n]))
                         {
                             printf("%c",(((user_message[n] - 97) + movement) % 26) + 97);
                             position++;
                         }

                 }
        // if the letter isn't upper or lowercase then it isn't a letter and will print as is.
        // the key counter does not need to increase.
        else
        {
            printf("%c", user_message[n]);
        }

}
       printf("\n");
       return 0;
    }




