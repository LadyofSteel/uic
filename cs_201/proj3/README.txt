Course: CS 201
Project #: 3
Course Instructor: Prof. Mitchell D. Theys


Student Name: Ammar Subei
Source file name: asubei2.cpp

Program Info:
Postfix expression evaluator
Reads in a postfix expression by user, with both operators and operands delimited by space characters. Store that expression in a tree, then output expressions in both infix and prefix. After that, the program should ouput the resulting evaluation of the expression. All using recursive functions, trees, and stacks.

Methods:
I followed the professor's algorithm for building the tree given a postfix expression. First, I defined two different structures. One STACK struct, and one TREE struct. The STACK struct will only be used for the process of building the tree. So, the STACK struct contains a pointer to the next element, and a TREE struct. The TREE struct contains two other TREE structs, leftChild and rightChild, and a string that contains the value (either operand or operator).

The program fills the stack with operands until it reaches an operator, then it'll pop the last two elements and create a tree with the operator as root, and return the new tree into the stack. The first element popped would be the rightChild of the tree, and the second element popped would be the leftChild. I did that because I will be reading the tree from left to right.

After that, printing out the postfix, infix, and prefix expression were pretty straight-forward as discussed in class. Evaluating the expression was a bit tougher than expected. I use a function checkIfOperator to check if the value I read in the expression is an operator or not. Using checkIfOperator in the evaluateExpression function, I store the operator in a char and make a switch-case statement. In each different case, I recursively call evaluateExpression for leftChild, place operator, then call evaluateExpression for rightChild. Of course, the base case for this recursive function is when the value I read is not an operator, in which case the function returns the float number of the value.

Problems encountered:
I encountered a couple of seg-faults due to me confusingly using multiple pointers that point to different structs and entangling them together. They were quickly fixed though...

Solutions:
I used GDB to figure out the seg-fault problem I was encountering from the pointers and faulty memory allocations.

Testing:
I decided to be systematic and professional with my coding and documentation. I created a private repository on BitBucket and used Git to create multiple different commits at multiple stages of my program. I also used a makefile that compiles and runs my program using multiple test cases. All are included in the .zip file. All you need to do to make use of the makefile is to type in "make" in the same directory the Makefile is located. I also used the sample expression found on the Piazza page.