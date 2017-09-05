/* ---------------------------------------------
* This program reads in a 2D matrix of float
* numbers from a user-specified file, then
* calculates and displays the mean, median, and 
* standard deviation of each column in the matrix
* using an array of structures. *
* Class: CS 201, Fall 2015
* System: g++, Ubuntu 14.04 *
* @author Ammar Subei
* @version Sept. 8, 2015
* ---------------------------------------------- */ 
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// Defining a struct to store mean, median, and standard deviation of each column
typedef struct dataStruct{
	float mean;
	float median;
	float stdDev;
}columnStatStruct;

int main()
{	
	// Variable declarations
	int xDim, yDim;
	string fileName;

//******************** USER INPUT **********************
	ifstream inputFile;

	cout << "Please enter the number of rows: ";
	cin  >> yDim;
	cout << "Please enter the number of columns: ";
	cin  >> xDim; 
	cout << "Please enter your input file name: ";
	cin  >> fileName;	
//******************************************************

//******************** DATA STORAGE ********************

	// Open file given by user
	inputFile.open(fileName.c_str());

	// Create pointers using malloc for dynamic size
	float *readDataPtr = (float *) malloc(yDim*xDim*sizeof(float));
	columnStatStruct *structArrayPtr = (columnStatStruct *) malloc(xDim*sizeof(columnStatStruct));

	// First read stream row by row. Store each row in variable "line".
	// Variable 'i' determines row position.
	int i = 0;
	for (string line; getline(inputFile, line); )
	{
		// Now make a stream for the line itself
		istringstream stringStream(line);  

		while(stringStream)
		{
			string tempString;

			// Now we tokenize the line using ' ' as delimiter,
			// but each token will be stored as a string.
			for(int j = 0; getline(stringStream, tempString, ' '); j++)
			{
				// Create a temporary pointer to store the data in the indexed original pointer
				// because I can't use an indexed pointer before the assignment (=) operator.
				float *tempPtr = readDataPtr+i*xDim+j;
				*tempPtr = atof(tempString.c_str());
			}
		}
		i++;
	}

	// Close the file we read the data from.
	inputFile.close();

//******************* END OF STORAGE ********************


//******************* DATA PROCESSING *******************

	for (int i = 0; i <  xDim; i++)			// For each column
	{
    	float tempMean 		= 0;			// create temporary variables that hold mean,
    	float tempMedian 	= 0;			// median,
    	float variance 		= 0;			// variance for the standard deviation,
    	float tempStdDev 	= 0;			// standard deviation,
    	float sumColData 	= 0;			// sum of all numbers in the column,
    	vector<float> floatVector;			// and a float vector to store the column temporarily for processing

    	cout << endl << "Column " << i+1 << ": ";

      	for (int j = 0; j < yDim; j++)		// For each row
      	{
      		// Stack the vector with column data
      		floatVector.push_back(*(readDataPtr+j*xDim+i));

      		// Sum up column data and store in sumColData
      		sumColData += *(readDataPtr+j*xDim+i);

      		// Display data
      		cout << " " << *(readDataPtr+j*xDim+i) << " ";		
      	}

		//************* MEAN ***************

      	tempMean = sumColData/yDim;					// Mean is the average of the numbers in the column
      	(structArrayPtr + i)->mean = tempMean;		// Assign the "mean" element of the structure

      	// Display result
      	cout << endl << "Mean: " << (structArrayPtr+i)->mean;
		//**********************************


		//************ MEDIAN **************
		// sort() function sorts the vector in ascending order by default 
      	sort(floatVector.begin(), floatVector.begin() + yDim);

      	// Check if the number of elements in the column is even using modulus.
      	if (yDim % 2 == 0)
      		// Calculate the median to be the average of the two numbers in the middle.
      		tempMedian = ((floatVector.at(yDim/2)) + (floatVector.at((yDim/2)+1))) / 2; 
      	// Else
      	else
      		// Calculate the median to be the number in the middle.
      		tempMedian = floatVector.at(yDim/2);

      	// Assign the "median" element of the structure
      	(structArrayPtr + i) -> median = tempMedian;

      	// Display result
      	cout << endl << "Median: " << (structArrayPtr + i)->median;
		//**********************************


		//****** STANDARD DEVIATION ********
      	// For each number in the vector
      	for (int x = 0; x < yDim; x++)
      		// Calculate the variance
      		variance += (pow(floatVector.at(x) - tempMean, 2)) / yDim;

      	// Assign the standard deviation to be the square root of the variance
      	tempStdDev = sqrt(variance);

      	// Assign the "stdDev" element of the structure
      	(structArrayPtr + i) -> stdDev = tempStdDev;

      	// Display result
      	cout << endl << "StdDev: " << (structArrayPtr + i)->stdDev << endl;
		//**********************************


      // Clear the vector to reuse it again for the next column
      floatVector.clear();
	}
//**************** END OF PROCESSING ******************

	// We have to free the memory allocated for the two dynamic pointers from the heap.
	free(structArrayPtr);
	free(readDataPtr);

	return 0;
}