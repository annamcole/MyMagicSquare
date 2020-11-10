////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
// Other Files:      none TODO POSSIBLY NEED TO CHANGE THIS
// Semester:         CS 354 Fall 2020
//
// Author:           Anna Stephan
// Email:            amstephan@wisc.edu
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;      // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
    int size; // size of array
    
    printf("Enter magic square's size (odd integer >= 3)\n");
    scanf("%i", &size);
    // check for errors
    if( size%2 == 0 || size < 3) 
    {
        if(size%2 == 0) 
        {
            perror("Size must be odd.\n");
            exit(1);
        }
        if(size < 3) 
        {
            perror("Size must be >= 3.\n"); 
            exit(1);
        }
        return -1;
    }
    return size;
} 
  
/* Makes a magic square of size n using the alternate 
 * Siamese magic square algorithm from assignment and 
 * returns a pointer to the completed MagicSquare struct.
 *
 * n the number of rows and columns
 */
MagicSquare *generateMagicSquare(int n) {
    int row;         // current row
    int col;         // current column
    int nextRow;     // next row position
    int nextCol;     // next column position
    
    // allocate board memory
    int **board = malloc(sizeof(int*)*n);    // 2D array to contain magic numbers
    if(board == NULL)
    {
        perror("Error, memory not allocated.");
        exit(1);
    }
    for(int i = 0; i < n; i++) 
    {
        *(board+i) = malloc(sizeof(int)*n);
        if(*(board+i) == NULL)
        {
            perror("Error, memory not allocated.");
            exit(1);
        }
    }

    // initialize board to all zeros for later check
    for(int k = 0; k < n; k++) 
    {
        for(int p = 0; p < n; p++) 
        {
            *(*(board+k)+p) = 0;
        }
    }

    // calculate starting position
    row = n/2;
    col = n-1;
    nextRow = row + 1;
    nextCol = col + 1;
    // fill in board
    for(int m = 1; m <= (n*n); m++)
    {  
        *(*(board+row)+col) = m;
        
        nextRow = row + 1;
        nextCol = col + 1;
        
        // position wrap-around
        if( nextRow == n && nextCol == n) 
        {
            nextRow--;
            nextCol -= 2;
            
            row = nextRow;
            col = nextCol;
            continue;
        } else if(nextRow == n || nextCol == n) 
        {
          if(nextRow == n)
              nextRow = 0;
          if(nextCol == n)
              nextCol = 0; 
        }  
            
        // check if next position is full
        if( *(*(board+nextRow)+nextCol) != 0 ) 
        {
            nextCol -=2;
            nextRow--;
        }
        
        row = nextRow;
        col = nextCol;

    }
    
    MagicSquare *square = (MagicSquare*)malloc(sizeof(MagicSquare)); // magic square
    square->size = n;
    square->magic_square = board;
    
    return square;    
} 

/* Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
    FILE *fp = fopen(filename, "w");    // output file
    if(fp == NULL) 
    {
        perror("Couldn't open file");
        exit(1);
    }
    
    int size = magic_square->size;     // size of array
    int **board = magic_square->magic_square;    // 2D array to write to output file
    
    fprintf(fp, "%i\n", size);
    for(int i = 0; i < size; i++) 
    {
        for(int j = 0; j < size; j++) 
        {
            int num = *(*(board+i)+j);
            if(j == 0) 
              fprintf(fp, "%i", num );
            else 
              fprintf(fp, ", %i", num );
        }
        fprintf(fp, "\n");
    }    
    
    fclose(fp);
}

/* Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[]) {
    // Check input arguments to get output filename
    if(argc != 2) 
      perror("Incorrect number of arguments!");

    // Get magic square's size from user
    int size = getSize();

    // Generate the magic square
    MagicSquare *square = generateMagicSquare(size);

    // Output the magic square
    fileOutputMagicSquare(square, argv[1]);
    
    // Free allocated memory
    int **board = square->magic_square;
    for(int i = 0; i < size; i++)
    {
        *(board+i) = NULL;
    }
    free(board);
    free(square);
    
    return 0;
} 


                                                         
//				myMagicSquare.c      

