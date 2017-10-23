#include<stdio.h>
#include<stdlib.h>

struct person{
  char *name;
  struct plist *friends;
};

struct plist{
  struct person *data;
  struct plist *next;
};


/* 自作 */
struct elem{
  struct elem *next;
  int hop;
  struct person *pl;
};

struct pqueue{
  struct elem *head;
  struct elem *tail;
};

void plist_free(struct plist *pl){
  struct plist *tmp = pl;

  while(tmp != NULL){
    tmp = pl->next;
    free(pl);
    pl = tmp;
  }
}

struct plist *plist_alloc(){
  struct plist *tmp;

  tmp = malloc(sizeof(struct plist));
  if(tmp == NULL){
    printf("ERROR");
    return (struct plist *)-1;
  }
  tmp->data = NULL;
  tmp->next = NULL;
  return tmp;
}

void plist_add(struct plist **pl, struct person *p){
  struct plist *tmp1;

  for(tmp1 = *pl; tmp1->next != NULL; tmp1 = tmp1->next){
  }
  if(tmp1->data == NULL){
    tmp1->data = p;  
  }else{
    tmp1->next = plist_alloc();
    tmp1->next->data = p;
  }
}

int plist_contains(struct plist *pl, struct person *p){
  struct plist *tmp;

  for(tmp = pl;tmp != NULL;tmp = tmp->next){
    if(tmp->data == p){
      return 1;
    }
  }
  return 0;
}

struct pqueue *pqueue_alloc(){
  struct pqueue *q;
  
  q = malloc(sizeof(struct pqueue));
  q->head = NULL;
  q->tail = NULL;
  return q;
}

void pqueue_free(struct pqueue *q){
  struct elem *elem, *tmp;

  elem = tmp = q->head;
  while(elem != NULL){
    elem = elem->next;
    free(tmp);
    tmp = elem;        
  }
  free(q);
}

void pqueue_put(struct pqueue *q, struct person *p, int n){
  struct elem *elem;

  elem = malloc(sizeof(struct elem));
  elem->hop = n;
  elem->pl = p;
  elem->next = NULL;
  if(q->tail == NULL){
    q->head = elem;
  }else{
    q->tail->next = elem;
  }
  q->tail = elem;
}

int pqueue_get(struct pqueue *q, struct person **pp, int *np){
  struct elem *elem = q->head;

  if(q->tail == NULL){
    return 0;
  }
  *pp = elem->pl;
  *np = elem->hop;
  q->head = elem->next;
   if(q->head == NULL){
    q->tail = NULL;
  }
  free(elem);
  return 1;
}
/* 自作ここまで */

void print_person(struct person *p){
  printf("Name: %s, friends: {",p->name);
  for(struct plist *pl = p->friends; pl != NULL; pl = pl->next){
    printf("%s, ",pl->data->name);
  }
  printf("}\n");
}

void become_friends(struct person *p1, struct person *p2){
  /* (a) */
  plist_add(&p1->friends, p2);
  /* (b) */
  plist_add(&p2->friends, p1);  
}

void print_common_friends(struct person *p1, struct person *p2){
  /* (c) */
  struct plist *tmp1, *tmp2;

  printf("%s and %s have common friends: {", p1->name, p2->name);
  /* (d) */
  for(tmp1 = p1->friends; tmp1 != NULL; tmp1 = tmp1->next){
    /* (e) */
    for(tmp2 = p2->friends; tmp2 != NULL; tmp2 = tmp2->next){
      /* (f) */
      if(tmp1->data->name == tmp2->data->name){
        /* (g) */
        printf("%s, ", tmp1->data->name);
      }
    }
  }
  printf("}\n");
}

int access_ok1(struct person *p1, struct person *p2, struct plist **visited, 
                struct pqueue *q, int maxhop)
{
  struct person *p;
  int hop;

  pqueue_put(q, p1, 0);
  while(pqueue_get(q, &p, &hop)){
    /* (h) */
    plist_add(visited, p);
    /* (i) */
    if(hop > maxhop){
      return 0;
    }
    /* (j) */
    if(p == p2){
      return 1;
    }
    for(struct plist *pl = p->friends;pl != NULL;pl = pl->next)
    {
      struct person *f = pl->data;
      /* (k) */
      if(plist_contains(*visited, f) == 0){
        /* (l) */
        pqueue_put(q, f, hop+1);
      }
    }
  }
  return 0;
}

int access_ok(struct person *p1, struct person *p2, int maxhop)
{
  struct plist *visited = plist_alloc();
  struct pqueue *q = pqueue_alloc();
  int result = access_ok1(p1, p2, &visited, q, maxhop);

  pqueue_free(q);
  plist_free(visited);
  return result;
}



int main(){
  struct person account[6];

  account[0].name = "Alice";
  account[0].friends = plist_alloc();
  account[1].name = "Bob";
  account[1].friends = plist_alloc();
  account[2].name = "Carol";
  account[2].friends = plist_alloc();
  account[3].name = "Dave";
  account[3].friends = plist_alloc();
  account[4].name = "Ellen";
  account[4].friends = plist_alloc();
  account[5].name = "Frank";
  account[5].friends = plist_alloc();

  become_friends(&account[0], &account[1]);
  become_friends(&account[0], &account[2]);
  become_friends(&account[1], &account[3]);
  become_friends(&account[2], &account[3]);
  become_friends(&account[2], &account[4]);
  become_friends(&account[2], &account[5]);
  become_friends(&account[3], &account[4]);
  become_friends(&account[4], &account[5]);

  for(int i = 0; i < 6; i++){
    print_person(&account[i]);
  }

  print_common_friends(&account[0], &account[5]);


  printf("access_ok(Alice, Frank, 3):%s", access_ok(&account[0], &account[5], 3)? "detected" : "failed");


  return 0;
}