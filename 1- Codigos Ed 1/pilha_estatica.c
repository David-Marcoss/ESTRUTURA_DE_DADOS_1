#include<stdio.h>
#include<stdlib.h>

int const MAX=100;

int pilha[MAX];
int topo;

void inicia_pilha(){
	topo=-1;
}

int pilha_vazia(){
	
	if(topo==-1)
		return 0;
	else
		return 1;
}

int pilha_cheia(){

	if(topo==99)
		return 0;
	else
		return 1;
}

void insere_pilha(int valor){
	
	if(pilha_cheia() == 1 ){
		topo++;
		pilha[topo]= valor;
		printf("valor inserido: %d\n",pilha[topo]);
}

void retira_pilha(){
	int aux;
	
	if(pilha_vazia() == 1){
		aux= pilha[topo];
		topo--;
		printf("valor retirado: %d\n",aux);
	}
}

int main(){

	inicia_pilha();

	insere_pilha(4);
	insere_pilha(3);
	insere_pilha(2);
	insere_pilha(1);

	retira_pilha();
	
	return 0;

}



