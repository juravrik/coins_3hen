#include <stdio.h>
#include <stdlib.h>
static int c1,c2;

unsigned int check_flag1(unsigned int *flag, unsigned int p){
  if(flag[p]!=0){
    c1++;
  }
  return flag[p];
}

void reset_flag1(unsigned int *flag, unsigned int p){
  flag[p] = 0;
}

void prime1(unsigned int max){
    unsigned int p, i;
    unsigned int *flag = 
        (unsigned int *) malloc(sizeof(unsigned int) * (max + 1));

    //initialization of all flags
    for (p = 2; p <= max ; p++){
      flag [p] = 1;
    }
    //sieving (FURUI NI KAKERU)
    for (p = 2; p * p <= max; p++){
        if (check_flag1(flag, p) != 0){
            for (i = p * p; i <= max; i += p) {
              reset_flag1(flag, i);
              c2++;
            }
        }
    }
    //output
    for (p = 2; p <= max; p++){
        if (check_flag1(flag, p) != 0) printf("%d ", p);
    }
    printf ("\n");
}

int main(){
  prime1(10);
  printf("(1) %d回\n",c1);

  c2 = 0;
  prime1(100);
  printf("(2) %d回\n",c2);
}