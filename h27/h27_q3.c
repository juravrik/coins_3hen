#include<stdio.h>
int count = 0;

void swap(int i, int j, int array[])
{
  int tmp = array[i];
  /*(ア),(イ)*/
  array[i] = array[j];
  /*(ウ)*/
  array[j] = tmp;
}

int max_position(int n, int array[])
{
    count++;
    if(n > 1){
        int p = max_position(n-1, array);
        if(array[n-1] < array[p]){
          return max_position(n-1, array); /* ※ */
          //return p;
        }else{
          /*(エ)*/
          return n-1;
        }
    }
    /*(オ)*/
    return n-1;
}

void s(int n, int array[]){
    if(n > 1){
        swap(n-1, max_position(n, array),array);
        s(n-1,array);
    }
}

void r(int n, int array[]){
    if(n > 1){
        swap(0, max_position(n, array), array);
        r(n-1,array+1);
    }
}

int main(void)
{
  int a10[] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int a10p[] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  printf("(4)\n");
  count = 0;
  s(10, a10);
  printf("A = %d\n", a10[3]);
  printf("B = %d\n", a10[9]);
  printf("C = %d\n", count);
 
  printf("(5)\n");
  r(10, a10);
  printf("D = %d\n", a10p[3]);
  printf("E = %d\n", a10p[9]);
  

  return 0;
}