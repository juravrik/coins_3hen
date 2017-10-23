#include <stdio.h>
#include <string.h>

int count =0;

int proc(char *text, char *ptn){
  int i = 0, j = 0, m, n;

  n = strlen(text);
  m = strlen(ptn);

  while(i < n){
    count++;
    if(text[i] == ptn[j]){
      if(j == m - 1){
        return i - m + 1;
      }else{
        i++;
        j++;
      }
    }else{
      i = i - j + 1;
      j = 0;
    }
  }
  return -1;
}

int main(int argc, char *argv[]){
  printf("Result: %d.\n",proc(argv[2],argv[1]));
  printf("%d\n",count);
}