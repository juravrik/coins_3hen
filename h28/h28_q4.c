#include<stdio.h>
#define N 5

int a[N][N] = {
  {0, 1, 1, 0, 0},
  {1, 0, 0, 1, 0},
  {0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0}
};

/* (1) */
int b[N][N] = {
  {0, 1, 1, 0, 0},
  {1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0}
};

int maxranked(){
  int i, j, rank, max = 0, node = -1;

  for(i = 0;i < N;i++){
    rank = 0;
    for(j = 0;j < N;j++){
      if(a[j][i]){
        rank++;
      }
    }

    if(rank > max){
      max = rank;
      node = i;
    }
  }
  return node;
}

int visited[N];
int is_reachable1(int s, int g){
  int i;
  if(s == g){
    return 1;
  }
  if(visited[s]){
    return 0;
  }
  visited[s] = 1;
  for(i = 0;i < N;i++){
    /* (4) */
    if(a[s][i] == 1){
      if(is_reachable1(i, g)){
       return 1;
      }
    }
  }
  return 0;
}

int is_reachable(int s, int g)
{
  int i;
  
  for(int i = 0;i < N;i++){
    visited[i] = 0;
  }
  return is_reachable1(s, g);
}

int dijkstra(int s, int g){
  struct {
    int found;
    int distance;
  }node[N];

  int i, j, min;
  for(i = 0;i < N;i++){
    node[i].found = 0;
    node[i].distance = N;
  }

  node[s].distance = 0;

  for(j = 1;j < N;j++){
    node[s].found = 1;
    if(s == g){
      return node[s].distance;
    }

    for(i = 0;i < N;i++){
      /* (5) */
      if(a[s][i] == 1 && node[i].found != 1){
        if(node[i].distance > (node[s].distance + 1)){
          node[i].distance = (node[s].distance + 1);
        }
      }
    }

    min = N;
    for(i = 0;i < N;i++){
      if(!node[i].found){
        if(node[i].distance < min){
          min = node[i].distance;
          s = i;
        }
      }
    }
  }
  return -1;
}

int main(){
  printf("(2)\n");
  printf("(a):maxranked() = %d\n", maxranked());

  printf("(4)\n");
  printf("(a):is_reachable(0, 4) = %s\n", is_reachable(0,4)? "true" : "false");

  printf("(5)\n");
  printf("(a):dijkstra(0, 3) = %d\n", dijkstra(0,3));
}