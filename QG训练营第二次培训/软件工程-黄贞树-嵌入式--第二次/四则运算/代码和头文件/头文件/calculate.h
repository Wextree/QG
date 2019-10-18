#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef enum Status
{
    ERROR = 0,SUCCESS = 1
}Status;

typedef struct intSqStack{
       int	*elem;
       int top;
       int size;
}intSqStack;

typedef struct charSqStack{
       char	*elem;
       int top;
       int size;
}charSqStack;

int priority(char c);
Status initIntStack(intSqStack *s1,int sizes);
Status initCharStack(charSqStack *s2,int sizes);
int getTopStack(intSqStack *s1);
Status changeTop(intSqStack *s1,int num);
Status pushIntStack(intSqStack *s1,int num);
Status pushCharStack(charSqStack *s2,char c);
char getCharTop(charSqStack *s1);
Status changeCharTop(charSqStack *s2,char c);
Status getTwoNum(intSqStack *s1,int *num1,int *num2);
int calculate(int num1,int num2,char c);
char popCharStack(charSqStack *s2);
int stackLength(charSqStack *s2);

#endif
