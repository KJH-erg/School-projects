#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct linked_list_node{
    int value;
    struct linked_list_node* next;
} Node;

typedef Node* List;

int Exist(List p, int value)
{
    // judge whether linked list p contains the value
    // you should visit each node of the linked list one by one, and check whether it is equal to the value
    // if you find it then return 1, otherwise return 0
    while(p!=NULL)
    {
        if(p->value==value) return 1;
        p = p->next;
    }
    return 0;
}

void Print(List p)
{
    // print all integers from the head of linked list in one line(separated by a space), in other words, you should firstly print the integer p points to
    // to be more specific, print p->value and then move p to the next node p->next recursively, until p points to NULL

    p = p->next;
    // this statement is added to skip the first list with empty value pointing to the first list with value
    while(p!=NULL)
    {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
}

int Num(List p){
    int count = 0;
    while(p!=NULL)
    {
        count++;
        p = p->next;
    }
    return count-1;
}

// this function is used to check that the next list is NULL or not
int checkEnd(List p)
{
    if(p->next ==NULL)
        return 1;
    else
        return 0;
}

int MiddleIndex(List p){
	// the indices of a length-n linked list are 0, 1, ..., (n-1)
    return floor((float)Num(p)/2);
}

List Delete_a(List p){
    List prev , next;
    prev = p;
    next = p->next;
    // remove the first list by returning the second list
    return next;

}

List Delete_b(List p){
    List prev , next, afternext;
    // first second third list in row
    prev = p;
    next = p->next;
    afternext = next->next;
    // move forward until third list is nul
    while(afternext!=NULL)
    {
        prev = next;
        next= prev->next;
        afternext = next->next;
    }
    // unlink the second list which is with value
    prev->next = NULL;
    return p;
}

List Delete_c(List p){
    int index = MiddleIndex(p);
    List prev, rem, next;
    // three lists for remove area previous to remove area next to remove area
    prev = p;
    rem = p->next;
    next = rem->next;
    // move forward with number of index times
    for(int i = 0; i<index ; i++)
    {
        prev = rem;
        rem= prev->next;
        next = rem->next;
    }
    // unlink the middle(rem) and link to the next list
    prev->next = next;
    return p;

}

List Insert(List p, int value)
{
    // memory allocation
    List new_lst = (List) malloc(sizeof(Node));
    // lists to indicate previous and next list
    List prev , next;
    // copy value
    new_lst->value = value;
    // In case p is NULL create a new list without value linking to the first list
    if(p == NULL)
    {
        List empty = (List) malloc(sizeof(Node));
        p=empty;
        p->next = new_lst;
        new_lst->next = NULL;
        return p;
    }
    // if p is not null and there is the same value in the list
    else if(Exist(p,value) == 1)
    {
       return p;
    }

    else
    {
        prev = p;
        next = p->next;
        // loop until the condition met
        do
        {
            // in case next list's value has a greater value
            if (next->value<value)
            {
                // add a new list with value after prev and before next
                new_lst->next = prev->next;
                prev->next = new_lst;
                return p;
            }
            // in case list is located at the end and input value is lesser than next value
            else if(next->value>value&&checkEnd(next)==1)
            {
                // add a new list with a value in the end (append)
                next->next = new_lst;
                new_lst->next = NULL;
                return p;
            }
            // neither case move to next link
            else
            {
                prev = next;
                next= prev->next;
            }
        // until the next list is null
        } while(next!=NULL);

    }
return p;

}


int main()
{
    List p = NULL;
    int n, m;
    int value;

    // printf("List initialization: \n");
    // printf("How many integers in list initially: ");
    scanf("%d", &n);
    // printf("What are the integers: ");
    for(int i=0; i<n; i++)
    {
        int value;
        scanf("%d", &value);
        p = Insert(p, value);
    }

     //printf("Delete a value from head\n");
	p = Delete_a(p);

    //printf("Delete a value from end\n");
	p = Delete_b(p);

    //printf("Delete a value from middle\n");
	p = Delete_c(p);

    //printf("Current list: \n");
    Print(p);
    return 0;
}
