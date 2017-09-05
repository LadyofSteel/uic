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

typedef enum { false, true } bool;

/**
 *  @brief Resizes given integer array
 *
 *  Resizes the given integer array by doubling the previous array capacity. The new
 *  array capacity is also updated accordingly. The array size is used to copy the
 *  elements of the initial array.
 *
 *  @param int** reference to input array
 *  @param int* reference to array capacity
 *  @param int* reference to array size
 *  @return bool resize successful
*/
bool ResizeArray(int **array, int *capacity, int *size);

/**
 *  @brief Cleans up array
 *
 *  Handles memory cleanup for the given array of integers. All array contents
 *  are deleted.
 *
 *  @param int* input array
 *  @return bool cleanup successful
*/
bool CleanArray(int *array);

/**
 *  @brief Inserts integers from user input
 *
 *  Reads user input and inserts it in the given integer array. The array size is
 *  dynamic and is doubled when it runs out of space.
 *
 *  @param int** reference to input array
 *  @param int* reference to current array capacity
 *  @param int* reference to current array size
*/
void InsertIntegers(int **array, int *capacity, int *size);

/**
 *  @brief Inserts integers from user input
 *
 *  Reads user input and search for it in the given integer array.
 *
 *  @param int* unsorted input array
 *  @param int* sorted input array
 *  @param int current array size
*/
void SearchIntegers(int *unsorted_array, int * sorted_array, int size);

/**
 *  @brief Prints out the search results
 *
 *  Prints out the important information for the given array name.
 *
 *  @sa SearchIntegers()
 *  @param const char* array name
 *  @param const int search value
 *  @param const int index
 *  @param const int number of comparisons performed
*/
void PrintResults(const char *array, const int value, const int index, const int comparisons);

/**
 *  @brief Creates a clone array
 *
 *  Creates a clone of the source array and puts it in the destination array.
 *  It basically creates an identical, separate copy of source, and assigns it
 *  to destination.
 *
 *  @param int* source array to clone
 *  @param int* destination array
 *  @param int array size
 *  @return bool cloning successful
*/
bool CloneArray(int *source, int *destination, int size);

/**
 *  @brief Utility function to swap two integers
 *
 *  Performs the partitioning of a given array for proper quicksort implementation.
 *  Reference: http://www.geeksforgeeks.org/quick-sort/
 *
 *  @param int* reference to first integer
 *  @param int* reference to second integer
*/
void SwapInts(int *a, int *b);

/**
 *  @brief Helper function for quicksort
 *
 *  Performs the partitioning of a given array for proper quicksort implementation.
 *  Reference: http://www.geeksforgeeks.org/quick-sort/
 *
 *  @param int* array to be sorted
 *  @param int starting index
 *  @param int ending index
 *  @return int pivot point
*/
int _SortArray (int *array, int start_index, int end_index);

/**
 *  @brief Sorts array using quicksort
 *
 *  Sorts the given integer array in ascending order using quicksort algorithm.
 *  Reference: http://www.geeksforgeeks.org/quick-sort/
 *
 *  @param int* array to be sorted
 *  @param int starting index
 *  @param int ending index
*/
void SortArray (int *array, int start_index, int end_index);

/**
 *  @brief Array linear search
 *
 *  Performs linear search on the given integer array for the specified value.
 *  If the value was found, the function returns the index of the value in the
 *  array. Otherwise, -1 is returned.
 *  It also updates the number of comparisons done to find the value.
 *
 *  @param int* input array
 *  @param int current array size
 *  @param int target value to search for
 *  @param int* reference to the number of comparisons
 *  @return int index of value to be found
*/
int LinearSearch(int *array, int size, int target, int *comparisons);

/**
 *  @brief Array binary search
 *
 *  Performs binary search on the given sorted array for the specified value.
 *  If the value was found, the function returns the index of the value in the
 *  array. Otherwise, -1 is returned.
 *  It also updates the number of comparisons done to find the value.
 *
 *  @param int* input array
 *  @param int current array size
 *  @param int target value to search for
 *  @param int* reference to the number of comparisons
 *  @return int index of value to be found
*/
int BinarySearch(int *array, int size, int target, int *comparisons);
