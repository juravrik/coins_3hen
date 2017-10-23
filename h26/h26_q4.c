#include<stdlib.h>
#include<stdio.h>
static int c;

struct node{
  int adjacent;
  struct node *next;
};

void insert_node(struct node *n, int v){
  struct node *t = malloc(sizeof(struct node));
  
  if(n->adjacent == -1){
    t->adjacent = -1;
    t->next = NULL;
    n->adjacent = v;
    n->next = t;
    return;
  }else{
    while(n->next->adjacent != -1){
      n = n->next;
    }
    t->next = n->next;
    n->next = t;
    t->adjacent = v;
  }
}

void visit(int id, int visited[], struct node nodes[]){
  struct node *n;
  c++;
  if(visited[id]){
    return;
  }
  visited[id] = 1;
  for(n = &nodes[id];n->adjacent != -1; n=n->next){
    visit(n->adjacent, visited, nodes);
  }
}

int is_connected(int nnode, struct node nodes[]){
  int i, *visited;

  visited = (int *)malloc(sizeof(int)*nnode);
  for(i = 0; i < nnode; i++){
    visited[i] = 0;
  }
  visit(0, visited, nodes);
  for(i = 0;i < nnode;i++){
    if(visited[i] == 0){
      return 0;
    }
  }
  return 1;
}

int is_euler(int nnode, struct node nodes[]){
  int i, j, count = 0;
  struct node *n;
  if(!is_connected(nnode, nodes)){
    return 0;
  }
  for(i = 0;i < nnode;i++){
    n = nodes[i].next;
    j = 0;
    while(n != NULL){
      j++;
      n = n->next;
    }
    /*(a)*/
    if(j & 1){
      count++;
    }
  }
  return count == 0 || count ==2;
}

int main(void){
  struct node g1[4], g2[4], g3[5];
  int ic1,ic2,ic3,c1,c2;

  for(int i = 0;i<4;i++){
    g1[i].adjacent=-1;
    g1[i].next=NULL;
  }

  insert_node(&g1[0],1);
  insert_node(&g1[1],3);
  insert_node(&g1[1],2);
  insert_node(&g1[1],0);
  insert_node(&g1[2],3);
  insert_node(&g1[2],1);
  insert_node(&g1[3],2);
  insert_node(&g1[3],1);

  for(int i = 0;i<4;i++){
    g2[i].adjacent=-1;
    g2[i].next=NULL;
  }
  insert_node(&g2[0], 2);
  insert_node(&g2[0], 1);
  insert_node(&g2[1], 2);
  insert_node(&g2[1], 0);
  insert_node(&g2[2], 1);
  insert_node(&g2[2], 0);

  for(int i = 0;i<5;i++){
    g3[i].adjacent=-1;
    g3[i].next=NULL;
  }
  insert_node(&g3[0], 1);
  insert_node(&g3[1], 3);
  insert_node(&g3[1], 2);
  insert_node(&g3[1], 0);
  insert_node(&g3[2], 4);
  insert_node(&g3[2], 3);
  insert_node(&g3[2], 1);
  insert_node(&g3[3], 2);
  insert_node(&g3[3], 1);
  insert_node(&g3[4], 2);

  ic1 = is_connected(4,g1);
  c1 = c;
  c = 0;

  ic2 = is_connected(4,g2);
  c2 = c;
  c = 0;

  ic3 = is_connected(5,g3);
  
  printf("(1)\nG1:%d G2:%d G3:%d\n",ic1, ic2, ic3);

  printf("(4)\nexample G1:%d G2:%d G3:%d\n",is_euler(4,g1), is_euler(4,g2), is_euler(5,g3));
}