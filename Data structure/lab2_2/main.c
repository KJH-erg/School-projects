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
#define MAX 100000

typedef enum{FALSE =0, TRUE = 1} Boolean;

typedef struct{
    int size;
    int top;
    int *stacklist;
}stack;

stack *createS(int size){
    stack *s;
    s = (stack*)malloc(sizeof(stack));
    s->size =size;
    s->stacklist = (int*)malloc(size * sizeof(int));
    s->top = -1;
    return s;
}

Boolean IsFull(stack *s){
    if (s->top == s->size -1)
        return TRUE;
    else return FALSE;
}

Boolean IsEmpty(stack *s){
    if (s->top == -1)
        return TRUE;
    else return FALSE;
}


void push(stack *s, char e){
    if (!IsFull(s)){
        s->top++;
        s->stacklist[s->top] = e;

    }
}

char pop(stack *s){
    int i;
    if (!IsEmpty(s)){
        i = s-> stacklist[s->top];
        s->top--;
        return i;
    }else{printf("error\n"); return -1;}
}

char top(stack *s){ return s->stacklist[s->top];}

// function to check the given two values are equal
//  if yes, return 1; else return 0
Boolean isMatching(char character1, char character2)
{
    if(character1 == character2)
        return 1;
    else
        return 0;
}

Boolean test(char exp[], int size_n)
{
    int i = 0;
    // temporary character stored
    char tmp;
    // count the number of open parenthesis
    int count_op=0;
    // count the number of closed parenthesis
    int count_cp=0;
    // count the number of open brakets
    int count_ob=0;
    // count the number of closed parenthesis
    int count_cb=0;
    // stack initialization
    stack *stack_holder = createS(20000);
    // push all stored values in stacks
    for(i=0;i<size_n;i++)
        push(stack_holder,exp[i]);

    // loop until the stack is empty
    while(!IsEmpty(stack_holder))
    {
        // temporary store the value of the top value and delete by pop function
        tmp = pop(stack_holder);
        // if tmp is ( add 1
        if(isMatching('(',tmp))
            count_op++;
        // if tmp is [ add 1
        else if(isMatching('[',tmp))
            count_ob++;
        // if tmp is ) add 1
        else if(isMatching(')',tmp))
            count_cp++;
        // remaing case tmp is ] add 1
        else
            count_cb++;

    }
    //use stack_holder to help checking exp is valid or not, return TRUE if exp is valid, otherwise FALSE.
    if(count_op==count_cp&&count_ob==count_cb)
        return 1;
    else
        return 0;
}

int main()
{
    char value;
    char buf[MAX];
    int size_n;
    printf("Input the number of chars in buf:\n");
    scanf("%d", &size_n);
    printf("Input these chars:\n");
    scanf("%s", buf);

    if (test(buf,size_n))
        printf("Valid \n");
    else
        printf("Invalid \n");

    return 0;
}
