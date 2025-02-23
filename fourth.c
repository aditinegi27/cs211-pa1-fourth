#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **rowSwap(double **arr, int row1, int row2, int cols){
   for (int c = 0; c < cols; c++){
      //arr[c] = arr[row1][c};
      double temp = arr[row1][c];
      arr[row1][c] = arr[row2][c];
      arr[row2][c] = temp;
   }
   return arr;
}

double **rowScale(double **arr, int row, int col, int cols){
   double scale = 1/(arr[row][col]); //figure out scale factor
   for (int c = 0; c < cols; c++){
      arr[row][c] *= scale;
   }
   return arr;
}

double **rowAdd(double **arr, int row1, int row2, int col, int cols){
   //row1 is the row being changed and row2 is being scaled and added to row1
   double scale = (arr[row1][col])/(arr[row2][col]);
   for (int c = 0; c < cols; c++){
      //array[c] = scale*arr[row2][c];
      arr[row1][c] -= scale * arr[row2][c]; //technically subtracted so that row1 becomes 0
   }
   return arr;
}

void freeMatrix(double **matrix, int r){
   for(int i = 0; i < r; i++){
      free(matrix[i]);  //free each row
   }
   free(matrix);  //free row pointers
}

void printMatrix(double **matrix, int row, int col){
   for(int l = 0; l < row; l++){
      for(int p = 0; p < col; p++){
         if(matrix[l][p] == 0)
            printf("%lf\t", fabs(matrix[l][p])); //no negative zero
         else
            printf("%lf\t", matrix[l][p]);
      }
      printf("\n");
   }
}


int main(int argc, char** argv){

   if(argc < 2) { //checks if there are 2 arguments!
      fprintf(stderr,"./first {text file}"); //prints messages to stderr. Primarily for error messages
      exit(1); //exits the program with a return code 1.
   }
   
   FILE *file = fopen(argv[1], "r"); //opening file
   if(file == NULL){ //if fopen fails to open the file, it returns NULL
      fprintf(stderr,"%s failed to open\n",argv[1]);
      exit(1); //exits your program
   }
   
   int row, col;
   //fix instance where a,a is 0 and must go down to the next row in column to make 1
   
   int f1 = fscanf(file, "%d %d", &row, &col);
   if(f1 != 2) return 0;
   int low = row;
   if (col<row) low = col;
   
   // Allocate memory for row pointers
   double **matrix = malloc(row * sizeof(double *));

   // Allocate memory for each row
   for(int b = 0; b < row; b++){
      matrix[b] = malloc(col*sizeof(double));
   }
   
   
   for(int i = 0; i < row; i++){
      for(int j = 0; j < col; j++){
         int f2 = fscanf(file, "%lf", &matrix[i][j]);
         if(f2 != 1) return 0;
         //matrix[i][j] = fscanf(file, "%lf"); // Assign values
      }
   }
   fclose(file);
      //fix instance where a,a is 0 and must go down to the next row in column to make 1
   int a = 0, b = 0;
   for(a = 0; a < low; a++){
      //int b 
     // if(matrix[a][b] == 0) b++;
      if(matrix[a][b] != 1){
         //check if can row swap
         int swap = 0;
         for (int r = a; r < row; r++){
            if (matrix[r][b] == 1){
               rowSwap(matrix, a, r, col);
               swap = 1;
               //break;
            }
         }
         
         //scale the row if it didn't swap to become 1
         if (swap == 0) {
               if(matrix[a][b] == 0) b++;
               if(b >= col) break;
               rowScale(matrix, a, b, col);
               //break;
            }
      }
      //check everything in column is 0
      for(int x = 0; x < row; x++){
         if(x==a) continue;//skip
         else if(matrix[x][a] != 0){
            rowAdd(matrix, x, a, a, col); //row addition, row x is becoming 0
         }
      }
      b++;
      if(b >= col) break;
      //printMatrix(matrix, row, col);
   }
   
   printMatrix(matrix, row, col);
   
   
   freeMatrix(matrix, row);
   
}
