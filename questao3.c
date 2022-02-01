#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _Pilha{
	char valor;
	struct _Pilha *ant;

}Pilha;


void aloca(Pilha **No){
      Pilha *novo;      //cria uma strutura do tipo pilha

      novo = NULL;

      novo = (Pilha*)malloc(sizeof(Pilha));  //aloca essa estrutura

      *No = novo; //e faz o no receber a estrutura alocada

}

void empilha(int valor,Pilha **topo, Pilha *No){
	
	if (No != NULL){  			//se o no for diferente de NULL quer dizer que o valor foi alocado corretamente
		(*No).valor = valor;   // faz o no receber o valor
		(*No).ant = *topo;    //  e o no anterior recebe o topo
		*topo = No;          // o topo recebe o conteudo do no


	}

}

char desempilha(Pilha **topo){
	char valor;
	Pilha *aux;

	if(*topo != NULL){	 			// se o topo nao for nulo
		valor = (**topo).valor; 	// o valor recebe o conteudo que ta no topo
		aux = *topo;                // auxiliar aopmnta pro topo
		*topo = (**topo).ant;      // o topo a ponta para o valor que ta na posição anterior

		free(aux);             // e da um free no topo

		
	}

	return valor;
}

int valida(char ex[]){
	int i=0,flag = 0, aux = 0;

	pilha *p,*No;

	do{
		if (ex[i] == '('){
			aloca(&No);
			empilha('(',&p,No);
		
		}else if(ex[i] == ')' && p != NULL){
			desempilha(&p);
		}

	}while(ex[i] != '\0' || flag != 1);

	if(pilha != NULL){
		flag = 1;
	}

	return flag;

}

int main(){
	char expressao[1000];

	printf("digite a expressao: \n");
	scanf("%s",expressao);

	if ( valida(expressao)){
		printf("Ha expressao e valida!!\n");
	else
		printf("Ha expressao e invalida!!\n", );









	return 0;
}







