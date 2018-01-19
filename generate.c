/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */

#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // If the argument count is not 2 or 3 (the user did not input any values),
    // then remind the user of the neccessary input.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // Change the "n" input to an integer
    int n = atoi(argv[1]);

    // If the argument count is 3 (there is n input and an s input),
    // use the srand48 function to initialize the n input, using the s input as an influence.
    // The s input must be changed to an integer.
    // Else the argument count must be 2, and the srand48 function will initialize the n input with no influence.
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    //Print out a randomized number until the number count has reached the desired count provided by the user.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
