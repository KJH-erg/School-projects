/**
 * ENGG1110 Problem Solving by Programming
 *
 * Math Tool Box Phase 2
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
 * Student ID   : 1155096482 <fill in yourself>
 * Class/Section: ENGG1110F <fill in yourself>
 * Date         : 20 10 2017 <fill in yourself>
 */

#include <stdio.h>
#include <math.h>

#define EPSILON 1e-6

void initZeroVector2(double v[2])
{
}

void printVector2(double v[2])
{
    printf("/                 \\\n");
    printf("| %+7.2f %+7.2f |\n", v[0], v[1]);
    printf("\\                 /\n");
}

double dotProductVector2(double v[2], double w[2])
{

   double result;
   result = v[0]*w[0]+v[1]*w[1];
   return result;
}

double lenVector2(double v[2])
{
    return sqrt(dotProductVector2(v, v));
}

void printMatrix2x2(double m[2][2])
{
    printf("/                 \\\n");
    printf("| %+7.2f %+7.2f |\n", m[0][0], m[0][1]);
    printf("| %+7.2f %+7.2f |\n", m[1][0], m[1][1]);
    printf("\\                 /\n");
}

double detMatrix2x2(double m[2][2])
{
    double result = 0;
    result=m[0][0]*m[1][1]-m[1][0]*m[0][1];
    return result;
}

void multVector2Matrix2x2(double result[2], double v[2], double m[2][2])
{
    result[0]=m[0][0]*v[0]+m[1][0]*v[1];
    result[1]=m[0][1]*v[0]+m[1][1]*v[1];
}

void multMatrix2x2Vector2(double result[2], double m[2][2], double w[2])
{
    result[0] = m[0][0] * w[0] + m[0][1] * w[1];
    result[1] = m[1][0] * w[0] + m[1][1] * w[1];
}

void transposeMatrix2x2(double result[2][2], double m[2][2])
{
    result[0][0]=m[0][0];
    result[0][1]=m[1][0];
    result[1][0]=m[0][1];
    result[1][1]=m[1][1];
}

void inverseMatrix2x2(double result[2][2], double m[2][2])
{
    double mdet = 0;
    mdet=m[0][0]*m[1][1]-m[1][0]*m[0][1];
    result[0][0]=m[1][1]/mdet;
    result[0][1]=(-1)*m[0][1]/mdet;
    result[1][0]=(-1)*m[1][0]/mdet;
    result[1][1]=m[0][0]/mdet;
}


void addMatrix2x2(double result[2][2], double ma[2][2], double mb[2][2])
{
    result[0][0] = ma[0][0] + mb[0][0];
    result[0][1] = ma[0][1] + mb[0][1];
    result[1][0] = ma[1][0] + mb[1][0];
    result[1][1] = ma[1][1] + mb[1][1];
}

void multMatrix2x2(double result[2][2], double ma[2][2], double mb[2][2])
{
    result[0][0]=ma[0][0]*mb[0][0]+ma[0][1]*mb[1][0];
    result[0][1]=ma[0][0]*mb[0][1]+ma[0][1]*mb[1][1];
    result[1][0]=ma[1][0]*mb[0][0]+ma[1][1]*mb[1][0];
    result[1][1]=ma[1][0]*mb[0][1]+ma[1][1]*mb[1][1];
}


void initZeroMatrix2x2(double m[2][2])
{
    m[0][0] = 0; m[0][1] = 0;
    m[1][0] = 0; m[1][1] = 0;
}

void initIdentityMatrix2x2(double m[2][2])
{
}


void initMatrixNxN(double m[9][9], int n, double value)
{
    int i, j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
        m[i][j]=value;
        }
    }
}

void initPatternMatrixNxN(double m[9][9], int n)
{
    int row, col;
    for (row = 0; row < n; row++)
        for (col = 0; col < n; col++)
            m[row][col] = row + col * 0.1;
}

void copyMatrixNxN(double result[9][9], double m[9][9], int n)
{
    int row, col;
    for (row = 0; row < n; row++)
        for (col = 0; col < n; col++)
            result[row][col] = m[row][col];
}

void printMatrixNxN(double m[9][9], int n)
{
    int col,i,j;

    printf("/");
    for (col = 0; col < n; col++)
        printf("        ");
    printf(" \\\n");


    for(i=0;i<n;i++)
    {
        printf("| ");
        for(j=0;j<n;j++)
        {

            printf("%+7.2f " ,m[i][j]);
        }
        printf("|\n");
    }
    printf("\\");
    for (col = 0; col < n; col++)
        printf("        ");
    printf(" /\n");
}

void multMatrixNxN(double result[9][9], double ma[9][9], double mb[9][9], int n)
{
    int i, j, q;
    double sum=0;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {

            for(q=0;q<n;q++)
                {
                sum=sum+(ma[i][q]*mb[q][j]);

                }
                    result[i][j]=sum;
                    sum=0;
         }

    }

}

int main()
{
    printf("Math Tool Box\n");
    printf("/\\/\\/\\/\\/\\/\\/\n");

    {
        double v[2];
        double w[2];
        double vlen, wlen, vdotw;

        double M[2][2];
        double K[2][2];
        double P[2][2];
        double Q[2][2];
        double I[2][2];

        double R[9][9];

        double mdet;
        double pdet;

        printf("Phase 2\n");

        initZeroVector2(v);
        initZeroVector2(w);

        initZeroMatrix2x2(M);
        initZeroMatrix2x2(K);
        initZeroMatrix2x2(P);
        initZeroMatrix2x2(Q);
        initIdentityMatrix2x2(I);

        printf("\nInput a 2-element vector v:\n");
        scanf("%lf%lf", &v[0], &v[1]);

        printf("\nYour 2-element vector v:\n");
        printVector2(v);

        vlen = lenVector2(v);
        printf("\nLength of vector v = |v| = %f\n", vlen);

        printf("\nInput a 2x2 matrix M:\n");
        scanf("%lf%lf%lf%lf", &M[0][0], &M[0][1], &M[1][0], &M[1][1]);

        printf("\nYour 2x2 matrix M:\n");
        printMatrix2x2(M);

        mdet = detMatrix2x2(M);
        printf("\nDeterminant(M) = %f\n", mdet);

        if (fabs(mdet) < EPSILON)
            printf("\nM has NO inverse!\n");
        else
        {
            printf("\nInverse(M):\n");
            inverseMatrix2x2(K, M);
            printMatrix2x2(K);
        }

        printf("\nAdd identity matrix I with matrix M, yield matrix P:\n");
        I[0][0]=1;
        I[1][1]=1;
        addMatrix2x2(P, M, I);
        printMatrix2x2(P);

        pdet = detMatrix2x2(P);
        printf("\nDeterminant(P) = %f\n", pdet);

        if (fabs(pdet) < EPSILON)
            printf("\nP has NO inverse!\n");
        else
        {
            printf("\nInverse(P):\n");
            inverseMatrix2x2(Q, P);
            printMatrix2x2(Q);
        }

        printf("\nMultiply vector v with matrix M, yield vector w:\n");
        multVector2Matrix2x2(w, v, M);
        printVector2(w);

        wlen = lenVector2(w);
        printf("\nLength of vector w = |w| = %f\n", wlen);

        printf("\nDot product of vector v with vector w = %f\n", vdotw = dotProductVector2(v, w));

        printf("\nTranspose(M), yield matrix Q:\n");
        transposeMatrix2x2(Q, M);
        printMatrix2x2(Q);

        printf("\nMultiply matrix Q with matrix M:\n");
        multMatrix2x2(K, Q, M);
        printMatrix2x2(K);

        printf("\nRaise matrix M to the power of 3:\n");
        multMatrix2x2(K, M, M);
        multMatrix2x2(Q, K, M); // avoid reusing K as both operand and result
        printMatrix2x2(Q);



        printf("\nConstant 7x7 matrix Y:\n");
        double Y[9][9];
        int dimY = 7;
        initMatrixNxN(Y, dimY, -1);
        printMatrixNxN(Y, dimY);

        printf("\nPatterned 9x9 matrix Z:\n");
        double Z[9][9];
        int dimZ = 9;
        initPatternMatrixNxN(Z, dimZ);
        printMatrixNxN(Z, dimZ);

        printf("\nMultiply matrix Z with matrix Z:\n");

        multMatrixNxN(R, Z, Z, dimZ);
        printMatrixNxN(R, dimZ);
    }


    return 0;
}

