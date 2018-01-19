/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // declare integers for the bounds of the initial search
    int left_bound = 0;
    int right_bound = n - 1;
    // run the loop while the left bound is smaller than the right bound
	while (right_bound >= left_bound)
	{
	    // the middle position is the parameters of the bound in half
        int middle_position = (left_bound + right_bound) / 2;
        // if the value is larger than the middle point, update the right bound. left bound remains.
        if (value < values[middle_position])
	    {
	        right_bound = middle_position - 1;
	    }
	    // if the value is smaller than the middle point, update the left bound. right bound remains.
        if (value > values[middle_position])
	    {
    	    left_bound = middle_position + 1;
	    }
	    // if the value is the middle point, return true.
        if (value == values[middle_position])
	    {
			return true;
		}
    }
    // if the value is not found, the program will return false.
    return false;
}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
    //bubble sort

// iterate over list
// swap is the end of the swappable array, r is the counter of swaps
for (int swap = (n - 1), r = 0; swap > r; r++)
	{
	    // create a space for the swapping of numbers so that they don't end up equalling each other
	    int placeholder;
        int i = swap - r;
        int endgame = 0;
    // iterate the position in the index
    // changing the end index spot once the larges number has been bubbled

	for (int c = 0; c < i; c++)
		{
		// compare adjacent elements
		// swap elements that are in the wrong order
		if (values[c] > values[c + 1])
			placeholder = values[c];
			values[c] = values [c + 1];
			values[c+1] = placeholder;
			endgame = 1;

	}
// the list is sorted once no elements have been swapped
if (endgame == 0)
{
	break;
}

    return;
}
}
