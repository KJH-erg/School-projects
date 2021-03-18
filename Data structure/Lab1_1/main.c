
#include <stdio.h>

int Insert(int value, int A[], int n)
{
    // insert value into A[], return new length n
    int tmp [100]; // temporary array to copy the original array
    int pos = 0;   // position variable
    // if array n is 0 just copy the value to A[0] and return n+1
    if(n==0)
    {
        A[0] = value;
        return n+1;
    }
    // if n is greater than 0
    else
        {
            // copy array
            for(int i = 0; i <=n ; i++)
            {
                tmp[i] = A[i];
            }
            // from the beginning to the end of array check value greater than accepted value
            for(int i = 0; i <=n ; i++)
            {
                // if value is found remember the position of array and escape the loop
                if(value < A[i])
                {
                    pos = i;
                    break;
                }
            }
            // from the pos+1 array copy from tmp array value till the end
            for(int i = pos; i <=n ; i++)
            {
                A[i+1] = tmp[i];
            }
            // copy the value in array's pos position
            A[pos] = value;
        }

    return n+1;
}

int Delete(int value, int A[], int n)
{
    // delete value from A[], return new length n
    int tmp [100];
    int pos = 0;
    // from the beginning to the end of array check value equal to accepted value
    for(int i = 0; i <=n ; i++)
        {
            tmp[i] = A[i];
        }

    for(int i = 0; i <=n ; i++)
        {
            // if value is found remember the position of array and escape the loop
            if(value == A[i])
                {
                    pos = i;
                    break;
                }
            }
    // from the pos+1 array of tmp array copy value in A till the end
    for(int i = pos; i <=n ; i++)
        {
            A[i] = tmp[i+1];
        }

    return n-1;

}

int Exist(int value, int A[], int n){
    // check whether value exists in array A[]

    for(int i = 0; i <n ; i++)
        {
            if(value == A[i])
                {
                    return 1;
                    break;
                }
        }
    return 0;
}

int Update_one(int old_value, int new_value, int A[], int n)
{
    // change old_value to new_value, return new length n
    //Delete value n is decreased by 1
    Delete(old_value, A, n);
    // Thus when insert add 1 in n
    Insert(new_value, A, n+1);
    return n;

}

int Update_all(int old_value, int new_value, int A[], int n)
{
    // change old_value to new_value, return new length n
    // variable to check the redundant values
    int count = 0;
    // loop to check the entire array
    while(Exist(old_value,A ,n))
        {
            // if sample value is found delete n is decreased by 1
            n=Delete(old_value, A, n);
            // count is increased by 1
            count++;

        }
     // count represents number of value deleted so insert new value with the same number of count
    for(int i=0;i<count;i++)
        {
            n=Insert(new_value, A, n);
        }
    return n;

}

void Print(int A[], int n)
{
    // print A[0], A[1], ..., A[n-1] in one line, every two integers are separated by a space
    for(int i=0; i<(n-1); i++)
        {
            printf("%d ", A[i]);
        }
            printf("%d", A[n-1]);

}

int main()
{
    int A[100];
    int n; // the number of integers in A
    int value, new_value;

    //printf("Array initialization: \n");
    //printf("How many integers in array initially: ");
    scanf("%d", &n);
    //printf("What are the integers: ");
    int temp = 0;
    for(int i=0; i<n; i++){
        scanf("%d", &value);
        temp = Insert(value, A, temp);


    }

    //printf("Input a value for insertion: ");
	scanf("%d", &value);
	n = Insert(value, A, n);

	//printf("Input a value for deletion: ");
	scanf("%d", &value);
	n = Delete(value, A, n);

	//printf("Input the old and new values for update(one): ");
	scanf("%d%d", &value, &new_value);
	n = Update_one(value, new_value, A, n);

    //printf("Input the old and new values for update(all): ");
	scanf("%d%d", &value, &new_value);
	n = Update_all(value, new_value, A, n);

    //printf("Current array: \n");
	Print(A, n);

	return 0;
}
