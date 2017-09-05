#include "solveSK.h"

/*void printStats(stats* stats, int cpu_time)
{
    
    printf("restarts          : %12d\n", stats->starts);
   
    printf("conflict literals : %12.0f(%9.2f %% deleted  )\n", (double)stats->tot_literals, (double)(stats->max_literals - stats->tot_literals) * 100.0 / (double)stats->max_literals);
    
}*/

int main(int argc, char *argv[]){
    solver* s = solver_new();
    lbool   st;
    veci lits;
    veci_new(&lits);
    lit* begin;
    // int clk = clock();
    int row, colmn, num, block, topOrBottom;
 	int nSquared = n*n;
    int implicateArray[n];

    // Add clauses for each cell to only have one number
	// W OR X OR Y OR Z (where W,X,Y,Z represent the different values in a cell)

	printf("\n+++++++  CELLS  +++++++ \n");

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
	    		printf("%d OR ", index + num);
	    	}
	    	printf("\n");

			begin = veci_begin(&lits); // get the beginning of the vector
			solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
			// Add clauses for the implicates
			// X -> ~Y = ~X OR ~Y
			createImplicates(implicateArray, s, &lits, begin, n);
		}
	}

	// Add clauses for each row to only have one instance of a number
	// W OR X OR Y OR Z (where W,X,Y,Z represent each cell in a row)

	printf("\n+++++++  ROWS  +++++++ \n");

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
	    		printf("%d OR ", index + (n*colmn));
			}
			printf("\n");

			begin = veci_begin(&lits); // get the beginning of the vector
			solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
			// Add clauses for the implicates
			// X -> ~Y = ~X OR ~Y
			createImplicates(implicateArray, s, &lits, begin, n);
		}
	}

	// Add clauses for each column to only have one instance of a number
	// W OR X OR Y OR Z (where W,X,Y,Z represent each cell in a column)

	printf("\n+++++++  COLUMNS  +++++++ \n");

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
	    		printf("%d OR ", index + (nSquared*row));
			}
			printf("\n");

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
		    		int index = ((3*nSquared*topOrBottom) + (2*n*block) + num);
		    		veci_delete(&lits);
			    	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
					veci_resize(&lits,0);
		    		for(row = 0; row < 2; row++)
		    		{
		    			if(row == 0)
			    			for(colmn = 0; colmn < 2; colmn++)
			    			{
						    	// pushes proposition into both vector AND the implicates array
					    		veci_push(&lits,toLit(index + (4*colmn)));
					    		implicateArray[colmn] = index + (4*colmn);
					    		printf("%d OR ", index + (4*colmn));
					    	}
					    else if(row == 1)
					    	for(colmn = 0; colmn < 2; colmn++)
		    				{
			    				int newIndex = colmn + row + 1;
						    	// pushes proposition into both vector AND the implicates array
					    		veci_push(&lits,toLit(index + (4*colmn) + (16*row)));
					    		implicateArray[newIndex] = index + (4*colmn) + (16*row);
					    		printf("%d OR ", index + (4*colmn + (16*row)));
				    		}
			    	}

					printf("\n");

					begin = veci_begin(&lits); // get the beginning of the vector
					solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
					// Add clauses for the implicates
					// X -> ~Y = ~X OR ~Y
					createImplicates(implicateArray, s, &lits, begin, 4);
		    	}
			}
		}
	for(topOrBottom = 0; topOrBottom < 2; topOrBottom++)
	{
		for(block = 0; block < 2; block++)
	    {
	    	for(num = 0; num < 4; num++)
	    	{
	    		int index = ((32*topOrBottom) + (8*block) + num);
	    		veci_delete(&lits);
		    	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
				veci_resize(&lits,0);
	    		for(row = 0; row < 2; row++)
	    		{
	    			if(row == 0)
		    			for(colmn = 0; colmn < 2; colmn++)
		    			{
					    	// pushes proposition into both vector AND the implicates array
				    		veci_push(&lits,toLit(index + (4*colmn)));
				    		implicateArray[colmn] = index + (4*colmn);
				    		printf("%d OR ", index + (4*colmn));
				    	}
				    else if(row == 1)
				    	for(colmn = 0; colmn < 2; colmn++)
		    			{
		    				int newIndex = colmn + row + 1;
					    	// pushes proposition into both vector AND the implicates array
				    		veci_push(&lits,toLit(index + (4*colmn) + (16*row)));
				    		implicateArray[newIndex] = index + (4*colmn) + (16*row);
				    		printf("%d OR ", index + (4*colmn + (16*row)));
				    	}
		    	}

				printf("\n");

				begin = veci_begin(&lits); // get the beginning of the vector
				solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
				// Add clauses for the implicates
				// X -> ~Y = ~X OR ~Y
				createImplicates(implicateArray, s, &lits, begin, 4);
	    	}
		}
	}

	/* Manually inserting the facts for testing purposes. The program works perfectly.

	// p(0,0,1)
	veci_delete(&lits);
	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
	veci_resize(&lits,0);
	veci_push(&lits,toLit(0));
	begin = veci_begin(&lits); // get the beginning of the vector
	solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list

	//p(0,3,4)
	veci_delete(&lits);
	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
	veci_resize(&lits,0);
	veci_push(&lits,toLit(15));
	begin = veci_begin(&lits); // get the beginning of the vector
	solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list

	//p(1,1,4)
	veci_delete(&lits);
	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
	veci_resize(&lits,0);
	veci_push(&lits,toLit(24));
	begin = veci_begin(&lits); // get the beginning of the vector
	solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list

	//p(1,3,2)
	veci_delete(&lits);
	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
	veci_resize(&lits,0);
	veci_push(&lits,toLit(29));
	begin = veci_begin(&lits); // get the beginning of the vector
	solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list

	//p(2,0,4)
	veci_delete(&lits);
	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
	veci_resize(&lits,0);
	veci_push(&lits,toLit(35));
	begin = veci_begin(&lits); // get the beginning of the vector
	solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list

	//p(2,2,2)
	veci_delete(&lits);
	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
	veci_resize(&lits,0);
	veci_push(&lits,toLit(41));
	begin = veci_begin(&lits); // get the beginning of the vector
	solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list

	//p(3,0,2)
	veci_delete(&lits);
	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
	veci_resize(&lits,0);
	veci_push(&lits,toLit(49));
	begin = veci_begin(&lits); // get the beginning of the vector
	solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list

	//p(3,3,1)
	veci_delete(&lits);
	veci_new(&lits);	// delete the clause so we can reuse the vec and create another clause
	veci_resize(&lits,0);
	veci_push(&lits,toLit(60));
	begin = veci_begin(&lits); // get the beginning of the vector
	solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
*/

	st = solver_solve(s,0,0);
	int offset = 0;
	int i, j, k;
	for(i = 0; i < n; i++)
	{
	    for(j = 0; j < n; j++)
	    {
	        for(k = 0; k < n; k++)
	        {
	            offset = ((i * nSquared) + (j * n) + k);

	            if(s->model.ptr[offset] == l_True)
	            {
	                board[i][j] = (k + 1) + '0';
	            }
	        }
	    }
	}
	// printStats(&s->stats, clock() - clk);
	printf("\n");
	printf("%d",st);
	printf("model size %d\n",s->model.size);
	// we now check to see if a solution was found
    if ( st == l_True )
    {
        int k;
        printf( "\nSatisfying solution: " );
        for ( k = 0; k < s->model.size; k++ ){
            printf( "\n proposition%d=%d", k, s->model.ptr[k] == l_True );
	    }

        printf( "\n" );
    }
 
	return 0;
}