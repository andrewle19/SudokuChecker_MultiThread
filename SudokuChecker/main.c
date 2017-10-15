/*
 AUTHOR: Andrew Le and Andrew Rivada
 Email: andrewle19@csu.fullerton.edu
 Date: 10/15/17

 Using Multithreaded programming to check if a sudoku solution is valid
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct parameters{
    int srow; // starting row
    int scol; // starting column
    int row; // ending row
    int col; // ending col
    int threadnum; // the number in the thread
} parameters;

// valid checker for 11 threads if all are 1 then soltion is valid else it is not
int valid[11] = {1,1,1,1,1,1,1,1,1,1,1};

// Sudoku puzzle to be solved
int sudoku[9][9] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

// resets check array to all 0
void reset_check(int array[],int size)
{
    for(int i = 0; i < size; i++){
        array[i] = 0;
    }
}

// thread function that checks if the columns in sudoku are valid
void * checkColumn(void *params)
{
    // check array to check 9 spots of column
    int check[9] = {0,0,0,0,0,0,0,0,0};

    // loop through all the columns
    for(int i = 0; i < 9; i++)
    {
        reset_check(check, 9);
       
        for(int j = 0; j < 9; j++){
            // grab index of column
            int index = sudoku[j][i]-1;
            // sets the check array to make sure each checked section has integer 0...9
            if(check[index] == 0){
                check[index] = sudoku[j][i];
            }
            // checks if the spots have a number from 0-9 if not then makes the solution invalid
            if(sudoku[j][i] < 1 || sudoku[j][i] > 9){
                valid[1] = 0;
            }
            
        }
        
        // checks the check array to make sure check section has integers 0...9 if not solution invalid
        for (int k = 0; k < 9; k++) {
            if(check[k] == 0){
                valid[1] = 0;
            }
        }
        
    }
    pthread_exit(0);
}

// thread function that checks if the rows in sudoku are valid
void *checkRow(void *params)
{
    // check array to check 9 spots of column
    int check[9] = {0,0,0,0,0,0,0,0,0};
    
    for(int i = 0; i < 9; i++){
        reset_check(check, 9);
        
        for(int j = 0; j < 9; j++){

            int index = sudoku[i][j]-1;
            // sets the check array to make sure each checked section has integer 0...9
            if(check[index] == 0){
                check[index] = sudoku[i][j];
            }
            
            //checks if spots have a number from 0-9 if not that makes the solution invalid
            if(sudoku[i][j] < 1 || sudoku[i][j] > 9){

                valid[0] = 0;
            }
        }
        
        // checks the check array to make sure check section has integers 0...9 if not solution invalid
        for (int k = 0; k < 9; k++) {
            if(check[k] == 0){

                valid[0] = 0;
            }
        }
        
    }
    pthread_exit(0);
}

// thread function that checks if the subsection is valid
void *checkSubSection(void *params)
{
    // get the parameters
    parameters *args = (parameters*) params;

    
    // check array to check 9 spots of column
    int check[9] = {0,0,0,0,0,0,0,0,0};
    
    // Checking the subsection based on the arguments passed
    for(int i = args->srow; i < args->row; i++){
        
        for(int j = args->scol; j < args->col; j++){
            
            int index = sudoku[i][j]-1;
            // sets the check array to make sure each checked section has integer 0...9
            if(check[index] == 0){
                check[index] = sudoku[i][j];
            }
            //checks if spots have a number from 0-9 if not that makes the solution invalid
            if(sudoku[i][j] < 1 || sudoku[i][j] > 9){
                printf("here");
                printf("invalid num %i, i:%i,j:%i\n",sudoku[i][j],i,j);
                valid[args->threadnum] = 0;
            }
        }

    }
    // checks the check array to make sure check section has integers 0...9 if not solution invalid
    for (int k = 0; k < 9; k++) {
        if(check[k] == 0){
            valid[args->threadnum] = 0;
           // printf("invalid num%i\n",k);
        }
    }
    pthread_exit(0);
}


int main(int argc, const char * argv[]) {

    // bool to determine if solution is valid
    int correct = 1;
    
    // declare 9 parameters for the 9 parameters that will be used for checking nine 3x4 sections
    parameters param3,param4,param5,param6,param7,param8,param9,param10,param11;
    
    // NOTE theadnum for parameters will be thread-1
    
    // declare parameter for thread 3
    param3.srow = 0;
    param3.row = 3;
    param3.scol = 0;
    param3.col = 3;
    param3.threadnum = 2;
    
    // declare parameter for thread 4
    param4.srow = 0;
    param4.row = 3;
    param4.scol = 3;
    param4.col = 6;
    param4.threadnum = 3;
    
    // declare parameter for thread 5
    param5.srow = 0;
    param5.row = 3;
    param5.scol = 6;
    param5.col = 9;
    param5.threadnum = 4;
    
    // declare parameter for thread 6
    param6.srow = 3;
    param6.row = 6;
    param6.scol = 0;
    param6.col = 3;
    param6.threadnum = 5;
    
    // declare parameter for thread 7
    param7.srow = 3;
    param7.row = 6;
    param7.scol = 3;
    param7.col = 6;
    param7.threadnum = 6;
    
    // declare parameter for thread 8
    param8.srow = 3;
    param8.row = 6;
    param8.scol = 6;
    param8.col = 9;
    param8.threadnum = 7;
    
    // declare parameter for thread 9
    param9.srow = 6;
    param9.row = 9;
    param9.scol = 0;
    param9.col = 3;
    param9.threadnum = 8;
    
    // declare parameter for thread 10
    param10.srow = 6;
    param10.row = 9;
    param10.scol = 3;
    param10.col = 6;
    param10.threadnum = 9;
   
    // declare parameter for thread 11
    param11.srow = 6;
    param11.row = 9;
    param11.scol = 6;
    param11.col = 9;
    param11.threadnum = 10;
    
    
    // create 11 total threads
    // thread 3-11 will be used for nine 3X3 subsections
    pthread_t thrd1, thrd2, thrd3,thrd4,thrd5,thrd6,thrd7,thrd8,thrd9,thrd10,thrd11;
    
    
    
    
    
    // create 11 threads
    // check row
    pthread_create(&thrd1, NULL, checkRow, NULL);
    //check column
    pthread_create(&thrd2, NULL, checkColumn, NULL);
    // check all 3x3 subsections
    pthread_create(&thrd3, NULL, checkSubSection, &param3);
    pthread_create(&thrd4, NULL, checkSubSection, &param4);
    pthread_create(&thrd5, NULL, checkSubSection, &param5);
    pthread_create(&thrd6, NULL, checkSubSection, &param6);
    pthread_create(&thrd7, NULL, checkSubSection, &param7);
    pthread_create(&thrd8, NULL, checkSubSection, &param8);
    pthread_create(&thrd9, NULL, checkSubSection, &param9);
    pthread_create(&thrd10, NULL, checkSubSection, &param10);
    pthread_create(&thrd11, NULL, checkSubSection, &param11);
    
    
    // join up all the threads
    pthread_join(thrd1, NULL);
    pthread_join(thrd2, NULL);
    pthread_join(thrd3, NULL);
    pthread_join(thrd4, NULL);
    pthread_join(thrd5, NULL);
    pthread_join(thrd6, NULL);
    pthread_join(thrd7, NULL);
    pthread_join(thrd8, NULL);
    pthread_join(thrd9, NULL);
    pthread_join(thrd10, NULL);
    pthread_join(thrd11, NULL);
    
    // check if the solution was valid after all the thread checks
    for(int i = 0; i < 11; i++)
    {
        if(valid[i] == 0)
        {
            correct = 0;
        }
    }
    
    // print appropriate message
    if(correct){
        printf("Solution is valid\n");
    } else {
        printf("Solution is invalid\n");
    }

    
    return 0;
}
