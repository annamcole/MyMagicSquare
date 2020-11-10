////////////////////////////////////////////////////////////////////////////////
// Main File:        n_in_a_row.c
// This File:        n_in_a_row.c
// Other Files:      none
// Semester:         CS 354 Fall 2020
//
// Author:           Anna Stephan
// Email:            amstephan@wisc.edu
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *DELIM = ",";  // commas ',' are a common delimiter character for data strings
     
/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size) {      
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1) {
        printf("Error in reading the file.\n");
        exit(1);
    }

    char *token = NULL;
    token = strtok(line, DELIM);
    *size = atoi(token);
}       
 
   
  
/* Returns 1 if and only if the board is in a valid state.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * size: number of rows and columns
 */
int n_in_a_row(int **board, int size) {
    if( (size%2) == 0)
        return 0;
  
    // count of wins
    int x_wins = 0;
    int o_wins = 0;
    
    // count of win types
    int x_horiz = 0;
    int x_vert = 0;
    int x_diag_for = 0;
    int x_diag_back = 0;
    int o_horiz = 0;
    int o_vert = 0;
    int o_diag_for = 0;
    int o_diag_back = 0;
  
    // location of win
    int x_h_i = -1;
    int x_v_i = -1;
    int o_h_i = -1;
    int o_v_i = -1;
  
    // count of elements on board per direction (by row / by column / by diagonal)
    int total_num_x = 0;
    int total_num_o = 0;
    
    int num_x = 0;
    int num_o = 0;
  
    // special case: 4 wins [boolean 0 = false, 1 = true]
    int x_h_center = 0;
    int x_v_center = 0;
    int x_df_center = 0;
    int x_db_center = 0;
    int o_h_center = 0;
    int o_v_center = 0;
    int o_df_center = 0;
    int o_db_center = 0;
  
    // board index
    int i = 0;
    int j = 0;
  
    //count horizontal wins
    for(i = 0; i < size; i++) {
        num_x = 0;
        num_o = 0;
    
      	for(j = 0; j < size; j++) {
      	    if(*(*(board+i)+j) == 1){
          		num_x++;
          		total_num_x++;
      	    }
      	    if(*(*(board+i)+j) == 2){
          		num_o++;
          		total_num_o++;
      	    }
        }
    	
    
        if(num_x == size){
           if( (size/2)+1 == i ){
        		    x_h_center = 1;
          	    x_wins++;
          	    x_horiz++;
          	    x_h_i = i;
        	} else if(num_o == size) {
        	    if( (size/2)+1 == i)
          		  o_h_center = 1;
          	    o_wins++;
          	    o_horiz++;
          	    o_h_i = i;
            }
        }
    }
  
    //check correct number of xs and os
    if((total_num_x - total_num_o) != 1 && (total_num_x - total_num_o) != 0 )
        return 0;
  
    //count vertical wins
    for(j = 0; j < size; j++) {
      	num_x = 0;
        num_o = 0;
    
      	for(i = 0; i < size; i++) {
      	    if(*(*(board+i)+j) == 1)
      		      num_x++;
      	    if(*(*(board+i)+j) == 2)
      		      num_o++;
      	}
      
      	if(num_x == size) {
      	    if( (size/2)+1 == j )
          		  x_v_center = 1;
          	    x_wins++;
          	    x_vert++;
          	    x_v_i = j;
      	} else if(num_o == size) {
        	    if( (size/2)+1 == j )
        		    o_v_center = 1;
          	    o_wins++;
          	    o_vert++;
          	    o_v_i = j;
      	}
    }
    
    //count forward diagonal wins
    num_x = 0;
    num_o = 0;
    for(i = size-1; i >= 0; i--) {
      	for(j = 0; j < size; j++) {
      	      if(*(*(board+i)+j) == 1)
      		        num_x++;
      	      if(*(*(board+i)+j) == 2)
      		        num_o++;
      	}
    }
    if(num_x == size) {
      	x_wins++;
      	x_diag_for++;
      	x_df_center = 1;
    } else if(num_o == size) {
      	o_wins++;
      	o_diag_for++;
      	o_df_center = 1;
    }
  
    //count backward diagonal wins
    num_x = 0;
    num_o = 0;
    for(i = 0; i < size; i++) {
      	for(j = size-1; j >= 0; j--) {
      	    if(*(*(board+i)+j) == 1)
 		            num_x++;
      	    if(*(*(board+i)+j) == 2)
      		      num_o++;
      	}
    }
    if(num_x == size) {
      	x_wins++;
      	x_diag_back++;
      	x_db_center = 1;
    } else if(num_o == size) {
      	o_wins++;
      	o_diag_back++;
      	o_db_center = 1;
    }
    
    //check if there are a valid number of wins
    if( !( ( x_wins == 0  && o_wins != 0 ) || ( x_wins != 0 && o_wins == 0 ) || ( x_wins == 0 && o_wins == 0 ) ) ) 
        return 0;
        
    //make sure x went first
    if(x_wins != 0 && total_num_x == total_num_o)
        return 0;

    //check if board analysis reports a valid board
    if( (x_horiz > 1) || (x_vert > 1) || (x_diag_for > 1) || (x_diag_back > 1) )
        return 0;
    if( (o_horiz > 1) || (o_vert > 1) || (o_diag_for > 1) || (o_diag_back > 1) )
        return 0;
        
    //check special case: 4-win
    if((x_horiz + x_vert + x_diag_for + x_diag_back) == 4) {
      	if(x_h_center != 1 || x_v_center != 1 || x_df_center != 1 || x_db_center != 1) 
      	    return 0;
    }
    if((o_horiz + o_vert + o_diag_for + o_diag_back) == 4) {
      	if(o_h_center != 1 || o_v_center != 1 || o_df_center != 1 || o_db_center != 1) 
      	    return 0;
    }
  //check special case: 3-win
    if((x_horiz + x_vert + x_diag_for + x_diag_back) == 3) {
        // top left corner intersection
      	if(x_h_i != 0 || x_v_i != 0 || x_diag_back == 0)
      	    return 0;
      	// top right corner intersection
      	else if(x_h_i != 0 || x_v_i != size-1 || x_diag_for == 0)
      	    return 0;
      	// bottom left corner intersection
      	else if(x_h_i != size-1 || x_v_i != 0 || x_diag_for == 0)
      	    return 0;
      	// bottom right corner intersection
      	else if(x_h_i != size-1 || x_v_i != size-1 || x_diag_back == 0)
      	    return 0;
      
      	// top left corner intersection
      	if(o_h_i != 0 || o_v_i != 0 || o_diag_back == 0)
      	    return 0;
      	// top right corner intersection
      	else if(o_h_i != 0 || o_v_i != size-1 || o_diag_for == 0)
      	    return 0;
      	// bottom left corner intersection
      	else if(o_h_i != size-1 || o_v_i != 0 || o_diag_for == 0)
      	    return 0;
      	// bottom right corner intersection
      	else if(o_h_i != size-1 || o_v_i != size-1 || o_diag_back == 0)
      	    return 0;
    }
    
    return 1;   
}    
  
 
   
/* PARTIALLY COMPLETED:
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {              

    //Check if number of command-line arguments is correct.
    if(argc != 2) {
        printf("Incorrect number of arguments\n");
        exit(1);
    }
    
    //Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    //Declare local variables.
    int size;

    //Call get_dimensions to retrieve the board size.
    get_dimensions(fp, &size);   

    //Dynamically allocate a 2D array of dimensions retrieved above.
    int **board = malloc(sizeof(int*)*size);
    for(int i = 0; i < size; i++) {
        *(board + i) = malloc(sizeof(int)*size);
    }

    //Read the file line by line.
    //Tokenize each line wrt the delimiter character to store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading the file.\n");
            exit(1);
        }

        token = strtok(line, DELIM);
        for (int j = 0; j < size; j++) {
            // Complete the line of code below
            //to initialize your 2D array.
            *(*(board+i)+j) = atoi(token);
            token = strtok(NULL, DELIM);
        }
    }

    //Call the function n_in_a_row and print the appropriate
    //output depending on the function's return value.
    int valid = n_in_a_row(board, size);
    if(valid == 1)
	      printf("valid\n");
    else
	      printf("invalid\n");

    //Free all dynamically allocated memory.
    for(int i = 0; i < size; i++) {
        free(*(board + i));
        *(board + i) = NULL;	
    }
    free(board);
    board = NULL;
    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    } 
     
    return 0;

}   // FIN
