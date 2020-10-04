#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <string.h>
#include <errno.h> 
#include <stdlib.h>

//gera um número pseudorandomico, real no intervalo [0,1]
float realRandon(void){
  int a = rand()%1000;
  int b = rand()%1000;
  if(a>b) return (float)b/a;
  else  return (float)a/b;
}

//devolve um valor de um cosseno pseudorandomico
float coseno(void){
  int a = rand()%1000;
  int b = rand()%1000;
  return ((float)b / sqrt(a*a+b*b));
}

int main(int argc, char  *argv[])
{
  float soma = 0;
  int i, max, count =0;
  long seed = time(NULL);
  srand((unsigned)seed);
  printf("Digite o valor maximo:\n");
  scanf("%d", &max);

  if(max>1){
  if(max%2!=0) i = max/2;
  else i = (max/2)-1;
  }
  else{
    printf("Valor muito pequeno\n");
    exit(0);
  }
  pid_t pid;
  pid = fork();
  if(pid<0){
    printf("Ops, :(\n");
    perror(argv[0]);
    exit(errno);
  }
  else if(pid==0){
  int j = 0;
  for(; j<=i; j++)    if(realRandon() < coseno())  count++;
  printf("Valor do filho: %f\n", 2.0*(float)j /(1.0*count));
  }
  else{
  wait(NULL);
  int metade = i;
  for(; i<max; i++)    if(realRandon() < coseno())  count++;
  i -= metade;
  printf("Valor do Pai: %f\n", 2.0*(float)i /(1.0*count));

  }
}
