/*Операция SearchByRank : A × ℕ → P для ассоциативного массива возвращает словарную пару с заданным 
номером в отсортированной последовательности входящих в ассоциативный массив словарных пар.

Модифицируйте представление и реализацию бинарного дерева поиска, чтобы операция SearchByRank
для него работала за время O(h), где h – высота дерева.

Составьте программу ranktree.c, демонстрирующую работоспособность реализованной операции.*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tree{
  int k;
  char *w;
  struct Tree *parent, *left, *right;
};

struct Tree* InitTree()
{
  struct Tree *t=malloc(sizeof(struct Tree));
  t->parent=t->left=t->right=NULL;
  t->w=malloc(20*sizeof(char));
  return t;
}

struct Tree* Descend(struct Tree *t, int k)
{
  struct Tree *x;
  x=t;
  while (x!=NULL && x->k!=k){
    if (k<x->k) x=x->left;
    else x=x->right;
  }
  return x;
}

char * Lookup(struct Tree *t, int k)
{
  struct Tree *x;
  x=Descend(t,k);
  return(x->w);
}

struct Tree* Insert(struct Tree *t)
{
  struct Tree *y, *x;
  y=InitTree();
  scanf("%d %s",&y->k,y->w);
  x=t;
  if (t==NULL) t=y;
  else {
    while (1==1){
      if (y->k<x->k){
        if (x->left==NULL){
          x->left=y;
          y->parent=x;
          break;
        }
        x=x->left;
      }
      else{
        if (x->right==NULL){
          x->right=y;
          y->parent=x;
          break;
        }
        x=x->right;
      }
    }
  }
  return t;
}

struct Tree* Minimum(struct Tree *t)
{
  struct Tree *x;
  if (t==NULL) x=NULL;
  else {
    x=t;
    while (x->left!=NULL) {
      x=x->left;
    }
  }
  return x;
}

struct Tree* Succ(struct Tree *x)
{
  struct Tree *y;
  if (x->right!=NULL) y=Minimum(x->right);
  else{
    y=x->parent;
    while (y!=NULL && x==y->right){
      x=y;
      y=y->parent;
    }
  }
  return y;
}

struct Tree* ReplaceNode(struct Tree *t, struct Tree *x, struct Tree *y)
{
  struct Tree *p;
  if (x==t){
    t=y;
    if (y!=NULL) y->parent=NULL;
  }
  else{
    p=x->parent;
    if (y!=NULL) y->parent=p;
    if (p->left==x) p->left=y;
    else p->right=y;
  }
  return t;
}

char* Search(struct Tree *t, int k)
{
  struct Tree *x = Minimum(t);
  while (k--)
    x = Succ(x);
  return x->w;
}
struct Tree* Delete(struct Tree *t, int k)
{
  struct Tree *x, *y;
  x=Descend(t,k);
  if (x->left==NULL && x->right==NULL)
    t=ReplaceNode(t,x,NULL);
  else if (x->left==NULL)
    t=ReplaceNode(t,x,x->right);
  else if (x->right==NULL)
    t=ReplaceNode(t,x,x->left);
  else{
    y=Succ(x);
    t=ReplaceNode(t,y,y->right);
    x->left->parent=y;
    y->left=x->left;
    if (x->right!=NULL) x->right->parent=y;
    y->right=x->right;
    t=ReplaceNode(t,x,y);
  }
  free(x->w);
  free(x);
  return t;
}


void free_tree(struct Tree *t)
{
    if(t != NULL){
        free_tree(t->left);
        struct Tree *y = t->right;
	free(t->w);
        free(t);
	free_tree(y);
    }
}

int main()
{
  int n,i,j,k;
  struct Tree *t=NULL;
  char str[10];
  scanf("%d",&n);
  for (i=0;i<n;i++){
    scanf("%s",str);
    if (str[0]=='I'){
      t=Insert(t);
    }
    else if (str[0]=='D') {
      scanf("%d",&k);
      t=Delete(t,k);
    }
    else if (str[0]=='L'){
      scanf("%d",&k);
      printf("%s\n", Lookup(t,k));
    }
    else{
      scanf("%d",&k);
      printf("%s\n",Search(t,k));
    }
  }
  free_tree(t);
  return 0;
}
