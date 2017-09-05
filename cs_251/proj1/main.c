/*main.c*/

//
// Netflix movie analysis: top-10 by rating and # of reviews.
//
// Ammar Subei
// U. of Illinois, Chicago
// CS251, Spring 2017
// Project #01
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SORT_BY_RATING 1
#define SORT_BY_REVIEWS 0

typedef struct REVIEW
{
    char  Date[512];
    int   UserID;
    int   Rating;
    int   MovieID;
} REVIEW;

typedef struct MOVIE
{
    char  Name[512];
    int   ID;
    int   PubYear;
    int   numOfRatings;
    int   TotalRatings;
    double AverageRating;
} MOVIE;

//
// getFileName: inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be opened, an
// error message is output and the program is exited.
//
char *getFileName()
{
    char filename[512];
    int  fnsize = sizeof(filename) / sizeof(filename[0]);

    // input filename from the keyboard:
    fgets(filename, fnsize, stdin);
    filename[strcspn(filename, "\r\n")] = '\0';  // strip EOL char(s):

    // make sure filename exists and can be opened:
    FILE *infile = fopen(filename, "r");
    if (infile == NULL)
    {
        printf("**Error: unable to open '%s'\n\n", filename);
        exit(-1);
    }

    fclose(infile);

    // duplicate and return filename:
    char *s = (char *)malloc((strlen(filename) + 1) * sizeof(char));
    strcpy(s, filename);

    return s;
}

// Parses a line from movies file, and stores the data accordingly
void parseLineMovies(char *line, MOVIE *movie)
{
    line[strcspn(line, "\r\n")] = '\0';

    movie->ID = atoi(strtok(line, ","));

    char *temp = strtok(NULL, ",");
    strcpy(movie->Name, temp);

    movie->PubYear = atoi(strtok(NULL, ","));
}

// Stores each movie info read from file into the movies array
void storeMovies(int numOfMovies, FILE *fp, MOVIE *movies)
{
    char *line;
    size_t lineSize = 0;

    getline(&line, &lineSize, fp);
    getline(&line, &lineSize, fp);

    int i;
    for(i = 0; i < numOfMovies; i++)
    {
        parseLineMovies(line, &movies[i]);
        getline(&line, &lineSize, fp);
    }
}

// Parses a line from reviews file, and stores the data accordingly
void parseLineReviews(char *line, REVIEW *review, int numOfMovies, MOVIE *movies)
{
    line[strcspn(line, "\r\n")] = '\0';

    review->MovieID = atoi(strtok(line, ","));
    review->UserID = atoi(strtok(NULL, ","));
    review->Rating = atoi(strtok(NULL, ","));

    for (int i = 0; i < numOfMovies; ++i)
    {
        if (movies[i].ID == review->MovieID)
        {
            movies[i].numOfRatings++;
            movies[i].TotalRatings += review->Rating;
        }
    }

    char *temp = strtok(NULL, ",");
    strcpy(review->Date, temp);
}

// Stores each review info read from file into the reviews array
void storeReviews(int numOfReviews, FILE *fp, MOVIE *movies, int numOfMovies, REVIEW *reviews)
{
    char *line;
    size_t lineSize = 0;

    getline(&line, &lineSize, fp);
    getline(&line, &lineSize, fp);

    for(int i = 0; i < numOfReviews; i++)
    {
        parseLineReviews(line, &reviews[i], numOfMovies, movies);
        getline(&line, &lineSize, fp);
    }
}

// Computes the average rating for each movie
void computeAvgRating(MOVIE *movies, int numOfMovies)
{
    for (int i = 0; i < numOfMovies; ++i)
    {
        if (movies[i].numOfRatings > 0)
            movies[i].AverageRating = ((double)movies[i].TotalRatings)/((double)movies[i].numOfRatings);
        else
        {
            movies[i].TotalRatings = 0;
            movies[i].AverageRating = 0.0;
        }
    }
}


// Sort the movies array by specified criteria using merge sort
// NOTE: almost all the code for MergeSort was taken from zyante
// This function IS NOT of my own writing 
void Merge(MOVIE *movies, int i, int j, int k, int sortBy) 
{
    int mergedSize = k - i + 1;       // Size of merged partition
    MOVIE tempMovies[mergedSize];     // Temporary array for merged numbers
    int mergePos = 0;                 // Position to insert merged number
    int leftPos = 0;                  // Position of elements in left partition
    int rightPos = 0;                 // Position of elements in right partition

    leftPos = i;                      // Initialize left partition position
    rightPos = j + 1;                 // Initialize right partition position

    if(sortBy)
    {
        // Add smallest element from left or right partition to merged numbers
        while (leftPos <= j && rightPos <= k) 
        {
            if (movies[leftPos].AverageRating > movies[rightPos].AverageRating) 
            {
                tempMovies[mergePos] = movies[leftPos];
                ++leftPos;
            }
            else if (movies[leftPos].AverageRating == movies[rightPos].AverageRating)
            {
                if (strcmp(movies[leftPos].Name, movies[rightPos].Name) < 0)
                {
                    tempMovies[mergePos] = movies[leftPos];
                    ++leftPos;
                }
                else
                {
                    tempMovies[mergePos] = movies[rightPos];
                    ++rightPos;
                }
            }
            else 
            {
                tempMovies[mergePos] = movies[rightPos];
                ++rightPos;
            }
            ++mergePos;
        }

        // If left partition is not empty, add remaining elements to merged numbers
        while (leftPos <= j) 
        {
            tempMovies[mergePos] = movies[leftPos];
            ++leftPos;
            ++mergePos;
        }

        // If right partition is not empty, add remaining elements to merged numbers
        while (rightPos <= k) 
        {
            tempMovies[mergePos] = movies[rightPos];
            ++rightPos;
            ++mergePos;
        }

        // Copy merge number back to numbers
        for (mergePos = 0; mergePos < mergedSize; ++mergePos)
            movies[i + mergePos] = tempMovies[mergePos];
    }
    else
    {
        // Add smallest element from left or right partition to merged numbers
        while (leftPos <= j && rightPos <= k) 
        {
            if (movies[leftPos].numOfRatings > movies[rightPos].numOfRatings) 
            {
                tempMovies[mergePos] = movies[leftPos];
                ++leftPos;
            }
            else if (movies[leftPos].numOfRatings == movies[rightPos].numOfRatings)
            {
                if (strcmp(movies[leftPos].Name, movies[rightPos].Name) < 0)
                {
                    tempMovies[mergePos] = movies[leftPos];
                    ++leftPos;
                }
                else
                {
                    tempMovies[mergePos] = movies[rightPos];
                    ++rightPos;
                }
            }
            else 
            {
                tempMovies[mergePos] = movies[rightPos];
                ++rightPos;
            }
            ++mergePos;
        }

        // If left partition is not empty, add remaining elements to merged numbers
        while (leftPos <= j) 
        {
            tempMovies[mergePos] = movies[leftPos];
            ++leftPos;
            ++mergePos;
        }

        // If right partition is not empty, add remaining elements to merged numbers
        while (rightPos <= k) 
        {
            tempMovies[mergePos] = movies[rightPos];
            ++rightPos;
            ++mergePos;
        }

        // Copy merge number back to numbers
        for (mergePos = 0; mergePos < mergedSize; ++mergePos)
            movies[i + mergePos] = tempMovies[mergePos];
    }
}

// Sort the movies array by specified criteria using merge sort
// NOTE: almost all the code for MergeSort was taken from zyante
// This function IS NOT of my own writing
void MergeSort(MOVIE *movies, int i, int k, int sortBy) 
{
    int j = 0;

    if (i < k) 
    {
        j = (i + k) / 2;  // Find the midpoint in the partition

        // Recursively sort left and right partitions
        MergeSort(movies, i, j, sortBy);
        MergeSort(movies, j + 1, k, sortBy);

        // Merge left and right partition in sorted order
        Merge(movies, i, j, k, sortBy);
    }
}


int main()
{
    // get filenames from the user/stdin:
    char *MoviesFileName = getFileName();
    char *ReviewsFileName = getFileName();

    // Open movies file 
    FILE *fp;
    fp = fopen(MoviesFileName, "r");
    if (!fp)
        exit(EXIT_FAILURE);

    // Read first line and store integer value
    int numOfMovies;
    fscanf(fp, "%d", &numOfMovies);
    printf("Movies: %d\n", numOfMovies);

    // Store every movie info in array of MOVIE structs
    MOVIE *movies = (MOVIE *)calloc(numOfMovies, sizeof(MOVIE));
    storeMovies(numOfMovies, fp, movies);

    // We're done with the movies file
    fclose(fp);

    // Open reviews file
    fp = fopen(ReviewsFileName, "r");
    if (!fp)
        exit(EXIT_FAILURE);

    // Read first line and store integer value
    int numOfReviews;
    fscanf(fp, "%d", &numOfReviews);
    printf("Reviews %d\n", numOfReviews);

    // Store every review info in array of REVIEW structs
    REVIEW *reviews = (REVIEW *)calloc(numOfReviews, sizeof(REVIEW));
    storeReviews(numOfReviews, fp, movies, numOfMovies, reviews);

    // We're done with the reviews file
    fclose(fp);

    // Compute the average rating for each movie
    computeAvgRating(movies, numOfMovies);

    // Here we print out Top-10 by Rating
    printf("**Top-10 by Rating**\n");

    MergeSort(movies, 0, numOfMovies-1, SORT_BY_RATING);

    for (int i = 0; i < 10; ++i)
        printf("%d: %f,'%s'\n", i+1, movies[i].AverageRating, movies[i].Name);

    // Here we print out Top-10 by Num Reviews
    printf("**Top-10 by Num Reviews**\n");

    MergeSort(movies, 0, numOfMovies-1, SORT_BY_REVIEWS);

    for (int i = 0; i < 10; ++i)
        printf("%d: %d,'%s'\n", i+1, movies[i].numOfRatings, movies[i].Name);

    return 0;
}
