#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct record{
  char name[10];
  int point;
  struct record *next;
};

struct record *head = NULL;

void insert_record(char *name, int x){
  struct record *p, *q, *t;

  /*(a)*/
  t = (struct record *)malloc(sizeof(struct record));
  /*(b)*/
  strcpy(t->name, name);
  /*(c)*/
  t->point = x;

  q = NULL;
  for(p = head;p != NULL;p = p->next){
    /*(d)*/
    if(p->point > x){
      break;
    }
    q = p;
  }

  if(q != NULL){
    /*(e)*/
    q->next = t;
  }else{
    head = t;
  }
  t->next = p;
}

int main(int argc, char *argv[]){
  FILE *fp;
  struct record *p;
  int x;
  char name[10], buf[256];

  if(argc != 2){
    printf("missing file argument\n");
    return 1;
  }

  fp = fopen(argv[1], "r");
  if(fp == NULL){
    printf("can't open %s\n", argv[1]);
    return 1;
  }

  while(fgets(buf, sizeof(buf), fp) != NULL){
    sscanf(buf, "%s %d", name, &x);
    insert_record(name, x);
  }

  fclose(fp);

  p = head;
  while(p != NULL){
    printf("%s %d\n", p->name, p->point);
    /*(f)*/
    p = p->next;
  }

  return 0;
}