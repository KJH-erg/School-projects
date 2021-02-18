
/***********************************************************************************
 * YOU MAY COPY-AND-PASTE YOUR C SOURCE FILE main.c FROM YOUR Code::Blocks PROJECT *
 ***********************************************************************************/

/**
 * ENGG1110 Problem Solving by Programming
 *
 * Project Phase 1
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
 * Student Name : Kim, Jounghoon <fill in yourself>
 * Student ID   : 1155096482 <fill in yourself>
 * Class/Section: ENGG1110F <fill in yourself>
 * Date         : OCT 9, 2017 <fill in yourself>
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* include header file */
int main(void)
{

    double x,y,m1,m2,m3,m4,d, mi1,mi2,mi3,mi4,w1,w2,dp, a, W, R1,R2,R3,R4,dr,dr2,dd,RR1,RR2,RR3,RR4,PI, mul;

    printf("Math Tool Box\r\n");
    printf("/\\/\\/\\/\\/\\/\\/\n");
    printf("Phase 1\n\n");

    printf("Input a 2-element vector v:\n\n");
    scanf("%lf%lf", &x,&y);



    printf("Your 2-element vector v:\n");
    printf("/               \\\n");
    printf("| %+6.2f %+6.2f |\n",x ,y);
    printf("\\               /\n\n");
    printf("Length of vector v = |v| = %f\n\n", sqrt(x*x+y*y));


    printf("Input a 2x2 matrix M:\n\n");
    scanf("%lf%lf", &m1, &m2);
    scanf("%lf%lf", &m3, &m4);
    printf("Your 2x2 matrix M:\n");
    printf("/               \\\n");
    printf("| %+6.2f %+6.2f |\n",m1, m2);
    printf("| %+6.2f %+6.2f |\n",m3, m4);
    printf("\\               /\n\n");
    //determinant
    d = m1*m4-m2*m3;
    //length of vector v
    mul=sqrt(x*x+y*y);

    mi1=m1/d;
    mi2=m2/d;
    mi3=m3/d;
    mi4=m4/d;

    w1=(m1*x)+(m3*y);
    w2=(m2*x)+(m4*y);
    //
    dp=x*w1+y*w2;

    printf("Determinant(M) = %f\n\n", d);

    if(abs(d)<0.00001)
    {
        printf("M has NO inverse!\n\n");
    }
    else
    {
        printf("Inverse(M):\n\n");
        printf("/               \\\n");
        printf("| %+6.2f %+6.2f |\n",mi4, mi2*(-1));
        printf("| %+6.2f %+6.2f |\n",mi3*(-1), mi1);
        printf("\\               /\n\n");
    }

    printf("Multiply vector v with matrix M, yield vector w:\n");
    printf("                  /       M       \\\n");
    printf("                  | %+6.2f %+6.2f |\n",m1, m2);
    printf("                  | %+6.2f %+6.2f |\n",m3, m4);
    printf("                  \\               /\n");
    printf("/               \\ /               \\\n");
    printf("| %+6.2f %+6.2f | | %+6.2f %+6.2f |\n",x ,y, w1 ,w2);
    printf("\\       v       / \\       w       /\n\n");

    W=sqrt(w1*w1+w2*w2);
    a=acos(dp/(W*mul));
    printf("Length of vector w = |w| = %f\n\n", W);
    printf("Dot product of vector v with vector w:\n");
    printf("/               \\   /               \\\n");
    printf("| %+6.2f %+6.2f | . | %+6.2f %+6.2f | = %f\n",x ,y, w1 ,w2, dp);
    printf("\\       v       /   \\       w       /\n\n");

    if(W!=0||mul!=0)
    {
        printf("                                           /  (v.w)  \\\n");
        printf("Angle between vector v and vector w = acos | ------- | = %f radian\n", a);
        printf("                                           \\ |v| |w| /\n");

    }
    else
    {
        printf("Angle between vector v and vector w is UNDEFINED!\n");
    }


    R1=w1*x;
    R2=w2*x;
    R3=w1*y;
    R4=w2*y;

    printf("Multiply vector v with vector w, yield matrix R:\n");
    printf("           /       w       \\\n");
    printf("           | %+6.2f %+6.2f |\n",w1, w2);
    printf("           \\               /\n");
    printf("/        \\ /               \\\n");
    printf("| %+6.2f | | %+6.2f %+6.2f |\n",x ,R1, R2);
    printf("| %+6.2f | | %+6.2f %+6.2f |\n",y ,R3, R4);
    printf("\\    v   / \\       R       /\n\n");
    dr=R1*R4-R2*R3;
    printf("Determinant(R) = %f\n\n", dr);
    printf("Add identity matrix I to matrix R, replacing matrix R, i.e. R += I:\n");
    RR1=R1+1;
    RR2=R2;
    RR3=R3;
    RR4=R4+1;
    printf("/               \\\n");
    printf("| %+6.2f %+6.2f |\n",RR1, RR2);
    printf("| %+6.2f %+6.2f |\n",RR3, RR4);
    printf("\\               /\n\n");

    dr2=RR1*RR4-RR2*RR3;
    printf("Determinant(R) = %f\n\n",dr2);
    printf("Inverse(R), yields matrix RR:\n");
    printf("/               \\\n");
    printf("| %+6.2f %+6.2f |\n",RR4/dr2, RR2*(-1)/dr2);
    printf("| %+6.2f %+6.2f |\n",(-1)*RR3/dr2, RR1/dr2);
    printf("\\               /\n\n");
    dd=(RR4/dr2*RR1/dr2)-(RR2*(-1)/dr2*(-1)*RR3/dr2);
    printf("Determinant(RR) = %f\n\n",dd);
    printf("Multiply matrix R with matrix RR:\n");
    printf("/               \\\n");
    printf("| %+6.2f %+6.2f |\n",RR1*RR4/dr2+RR2*(-1)*RR3/dr2, RR1/dr2*RR2+RR2*(-1)/dr2*RR1);
    printf("| %+6.2f %+6.2f |\n",(-1)*RR3/dr2*RR4+RR4/dr2*RR3, RR1/dr2*RR4+RR2*(-1)/dr2*RR3);
    printf("\\               /\n\n");

    printf("Multiply matrix RR with matrix R:\n");
    printf("/               \\\n");
    printf("| %+6.2f %+6.2f |\n",RR2*(-1)*RR3/dr2+RR1*RR4/dr2, RR2*(-1)/dr2*RR1+RR1/dr2*RR2);
    printf("| %+6.2f %+6.2f |\n",RR4/dr2*RR3+(-1)*RR3/dr2*RR4, RR2*(-1)/dr2*RR3+RR1/dr2*RR4);
    printf("\\               /\n");






    // Enter your code here.


    /* last statement of this C program */
    return 0;
}
