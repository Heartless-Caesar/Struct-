/*
    2012160 - JOAO VICTOR CESA ANDRADE
     
    O processo deve conter um id do processo (PID) e o  do processo.
    O escalonador deve conter pelo menos duas filas de prioridade.
    Devem constar as seguintes funções
        
        Adicionar processo: adiciona um novo processo a uma fila. 
        Caso não seja definida a fila o processo será adicionado à fila de menor prioridade
        
        Executar processo: executa o primeiro processo da fila de maior prioridade que esteja com processos pendentes.
         O processo é movido para o final da fila de prioridade imediatamente inferior.
        
        Mover processo entre filas: transfere um processo de uma fila para outra.
         O processo movido pode estar em qualquer posição da fila de origem e será colocado no final da fila de destino.
        
        Finalizar processo: Encerra o primeiro processo da fila de maior prioridade,
         removendo-o completamente do sistema.
        
        Finalizar processo específico: Encerra um processo a partir do ID escolhido,
         removendo-o completamente do sistema. O processo pode estar em qualquer fila no momento da remoção.

*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct processo{
  
  struct processo *prox;
  int pid;
  char *name;

} ;

struct processo *criarLista(struct processo *Lista);
struct processo *criarElemento(int pid,char *name);
void moverProcesso(struct processo *Maior,struct processo *Menor, int idx);
void inserirProcesso(struct processo *lista, int pid, char *name);
void executarProcesso(struct processo *Maior, struct processo *Menor);
void removerPID(struct processo *Lista, int pid);
void addMenor(struct processo *Menor,int elemento, char *nomeP);
void finalizarProcesso(struct processo *Maior);
void printElement(struct processo *element);
void print(struct processo *List);
void printOutput(struct processo *Maior, struct processo *Menor);

int main(){
   
   int op, opc, temPID, cont, pos, remID;
   char *nomeP;
   
   struct processo *Maior = (struct processo *)malloc(sizeof(struct processo));
   struct processo *Menor = (struct processo *)malloc(sizeof(struct processo));

   criarLista(Maior);
   criarLista(Menor);
   
   do{
   
   printf("Que operacao deseja realizar:\n(1)Adicionar processo\n(2)Executar processo\n(3)Mover processo\n(4)Finalizar processo\n(5)Remover PID\n");
   scanf("%d",&opc);
   system("clear");
   switch(opc){
   
   case 1:
   
   printf("Em que lista deseja adicionar um processo:(1)Maior (2)Menor\n");
   scanf("%d", &op);
   
   if(op == 1){
     
     printf("Insira o PID do processo\n");
     scanf("%d", &temPID);
     printf("Insira o Nome do processo\n");
     scanf("%s", nomeP);
     inserirProcesso(Maior, temPID, nomeP);
     
     printOutput(Maior, Menor);
     
   }else{
     
     printf("Insira o PID do processo\n");
     scanf("%d", &temPID);
     printf("Insira o Nome do processo\n");
     scanf("%s", nomeP);
     inserirProcesso(Menor, temPID, nomeP);
     
     printOutput(Maior, Menor);
   }
 
   break;
   
   case 2:
     
     executarProcesso(Maior, Menor);
     printOutput(Maior, Menor);
     
   break;
   
   case 3:
     
     printf("Em que lista deseja mover um processo:(1)Maior (2)Menor\n");
     scanf("%d", &op);
   
    if(op == 1){
     
      printf("Insira o indice do processo(A partir de 1)\n");
      scanf("%d", &pos);
      moverProcesso(Maior, Menor,pos);
      printOutput(Maior, Menor);
     
     }else{
     
      printf("Insira o indice do processo(A partir de 1)\n");
      scanf("%d", &pos);
      moverProcesso(Menor, Maior, pos);
     
      printOutput(Maior, Menor);
    }
   
     
   
   break;
   
   case 4:
   
     finalizarProcesso(Maior);
     printOutput(Maior, Menor);
   
   break;
   
   case 5:
   
    printf("Insira o PID a ser removido\n");
    scanf("%d", &remID);
   
    removerPID(Maior, remID);
    
    removerPID(Menor, remID);
    
    printOutput(Maior, Menor);
   break;
   
   default:
    printf("Opcao invalida");
   break; 
   }
     
   printf("Deseja realizar outra operacao:(1)Sim (2)Nao\n");
   scanf("%d",&cont);
   system("clear");
  }while(cont == 1); 
   
   
   return 0;
}

//CREATE EMPTY LIST
struct processo *criarLista(struct processo *Lista){
    Lista->prox = NULL;
}

//CREATE ELEMENT
struct processo *criarElemento(int pid,char *name){
       
        struct processo *newP = (struct processo *)malloc(sizeof(struct processo));
	
	newP->pid = pid;
	newP->name = malloc(sizeof(char *));
	strcpy(newP->name, name);
	newP->prox = NULL;
	
	return newP;	
}

//INSERT PROCESS
void inserirProcesso(struct processo *lista, int pid,char *nomeP){
    
   struct processo *newP = criarElemento(pid, nomeP); 
    
   if(lista == NULL){
    
    lista = newP;
    
   } else {
   
     newP->prox = lista->prox;
     lista->prox = newP;
     
   }
  
}
//EXECUTE PROCESS
void executarProcesso(struct processo *Maior, struct processo *Menor){
  
  struct processo *elementoAtual = Maior->prox;
	
	//IF ONLY 1 ITEM
	if (elementoAtual->prox == NULL) {
	
		Maior = NULL;
	        
	
	} else {	
	
		struct processo *elementoAnterior = Maior->prox;	
		while (elementoAtual->prox != NULL) {
			elementoAnterior = elementoAtual;
			elementoAtual = elementoAtual->prox;
		}
		addMenor(Menor, elementoAtual->pid,elementoAtual->name); 		
		elementoAnterior->prox = NULL;
	}
	
    free(elementoAtual);				

}

void addMenor(struct processo *Menor, int elemento, char *nomeP){
   
   struct processo *newP = criarElemento(elemento, nomeP);
   
   if(Menor == NULL){
    
    Menor->prox = newP;
    
   } else {
   
     newP->prox = Menor->prox;
     Menor->prox = newP;
   
   }
   
}


//FINALIZAR PROCESSO FILA MAIOR
void finalizarProcesso(struct processo *Maior){
  
  struct processo *elementoAtual = Maior->prox;
	
	if (elementoAtual->prox == NULL) {
	
		Maior->prox = NULL;
	
	} else {	
		
		struct processo *elementoAnterior = Maior->prox;	
		while (elementoAtual->prox != NULL) {
			elementoAnterior = elementoAtual;
			elementoAtual = elementoAtual->prox;
		} 		
		elementoAnterior->prox = NULL;				
	}
	
	free(elementoAtual);
  
}

void moverProcesso(struct processo *Lista1,struct processo *Lista2, int idx){
   
 
   int i = 1;
   struct processo *temp, *posicao;
   temp = Lista1->prox;
   
   if(Lista1 == NULL){
     printf("Lista vazia\n");
   }
   else if(idx == 0){
      printf("Indice invalido\n"); 
   }
   else{
     
     while(i <= idx - 1){
       temp = temp->prox;
       i++;
     }
     addMenor(Lista2,temp->prox->pid,temp->prox->name);
     posicao = temp->prox;
     temp->prox = posicao->prox;
     
     free(posicao);
   }
}

void removerPID(struct processo *Lista, int remID){
   
   struct processo *temp = Lista;
   
   if(Lista == NULL){
   
   printf("Nada para remover\n");
   
   }else{
      
      while(temp->prox != NULL){
      
        if(temp->prox->pid == remID){
        
          temp->prox = temp->prox->prox;
        
        }else{
          
          temp = temp->prox;
          
        }
      
      }
   }
   

}


void print(struct processo *List) {
	
	if (List == NULL) {
		printf("Lista vazia \n");
	} else {
		struct processo *elementoAtual = List->prox;
		
		 if(elementoAtual != List){
		  while (elementoAtual != NULL && elementoAtual != List){
			printElement(elementoAtual);
			elementoAtual = elementoAtual->prox;
		}
	   }
	}
}

void printElement(struct processo *element) {	
	printf("ID: %d\n", element->pid );
	printf("Nome: %s\n", element->name);
}

void printOutput(struct processo *Maior, struct processo *Menor){

     printf("---------------\n");
     printf("Fila de maior prioridade\n");
     printf("---------------\n");
     print(Maior);
     printf("---------------\n");
     printf("Fila de menor prioridade\n");
     printf("---------------\n");
     print(Menor);
     printf("---------------\n");
     
}
