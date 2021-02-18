/**
 * ENGG1110 Problem Solving by Programming
 *
 * Math Tool Box Phase 3B Solver
 *
 * I declare that the assignment here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   http://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name : Kim Jounghoon <fill in yourself>
 * Student ID   : 1155096482     <fill in yourself>
 * Class/Section: F<fill in yourself>
 * Date         : 28 11 2017 <fill in yourself>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

typedef struct {
    double m[9][9];
    int num;
} MatrixType;

typedef struct {
    int m[100][100];
    int row;
    int col;
} MatrixTypeimage;



void edgedetection(MatrixTypeimage Final, MatrixTypeimage B)
{
    int i, j, row, col, value;
    int consent = 0;
    double result [10000];
    int R[100][100];
    Final.row = (B.row)   ;        // row of convoluted matrix
    Final.col = (B.col)  ;        // column of convoluted matrix

    for (i = 0 ; i<(Final.row); i++)
        {
            for (j = 0 ; j<(Final.col); j++)
            {
                if (abs(B.m[i][j]-B.m[i][j+1]>7))                    // for explanation read all values first
                    B.m[i][j] = 0;
                else
                    B.m[i][j] = 255;
            }
        }
    writefile(B.m, Final.row,Final.col);                        // write file process
}




void reverse(MatrixTypeimage Final, MatrixTypeimage B)
{
    int i, j, row, col, value;
    int consent = 0;
    double result [10000];
    int R[100][100];
    Final.row = (B.row)   ;        // row of convoluted matrix
    Final.col = (B.col)  ;        // column of convoluted matrix

    for (i = 0 ; i<(Final.row); i++)
        {
            for (j = 0 ; j<(Final.col); j++)
            {
                                   // for explanation read all values first
                    B.m[i][j] = abs(255 - B.m[i][j]);

            }
        }
    writefile(B.m, Final.row,Final.col);                        // write file process

}



void pixel(MatrixTypeimage Final, MatrixTypeimage B)
{
    int i, j, row, col, value;
    int consent = 0;
    double result [40000];
    int R[400][400];
    Final.row = 2*(B.row)   ;        // row of convoluted matrix
    Final.col = 2*(B.col)  ;        // column of convoluted matrix

    for (i = 0 ; i<(Final.row); i=i+2)
        {
            for (j = 0 ; j<(Final.col); j=j+3)
            {
                                   // for explanation read all values first
                    B.m[i][j] = B.m[i][j];
                    B.m[i+1][j+1] = B.m[i][j];
                    B.m[i+1][j+0] = B.m[i][j];
                    B.m[i+0][j+1] = B.m[i][j];
            }
        }
    writefile(B.m, Final.row/2,Final.col/2);                        // write file process
}





void star (MatrixTypeimage Final, MatrixTypeimage B)
{
    int i, j, row, col, value;
    int consent = 0;
    double result [40000];
    int R[400][400];
    Final.row = 2*(B.row)   ;        // row of convoluted matrix
    Final.col = 2*(B.col)  ;        // column of convoluted matrix

    for (i = 0 ; i<(Final.row); i=i+3)
        {
            for (j = 0 ; j<(Final.col); j=j+3)
            {
                                   // for explanation read all values first
                    B.m[i][j] = B.m[i][j];
                    B.m[i+1][j+1] = B.m[i][j];
                    B.m[i+2][j+2] = B.m[i][j];



            }
        }
    writefile(B.m, Final.row/2,Final.col/2);                        // write file process
}






void printMatrixNxN(MatrixType Z)
{
    int col,i,j;

        printf("/");
    for (col = 0; col < Z.num; col++)

        printf("        ");
        printf(" \\\n");


    for(i=0;i<Z.num;i++)
    {
        printf("| ");
        for(j=0;j<Z.num;j++)
        {

            printf("%+7.2f " ,Z.m[i][j]);
        }
        printf("|\n");
    }
        printf("\\");
    for (col = 0; col < Z.num; col++)
        printf("        ");
        printf(" /\n");

}

int Blend (int x[100][100], MatrixType Y)
{
    int i, j ;
    double result = 0;
    for (i = 0; i<Y.num; i++)
        {

        for (j=0; j<Y.num; j++)
            {
         result = result + Y.m[i][j]*x[i][j]  ;
            }
        }

        if (result>255)
            result = 255;
        if(result<0)
            result = 0;

    return floor (result+0.5);                          // for rounding up process if bigger than 0.5 up down less than 0.4
}

void defmatrix(int result [100][100], int X[100][100], int initialrow, int initialcol , int number )
    {
        int i, j;

        for (i=0; i<number; i++)
        {
            for(j=0; j< number; j++)
            {
                result[i][j] = X[initialrow+i][initialcol+j];   //  Define matrix required for blend

            }
        }

    }

writefile(int matrix[100][100], int row, int col)
{
    FILE *fin;
    int i,j;

   fin = fopen("output.pgm", "w");
      if (fin == NULL)
        {
            printf("Error reading pgm file [output.pgm]");
            exit(1);
        }
        else
            {
            fprintf(fin, "%c%c\n", 'P','2');
            fprintf(fin, "%d %d\n", col, row);
            fprintf(fin, "%d\n", 255);                  // MAX BRIGHTNESS DEF GIVEN IN SPECIFICATION

            for(i=0;i<row;i++)
                {
                for(j=0;j<col; j++)
                    {
                    fprintf(fin, "%d ", matrix [i][j]);
                    }
                fprintf(fin,"\n");
                }

                fclose(fin);


            }
}


void convol(MatrixTypeimage Final, MatrixTypeimage B,  MatrixType C)
{
    int i, j, row, col, value;
    int consent = 0;
    double result [10000];
    int R[100][100];
    Final.row = ((B.row)-(C.num)+1);            // row of convoluted matrix
    Final.col = ((B.col)-(C.num)+1);            // column of convoluted matrix

    for (i = 0 ; i<(Final.row); i++)
        {
            for (j = 0 ; j<(Final.col); j++)
            {
                defmatrix(R, B.m , i , j , C.num);
                result[consent] = Blend(R , C);
                consent = consent+1;                        // for explanation read all values first
            }
        }


        consent=0;
    for (i = 0 ; i<(Final.row); i++)
        {
           for (j = 0 ; j<(Final.col); j++)
             {
                 Final.m[i][j] =  (result[consent]);
                 consent= consent+1;                         // and re arrange by column and row
            }
        }
    writefile(Final.m, Final.row,Final.col);                        // write file process
}

int main()
{


    printf("Math Tool Box\n");
    printf("/\\/\\/\\/\\/\\/\\/\n");
    printf("Phase 3B\n");
    printf("Image filename: ");


// for the pgm file read
    FILE *openimage;
    char image[200]; // image file name
    char format[2];
    int i;
    scanf("%s", image);
    openimage = fopen(image, "r" );
    if (openimage == NULL)
        {
            printf("Error reading pgm file [%s]", image);
            exit(1);
        }

// for filter file read


    char filter[200];
    int j;

    printf("Filter filename: ");
    FILE *openfilter;
    scanf("%s", filter);
    openfilter = fopen(filter, "r" );
    if (openfilter == NULL)
        {
            printf("Error reading filter file [%s]", filter);
            exit(1);
        }

    // Matrix print for filter file

    double num[200];

    MatrixType F; // FOR filter file
    fscanf(openfilter, "%d", &F.num);

// pow is used since filter always has same width and length

    for(i=0; i<pow(F.num,2); i++)
    {
        fscanf(openfilter, "%lf", &num[i]);
    }
    int flag = 0;
    for(i = 0; i< F.num; i++)
    {
        for(j = 0; j< F.num; j++)
            {
                F.m [i][j] = num[flag];
                flag=flag+1;
            }
    }
    printMatrixNxN(F);
    fclose(openfilter);

// Rescale
    int value [11000];
    int max; // store max value 255
    int con;

MatrixTypeimage Img; // for the image file
MatrixTypeimage S; // extra matrix for store convoluted value
fscanf(openimage, "%s", &format); // read format p2"

fscanf(openimage, "%d%d", &Img.col, &Img.row); // read width and length

fscanf(openimage, "%d", &max);

 flag = 0;
    for(i=0; i<Img.col; i++)
    {
        for(j=0; j<Img.row; j++)
        {
            fscanf(openimage, "%d", &value[flag]);      // for explanation read all values first
            flag=flag+1;
        }

    }

con = 0;
for(i = 0; i< Img.row; i++)
    {
        for(j = 0; j< Img.col; j++)
            {
                Img.m [i][j] = value[con];              // and arrange by the row and column of the matrix given
                con = con+1;
            }
    }
    fclose(openimage);
    convol(S, Img, F);  // convolution write function included

    return 0;
}
