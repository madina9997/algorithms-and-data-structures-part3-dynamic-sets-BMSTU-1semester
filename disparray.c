/*Пусть разреженный целочисленный массив представлен в виде хеш-таблицы размера m. 
Реализуйте для него операции At и Assign. Составьте программу disparray.c,
демонстрирующую работоспособность реализованных операций. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Elem{
  struct Elem * next;
  int k,v;
};

struct Elem *  InitList()
{
  struct Elem * elem;
  elem=malloc(sizeof(struct Elem));
  elem->next=NULL;
  elem->k=0;
  elem->v=0;
  return elem;
}

struct Elem ** InitTable(int m)
{
  struct Elem **t;
  int i;
  t=malloc(m*sizeof(struct Elem *));
  for (i=0;i<m;i++){
    t[i]=InitList();
  }
  return t;
}

int h(int i,int m)
{
  return i%m;
}

struct Elem * ListSearch(struct Elem * l,int v)
{
  struct Elem * x;
  x=l;
  while (x!=NULL && x->k!=v)
    x=x->next;
  return x;
}

void Lookup(struct Elem ** t, int (*h)(int i,int m),int k,int m)
{
  struct Elem *p;
  p=ListSearch(t[h(k,m)],k);
  if (p==NULL) printf("0\n");
  else printf("%d\n",p->v);
}

struct Elem * InsertBeforeHead(struct Elem * l, struct Elem *y)
{
  y->next=l;
  l=y;
  return y;
}

void Insert(struct Elem ** t, int (*h)(int i,int m),int k,int v,int m)
{
  int i;
  i=h(k,m);
  struct Elem * elem;
  elem=InitList();
  elem->k=k;
  elem->v=v;
  t[i]=InsertBeforeHead(t[i],elem);
}

int main()
{
  int n,m,i,k,v;
  scanf("%d",&n);
  scanf("%d",&m);
  char *str;
  struct Elem * temp,*elem;
  struct Elem ** t;
  str=malloc(7*sizeof(char));

  t=InitTable(m);
  for (i=0;i<n;i++){
    scanf("%s",str);
    if (str[1]=='T'){
      scanf("%d",&k);
      Lookup(t,h,k,m);
    }
    else{
      scanf("%d %d",&k,&v);
      Insert(t,h,k,v,m);
    }
  }
  for (i=0;i<m;i++){
    elem=t[i];
    while(elem!=NULL){
      temp=elem->next;
      free(elem);
      elem=temp;
    }
  }
  free(t);
  free(temp);
  free(elem);
  free(str);
  return 0;
}
