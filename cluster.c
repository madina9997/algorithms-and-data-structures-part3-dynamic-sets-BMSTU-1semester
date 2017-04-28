/*Имеется вычислительный кластер, состоящий из N однопроцессорных узлов. На кластере нужно выполнить M задач. 
Каждая задача описывается парой ⟨t ,t ⟩ 1 2, где t1 – время в микросекундах от включения кластера, начиная с которого 
задачу можно посылать на выполнение (до этого времени входные данные для задачи неготовы); t2 – прогнозируемое время 
выполнения задачи в микросекундах.

Для выполнения каждой задачи задействуется один узел кластера, то есть задачи невозможно распараллеливать. 
Кроме того, нельзя менять порядок выполнения задач: если данные для задачи A оказываются подготовлены раньше,
чем данные для задачи B, то задача A не может быть запущена позже задачи B.

Необходимо составить программу cluster.c, вычисляющую минимальное время в микросекундах от начала работы кластера,
когда все задачи будут выполнены. В программе нужно использовать очередь с приоритетами для хранения времен окончания задач, 
запущенных на кластере. */

#include<stdio.h>
#include<stdlib.h>

struct Task{
  int t1,t2;
};

struct Task InitTask(int p,int q)
{
  struct Task helper;
  helper.t1=p;
  helper.t2=q;
  return helper;
}

struct Queue{
  struct Task *heap;
  int cap;
  int count;
};

struct Queue InitQueue(int n)
{
  struct Queue helper;
  helper.heap=malloc(n*sizeof(struct Task));
  helper.cap=n;
  helper.count=0;
  return helper;
}

struct Task Peak(struct Queue *q)
{
  return q->heap[0];
}

void Insert(struct Queue *q,struct Task t)
{
  int i=q->count;
  struct Task temp;
  q->count=i+1;
  q->heap[i]=t;
  while ((i>0) && (q->heap[(i-1)/2].t1+q->heap[(i-1)/2].t2)>(q->heap[i].t1+q->heap[i].t2)) {
    temp=q->heap[(i-1)/2];
    q->heap[(i-1)/2]=q->heap[i];
    q->heap[i]=temp;
    i=(i-1)/2;
  }
}

void Heapify(struct Queue *q,int i, int n)
{
  int l,r,j;
  struct Task temp;
  while (1==1) {
    l=2*i+1;
    r=l+1;
    j=i;
    if (l<n && (q->heap[l].t1+q->heap[l].t2)<(q->heap[i].t1+q->heap[i].t2))
      i=l;
    if (r<n && (q->heap[r].t1+q->heap[r].t2)<(q->heap[i].t1+q->heap[i].t2))
      i=r;
    if (i==j)
      break;
    temp=q->heap[i];
    q->heap[i]=q->heap[j];
    q->heap[j]=temp;
  }
}

struct Task ExtractPeak(struct Queue *q)
{
  struct Task t;
  t=q->heap[0];
  q->count=q->count-1;
  if (q->count>0) {
    q->heap[0]=q->heap[q->count];
    Heapify(q,0,q->count);
  }
}

int main() {
  int n,m,i,p,b,max;
  struct Task t;
  scanf("%d",&n);
  scanf("%d",&m);
  struct Queue q;
  q=InitQueue(n);
  for (i=0;i<n;i++) {
    scanf("%d %d",&p, &b);
    t.t1=p;
    t.t2=b;
    Insert(&q,t);
  }

  for(i=n;i<m;i++){
    t=Peak(&q);
    ExtractPeak(&q);
    scanf("%d %d",&p,&b);
    if ((t.t1+t.t2)<p) t.t1=p;
    else t.t1+=t.t2;
    t.t2=b;
    Insert(&q,t);
  }
  max=q.heap[0].t1+q.heap[0].t2;
  for (i=1;i<n;i++) {
    if ((q.heap[i].t1+q.heap[i].t2)>max)
      max=q.heap[i].t1+q.heap[i].t2;
  }
  printf("%d",max);
  free(q.heap);
  return 0;
}
