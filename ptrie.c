/*Реализуйте структуру данных, представляющую множество строк с операциями Insert (добавление строки в множество),
Delete (удаление строки из множества) и Prefix (подсчёт количества строк множества, имеющих указанных префикс).
Операции Insert и Delete должны работать за время O(len (k)), где k – добавляемая или удаляемая строка,
а операция Prefix – за время O(len (p)) – где p – префикс.

Составьте программу ptrie.c, демонстрирующую работоспособность реализованных операций. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define M 26
 
struct Peak {
  int v;
  struct Peak *parent;
  struct Peak **arcs;
  int prefix;
};
 
struct Pair{
  int i;
  struct Peak *x;
};
 
int Prefix(struct Peak* base, char* k) {
  int i, len_k = strlen(k), tmp = 0,z = 0;
  struct Peak* x = base;
  for ( i = 0; i < len_k; x = x->arcs[k[i]-97], i++)
    if (x->arcs[k[i] - 97] == NULL ) return 0;
  return x->prefix;
}
 
 
struct Peak * InitTrie()
{
  struct Peak *t = calloc(1,sizeof(struct Peak));
  t->v= t->prefix = 0;
  t->parent=NULL;
  t->arcs= calloc(M, sizeof(struct Peak *));
  return t;
}
 
 
struct Pair Descend(struct Peak* t, char *k)
{
  struct Peak *x, *y;
  x = t;
  int i = 0, len = strlen(k);
  while (i < len){
    y = x->arcs[k[i]-97];
    if ( y == NULL) break;
    y->prefix++;
    x = y;
    i++;
  }
  struct Pair p; p.x = x; p.i = i;
  return p;
}
 
 
void Insert(struct Peak *t, char *k)
{
  struct Pair temp = Descend(t,k);
  struct Peak *x = temp.x, *y;
  int i, len = strlen(k);
 
  i=temp.i;
  while (i < len){
    y=InitTrie();
    x->arcs[k[i]-97]=y;
    y->parent=x;
    y->prefix++;
    x=y;
    i++;
  }
  if (x->v > 0) {
    for(x->v = 0; x->parent != NULL; x = x->parent)
      x->prefix--;
  }
  else
    x->v++;
}
 
void Delete(struct Peak *t, char* k) {
  struct Peak *x,*y;
  int i,len_k;
  for ( x = t, i = 0, len_k = strlen(k); i < len_k;x = y, i++) {
    y = x->arcs[k[i] - 97];
    if ( y == NULL) break;
    y->prefix--;
  }
}
 
 
void free_bor(struct Peak *x)
{
    int i;
    for(i=0;i<M;++i)
    {
        if(x->arcs[i]!=NULL)
            free_bor(x->arcs[i]);
    }
    free(x->arcs);
    free(x);
}
int main()
{
  struct Peak *t;
  t=InitTrie();
  char str[7];
  char *stroka;
  stroka=malloc(100000000*sizeof(char));
  int n,i;
  scanf("%d",&n);
  for (i=0;i<n;i++){
    scanf("%s",str);
    if (str[0]=='I') {
      scanf("%s",stroka);
      Insert(t, stroka);
    }
    if (str[0]=='D'){
      scanf("%s",stroka);
      Delete(t,stroka);
    }
    if (str[0]=='P'){
      scanf("%s",stroka);
      printf("%d\n",Prefix(t,stroka));
    }
  }
  free_bor(t);
  free(stroka);
  return 0;
}
