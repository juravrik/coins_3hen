#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int check_flag2(unsigned int *flag, unsigned int p){
  return (flag[p / 32] & (1 << (p % 32)));
}

void reset_flag2(unsigned int *flag, unsigned int p){
  /*(ア)*/
  flag[p / 32] &= ~(1<< (p % 32));
}

void prime2(unsigned int max){
    unsigned int p, i;
    unsigned int words = ceil((double) (max + 1) / 32);
    unsigned int *flag = 
        (unsigned int *) malloc(sizeof(unsigned int) * words);

    //initialization of all flags
    for (i = 0; i < words; i++){
      flag [i] = 0xFFFFFFFF;
    }
    //sieving (FURUI NI KAKERU)
    for (p = 2; p * p <= max; p++){
        if (check_flag2(flag, p) != 0){
          for (i = p * p; i <= max; i += p){
            reset_flag2(flag, i);
          } 
        }
    }
    //output
    for (p = 2; p <= max; p++){
      if (check_flag2(flag, p) != 0){
        printf("%d ", p);
      }
    }
    printf ("\n");
    printf("(5) %x\n", flag[0]);
}

int main(){
  prime2(10);
}