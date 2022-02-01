#include<stdio.h>
#include<stdlib.h>
#define max 100

int pilha[max];
int topo;

void constroir(){
	topo = -1;
}

int pilha_vazia(){

	if (topo==-1){
		
		printf("pilha vazia\n");
		return 0;
	
	}else{

		return 1;
	}

}

int pilha_cheia(){

	if (topo==max-1){
		
		printf("pilha cheia\n");
		return 0;
	
	}else{

		return 1;
	}

}

void empilhar(int valor){
	
	if(pilha_cheia() == 1){
		topo++;
		pilha[topo]= valor;
		printf("valor inserido: %d \n",pilha[topo]);
	}

}

int desempilhar(int *valor){
	
	if (pilha_vazia() == 1){
		*valor= pilha[topo];
		topo--;
		printf("valor retirado: %d\n",*valor);
	}
}

int main(){
	int valor;

	constroir();
	empilhar(12);
	empilhar(13);
	empilhar(12);
	empilhar(11);
	empilhar(10);
	desempilhar(&valor);
	desempilhar(&valor);
	desempilhar(&valor);
	desempilhar(&valor);
	desempilhar(&valor);
	desempilhar(&valor);
	desempilhar(&valor);
	desempilhar(&valor);




	return 0;
}