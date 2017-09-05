Course: CS 201
Project #: 1
Course Instructor: Prof. Mitchell D. Theys


Student Name: Ammar Subei
Source file name: asubei2.cpp

Program Info:
Reads in a 2D matrix from a user-specified file, then calculates and displays the mean, median, and standard deviation of each column in that 2D matrix.

Methods:
Used malloc for the dynamic memory allocation of two arrays. One array stores the data read from user-specified file, and the other contains structures that hold the mean, median, and standard deviation of each column in the file. The data in the file is read row by row, and is processed column by column. I used simple pointer arithmetic to navigate through the array exactly how I wanted; column by column. For each column, I utilized a vector to hold the values for calculations. After that, I did all my calculations and stored them in an array of structs and displayed them.

Problems encountered:
At first, I tried to solve the problem head-on, which proved to be a bad plan and somewhat savage-like. I went through a lot, A LOT, of confusions, mainly about arrays, pointers, and pointer arithmetic. My initial plans were completely off and didn't help solve any problem. I didn't fully understand how to calculate the median and standard deviation, and I didn't figure out how to process the data column by column when I read them row by row! I thought about using double pointers (pointer to pointer) to solve this problem, but I realized it was overkill and too confusing. I almost lost hope...

Solutions:
I took the professor's advice and started small and slow. I first learned how to calculate the mean, median, and standard deviation of a set of numbers. I then tried building the project using static arrays and array notations, and neglected the use of pointers and dynamic memory. Then, I learned about dynamic memory allocation using malloc() and calloc() functions. Vectors helped a lot in calculating the mean, median, and standard deviations. I also utilized the sort() function to find the median very easily. Lastly, I used pointers and some pointer arithmetic to navigate through the array.

Testing:
I used GDB to put break points on specific lines where I suspect an error might occur. I also used valgrind to make sure there are no errors or issues in memory that I wasn't aware of. For the data calculations, I used the 5x3 matrix given by our TA, Natawut, on Piazza. The file, named "input.txt", is included in this archive too.

