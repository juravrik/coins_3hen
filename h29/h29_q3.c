#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 1024
#define MAX_SCORE 100

struct item{
  char id[8];
  int math;
  int eng;
};

int readfile(int n, struct item table[]){
  FILE *fp;
  char buf[256],id[8];
  int i = 0,math,eng;

  fp = fopen("h29/h29table.txt", "r");
  if(fp == NULL){
    printf("can't open file\n");
    return -1;
  }

  while((fgets(buf, sizeof(buf), fp) != NULL) && i < n){
    sscanf(buf, "%s %d %d", table[i].id, &table[i].math, &table[i].eng);
    i++;
  }

  fclose(fp);
  return i;
}


void print_table(int size, int r[], struct item t[]){
  int i;
  
  for(i = 0;i < size;i++){
    /* (a),(b),(c) */
    printf("%4d %7s %3d %3d\n",i+1, t[r[i]].id, t[r[i]].math, t[r[i]].eng);
  }
}

/* (2) */
void swap(int r[], int i, int j){
  int tmp;
  tmp = r[i];
  r[i] = r[j];
  r[j] = tmp;
}

/* (3) */
int cmp(int i, int j, int r[], struct item t[]){
  int tmp = t[r[i]].math - t[r[j]].math;

  if(tmp == 0){
    return t[r[i]].eng - t[r[j]].eng;
  }
  return tmp;
}

/* アキバさんver */
void make_ranking(int size, int r[], struct item t[]){
  int i, j;

  for(i = 0;i < size;i++){
    r[i] = i;
  }
  for(i = 0;i < size;i++){
    for(j = size-1;j > i;j--){
      if(cmp(i,j,r,t) > 0){
        swap(r, i, j);
      }
    }
  }
}

/* イバラさんver */
void make_ranking2(int size, int r[], struct item t[]){
  int count[MAX_SCORE + 1];
  int i;

  for(i = 0;i <= MAX_SCORE;i++){
    count[i] = 0;
  }
  for(i = 0;i < size;i++){
    count[t[i].math]++;
  }
  for(i = 1;i <= MAX_SCORE;i++){
    count[i] += count[i-1];
  }
  for(i = size - 1;i >= 0;i--){
    r[--count[t[i].math]] = i;
  }
}

int main(int argc, char *argv[]){
  struct item table[N];
  int rank[N];
  int size = readfile(N, table);

  make_ranking(size, rank, table);
//  make_ranking2(size, rank, table);
  print_table(size, rank, table);
  return 0;
}