#include<stdio.h>
#include<string.h>
#define N 10

struct kv {
  char *key;
  int value;
};

struct kv kv_array[N];

int search_array(char *key){
  int start = 0;
  int end = N -1;
  int middle;
  while(start <= end){
    middle = (start + end) / 2;
    if(strcmp(kv_array[middle].key, key) == 0){
      return kv_array[middle].value;
    }else if(strcmp(kv_array[middle].key, key) < 0){
      start = middle + 1;
    }else{
      /* (a) */
      end = middle - 1;
    }
  }

  /* (b) */
  return -1;
}

void kv_insert(char *k, int v, int n){
  kv_array[n].key = k;
  kv_array[n].value = v;
}

int main(void){
  /* 動作チェック */
  kv_insert("ant", 120, 0);
  kv_insert("any", 260, 1);
  kv_insert("anyway", 110, 2);
  kv_insert("apart", 380, 3);
  kv_insert("appear", 290, 4);
  kv_insert("apple", 190, 5);
  kv_insert("bad", 400, 6);
  kv_insert("bag", 220, 7);
  kv_insert("below", 310, 8);

  printf("searth_tree(\"anyway\") -> %d\n", search_array("anyway"));
  printf("searth_tree(\"alice\") -> %d\n", search_array("alice"));

  return 0;
}