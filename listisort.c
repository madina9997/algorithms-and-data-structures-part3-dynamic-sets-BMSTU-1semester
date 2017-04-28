/*Составьте программу listisort.c, выполняющую сортировку двунаправленного кольцевого списка целых чисел по возрастанию.
В программе должен быть реализован алгоритм сортировки вставками. */

#include<stdio.h>
#include<stdlib.h>

struct Elem{
  struct Elem *prev, *next;
  int v;
};

struct Elem * InitPtr()
{
  struct Elem *ptr;
  ptr=(struct Elem*)malloc(sizeof(struct Elem));
  ptr->prev=ptr;
  ptr->next=ptr;
  return(ptr);
}

int ListEmpty(struct Elem * ptr)
{
  return (ptr->next=ptr)? 1:0;
}

void Insert(struct Elem *x,struct Elem *y)
{
  struct Elem *z;
  z=x->next;
  x->next=y;
  y->prev=x;
  y->next=z;
  z->prev=y;
}

void Delete(struct Elem *x)
{
  struct Elem *y, *z;
  y=x->prev;
  z=x->next;
  y->next=z;
  z->prev=y;
  x->prev=x->next=NULL;
}

void InsertSort(struct Elem *ptr)
{
  struct Elem *i;
  i=ptr->next;
  struct Elem *a, *loc;
  while (i!=ptr){
    loc=i->prev;
    while ((loc!=ptr) && (loc->v > i->v)) {
      loc=loc->prev;
    }
    Delete(i);
    Insert(loc,i);
    i=i->next;
  }
}

int main()
{
  int n,i;
  scanf("%d",&n);
  struct Elem *ptr;
  ptr=InitPtr();
  struct Elem *elem, *t;
  for(i=0;i<n;i++) {
    elem=InitPtr();
    scanf("%d",&elem->v);
    Insert(ptr,elem);
  }
  InsertSort(ptr);
  elem=ptr->next;
  while (elem!=ptr) {
    printf("%d ",elem->v);
    elem=elem->next;
  }
  elem=ptr->next;
  while (elem!=ptr) {
    t=elem->next;
    free(elem);
    elem=t;
  }
  free(ptr);
  return 0;
}
