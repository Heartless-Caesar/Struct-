#include<stdio.h>
#include<stdlib.h>


int seqFibonacci(int n);


int main (){
  
  int pos, j;
  
  printf("Insira a posicao que quer da sequencia:\n");
  scanf("%d", &pos);
  
  printf("A sequencia eh:\n");
  
  for(j = 0; j < pos; j++){
     printf("%d ", seqFibonacci(j));
  }
  printf("\n");
  return 0;
  
}


int seqFibonacci(int n){

   if(n == 0){
     
     return 0;
   
   }else if(n == 1){
     
     return 1;
   
   }else{
   
     return (seqFibonacci(n - 1) + seqFibonacci(n - 2));
   
   }
  

}
