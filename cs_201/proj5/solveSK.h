#ifndef SOLVESK_H_INCLUDED
#define SOLVESK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vec.h"
#include "solver.h"

void createImplicates(int array[4], solver* s, veci *lits, lit* begin, int boardSize);
void solveSK(char ** board, int n);

#endif // SOLVESK_H_INCLUDED
