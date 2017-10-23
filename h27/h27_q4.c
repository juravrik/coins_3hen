#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100
int count = 0;

struct dict_list{
  /*(ア)*/
  struct dict_list *next;
  char *name;
};

struct dict_list *bucket[N];

int h(char *str){
  return *str%N;
}

int h2(char *str){
  return (str[0] + str[1]) % N;
}

int h3(char *str){
  unsigned int i, v;
  int l = strlen(str);

  v = 0;
  for(i = 0;i < l; i++){
    v = v + (str[i] << ((i * 7) % 31));
  }

  return v % N;
}

int search(char *str){
  struct dict_list *elem;
  int i;
  i = h(str);
  //i = h2(str);
  //i = h3(str);
  elem = bucket[i];
  while(elem){
    count++;
    if(!strcmp(elem->name, str)){
      return -1;
    }
    elem = elem->next;
  }
  /*(イ)*/
  return i;
}

void insert(char *str){
  struct dict_list *new;
  int i;

  i = search(str);
  if(i<0){
    return;
  }
  new = malloc(sizeof(struct dict_list));
  /*(ウ)*/
  new->next = bucket[i];
  new->name = str;
  /*(エ)*/
  bucket[i] = new;
}

void disply(void){
  int i;
  struct dict_list *elem;
  
  for(i = 0; i < N;i++){
    elem = bucket[i];
    if(elem == NULL){
      continue;
    }
    printf("bucket[%d]->",i);
    while(elem){
      printf("[%s]->",elem->name);
      /*(オ)*/
      elem = elem->next;
    }
    printf("[]\n");
  }
}

int main(void){
  insert("hydrogen");
  insert("hellium");
  insert("lithium");
  insert("beryllium");
  insert("boron");
  insert("carbon");
  insert("nitrogen");
  insert("oxygen");
  insert("fluorine");
  insert("neon");
  
  printf("(2)\n");
  disply();

  printf("(3)\n");
  count = 0;
  insert("natrium");
  printf("%d回\n", count);
  return 0;
}