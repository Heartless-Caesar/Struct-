#include <math.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
//#define RAND_MAX 1000

int arrSize(int *n);
void insertSort(int arr[], int n); 
void printarr(int arr[], int n); 
 
int main(){ 
  
  int n, i, count = 0;
  int arr[n],num[n];
  time_t t;
  
  printf("Informe o tamanho do vetor desejado\n");
  scanf("%d", &n);
  
  //INICIALIZACAO PARA GERACAO DE NUMEROS ALEATORIOS
  srand(time(0));
  
  //GERANDO NUMEROS ALEATORIOS, OU TENTANDO...
  for(i = 0; i < n; i++){
  	//i SE TORNANDO ALEATORIO ISSO RESULTA EM NAO PRINTAR
  	num[i] =  rand() % 1000; 
  }  
  
  printf("Vetor desordenado: \n");
  printarr(arr, n);
  
  //ORDENACAO
  insertSort(arr, n);
  
  //OUTPUT
  printf("Vetor ordenado \n"); 
  printarr(arr, n);
  
  return 0; 
}

void insertSort(int arr[], int n){ 
   int i, el, j; 
   for (i = 1; i < n; i++){ 
     el = arr[i];
     j = i - 1;
     while (j >= 0 && arr[j] > el) { 
       arr[j + 1] = arr[j]; 
       j = j - 1; 
      } 
     arr[j + 1] = el; 
    } 
}   

void printarr(int arr[], int n){ 
  
  int i; 
   
  for (i = 0; i < n; i++){ 
  
  printf("Posicao %d -> %d ", i+1, arr[i]);
 }  
 printf("\n");
}
