/* 
The first line in the file will provide the number of rows and columns in the matrix separated by a tab.  
The subsequentlines will provide the contents of the matrix.  
The numbers in the same row are tab separated andthe rows are separated with new lines.  
This will be followed by the same format for the dimensionsand content of the second matrix.
---
For example, a sample input file “file1.txt”:
2   3
1   2   3
4   5   6
3   2
1   2
3   4
5   6
$ ./matrix file1.txt
4
22  28
49  64
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{

    FILE *f = fopen(argv[1], "r");
    //does file exist?
    if (f == NULL)
    {
        //error
        printf("Error.\n");
    }
    //file exists
    else
    {
        //using a 1d matrix approach  
        int *matrix1 = NULL;
        int *matrix2 = NULL;
        int *matrixResult = NULL;


        int firstRows;
        int firstColumns;

        int dimension1 = fscanf(f, "%d\t%d\n", &firstRows, &firstColumns);
        if(dimension1 == 2)
        {
            matrix1 = (int*)malloc((firstRows*firstColumns)*sizeof(int));
        }
        else
        {
            return 0;
        }
        //printf("%d\n%d\n",firstRows,firstColumns);

        for(int i = 0; i < (firstRows*firstColumns); i++)
        {
            int rows;
            int rowsHold;

            if(i + 1 == firstColumns)
            {
                rows = fscanf(f, "%d\n", &rowsHold);
            }
            else
            {
                rows = fscanf(f, "%d", &rowsHold);
            }

            if(rows == 1)
            {
                *(matrix1 + i) = rowsHold;
            }
            else
            {
                free(matrix1);
                return 0;
            }
        }

       

        int secondRows;
        int secondColumns;
        
        int dimension2 = fscanf(f, "%d\t%d\n", &secondRows, &secondColumns);
        //printf("%d\n%d\n",secondRows,secondColumns);
        
        if(dimension2 == 2)
        {
            matrix2 = (int*)malloc((secondColumns*secondRows)*sizeof(int));
        }
        else
        {
            free(matrix1);
            return 0;
        }
        
        if(firstColumns != secondRows)
         {
            printf("bad-matrices");
           return 0;
        }

        //for(int i = 0; i < (firstRows*firstColumns); i++)
        //{
        //    printf("%d\n", matrix1[i]);
        //}

        for(int i = 0; i < (secondRows*secondColumns); i++)
        {
            int rows2;
            int rowsHold2;

            if(i + 1 == secondColumns)
            {
                rows2 = fscanf(f, "%d\n", &rowsHold2);
            }
            else
            {
                rows2 = fscanf(f, "%d", &rowsHold2);
            }

            if(rows2 == 1)
            {
                *(matrix2 + i) = rowsHold2;
            }
            else
            {
                free(matrix1);
                free(matrix2);
                return 0;
            }
        }

        //for(int i = 0; i < (secondRows*secondColumns); i++)
        //{
        //    printf("%d\n", matrix2[i]);
        //}

        fclose(f);

        //consulting https://www.mathsisfun.com/algebra/matrix-multiplying.html
        
        matrixResult = (int*) malloc((firstRows * secondColumns)*sizeof(int));
        
        /* 1d multiplication approach
        first for = rows of first matrix
        second for = columns of second matrix
        result matrix when multiplying = #rows of first * #columns of second
        third for = the values in row i to
        */
        for(int i = 0; i < firstRows; i++)
        {
            for(int j = 0; j < secondColumns; j++)
            {
                int ijMatrixValue = 0;
                for(int k = 0; k < firstColumns; k++)
                {
                    //printf("Val %d\n", (*(matrix1 + (k + i * firstColumns))));
                    //printf("Val2 %d\n", (*(matrix2 + (k + j * secondColumns))));
                    ijMatrixValue += (*(matrix1 + (k + i * firstColumns))) * (*(matrix2 + (j + k * secondColumns)));
                    //printf("m1 %d x m2 %d\n",(*(matrix1 + (k + i * firstColumns))), (*(matrix2 + (j + k * secondColumns))));
                    //printf("ij val %d\n", ijMatrixValue);
                }
                *(matrixResult + (j + i * secondColumns)) = ijMatrixValue;
            }
        }        

        for(int i = 0; i < (firstRows); i++)
        {
            for(int j = 0; j < (secondColumns); j++)
            {
                printf("%d", *(matrixResult+j + i * secondColumns));
                if(j != secondColumns-1)
                {
                    printf("\t");
                }
                else
                {
                    printf("\n");
                }
            }
        }
        //printf("%d\n", *(matrixResult+1));

        free(matrix1);
        free(matrix2);
        free(matrixResult);

    }
}