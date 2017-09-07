/**
 *  @brief CS 211 Project 1
 *
 *  This program basically compares the searching algorithms for both unsorted
 *  and sorted arrays of integers. The user first inputs an array of integers,
 *  the array is then copied and sorts one of the copies, then the user inputs
 *  integers to search for in both arrays. The program outputs the results for
 *  both the sorted and unsorted arrays with their own statistics and whatnot.
 *
 *  @author Ammar Subei
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

bool resizeArray(int **array, int *capacity, int *size)
{
  // Use a temporary array that has twice the capacity
  int *temp_array = (int *) malloc(2 * *capacity * sizeof(int));
  
  // Clone the original array to the temporary array
  if (!cloneArray(*array, temp_array, *size))
    return false;

  if (!cleanArray(*array))
    return false;

  // Now set the original array to be the temporary array, and update the array capacity
  (*array) = temp_array;
  (*capacity) *= 2;

  // printf("Resize successful\n");
  return true;
}

bool cleanArray(int *array)
{
  if (array == NULL)
    return false;

  free(array);
  return true;
}

bool cloneArray(int *source, int *destination, int size)
{
  if (destination == NULL)
    return false;

  int i;
  for (i = 0; i < size; i++) {
    destination[i] = source[i];
  }
  return true;
}

void swapInts(int* a, int* b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int _sortArray (int *array, int start_index, int end_index)
{
  const int pivot = array[end_index];
  int i = start_index - 1;
  int j;

  // Move all integers in the correct position with resepct to the pivot
  for (j = start_index; j <= end_index - 1; j++) {
    if (array[j] <= pivot) {
      i++;
      swapInts( &(array[i]), &(array[j]) );
    }
  }
  swapInts( &(array[i + 1]), &(array[end_index]) );
  return (i + 1);
}
 
void sortArray(int *array, int start_index, int end_index)
{
  if (start_index < end_index) {
    // Partition the array and get the pivot point
    int pi = _sortArray(array, start_index, end_index);

    // Sort elements in both partitions
    sortArray(array, start_index, pi - 1);
    sortArray(array, pi + 1, end_index);
  }
}

void insertIntegers(int **array, int *capacity, int *size)
{
  int input = 0;
  int position = 0;

  printf("Please enter integer values to add (-999 to stop):\n");

  // User input
  scanf("%d", &input);
  while (input != -999) {
    (*array)[position] = input;
    position++;
    (*size)++;

    // Resize array if it's full
    if (position >= *capacity)
      resizeArray(array, capacity, size);

    scanf("%d", &input);
  }
}

void searchIntegers(int *unsorted_array, int *sorted_array, int size)
{
  int input = 0;

  printf("Please enter integer values to search for (-999 to stop):\n");

  // User input
  scanf("%d", &input);
  while (input != -999) {
    int linear_comparisons = 0;
    int binary_comparisons = 0;
    
    // Run the search methods
    const int linear_index = linearSearch(unsorted_array, size, input, &linear_comparisons);
    const int binary_index = binarySearch(sorted_array, size, input, &binary_comparisons);

    // Print results for both search methods
    printResults("Linear search - Unsorted array", input, linear_index, linear_comparisons);
    printResults("Binary search - Sorted array", input, binary_index, binary_comparisons);
    printf("\n");

    scanf("%d", &input);
  }
}

void printResults(const char *array, const int value, const int index, const int comparisons)
{
  if (index == -1) {
    printf("%s: integer %d was not found after %d comparisons.\n", array, value, comparisons);
  } else {
    printf("%s: integer %d was found at position %d after %d comparisons.\n", array, value, index, comparisons);
  }
}

int linearSearch(int *array, int size, int target, int *comparisons)
{
  int index;
  for (index = 0; index < size; index++) {
    (*comparisons)++;

    if (array[index] == target)
      break;
  }

  // Target not found
  if (index == size)
    return -1;

  return index;
}

int binarySearch(int *array, int size, int target, int *comparisons)
{
  int leftmost = 0;
  int rightmost = size - 1;

  while (leftmost <= rightmost) {
    (*comparisons)++;
    int middle = leftmost + (rightmost - leftmost) / 2;

    if (array[middle] < target) {
      leftmost = middle + 1;
    } else if (array[middle] > target) {
      rightmost = middle - 1;
    } else {
      return middle;
    }
  }

  // Target not found
  return -1;
}

// Utility function to print out all the array elements.
// Only used for debugging purposes.
void printArrayElements(int *array, int size)
{
  int index;
  for (index = 0; index < size; index++) {
    printf("%d ", array[index]);
  }
  printf("\n");
}

int main()
{
  int array_capacity = 5;
  int array_size = 0;

  int *input_array = (int *) malloc(sizeof(int) * array_capacity);

  insertIntegers(&input_array, &array_capacity, &array_size);

  printf("All integers were successfully inserted.\n");

  int *clone_array = (int *) malloc(sizeof(int) * array_capacity);
  if (!cloneArray(input_array, clone_array, array_size)) {
    printf("ERROR: cloning array failed! Aborting...\n");
    return 0;
  }
  printf("Array successfully cloned.\n");
  // printArrayElements(clone_array, array_size);

  sortArray(clone_array, 0, array_size - 1);
  printf("Array successfully sorted using quicksort.\n");
  // printArrayElements(clone_array, array_size);

  searchIntegers(input_array, clone_array, array_size);

  printf("Cleaning up the mess...\n");
  cleanArray(input_array);
  printf("Done...\n");

  printf("Goodbye!\n");
  return 0;
}
