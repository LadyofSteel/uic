#include "solveSK.h"

void solveSK(char ** board, int n){
    solver* s = solver_new();
    lbool   st;
    veci lits;
    veci_new(&lits);
    lit* begin;
    // int clk = clock(), r, c, i, j, k;

 	int row, colmn, num, block, topOrBottom;
 	int nSquared = n*n;
    int implicateArray[n];

    // Add clauses for each cell to only have one number
	// W OR X OR Y OR Z (where W,X,Y,Z represent the different values in a cell)

	// printf("\n+++++++  CELLS  +++++++ \n");

    for(row = 0; row < n; row++)
    {
	    for(colmn = 0; colmn < n; colmn++)
	    {
	    	int index = (nSquared*row)+(n*colmn);
	    	veci_delete(&lits);
	    	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
			veci_resize(&lits,0);

	    	for(num = 0; num < n; num++)
	    	{
	    		// pushes proposition into both vector AND the implicates array
	    		veci_push(&lits,toLit((index + num)));
	    		implicateArray[num] = index + num;
	    		// printf("%d OR ", index + num);
	    	}
	    	// printf("\n");

			begin = veci_begin(&lits); // get the beginning of the vector
			solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
			// Add clauses for the implicates
			// X -> ~Y = ~X OR ~Y
			createImplicates(implicateArray, s, &lits, begin, n);
		}
	}

	// Add clauses for each row to only have one instance of a number
	// W OR X OR Y OR Z (where W,X,Y,Z represent each cell in a row)

	// printf("\n+++++++  ROWS  +++++++ \n");

	for(num = 0; num < n; num++)
	{
		for(row = 0; row < n; row++)
	    {
	    	int index = ((nSquared*row) + (num));
	    	veci_delete(&lits);
	    	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
			veci_resize(&lits,0);

		    for(colmn = 0; colmn < n; colmn++)
		    {
		    	// pushes proposition into both vector AND the implicates array
	    		veci_push(&lits,toLit(index + (n*colmn)));
	    		implicateArray[colmn] = index + (n*colmn);
	    		// printf("%d OR ", index + (n*colmn));
			}
			// printf("\n");

			begin = veci_begin(&lits); // get the beginning of the vector
			solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
			// Add clauses for the implicates
			// X -> ~Y = ~X OR ~Y
			createImplicates(implicateArray, s, &lits, begin, n);
		}
	}

	// Add clauses for each column to only have one instance of a number
	// W OR X OR Y OR Z (where W,X,Y,Z represent each cell in a column)

	// printf("\n+++++++  COLUMNS  +++++++ \n");

	for(colmn = 0; colmn < n; colmn++)
	{
		for(num = 0; num < n; num++)
	    {
	    	int index = ((n*colmn) + (num));
	    	veci_delete(&lits);
	    	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
			veci_resize(&lits,0);

		    for(row = 0; row < n; row++)
		    {
		    	// pushes proposition into both vector AND the implicates array
	    		veci_push(&lits,toLit(index + (nSquared*row)));
	    		implicateArray[row] = index + (nSquared*row);
	    		// printf("%d OR ", index + (nSquared*row));
			}
			// printf("\n");

			begin = veci_begin(&lits); // get the beginning of the vector
			solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
			// Add clauses for the implicates
			// X -> ~Y = ~X OR ~Y
			createImplicates(implicateArray, s, &lits, begin, n);
		}
	}

	// Add clauses for each block to only have one instance of a number
	// W OR X OR Y OR Z (where W,X,Y,Z represent each cell in a block)

	printf("\n+++++++  BLOCKS  +++++++ \n");

	if (n == 6)
		for(topOrBottom = 0; topOrBottom < 3; topOrBottom++)
		{
			for(block = 0; block < 2; block++)
		    {
		    	for(num = 0; num < n; num++)
		    	{
		    		int index = ((2*nSquared*topOrBottom) + (3*n*block) + num);
		    		veci_delete(&lits);
			    	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
					veci_resize(&lits,0);
		    		for(row = 0; row < 2; row++)
		    		{
		    			if(row == 0){
			    			for(colmn = 0; colmn < 3; colmn++)
			    			{
						    	// pushes proposition into both vector AND the implicates array
					    		veci_push(&lits,toLit(index + (n*colmn)));
					    		implicateArray[colmn] = index + (n*colmn);
					    		printf("%d OR ", index + (n*colmn));
					    	}
					    }

					    else if(row == 1)
					    	for(colmn = 0; colmn < 3; colmn++)
		    				{
			    				int newIndex = colmn + row + 1;
						    	// pushes proposition into both vector AND the implicates array
					    		veci_push(&lits,toLit(index + (n*colmn) + (nSquared*row)));
					    		implicateArray[newIndex] = index + (n*colmn) + (nSquared*row);
					    		printf("%d OR ", index + (n*colmn + (nSquared*row)));
				    		}
			    	}

					printf("\n");

					begin = veci_begin(&lits); // get the beginning of the vector
					solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
					// Add clauses for the implicates
					// X -> ~Y = ~X OR ~Y
					createImplicates(implicateArray, s, &lits, begin, n);
		    	}
			}
		}

	/*else
		for(topOrBottom = 0; topOrBottom < sqrt(n); topOrBottom++)
		{
			for(block = 0; block < sqrt(n); block++)
		    {
		    	for(num = 0; num < n; num++)
		    	{
		    		int index = ((2*nSquared*topOrBottom) + (2*n*block) + num);
		    		veci_delete(&lits);
			    	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
					veci_resize(&lits,0);
		    		for(row = 0; row < sqrt(n); row++)
		    		{
		    			if(row == 0)
			    			for(colmn = 0; colmn < sqrt(n); colmn++)
			    			{
						    	// pushes proposition into both vector AND the implicates array
					    		veci_push(&lits,toLit(index + (4*colmn)));
					    		implicateArray[colmn] = index + (4*colmn);
					    		// printf("%d OR ", index + (4*colmn));
					    	}
					    else if(row == 1)
					    	for(colmn = 0; colmn < 2; colmn++)
			    			{
			    				int newIndex = colmn + row + 1;
						    	// pushes proposition into both vector AND the implicates array
					    		veci_push(&lits,toLit(index + (4*colmn) + (16*row)));
					    		implicateArray[newIndex] = index + (4*colmn) + (16*row);
					    		// printf("%d OR ", index + (4*colmn + (16*row)));
					    	}
			    	}

					// printf("\n");

					begin = veci_begin(&lits); // get the beginning of the vector
					solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
					// Add clauses for the implicates
					// X -> ~Y = ~X OR ~Y
					createImplicates(implicateArray, s, &lits, begin, 4);
		    	}
			}
		}
*/

	int i, j, k;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(board[i][j] != '-')
			{
				// subtract 49 from the char we get in order to obtain the right number
				int number = board[i][j] - 49;

				// defining the offset
				int offset = (nSquared*i) + (n*j) + number;

				// then push that number into the vector using the offset
				veci_delete(&lits);
				veci_new(&lits);	
				veci_resize(&lits,0);
				veci_push(&lits,toLit(offset));
				begin = veci_begin(&lits); 

				// then add the clause to the list
				solver_addclause(s, begin, begin+veci_size(&lits)); 
			}
		}
	}


	st = solver_solve(s,0,0);
	int offset = 0;
    if (st == l_True)
    {
    	printf( "\nSatisfying solution: \n" );

		for(i = 0; i < n; i++)
		{
		    for(j = 0; j < n; j++)
		    {
		        for(k = 0; k < n; k++)
		        {
		            offset = ((i*nSquared) + (j*n) + k);

		            if(s->model.ptr[offset] == l_True)
		            {
		                board[i][j] = (k + 1) + '0';
		            }
		        }
		    }
		}
	}
}

void createImplicates(int array[4], solver* s, veci *lits, lit* begin, int boardSize)
{
	int i,j;
	for(i = 0; i < boardSize; i++){
		for(j = (i+1); j < boardSize; j++){
			veci_delete(lits);
	    	veci_new(lits);	// delete the clause so we can reuse the vec and create another clause
			veci_resize(lits,0);

			veci_push(lits,lit_neg(toLit(array[i])));
			veci_push(lits,lit_neg(toLit(array[j])));
			begin = veci_begin(lits); // get the beginning of the vector
			solver_addclause(s, begin, begin+veci_size(lits)); // add the clause to the list
			// printf("~%d OR ~%d added\n",array[i], array[j]);
		}
	}
}