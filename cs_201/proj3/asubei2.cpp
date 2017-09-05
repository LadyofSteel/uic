#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
using namespace std;

/*
Course: CS 201
Project #: 3
Course Instructor: Prof. Mitchell D. Theys

Student Name: Ammar Subei
Source file name: asubei2.cpp

Program Info:
Postfix expression evaluator
Reads in a postfix expression by user, with both operators and operands 
delimited by space characters. Store that expression in a tree, then output 
expressions in both infix and prefix. After that, the program should ouput 
the resulting evaluation of the expression. 
All using recursive functions, trees, and stacks.
*/

// pointers to the two different structs
typedef struct STACK *STACKPTR;
typedef struct TREE *TREEPTR;

struct TREE {
	TREEPTR leftChild;
	TREEPTR rightChild;
	string value;
};

struct STACK{
	TREEPTR tree;
	STACKPTR next;
};

// checks if the given string is an operator
bool checkIfOperator(string s){
	if(s == "-" || s == "+" || s == "*" || s == "/" || s == "&" || s == "|" || s == "^")
		return true;
	else
		return false;
}

// prints the tree in infix
void printInfix (TREEPTR T){
	if (T==NULL)
		return;
	else{
		printInfix(T->leftChild);
		cout << T->value << ' ';
		printInfix(T->rightChild);
	}
}

// prints the tree in prefix
void printPrefix (TREEPTR T){
	if (T==NULL)
		return;
	else{
		cout << T->value << ' ';
		printPrefix(T->leftChild);
		printPrefix(T->rightChild);
	}
}

// prints the tree in postfix
void printPostfix (TREEPTR T){
	if (T==NULL)
		return;
	else{
		printPostfix(T->leftChild);
		printPostfix(T->rightChild);
		cout << T->value << ' ';
	}
}

// evaluates the tree 
float evaluateExpression(TREEPTR T){
	float result;
	// base case
	// if not operator, return float type of value
	if(!checkIfOperator(T->value))
		return atof((T->value).c_str());

	// otherwise, perform operation accordingly
	else{
		char operation = *((T->value).c_str());

		switch(operation){
		case '+':
			return ( (evaluateExpression(T->leftChild)) + (evaluateExpression(T->rightChild)) );
			break;
		case '-':
			return ( (evaluateExpression(T->leftChild)) - (evaluateExpression(T->rightChild)) );
			break;
		case '*':
			return ( (evaluateExpression(T->leftChild)) * (evaluateExpression(T->rightChild)) );
			break;
		case '/':
			return ( (evaluateExpression(T->leftChild)) / (evaluateExpression(T->rightChild)) );
			break;
		case '&':
			return ( ((int)evaluateExpression(T->leftChild)) & ((int)evaluateExpression(T->rightChild)) );
			break;
		case '|':
			return ( ((int)evaluateExpression(T->leftChild)) | ((int)evaluateExpression(T->rightChild)) );
			break;
		case '^':
			return ( ((int)evaluateExpression(T->leftChild)) ^ ((int)evaluateExpression(T->rightChild)) );
			break;
		}
	}
}

// pushes nodes into the stack
STACKPTR pushNode (STACKPTR head, string inputOperand){
	TREEPTR tmpTree = new(struct TREE);
	tmpTree->value = inputOperand;
	tmpTree->leftChild = NULL;
	tmpTree->rightChild = NULL;

	if(head){
		STACKPTR tmpptr = new(struct STACK);
		tmpptr->next = head;
		head = tmpptr;
	}
	else
		head = new(struct STACK);
	
	head->tree = tmpTree;
	return head;
}

// pops the last two nodes from stack, and creates a tree with 
// operator as root
STACKPTR mergeNodes(STACKPTR head, string inputOperator){
	TREEPTR tmpTree = new(struct TREE);
	tmpTree->value = inputOperator;
	tmpTree->rightChild = head->tree;
	tmpTree->leftChild = head->next->tree;

	STACKPTR tmpptr = new(struct STACK);
	tmpptr = head;
	head = head->next;
	head->tree = tmpTree;
	free(tmpptr);
	return head;
}


int main(){
	float finalResult;
	STACKPTR head = NULL;
	string input;
	cout << "Please enter a valid postfix expression: ";

	// read input expression
	getline(cin, input);
	// make the input line a stream
	istringstream ss(input);
	string stringElement;

	// store each element in stringElement, with
	// each element delimited by space
	while(getline(ss, stringElement, ' ')){
		// if it's an operator
		if(checkIfOperator(stringElement))
			// pop last two nodes and make operator root of tree
			head = mergeNodes(head, stringElement);
		else
			// otherwise, push node into stack
			head = pushNode(head, stringElement);
	}

	// print all different expressions
	cout << endl << "Postfix expression: ";
	printPostfix(head->tree);
	cout << endl << "Infix expression: ";
	printInfix(head->tree);
	cout << endl << "Prefix expression: ";
	printPrefix(head->tree);
	
	// evaluate expression
	finalResult = evaluateExpression(head->tree);

	cout << endl << "Evaluation: " << finalResult << endl;
}