/*Составьте программу listbsort.c, выполняющую сортировку слов в предложении в порядке возрастания их длин. 
Слова в предложении разделены одним или несколькими пробелами. 
Программа должна формировать однонаправленный список слов, а затем сортировать этот список пузырьком. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Elem {
  struct Elem *next;
  char *word;
};

struct Elem * InitList(char *w)
{
  struct Elem *elem;
  elem=malloc(sizeof(struct Elem));
  elem->word=malloc(20*sizeof(char));
  strcpy(elem->word,w);
  elem->next=NULL;
  return elem;
}

struct Elem * Insert(struct Elem * x, char * w)
{
  struct Elem *y;
  y=InitList(w);
  x->next=y;
  return y;
}

void swap(struct Elem *x)
{
  struct Elem *y,*z;
  y=x->next;
  z=x->next->next;
  x->next=z;
  y->next=z->next;
  z->next=y;
}

void BubbleSort(struct Elem *list)
{
  struct Elem *e, *bound, *t=list->next, *i, *temp=list;
  while (t->next!=NULL){
    t=t->next;
  }
  while(t!=list && t!=list->next){
    bound=t;
    t=list;
    i=list;
    while (i->next->next!=NULL) {
      if (strlen(i->next->word)>strlen(i->next->next->word)) {
        temp=i->next->next;
        swap(i);
        t=i->next;
      }
      i=i->next;
    }
  }
}

int main()
{
  int i,j;
  char * str, *helper;
  str=malloc(100*sizeof(char));
  helper=malloc(20*sizeof(char));
  gets(str);
  struct Elem *list,* elem, *t;
  list=InitList("");
  t=list;
  i=0;
  while (i< strlen(str)){
    while (str[i]==' ') {
      i++;
    }
    j=0;
    while(str[i] && str[i]!=' '){
      helper[j]=str[i];
      i++;
      j++;
    }
    helper[j]='\0';
    t=Insert(t,helper);
  }
  BubbleSort(list);
  elem=list->next;
  while(elem!=NULL){
    printf("%s ",elem->word);
    t=elem->next;
    free(elem->word);
    free(elem);
    elem=t;
  }
  free(list->word);
  free(list);
  free(str);
  free(helper);
  return 0;
}
