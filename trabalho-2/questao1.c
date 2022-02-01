#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define TAM 10

typedef struct C{
	char placa[20];
	int mov; //indica quantas vezes o carro foi movimentado


}carro;

typedef struct { 
	carro C[10];
	int tras;
	
}fila;  // define a estrutura fila  


void inicia_f(fila *aux){ // inicia fila
	
	aux->tras = -1;

}

int f_vazia(fila aux){ // verifica se a fila ta vazia
	
	if (aux.tras < 0 )
		
		return 1;   //retorna 1 se tiver
	
	else
		return 0; //retorna 0 se nao tiver
	

}

int f_cheia(fila aux){ // verifica se a fila ta cheia
	
	if (aux.tras == TAM-1)       
		return 1;  //retorna 1 se tiver
	else
		return 0; //retorna 0 se nao tiver
}

void ler_carro(carro *carro){  //le dados do carro

	printf("digite a palca do carro: ");
	scanf("%s",carro->placa);

	carro->mov = 0;

}

void copia(fila *est, carro aux){

	strcpy(est->C[est->tras].placa, aux.placa);
	est->C[est->tras].mov =  aux.mov;
}


void enfileira(fila *Est ,carro Car){ //insere um valor na fila

	if (f_cheia(*Est) == 1){  //verifica se a fila ta cheia
		printf("\nEstacionamento esta cheio!! Nao é possivel inserir mais carros\n");
	
	}else{  //se nao tiver insere o item na fila
		Est->tras++;
		copia(Est,Car);

	}

}



void desenfileira(fila *l, carro *Car){ //remove o valor da primeira possição da fila
	int i;

	if (f_vazia(*l) == 1 ){
		printf("\nERRO: lista vazia\n");	
	
	}else{
		*Car = l->C[0]; // recebe o carro que vai ser removido

		for (i = 0; i <= l->tras; ++i){  				//remove o valor da primeira posição da fila
                strcpy(l->C[i].placa,l->C[i+1].placa);	// puxa os valores para tras
                l->C[i].mov = l->C[i+1].mov;

		}

		l->tras--;          //diminui o tamanho da fila
							  
	}

		
}

int sair(fila *l, carro *Car, char *placa){
	int quant_man=-1,cont = 0; //conta quantos carros foram movidos 
	
	int flag=0; //indica se o carro foi encontrado

	fila aux;  //cria fila auxiliar
	carro Car_aux;

	inicia_f(&aux); //inicia fila auxiliar


	if ( strcmp(l->C[0].placa,placa) == 0 ){  // se o carro tiver no inicio
	 	desenfileira(l,Car);
	 	quant_man = 0;
	
	}else{
		
		while(l->tras > -1){

			if (strcmp(l->C[0].placa,placa) != 0  && flag != 1){ //se o carro que estiver no inicio da fila nao for 
													// o que estou procurando 

				l->C[0].mov++; 				// incrementa mov que indica que o primeiro carro da fila foi movimentado
			}
			
			if (strcmp(l->C[0].placa,placa) == 0 ){ //se entrar neste caso quer dizer que encontramos
													//o carro que queremos retirar da fila
				desenfileira(l,Car);    //retorna em car os dados do carros
				quant_man = cont;      //recebe a quantidade de carros que foram movimentados ate tirar o carro
				flag = 1;             //indica se o carro foi encontrado

			}else{
				cont++; 					//conta a quantidade de carros que foram movimentados ate tirar o carro
				desenfileira(l,&Car_aux);  //desenfileira fila de entrada
				enfileira(&aux,Car_aux);   //enfileira fila auxiliar

			}
		}


		*l = aux; // faz a  fila de entrada receber a fila auxiliar

	} 

	
	return quant_man;   //indica a quantidade de carros que foram movimentados ate tirar o carro
						// qunat_man == -1 indica que a placa passada nao existe 

}

int busca(fila *l,char *placa){  // verifica se um carro esta na fila
	int flag = 0; //indica se o carro ja esta no estacionamento
	
	fila aux;
	carro Car_aux;

	inicia_f(&aux);

	if (f_vazia(*l) == 0){
		
		while(l->tras > -1){ //enquanto a fila nao for vazia
				
			if (strcmp(l->C[0].placa,placa) == 0 ){ // verifica a placa
				flag = 1; // indica que o carro ja esta na fila
			}
			desenfileira(l,&Car_aux); //desenfileira fila
			enfileira(&aux,Car_aux); //enfileira em fila auxiliar

		}

		*l = aux; // faz a  fila de entrada receber a fila auxiliar
	} 

	return flag; //flag == o carro nao esta na fila
				//flag == 1 carro  esta na fila

}



int menu(char *op){ // imprime menu

	printf("\n[0] para sair\n" );
	printf("[E] para entrar com carro no estacionamento \n");
	printf("[S] para sair com carro do estacionamento \n");

	printf("\nescolha a opcao: ");
	scanf("%s",op);

	op[0]= toupper(op[0]);


}

int main(){
	fila est;  	 	 // fila do estacionamento
	carro Car;  	// estrutura auxiliar e variavei auxiliares
	char placa[30];
	int quant_man;
	char op[3];

	inicia_f(&est); // iniia fila

	do{
		menu(op);

		if (strcmp(op,"E") == 0){
		
			if (f_cheia(est) == 1){
				printf("\nEstacionamento esta cheio!! Nao é possivel inserir mais carros\n");
					
			}else{
				ler_carro(&Car);
				
				if(busca(&est,Car.placa) == 0){
					enfileira(&est,Car);
					printf("\nCarro foi inserido no estacionamento!!\n");
					
				}else{
					printf("\nERRO!! ja exite um carro com esta placa\n");
				}
			
			}

		}else if(strcmp(op,"S") == 0){

			if (f_vazia(est) == 1){
					printf("\nEstacionamento esta vazio!!\n");
					
			}else{

				printf("digite a placa do carro: ");
				scanf("%s",placa);
					
				

				if(busca(&est,placa) == 1){ // verifica se o carro existe

					quant_man = sair(&est,&Car,placa);

					printf("\ncarro saiu do estacionamento!\n");

					printf("\nquantidade de vezes que o carro foi manobrado para que outros carros saisem: %d \n",Car.mov);
					printf("quantidade  carros foram manobrados para que ele saisse: %d \n",quant_man);
			
				}else{

					printf("\nERRO!! placa de carro invalida\n");
				}
			}
		
		}else if (strcmp(op,"0") != 0){
			printf("\nopção invalida!!\n");
		}
			


	}while(strcmp(op,"0") != 0);


	return 0;
}