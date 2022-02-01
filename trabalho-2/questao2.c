#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define TAM 10

typedef struct C{
	char placa[20];
	int mov; //indica quantas vezes o carro foi movimentado


}carro;


typedef struct F{   //declara a estrutura fila
	
	carro C;
	struct F *prox;

}Fila;

void ler_carro(carro *carro){  //le dados do carro

	printf("digite a palca do carro: ");
	scanf("%s",carro->placa);

	carro->mov = 0;

}

void aloca(Fila **No, carro Car){  // aloca um estrutura do tipo fila

	*No = 	(Fila*) malloc( sizeof(Fila) );  //aloca estrutura
	(**No).C = Car;                   // armazena o valor na estrutura alocada
	(**No).prox = NULL;                    // e faz o ponteiro prox apontar para null

}

void inicia(Fila **Inicio, Fila **Fim){  //inicia um fila fazendo o inicio e o fim receber NUll
	 
	*Inicio = *Fim = NULL;

}

void enfilera(Fila **Inicio, Fila **Fim, Fila *No){ //enfileira um valor

	if (*Inicio == NULL){  		// se o inicio for nulo
		*Inicio = *Fim = No;  	// faz o inicio e o fim a pontar para a estrutura alocada
	
	}else{						// se nao for nulo
		(**Fim).prox = No;     // faz o fim.prox apontar para a estrutura alocada 
		*Fim = No;            // e faz o fim apontar para estrutura alocada

	}

}

void desenfilera(Fila **Inicio, Fila **Fim, carro *Car){   //retira um valor da fila sempre é retirado pelo inicio
	Fila *aux;

	if (*Inicio != NULL){     // se o inicio nao for nulo
		aux = *Inicio;        // faz o auxiliar receber o inicio
		*Car = (**Inicio).C;
		
		
		if ((**Inicio).prox != NULL){ //se o inicio.prox nao for nulo quer dizer que o ponteiro que ta na proxima posição nao é nulo
			*Inicio = (**Inicio).prox;  // entao faz o inicio apontar para o inicio.prox
		
		}else{ // se o inicio.prox  for nulo  quer dizer que esta na ultima posisao da fila
			*Inicio = *Fim = (**Inicio).prox;  // entao modifica o inicio e o fim faz conque eles sejam nulos

		}
		free(aux); //libera o espaçõ alocado
	
	}

}

int sair(Fila **Inicio, Fila **Fim, carro *Car ,char *placa){
	int quant_man=-1,cont = 0; //conta quantos carros foram movidos
	carro Car_aux;

	int flag=0; //indica se o carro foi encontrado

	Fila *F_aux, *I_aux, *No; 			//cria um fila auxiliar

	inicia(&I_aux,&F_aux); 				//inicia a fina auxiliar

	if (strcmp( (**Inicio).C.placa , placa) == 0 ){
		desenfilera(Inicio,Fim,Car);
		quant_man = 0;
		
	}else{

		while(*Inicio != NULL){ 

			if (strcmp( (**Inicio).C.placa , placa) != 0  && flag != 1){ //se o carro que estiver no inicio da fila nao for 
													// o que estou procurando 

				(**Inicio).C.mov++;  //conta a quantidade de carros que foram movimentados para fora do estacionamento para tirar o carro
			}

			if (strcmp( (**Inicio).C.placa , placa) == 0 ){
				desenfilera(Inicio,Fim,Car);
				quant_man = cont;      //recebe a quantidade de carros que foram movimentados ate tirar o carro
				flag = 1;   		 //indica se o carro foi encontrado
			
			}else{
				cont++;

				desenfilera(Inicio,Fim,&Car_aux); //desenfileira a fila de entrada
				aloca(&No,Car_aux);

				enfilera(&I_aux,&F_aux,No); 	// enfileira o valor reirado da fila de entrada
			}

		}
		*Inicio = I_aux; 				//faz com que a fila de entrada receba a fila auxiliar
		*Fim = F_aux;
	}

	return quant_man;    //indica a quantidade de carros que foram movimentados ate tirar o carro
						// qunat_man == -1 indica que a placa passada nao existe 


}

int busca(Fila **Inicio, Fila **Fim,char *placa){  // verifica se um carro esta na fila
	
	int flag=0; //indica se o carro foi encontrado
	carro Car_aux;

	Fila *F_aux, *I_aux, *No; 			//cria um fila auxiliar

	inicia(&I_aux,&F_aux); 				//inicia a fina auxiliar

	if (*Inicio != NULL){

		if (strcmp( (**Inicio).C.placa , placa) == 0 ){
		
			flag = 1; // indica que o carro foi encontrado
		
		}else{

			while(*Inicio != NULL){ 

				if (strcmp( (**Inicio).C.placa , placa) == 0){ //se o carro que estiver no inicio da fila nao for 
														       // o que estou procurando 
					flag = 1; // indica que o carro foi encontrado
					
				}

				desenfilera(Inicio,Fim,&Car_aux); //desenfileira a fila de entrada
				aloca(&No,Car_aux);

				enfilera(&I_aux,&F_aux,No); 	// enfileira o valor reirado da fila de entrada
					

			}
				*Inicio = I_aux; 				//faz com que a fila de entrada receba a fila auxiliar
				*Fim = F_aux;
		} 

	
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
	Fila *I_est,*F_est; //fila estacionamento
	Fila *No;
	carro Car;
	
	int quat_car=0; //indica a quantidade de carros inseridos na fila
	int quant_man=0; //indica a quantidade de carros foram manobrados para tirar um carro da fila
	char op[3],placa[20];

	inicia(&I_est,&F_est);

	do{
		menu(op);

		if (strcmp(op,"E") == 0){

			if (quat_car == TAM){
				printf("\nEstacionamento esta cheio!! Nao é possivel inserir mais carros\n");
					
			}else{
				ler_carro(&Car);  //ler os dados do carro
				
				if (busca(&I_est,&F_est,Car.placa) == 0){	
					
					aloca(&No,Car);   // aloca o  NO
					enfilera(&I_est,&F_est,No); //insere o carro no estacionamento
					printf("\nCarro foi inserido no estacionamento!!\n");
					
					quat_car++;  //conta quantos carros foram inseridos

				}else{
					printf("\nERRO!! ja exite um carro com esta placa\n");
				}
				
			}

		}else if(strcmp(op,"S") == 0){ //retira um carro do estacionamento

			if (I_est == NULL){
					printf("\nEstacionamento esta vazio!!\n");
					
			}else{
				printf("digite a placa do carro: ");
				scanf("%s",placa);
					
				if(busca(&I_est,&F_est,placa) == 1){

					quant_man = sair(&I_est,&F_est,&Car,placa); //retorna a quantidade de carros foram manobrados para tirar um carro da fila
															//e quantidade de vezes que o carro foi manobrados para fora do estacionamento para tirar outro carro da fila
					
					printf("\ncarro saiu do estacionamento!\n");  

					printf("\nquantidade de vezes que o carro foi manobrado para que outros carros saisem: %d \n",Car.mov);
					printf("quantidade  carros foram manobrados para que ele saisse: %d \n",quant_man);

					quat_car--;  //diminui a quantidade de carros do estacionamento
			
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