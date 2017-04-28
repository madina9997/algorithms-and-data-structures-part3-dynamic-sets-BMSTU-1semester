/*Пусть стековая машина – это устройство для выполнения арифметических операций, 
использующее для хранения промежуточных результатов вычислений стек целых чисел.
Подразумевается, что каждая операция берёт операнды из стека и оставляет на стеке результат.

Составьте программу stackmachine.c, моделирующую работу стековой машины. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Stack
{
  int * data;
  int top;
};

struct Stack InitStack(int n)
{
  struct Stack s;
  s.data=malloc(2*n*sizeof(int));
  s.top=0;
  return s;
}

void Push(struct Stack * s, int x)
{
  s->data[s->top]=x;
  ++s->top;
  
}

int Pop (struct Stack * s)
{
  --s->top;
  return s->data[s->top];
}

int main ()
{
  int n,i,value,p,q;
  scanf("%d",&n);
  char str[6];
  struct Stack stack;
  stack=InitStack(n);
  for (i=0;i<n;i++) {
    scanf("%s",str);
    if (!(strcmp(str,"CONST"))) {
      scanf("%d",&value);
      Push(&stack,value);
    }
    else if (!(strcmp(str,"ADD"))) Push(&stack, Pop(&stack)+Pop(&stack));
    else if (!(strcmp(str,"SUB"))) Push(&stack, Pop(&stack)-Pop(&stack));
    else if (!(strcmp(str,"MUL"))) Push(&stack, Pop(&stack)*Pop(&stack));
    else if (!(strcmp(str,"DIV"))) Push(&stack, Pop(&stack)/Pop(&stack));
    else if (!(strcmp(str,"MAX"))) {
      p=Pop(&stack);
      q=Pop(&stack);
      Push(&stack, (p<q)? q:p);
    }
    else if (!(strcmp(str,"MIN"))) {
      p=Pop(&stack);
      q=Pop(&stack);
      Push(&stack, (p<q)? p:q);
    }
    else if (!(strcmp(str,"NEG"))) stack.data[stack.top-1]*=(-1);
    else if (!(strcmp(str,"DUP"))) Push(&stack, stack.data[stack.top-1]);
    else if (!(strcmp(str,"SWAP"))) {
      p=Pop(&stack);
      q=Pop(&stack);
      Push(&stack, p);
      Push(&stack, q);
    }
  }
  printf("%d",Pop(&stack));
  free(stack.data);
  return 0;
}
