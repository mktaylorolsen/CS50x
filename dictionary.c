/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

#define HASH_SIZE 2000


//create the node
typedef struct node
{
	char word[LENGTH + 1];
	struct node *next;
}
node;


//Hash function via https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn/
int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n = strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASH_SIZE;
}

//create an array of pointer-to-nodes of size HASH_SIZE
node* hashtable[HASH_SIZE];

//global variable for dictionary word count
int dict_count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{

int length = strlen(word);
char copyword[length + 1];
copyword[length] = '\0';

//convert the word to lowercase and store it in the copy
for (int m = 0; m < length; m++)
{
    copyword[m] = tolower(word[m]);
}



    //where head is the pointer of the beginning of the linked list. is something different in my code
    int new_ind = hash_it(copyword);
    node *cursor = hashtable[new_ind];
    while (cursor != NULL)
    	{
    		//compare the specific word from the text and the word the cursor is pointing to
    		int result;
    		result = strcasecmp(word, cursor->word);
    		//if the items are not equal then the cursor moves to the next word.
    		if (result != 0)
    		{
    			cursor = cursor->next;
    		}
    		else
    		{
    			//word exists in dictionary.
    			return true;
    		}
    	}
    	//word does not exist in the dictionary
    	return false;
}


/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
//open dictionary
FILE *fp = fopen("dictionary", "r");
if (fp == NULL)
{
	return 1;
}

char *word = NULL;
/*scan dictionary (file) word by word by finding a string until the end of the
dictionary file is reached*/
while(fscanf(fp, "%s", word)!=EOF)
{
	//allocate space for the new word.
	node *new_node = malloc(sizeof(node));
	//put the word read into the new node
	strcpy(new_node -> word, word);
    //determine where in the array the word will go
	int index = hash_it(word);
    //up the counter
	dict_count++;

	/*if the area in the hashtable is null (open and available), then put the new_node
	in that area and make the new_node point to nothing.*/
	if (hashtable[index] == NULL)
	{
		hashtable[index] = new_node;
		new_node->next = NULL;
	}
	/*otherwise, the new node points to the existing item in the index, and the new
	node goes into the index */
	else
	{
		new_node->next = hashtable[index];
		hashtable[index] = new_node;
	}
}

// shut it down
fclose(fp);

// return true if it works!
return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
return dict_count;
}


/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int p = 0; p < HASH_SIZE; p++)
    {
    	node *cursor = hashtable[p];
    	while (cursor != NULL)
    	{
    		node *temp = cursor;
    		cursor = cursor->next;
    		free(temp);
    	}
    }
    return true;
}
