
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void PrintArray(int A[], int n)
{
    for(int i=0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void merge(int A[], int left, int mid, int right, int n){
    int tmp[n];
    int count;
    int limit = right-left+1;
    int ini = left;
    int check = mid+1;
        for(int count = 0; count<limit; count++){
            if(check>right)
            {
                tmp[count] = A[ini];
                ini++;
                continue;

            }
            else if(ini>mid)
            {
                tmp[count] = A[check];
                check++;
                continue;

            }
            else if(A[ini]>=A[check])
            {
               tmp[count]= A[ini];
                ini++;
                continue;
            }
            else if(A[ini]<A[check])
            {
              tmp[count]= A[check];
                check++;
                continue;
            }

        }
        for(int count = 0; count<limit; count++)
        {
            A[count+left]=tmp[count];
        }


}

void MergeSort(int A[], int left, int right, int n)
{

    if(left < right){
        int mid = floor((left + right)/2);
        MergeSort(A, left, mid,n);
        MergeSort(A, mid+1, right,n); /* sort the 2nd half */
        merge(A, left,mid,right,n);

    }

}
int main()
{
    int n;
    scanf("%d",&n);

    int A[n];

    for(int i=0; i < n; i++) scanf("%d", &A[i]);

    MergeSort(A, 0, n-1, n);
    PrintArray(A, n);
    return 0;
}
