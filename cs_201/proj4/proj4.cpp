/* Project 4

Design a hash table to store a dictionary of table that will be
utilized by a game. Given a word, we want to know the number of
valid 3, 4, 5, 6, 7, or 8 character table that can be made with 
letters from the word. Here are the points for valid table 
a valid 3 letter word is worth 10 points
a valid 4 letter word is worth 25 points
a valid 5 letter word is worth 50 points
a valid 6 letter word is worth 100 points
a valid 7 letter word is worth 200 points
a valid 8 letter word is worth 500 points
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#define WORDMAXSIZE 25
const int HASHTABLESIZE = 100000;
using namespace std;

typedef struct CELL *LIST;
struct CELL {
	char *word;
	// int length;  // NOT USED
	// int score;	// NOT USED
	LIST next;
};

typedef struct HASHTABLE {
	LIST array[HASHTABLESIZE];
} hashtable;

/* This function prints out the hash table! IT'S ONLY
	FOR TESTING PURPOSES!*/
void printTable(LIST element){
	if(element != NULL){
		printTable(element->next);
		printf("%s %c", element->word, ' ');
	}		
}

/* returns the integer hash function of a word */
int hashFunction(char *word){
	char *tmpptr = word;
	if((*tmpptr) == '\0' || (*tmpptr) == '\n')
		return -1;
	
	int count 	= 0;
	unsigned long hashKey = 0;
	while((*tmpptr) != '\0' && (*tmpptr) != '\n'){
		unsigned long x = 1;
		for (int i = 0; i < count; i++)
			x = x * 26;
		hashKey += (int)(*tmpptr) * x;
		count++;
		tmpptr++;
	}
	hashKey = hashKey % HASHTABLESIZE;
	return hashKey;

}

/* This function stores the words in the linked lists of each
	element in the hash table array */
void storeWordInList(hashtable *table, int index, char* str){
	LIST current = table->array[index];

	if(current == NULL) {
		LIST tmp = (LIST) malloc(sizeof(CELL));
		tmp->word = (char *) malloc(strlen(str));
		strcpy(tmp->word, str);
		tmp->next = NULL;
		table->array[index] = tmp;
		return;
	}

	while(current->next != NULL)
		current = current->next;

	// now that we're at the end of our list, create a new element
	LIST tmp = (LIST) malloc(sizeof(CELL));
	tmp->word = (char *) malloc(strlen(str));
	strcpy(tmp->word, str);
	current->next = tmp;
}

/* Initialize all the pointers to NULL
then prompts the user for a dictionary file 
reads all the table and places in table */
void initializeHashTable(hashtable *table)
{
	// Prompt user for dictionary file
	ifstream inFile;
	string fileName;
	cout << "Please enter dictionary file name: ";
	cin >> fileName;
	inFile.open(fileName.c_str());

	// Get the index for each word using hashFunction
	int index = 0;
	while(inFile){
		string tmpString;
		inFile >> tmpString;
		char *str = (char *) malloc(tmpString.length() + 1);
		tmpString.copy(str, tmpString.length());
		index = hashFunction((char*)tmpString.c_str());
		if(index < 0)
			continue;
		storeWordInList(table, index, str);
		//printTable(table->array[index]);
		printf("%d\n", index);
	}
	inFile.close();
}

/* function scoreWord
Determines if a word is valid and not already in the subwords list.
1) call hashfunction with word to determine if valid
2) check if word alread in linked list subwords
3) if not add to linked list subwords
4) return the score of the word
*/
int scoreWord(char word[], hashtable table, LIST *subWords){
	return 0;
};

void perm (char v[], int end, int start, hashtable table, LIST *subwords);

/* code for generating combinations */
/* grabbed from http://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/ */

void combinationUtil(char arr[], char data[], int start, int end, 
                     int index, int r, hashtable table, LIST *ptrsubwords);
 // Needed for qsort.  See http://w...content-available-to-author-only...s.com/reference/cstdlib/qsort/
int compare (const void * a, const void * b)
{  return ( *(int*)a - *(int*)b );  }

// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil()
void printCombination(char arr[], int n, int r, hashtable table, LIST *ptrsubwords)
{
    // A temporary array to store all combination one by one
    char data[r];
 
   // Sort array to handle duplicates
    qsort (arr, n, sizeof(char), compare);

    // Print all combination using temprary array 'data[]'
    combinationUtil(arr, data, 0, n-1, 0, r, table, ptrsubwords);
}
 
/* arr[]  ---> Input Array
   data[] ---> Temporary array to store current combination
   start & end ---> Staring and Ending indexes in arr[]
   index  ---> Current index in data[]
   r ---> Size of a combination to be printed */
void combinationUtil(char arr[], char data[], int start, int end,
                     int index, int r, hashtable table, LIST *ptrsubwords)
{
    // Current combination is ready to be printed, print it
    if (index == r)
    {
    	perm(data,r,0,table,ptrsubwords);
        return;
    }
 
    // replace index with all possible elements. The condition
    // "end-i+1 >= r-index" makes sure that including one element
    // at index will make a combination with remaining elements
    // at remaining positions
    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r, table,ptrsubwords);
        
          // Remove duplicates
        while (arr[i] == arr[i+1])
             i++;
    }
}



/* code for generating permutations
http://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/ */
/* swap */
/* function to swap array elements */

void swap (char v[], int i, int j) {
	char	t;

	t = v[i];
	v[i] = v[j];
	v[j] = t;
}


/* recursive function to generate permutations */
void perm (char v[], int end, int start, hashtable table, LIST *ptrsubwords) {

	/* this function generates the permutations of the array
	 * from element start(i) to element end(n)-1
	 */
	int	j;
	int runningTotal=0;

	/* if we are at the end of the array, we have one permutation
	 * we can use (here we print it for testing purposes and also 
	 * word to scoreWord to keep track of running total of points
	 * array off to some other function that uses it for something
	 */
	if (start == end) {
		for (j=0; j<end; j++) printf ("%c", v[j]);
		printf ("\n");
		runningTotal += scoreWord(v,table,ptrsubwords);
	} else
		/* recursively explore the permutations starting
		 * at index i going through index n-1
		 */
		for (j=start; j<end; j++) {

			/* try the array with start and j switched */

			swap (v, start, j);
			perm (v, end, start+1,table,ptrsubwords);

			/* swap them back the way they were */

			swap (v, start, j);
		}
}

int main (){
	LIST subwords 	= NULL;
	LIST tmpptr 	= NULL;
	hashtable *table = (HASHTABLE*) malloc(sizeof(hashtable));
	initializeHashTable(table);
	int maxlength=0;
	int i;
	int totalscore = 0;
	/* replace this hard coded word with prompt the user
	for a valid word to score*/
	char array[WORDMAXSIZE];
	cout << "Please enter a valid word: ";
	cin >> array;
	strtok(array, "\n");
	char saveWord[WORDMAXSIZE];
	strcpy(saveWord,array);
	int wordlength = strlen(array);
	if (wordlength < 8)
		maxlength = wordlength;
	else maxlength = 8;
	for (i=3;i<=maxlength;i++){
		printCombination(array, wordlength, i, *table, &subwords);
	}
	// THE FOLLOWING HAS BEEN COMMENTED OUT BECAUSE IT IS NOT USED AT ALL!

	// tmpptr = subwords;
	// printf("List of table that were made from %s\n",saveWord);
	// while (tmpptr != NULL){
	// 	printf("%s\n",tmpptr->word);
	// 	// totalscore+=tmpptr->score;
	// 	tmpptr = tmpptr->next;
	// }
	// printf("Total score for the word %s is %d\n",saveWord,totalscore);
}
