#include<stdio.h>

void exch(int a[], int i, int j){
  int tmp;
  tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

int partition(int a[], int p, int r){
  int j, i, x;

  x = a[r];
  i = p-1;
  for(j=p;j<r;j++){
    if(a[j] <= x){
      i = i + 1;
      exch(a,i,j);
      printf("i=%d, j=%d\n",i,j);
    }
  }
  exch(a,r,i+1);
  return i+1;
}

void sort(int a[], int p, int r){
  int q;

  if(p < r){
    q = partition(a,p,r);
    /*(ア),(イ)*/
    sort(a,p,q-1);
    sort(a,q+1,r);
  }
}

int select(int a[], int p, int r, int i){
  int q,k;

  if(p == r){
    return a[p];
  }
  q = partition(a, p, r);
  k = q - p;
  if(i == k){
    return a[q];
  }else if(i < k){
    return select(a,p,q-1,i);
  }else{
    return select(a, q+1, r, i-(k+1));
  }
}

int main(){
  int a1[] = {5, 10, 7, 12, 8, 9};

  partition(a1, 0, 5);
}