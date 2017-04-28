/*Необходимо составить программу qsstack.c, осуществляющую сортировку массива целых чисел в порядке возрастания. */

#include<stdio.h>
#include<stdlib.h>

int n;
int *a;

struct Task {
  int low,high;
};
struct Stack {

  struct Task *data;
  int top;
};

struct Stack InitStack (int n)
{
  struct Stack helper;
  helper.data=(struct Task*)malloc(n*sizeof(struct Task));
  helper.top = 0;
  return helper;
}

void Push(struct Stack *s, struct Task x)
{
  s->data[s->top]=x;
  ++s->top;
}

struct Task Pop (struct Stack *s)
{
  --s->top;
  return s->data[s->top];
}

int compare(int i,int j)
{
  printf("compare %d %d ",i,j);
  return a[i]<a[j]? 1:0;
}

void swap(i,j)
{
  int t;
  t=a[i];
  a[i]=a[j];
  a[j]=t;
}

int partition(int l,int h, void (*swap)(int i, int j))
{
  int i=l,j=i;
  for (;j<h;j++)
    if (a[j]<a[h]) {
      swap(i,j);
      i++;
    }
  swap(i,h);
  return i;
}

void qsstack(struct Stack *s)
{
  int i,l=0,h=(n-1),q;
  struct Task task;
  task.low=0;
  task.high=n-1;
  Push(s,task);
  while (s->top!=0) {
    task=Pop(s);
    l=task.low;
    h=task.high;
    while(l<h) {
      q=partition(l,h,swap);
      task.low=l;
      task.high=(q-1);
      Push(s,task);
      l = q + 1;
    }
  }
}

int main()
{
  int i;
  scanf("%d",&n);
  struct Stack s;
  a=(int*)malloc(n*sizeof(int));
  for (i=0;i<n;i++)
    scanf("%d",a+i);
  s=InitStack(2*n);
  qsstack(&s);
  for (i=0;i<n;i++)
    printf("%d ",a[i]);
  free (s.data);
  free(a);
  return 0;
}
