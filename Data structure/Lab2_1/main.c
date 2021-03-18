/*
I, Jounghoon Kim, am submitting the assignment for
an individual project.
I declare that the assignment here submitted is original except for
source material explicitly acknowledged, the piece of work, or a part
of the piece of work has not been submitted for more than one purpose
(i.e. to satisfy the requirements in two different courses) without
declaration. I also acknowledge that I am aware of University policy
and regulations on honesty in academic work, and of the disciplinary
guidelines and procedures applicable to breaches of such policy and
regulations, as contained in the University website
http://www.cuhk.edu.hk/policy/academichonesty/.
It is also understood that assignments without a properly signed
declaration by the student concerned will not be graded by the
teacher(s).
*/


#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list_node{
    int value;
    struct linked_list_node* next;
} Node;

typedef Node* List;

//Given function
List Insert(List head, int value)
{
    Node *ptr = (List)malloc(sizeof(Node)); // allocate a piece of memory for the new node
    ptr->value = value;
    if(head==NULL || value < head->value)
    {
        ptr->next = head;
        return ptr;
    }
    Node *current = head;
    Node *after = head->next;
    while(1)
    {
        if(current->next==NULL || (value > current->value && after->value > value))// this part is modified to avoid the error
        {
            ptr->next = current->next;
            current->next = ptr;
            break;
        }
        else
            {
            current = current->next;
            after = current->next;
                }
    }
    return head;
}
    //Generate a linked list head to contain the intersection of A and B in ascending order.
    //You can only visit the input linked list headA and headB but not edit them. Finally, return head.
List Intersection(List headA, List headB)
{
    List head = NULL;
    // temporary list
    List tmp;
    // array to contain intersection values
    int A[100];
    // count number of intersection values
    int count = 0;
    //loop to search all values in headA
    while(headA!=NULL)
    {
        // refresh tmp having headB address to original state
        tmp = headB;
        while(tmp!=NULL)
        {
            //if the same value is found store in array and increase count and escape the loop
            if(headA->value == tmp->value)
            {
                A[count] = headA->value;
                count= count+1;
                break;
            }
            // make tmp to next address
            tmp = tmp->next;
        }
        // make headA to next address to search
        headA = headA->next;
    }
    // count is zero no intersection return head null
    if(count ==0)
        return head;

    //else create new lists and store the values from array
    Node *new_lst = (List)malloc(sizeof(Node));
    new_lst->value =A[0];
    new_lst->next = NULL;
    head = new_lst;
    for(int i =1; i<count; i++)
    {
        Node *new_add = (List)malloc(sizeof(Node));
        new_add->value = A[i];
        new_add->next = NULL;
        new_lst->next = new_add;
        new_lst = new_add;
    }
    // return the head
    return head;
}

List Union(List headA, List headB)
{
    List head = NULL;
    // counter for number of intersection values
    int count_i = 0;
    // check the number of the remainder values in headA or headB
    int count_r = 0;
    // flag is used to check the intersection value is in lists or not
    int flag = 0;
    //array to store intersection values
    int inter[100];
    // remainder value that lists have but not in intersection
    int Remainder [100];
    // list to call intersection
    List intersection = Intersection(headA, headB);
    // first make the head the same with intersection
    head = intersection;

    //loop to store intersection values in inter array
    while(intersection!=NULL)
        {
            inter[count_i] = intersection->value;
            intersection = intersection->next;
            count_i++;
        }
    //exhaustive search for same intersection values if yes add one to flag headA
    while(headA!=NULL)
    {
        flag = 0;
        for(int i = 0; i<count_i; i++)
        {
            if(inter[i]==headA->value)
                flag++;
        }
        // if flag is zero it means this value is not in intersection add this value to remainder array
        if(flag==0)
            {
                Remainder[count_r] = headA->value;
                count_r++;
            }
            headA = headA->next;
    }

    //exhaustive search for same intersection values if yes add one to flag headB
     while(headB!=NULL)
    {
        flag = 0;
        for(int i = 0; i<count_i; i++)
        {
            if(inter[i]==headB->value)
                flag++;
        }
            // if flag is zero it means this value is not in intersection add this value to remainder array
        if(flag==0)
            {
                Remainder[count_r] = headB->value;
                count_r++;
            }
            headB = headB->next;
    }

    // if remainder array is zero then all components in headA and headB is equal
    if(count_r==0)
        //so just return intersection
        return head;
    //else add remainder values ton intersection array
    for(int i = 0 ; i<count_r ; i++)
    {
        head = Insert(head, Remainder[i]);
    }
    return head;
}

void Print(List head)
{
    while(head!=NULL)
    {
        printf("%d ",head->value);
        head = head->next;
    if(head == NULL)
        {
            printf("\n");
            return;
        }
    }
}

int main()
{
    List headA = NULL;
    List headB = NULL;
    int n, m;
    int value;

    printf("Input the number of integers in A:\n");
    scanf("%d", &n);
    printf("Input these integers:\n");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &value);
        headA = Insert(headA, value);
    }

    printf("Input the number of integers in B:\n");
    scanf("%d", &m);
    printf("Input these integers:\n");
    for(int i=0; i<m; i++)
    {
       scanf("%d", &value);
       headB = Insert(headB, value);
    }

    List headC = NULL;
    List headD = NULL;
    headC = Intersection(headA, headB);
    headD = Union(headA, headB);

    Print(headA);
    Print(headB);
    printf("The intersection list contains:\n");
    Print(headC);
    printf("The union list contains:\n");
    Print(headD);

    return 0;
}

