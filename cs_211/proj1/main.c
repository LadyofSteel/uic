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

bool ResizeArray(int **array, int *capacity, int *size)
{
  int *temp_array = (int *) malloc(2 * *capacity * sizeof(int));
  
  if (!CloneArray(*array, temp_array, *size))
    return false;

  if (!CleanArray(*array))
    return false;

  (*array) = temp_array;
  (*capacity) *= 2;

  printf("Resize successful\n");
  return true;
}

bool CleanArray(int *array)
{
  if (array == NULL)
    return false;

  free(array);
  return true;
}

void InsertIntegers(int **array, int *capacity, int *size)
{
  int input = 0;
  int position = 0;

  printf("Please enter integer values to add (-999 to stop):\n");

  scanf("%d", &input);
  while (input != -999) {
    (*array)[position] = input;
    position++;
    (*size)++;

    if (position >= *capacity)
      ResizeArray(array, capacity, size);

    scanf("%d", &input);
  }
}

void SearchIntegers(int *unsorted_array, int *sorted_array, int size)
{
  int input = 0;

  printf("Please enter integer values to search for (-999 to stop):\n");

  scanf("%d", &input);
  while (input != -999) {
    int linear_comparisons = 0;
    int binary_comparisons = 0;
    const int linear_index = LinearSearch(unsorted_array, size, input, &linear_comparisons);
    const int binary_index = BinarySearch(sorted_array, size, input, &binary_comparisons);

    if (linear_index == -1 &&
        binary_index == -1) {
      printf("Integer %d was not found in the arrays\n", input);
    } else {
      PrintResults("Linear search - Unsorted array", input, linear_index, linear_comparisons);
      PrintResults("Binary search - Sorted array", input, binary_index, binary_comparisons);
      printf("\n");
    }

    scanf("%d", &input);
  }
}

void PrintResults(const char *array, const int value, const int index, const int comparisons)
{
  printf("%s: found %d at position %d after %d comparisons.\n", array, value, index, comparisons);
}

bool CloneArray(int *source, int *destination, int size)
{
  if (destination == NULL)
    return false;

  int i;
  for (i = 0; i < size; i++) {
    destination[i] = source[i];
  }
  return true;
}

void SwapInts(int* a, int* b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int _SortArray (int *array, int start_index, int end_index)
{
  const int pivot = array[end_index];
  int i = start_index - 1;
  int j;

  for (j = start_index; j <= end_index - 1; j++) {
    // If current element is smaller than or
    // equal to pivot
    if (array[j] <= pivot) {
      i++;    // increment index of smaller element
      SwapInts( &(array[i]), &(array[j]) );
    }
  }
  SwapInts( &(array[i + 1]), &(array[end_index]) );
  return (i + 1);
}
 
void SortArray(int *array, int start_index, int end_index)
{
  if (start_index < end_index) {
    // Partition the array and get the pivot point
    int pi = _SortArray(array, start_index, end_index);

    // Sort elements in both partitions
    SortArray(array, start_index, pi - 1);
    SortArray(array, pi + 1, end_index);
  }
}

int LinearSearch(int *array, int size, int target, int *comparisons)
{
  int index;
  for (index = 0; index < size; index++) {
    (*comparisons)++;

    if (array[index] == target)
      break;
  }

  if (index == size)
    return -1;

  return index;
}

int BinarySearch(int *array, int size, int target, int *comparisons)
{
  int leftmost = 0;
  int rightmost = size - 1;

  while (leftmost <= rightmost) {
    int middle = leftmost + (rightmost - leftmost) / 2;

    if (array[middle] < target) {
      leftmost = middle + 1;
      (*comparisons)++;
    } else if (array[middle] > target) {
      rightmost = middle - 1;
      (*comparisons)++;
    } else {
      (*comparisons)++;
      return middle;
    }
  }

  return -1;
}

void PrintArrayElements(int *array, int size)
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

  InsertIntegers(&input_array, &array_capacity, &array_size);

  printf("All integers were successfully inserted.\n");

  int *clone_array = (int *) malloc(sizeof(int) * array_capacity);
  if (!CloneArray(input_array, clone_array, array_size)) {
    printf("ERROR: cloning array failed! Aborting...\n");
    return 0;
  }
  printf("Array successfully cloned.\n");
  /*PrintArrayElements(clone_array, array_size);*/

  SortArray(clone_array, 0, array_size - 1);
  printf("Array successfully sorted using quicksort.\n");
  /*PrintArrayElements(clone_array, array_size);*/

  SearchIntegers(input_array, clone_array, array_size);

  printf("Cleaning up the mess...\n");
  CleanArray(input_array);
  printf("Done...\n");

  printf("Goodbye!\n");
  return 0;
}
