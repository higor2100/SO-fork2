#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <string.h> 
#include <stdlib.h> 
//gera um número pseudo­randomico real no intervalo [0,1] 
float realRandon(void){
	int a = rand()%1000;
	int b = rand()%1000;
	if(a>b)return (float)b/a;
	else return (float)a/b;
}
//devolve um valor de um cosseno pseudo­randomico
float coseno(void){
	int a = rand()%1000;
	int b = rand()%1000;
	return ((float)b / ((a*a+b*b)^(1/2)));
}

float prob(int total){
	if((total/2147483647)<=(1/4)) return 0.5;
	else if((total/2147483647)<=(1/2)) return 0.25;
	else if((total/2147483647)<=(1-(1/4))) return 0.25/2;
	else if((total/2147483647)<=(1-(1/8))) return 0.25/4;
    else return 0.25/8;
}


int main(int argc, int valMax, char *argv[]){
	pid_t pid;

	float soma = 0;
	int i, count=0, total;
	long seed = time(NULL);
	srand((unsigned)seed);

	i = 0;
	count = 0;
	if(i < total){
	float valorP = prob(total);
	pid = fork();
    printf("%d\n",pid);
		if(pid<0){
			printf("Ops\n");
			return 0;
		}
		else if(pid==0){
			valMax += (int)(total*valorP);
			for(; i < valMax; i++) if(realRandon() < coseno()) count++;
			i = valMax;
      main(argc,valMax, NULL);
			}
        else{
          wait(NULL);
          printf("%f\n", 2.0*(float)i /(1.0*count));
        }
  }
}