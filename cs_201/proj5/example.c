#include <stdio.h>
#include <stdlib.h>
#include "solver.h"
#include "vec.h"


void printStats(stats* stats, int cpu_time)
{
    
    printf("restarts          : %12d\n", stats->starts);
   
    printf("conflict literals : %12.0f(%9.2f %% deleted  )\n", (double)stats->tot_literals, (double)(stats->max_literals - stats->tot_literals) * 100.0 / (double)stats->max_literals);
    
}

int main(int argc, char *argv[]) {

    solver* s = solver_new();
    lbool   st;
    veci lits;
    veci_new(&lits);
    lit* begin;
    int clk = clock();

/*
The above is necessary to get everything setup with minisat. 
We will then create expressions by pushing the proposition, or its complement
to the expression and then add the expression to the set of expressions 
we know are true.
*/

/* we are going to solve the following problem
The police have three suspects for the murder of Mr. Cooper: 
Mr. Smith, Mr. Jones, and Mr. Williams. 
Smith, Jones, and Williams each declare that they did not 
kill Cooper. Smith also states that Cooper was a friend of 
Jones and that Williams disliked him. Jones also states that 
he did not know Cooper and that he was out of town the day 
Cooper was killed. Williams also states that he saw both Smith 
and Jones with Cooper the day of the killing and that either 
Smith or Jones must have killed him. Can you determine who the 
murderer was if one of the three men is guilty, the two innocent
 men are telling the truth, but the statements of the guilty man
  may or may not be true?
*/
/* propositions
0   - Mr Smith killed Mr Cooper
1   - Mr Jones killed Mr Cooper
2   - Mr Williams killed Mr Cooper
3   - Smith is telling the truth
4   - jones is telling the truth
5   - williams is telling the truth
6   - Cooper was a friend of Jones
7   - Williams disliked cooper
8   - jones knew cooper
9   - jones out of town
10  - smith seen with cooper
11  - jones seen with cooper
*/
/* assumptions
only 1 killed Mr Cooper
0 OR 1 OR 2
0 --> ~1 == ~0 OR ~1
0 --> ~2 == ~0 OR ~2
1 --> ~0 == ~1 OR ~0 << not needed
1 --> ~2 == ~1 OR ~2
2 --> ~0 == ~2 OR ~0 << not needed
2 --> ~1 == ~2 OR ~1 << not needed
only 1 is lying
~3 OR ~4 OR ~5
~3 --> 4 == 3 OR 4
~3 --> 5 == 3 OR 5
~4 --> 3 == 4 OR 3 << not needed
~4 --> 5 == 4 OR 5
~5 --> 3 == 5 OR 3 << not needed
~5 --> 4 == 5 OR 4 << not needed
killer is lying
~0 --> 3 == 0 OR 3
~1 --> 4 == 1 OR 4
~2 --> 5 == 2 OR 5

6 --> 8
11 --> 8
9 --> ~1

*/
/* Facts
3 --> 6 == ~3 OR 6
3 --> 7 == ~3 OR 7
4 --> ~8 == ~4 OR ~8
4 --> 9 == ~4 OR 9
5 --> 10 == ~5 OR 10
5 --> 11 == ~5 OR 11
*/

//0 OR 1 OR 2
veci_push(&lits,toLit(0)); 
veci_push(&lits,toLit(1));
veci_push(&lits,toLit(2)); 
begin = veci_begin(&lits); // get the beginning of the vector
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause
printf("0 OR 1 OR 2 added\n");
veci_new(&lits);
veci_resize(&lits,0);
veci_push(&lits,lit_neg(toLit(0)));
veci_push(&lits,lit_neg(toLit(1)));
begin = veci_begin(&lits); // get the beginning of the vector
printf("vector 2 size %d\n",veci_size(&lits));
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("~0 OR ~1 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause
veci_new(&lits);
veci_resize(&lits,0); 
veci_push(&lits,lit_neg(toLit(0)));
veci_push(&lits,lit_neg(toLit(2)));
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("~0 OR ~2 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause
veci_new(&lits);
veci_resize(&lits,0); 
veci_push(&lits,lit_neg(toLit(1)));
veci_push(&lits,lit_neg(toLit(2)));
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("~1 OR ~2 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause
veci_new(&lits);
veci_resize(&lits,0);
veci_push(&lits,lit_neg(toLit(3))); 
veci_push(&lits,lit_neg(toLit(4)));
veci_push(&lits,lit_neg(toLit(5))); 
begin = veci_begin(&lits); // get the beginning of the vector
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause
printf("~3 OR ~4 OR ~5 added\n");
//~0 --> 3 == 0 OR 3
veci_new(&lits);
veci_resize(&lits,0);
veci_push(&lits,(toLit(0)));
veci_push(&lits,(toLit(3)));
begin = veci_begin(&lits); // get the beginning of the vector
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("0 OR 3 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause

//~1 --> 4 == 1 OR 4
veci_new(&lits);
veci_resize(&lits,0);
veci_push(&lits,(toLit(1)));
veci_push(&lits,(toLit(4)));
begin = veci_begin(&lits); // get the beginning of the vector
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("1 OR 4 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause

//~2 --> 5 == 2 OR 5
veci_new(&lits);
veci_resize(&lits,0);
veci_push(&lits,(toLit(2)));
veci_push(&lits,(toLit(5)));
begin = veci_begin(&lits); // get the beginning of the vector
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("2 OR 5 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause

//6 --> 8 == ~6 OR 8
veci_new(&lits);
veci_resize(&lits,0);
veci_push(&lits,lit_neg(toLit(6)));
veci_push(&lits,toLit(8));
begin = veci_begin(&lits); // get the beginning of the vector
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("~6 OR 8 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause

//11 --> 8 == ~11 OR 8
veci_new(&lits);
veci_resize(&lits,0);
veci_push(&lits,lit_neg(toLit(11)));
veci_push(&lits,toLit(8));
begin = veci_begin(&lits); // get the beginning of the vector
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("~11 OR 8 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause

//9 --> ~1 == ~9 OR ~1
veci_new(&lits);
veci_resize(&lits,0);
veci_push(&lits,lit_neg(toLit(9)));
veci_push(&lits,lit_neg(toLit(1)));
begin = veci_begin(&lits); // get the beginning of the vector
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("~9 OR ~1 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause

veci_new(&lits);
veci_resize(&lits,0);
veci_push(&lits,toLit(3));
veci_push(&lits,toLit(4));
begin = veci_begin(&lits); // get the beginning of the vector
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("3 OR 4 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause
veci_new(&lits);
veci_resize(&lits,0); 
veci_push(&lits,(toLit(3)));
veci_push(&lits,(toLit(5)));
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("3 OR 5 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause
veci_new(&lits);
veci_resize(&lits,0); 
veci_push(&lits,(toLit(4)));
veci_push(&lits,(toLit(5)));
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("4 OR 5 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause
//3 --> 6 == ~3 OR 6
veci_new(&lits);
veci_resize(&lits,0); 
veci_push(&lits,lit_neg(toLit(3)));
veci_push(&lits,(toLit(6)));
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("3 OR 6 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause

//3 --> 7 == ~3 OR 7
veci_new(&lits);
veci_resize(&lits,0); 
veci_push(&lits,lit_neg(toLit(3)));
veci_push(&lits,(toLit(7)));
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("~3 OR 7 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause
//4 --> ~8 == ~4 OR ~8
veci_new(&lits);
veci_resize(&lits,0); 
veci_push(&lits,lit_neg(toLit(4)));
veci_push(&lits,lit_neg(toLit(8)));
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("~4 OR ~8 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause
//4 --> 9 == ~4 OR 9
veci_new(&lits);
veci_resize(&lits,0); 
veci_push(&lits,lit_neg(toLit(4)));
veci_push(&lits,(toLit(9)));
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("~4 OR 9 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause
//5 --> 10 == ~5 OR 10
veci_new(&lits);
veci_resize(&lits,0); 
veci_push(&lits,lit_neg(toLit(5)));
veci_push(&lits,(toLit(10)));
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("~5 OR 10 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause
//5 --> 11 == ~5 OR 11
veci_new(&lits);
veci_resize(&lits,0); 
veci_push(&lits,lit_neg(toLit(5)));
veci_push(&lits,(toLit(11)));
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("~5 OR 11 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause


// if we new that prop. 1 is true, we would add an expression 
// with just that literal/prop.
/*
veci_new(&lits);
veci_resize(&lits,0); 
veci_push(&lits,(toLit(1)));
solver_addclause(s, begin, begin+veci_size(&lits)); // add the clause to the list
printf("1 added\n");
veci_delete(&lits); // delete the clause so we can reuse the vec and create another clause

*/ 

 
 /* once all the expressions (clauses) have been added to s, 
 we then call the solver */
 st = solver_solve(s,0,0);
 printStats(&s->stats, clock() - clk);
 printf("\n");
 printf("%d",st);
 printf("model size %d\n",s->model.size);
 // we now check to see if a solution was found
    if ( st == l_True )
    {
        int k;
        printf( "\nSatisfying solution: " );
        for ( k = 0; k < s->model.size; k++ )  
            printf( "proposition%d=%d ", k, s->model.ptr[k] == l_True );
        printf( "\n" );
    }
 
    




	return 0;


}
