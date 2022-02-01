#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define TAM 10

typedef struct p{
	int cod;      	  //numero do processo
	int tempo_ex;  	 //tempo de execulção
	int prioridade; //prioridade
	int quant_ex;  // quantidade de vezes que o processo foi execultado

}processo;


typedef struct F{   //declara a estrutura fila
	
	processo p;
	struct F *prox;

}Fila;

void traco(){
	printf("\n-----------------------------------------------------------------------------------\n");
}

void imprimir_processo(processo p){

	traco();

	printf("numero do processo: %d\n",p.cod);
	printf("tempo de execulcao processo: %d segundos\n",p.tempo_ex);
	printf("prioridade do processo: %d\n",p.prioridade);

	//printf("quantidade de vezes que o processo foi execultado: %d\n",p.quant_ex);
	

}

void aloca(Fila **No, processo p){  // aloca um estrutura do tipo fila

	*No = 	(Fila*) malloc( sizeof(Fila) );  //aloca estrutura
	(**No).p = p;                   // armazena o valor na estrutura alocada
	(**No).prox = NULL;                    // e faz o ponteiro prox apontar para null

}

int fila_vazia(Fila *inicio){
	
	if (inicio == NULL){
		return 1;   //retorna 1 se a fila for vazia
	}else{
		return 0; //retorna 0 se a fila nao tiver vazia
	}

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

void execulta_processo(Fila **Inicio, Fila **Fim, processo *p){   //retira um valor da fila sempre é retirado pelo inicio
	Fila *aux;													 // e simula a execulção do processo que é retirado da fila

	if (*Inicio != NULL){      // se o inicio nao for nulo
		
		(**Inicio).p.tempo_ex-=1;  //decrementa o tempo de execulção do processo
		(**Inicio).p.quant_ex++;  //incrementa a qunatidade de vezes que o processo foi execultado
		
		aux = *Inicio;        // faz o auxiliar receber o inicio
		*p = (**Inicio).p;   // retorna o processo
		
		
		if ((**Inicio).prox != NULL){ //se o inicio.prox nao for nulo quer dizer que o ponteiro que ta na proxima posição nao é nulo
			*Inicio = (**Inicio).prox;  // entao faz o inicio apontar para o inicio.prox
		
		}else{ // se o inicio.prox  for nulo  quer dizer que esta na ultima posisao da fila
			*Inicio = *Fim = (**Inicio).prox;  // entao modifica o inicio e o fim faz conque eles sejam nulos

		}
		free(aux); //libera o espaçõ alocado
	
	}

}

void desenfilera(Fila **Inicio, Fila **Fim, processo *p){  //apenas desenfileira o processo e retorna o processo
														  //retira um valor da fila sempre é retirado pelo inicio
	Fila *aux;

	if (*Inicio != NULL){      // se o inicio nao for nulo
		aux = *Inicio;        // faz o auxiliar receber o inicio
		*p = (**Inicio).p;   // retorna o processo
		
		
		if ((**Inicio).prox != NULL){ //se o inicio.prox nao for nulo quer dizer que o ponteiro que ta na proxima posição nao é nulo
			*Inicio = (**Inicio).prox;  // entao faz o inicio apontar para o inicio.prox
		
		}else{ // se o inicio.prox  for nulo  quer dizer que esta na ultima posisao da fila
			*Inicio = *Fim = (**Inicio).prox;  // entao modifica o inicio e o fim faz conque eles sejam nulos

		}
		free(aux); //libera o espaçõ alocado
	
	}

}

void mostrar_processo(Fila **Inicio, Fila **Fim){
	processo p;

	Fila *F_aux, *I_aux, *No; 			//cria um fila auxiliar

	inicia(&I_aux,&F_aux); 				//inicia a fina auxiliar

	if (fila_vazia(*Inicio)== 0){
		while(*Inicio != NULL){

			desenfilera(Inicio,Fim,&p);
			
			imprimir_processo(p);

			aloca(&No,p);

			enfilera(&I_aux,&F_aux,No); 	// enfileira o valor reirado da fila de entrada
		}

			
			*Inicio = I_aux; 				//faz com que a fila de entrada receba a fila auxiliar
			*Fim = F_aux;
	}else{
		traco();
		printf("\nERRO!! fila vazia\n");
	}
}

void escalonador(Fila **F1_i, Fila **F1_f,Fila **F2_i, Fila **F2_f,Fila **F3_i, Fila **F3_f){
	processo p;
	Fila *No;

	if (fila_vazia(*F1_i) == 0){         //se a fila 1 nao for vazia
		
		execulta_processo(F1_i,F1_f,&p);  //execulta o processo que esta no inicio da fila 1 

		traco();
		printf("processos da fila 1:\n");
		traco();
		printf("processo %d execultado!!\n",p.cod);
		

		

		if (p.tempo_ex == 0){   //verifica o tempo de execulção do processo
			traco();		   // se o tempo for 0 quer dizer qu o processo foi finalizado
			printf("\nprocesso %d finalizado!!\n",p.cod);
			
		
		}else if (p.quant_ex < 2){ //se o processo nao foi finalizado
								  // verifica a quantidade de vezes que o //verifica o tempo de execulção do processo
			aloca(&No,p);        
			enfilera(F1_i,F1_f,No); //enfileira o processo no fim da fila 1 
		
		}else{   // se processo ja foi execultado 2 vezes;

			p.quant_ex = 0; //zera a quantidade de execulçoes do processo
			aloca(&No,p);
			enfilera(F2_i,F2_f,No); //enfileira o processo no fim da fila 2 
		}

		if (fila_vazia(*F1_i) == 1){
			traco();
			printf("\nprocessos da fila 1 finalizados\n");
		}


	}else if (fila_vazia(*F2_i) == 0){         //se a fila 1 nao for vazia
		
		execulta_processo(F2_i,F2_f,&p);  //execulta o processo que esta no inicio da fila 1 

		traco();
		printf("processo da fila 2:\n");
		traco();
		printf("processo %d execultado!!\n",p.cod);

		if (p.tempo_ex == 0){   //verifica o tempo de execulção do processo
			traco();		   // se o tempo for 0 quer dizer qu o processo foi finalizado
			printf("\nprocesso %d finalizado!!\n",p.cod);

		}else if (p.quant_ex < 2){ //se o processo nao foi finalizado
								  // verifica a quantidade de vezes que o //verifica o tempo de execulção do processo
			aloca(&No,p);        
			enfilera(F2_i,F2_f,No); //enfileira o processo no fim da fila 1 
		
		}else{   // se processo ja foi execultado 2 vezes;
			aloca(&No,p);
			enfilera(F3_i,F3_f,No); //enfileira o processo no fim da fila 2 
		}

		if (fila_vazia(*F2_i) == 1){
			traco();
			printf("\nprocessos da fila 2 finalizados\n");
			
		}

	}else if (fila_vazia(*F3_i) == 0){         //se a fila 1 nao for vazia
		
		execulta_processo(F3_i,F3_f,&p);  //execulta o processo que esta no inicio da fila 1 

		traco();
		printf("processo da fila 3:\n");
		traco();
		printf("processo %d execultado!!\n",p.cod);
		

		if (p.tempo_ex == 0){          //verifica o tempo de execulção do processo
			traco();		          // se o tempo for 0 quer dizer qu o processo foi finalizado
			printf("\nprocesso %d finalizado!!\n",p.cod);
			
		
		}else{   					// se processo ja foi execultado 2 vezes;
			aloca(&No,p);
			enfilera(F3_i,F3_f,No); //enfileira o processo no fim da fila 2 
		}

		if (fila_vazia(*F3_i) == 1){
			traco();
			printf("\nprocessos da fila 3 finalizados\n");
			
		}


		
	
	}else{
		traco();
		printf("ERRO!! Nao ha processos para Execultar na CPU\n");
		
	}

}

void mostrar_processo_execultar_cpu(Fila *F1_i,Fila *F2_i,Fila *F3_i){
	processo p;

	if(F1_i != NULL){
		imprimir_processo(F1_i->p);

	}else if(F2_i != NULL){
		imprimir_processo(F2_i->p);

	}else if(F3_i != NULL){
		imprimir_processo(F3_i->p);
	
	}else{
		traco();
		printf("ERRO!! Nao ha processos para Execultar na CPU");
	}

}

int quantidade_processos(Fila **Inicio, Fila **Fim){ //recebe uma fila de processos
	int cont = 0;                                   // e retorna a quantidade de processos da fila
	processo p;

	Fila *F_aux, *I_aux, *No; 			//cria um fila auxiliar

	inicia(&I_aux,&F_aux); 				//inicia a fina auxiliar

	
	while(*Inicio != NULL){ 

		desenfilera(Inicio,Fim,&p); //desenfileira a fila
			
		cont++; //conta a quantidade de processos

		aloca(&No,p);

		enfilera(&I_aux,&F_aux,No); 	// enfileira o valor reirado da fila de entrada
	}

			
	*Inicio = I_aux; 				//faz com que a fila de entrada receba a fila auxiliar
	*Fim = F_aux;
	
	return cont;
}

int quant_tempo_execultar_processos(Fila **Inicio, Fila **Fim){   //recebe uma fila de processos
	int cont_tp = 0;                                              // e retorna a quantidade de tempo para execultar todos os processos da fila
	                                                             // conta os processos da filas 1 e 2 de maior prioridade
	processo p;                                              

	Fila *F_aux, *I_aux, *No; 			//cria um fila auxiliar

	inicia(&I_aux,&F_aux); 				//inicia a fina auxiliar

	
	while(*Inicio != NULL){ 

		desenfilera(Inicio,Fim,&p); //desenfileira a fila
			
		if (p.quant_ex > 0 || p.tempo_ex == 1){
			cont_tp++;  // se o processo ja tiver sido execultado 1 vez incrementa 1s ao tempo
		
		}else{ //se processo nao tiver sido execultado nenhuma vez incrementa 2s ao tempo
			cont_tp+=2;
		} 

		aloca(&No,p);

		enfilera(&I_aux,&F_aux,No); 	// enfileira o valor reirado da fila de entrada
	}

			
	*Inicio = I_aux; 				//faz com que a fila de entrada receba a fila auxiliar
	*Fim = F_aux;
	
	return cont_tp;
}

int quant_tempo_execultar_processos2(Fila **Inicio, Fila **Fim){ //recebe uma fila de processos
	int cont_tp = 0;                                             // e retorna a quantidade de tempo para execultar todos os processos da fila
																// conta os processos da filas 3 de maior prioridade
	processo p;

	Fila *F_aux, *I_aux, *No; 			//cria um fila auxiliar

	inicia(&I_aux,&F_aux); 				//inicia a fina auxiliar

	
	while(*Inicio != NULL){ 

		desenfilera(Inicio,Fim,&p); //desenfileira a fila
			
		cont_tp += p.tempo_ex; //conta o tempo de execulção do processo

		aloca(&No,p);

		enfilera(&I_aux,&F_aux,No); 	// enfileira o valor reirado da fila de entrada
	}

			
	*Inicio = I_aux; 				//faz com que a fila de entrada receba a fila auxiliar
	*Fim = F_aux;
	
	return cont_tp;
}

/*int quant_tempo_execultar_processos_escolhido(Fila **F1_i, Fila **F1_f,Fila **F2_i, Fila **F2_f,Fila **F3_i, Fila **F3_f,int cod){
	processo p;
	Fila *No;

	int flag = 0, cont_tp=0;
	
	Fila *i_aux1,*f_aux1;
	Fila *i_aux2,*f_aux2;
	Fila *i_aux3,*f_aux3;

	inicia(&i_aux1,&f_aux1);
	inicia(&i_aux1,&f_aux1);
	inicia(&i_aux1,&f_aux1);

	if (*F1_i != NULL){

		while(*F1_i != NULL){ 

			desenfilera(F1_i,F1_f,&p); //desenfileira a fila
				
			if (p.cod == cod){
				flag = 1;
			
			}else if (flag == 0){
				
				cont_tp++;
			} 

			aloca(&No,p);

			enfilera(&i_aux1,&f_aux1,No); 	// enfileira o valor reirado da fila de entrada
		}
	
		*F1_i = i_aux1; 				//faz com que a fila de entrada receba a fila auxiliar
		*F1_f = f_aux1;	
		
	}


	return cont_tp;
	
}*/

int processo_existe(Fila **Inicio, Fila **Fim, int cod){ // recebe uma fila e verifica se um processo
	processo p;                                         // ja foi inserido na fila

	int flag = 0;

	Fila *F_aux, *I_aux, *No; 			//cria um fila auxiliar

	inicia(&I_aux,&F_aux); 				//inicia a fina auxiliar

	
	while(*Inicio != NULL){
		desenfilera(Inicio,Fim,&p);
		
		if (p.cod == cod){
				flag = 1; 
	    }

		aloca(&No,p);
    	enfilera(&I_aux,&F_aux,No); 	// enfileira o valor reirado da fila de entrada
	}

			
	*Inicio = I_aux; 				//faz com que a fila de entrada receba a fila auxiliar
	*Fim = F_aux;
	
	return flag; //retorna 1 se o processo existir e 0 se nao

}

int verifica_processo(Fila **F1_i, Fila **F1_f,Fila **F2_i, Fila **F2_f,Fila **F3_i, Fila **F3_f, int cod){ //verifica se um processo ja foi inserido em 
	int flag = 0;																							   // uma das filas
																										  // retorna 1 se o processo ja tiver sido inserido
	if(processo_existe(F1_i,F1_f,cod) == 1){                                                             // e 0 se nao
		flag = 1;
	
	}else if(processo_existe(F2_i,F2_f,cod) == 1){
		flag = 1;
	
	}else if(processo_existe(F3_i,F3_f,cod) == 1){
		flag = 1;
	}

	return flag;
	
}


void ler_processo(processo *p){  //le dados do processo

	printf("digite o tempo de execulcao processo: ");
	scanf("%d",&p->tempo_ex);

	while(p->tempo_ex <1){
		printf("\nERRO: O TEMPO DE EXECULÇÃO DE UM PROCESSO NAO PODE SER MENOR QUE 1\n");
		
		printf("digite um tempo valido: ");
		scanf("%d",&p->tempo_ex);

	}
	
	printf("digite a prioridade do processo: ");
	scanf("%d",&p->prioridade);

	while(p->prioridade <1 || p->prioridade > 3){
		printf("\nERRO: A PRIORIDADE DE UM PROCESSO SO PODE SE 1, 2 OU 3\n");
		
		printf("digite uma prioridade valida: ");
		scanf("%d",&p->prioridade);


	}
	
	p->quant_ex = 0;

}

void inserir_processo(Fila **F1_i, Fila **F1_f,Fila **F2_i, Fila **F2_f,Fila **F3_i, Fila **F3_f){ //insere um processo em uma das filas
	processo p;																					  // de a cordo com a prioridade do processo
	Fila *No;                

	printf("digite o numero do processo: ");
	scanf("%d",&p.cod);

	if(verifica_processo(F1_i, F1_f,F2_i,F2_f,F3_i,F3_f,p.cod) == 0){
		
		ler_processo(&p);
		aloca(&No,p);

		if (p.prioridade == 1){			//se a prioridade do processo for 1
			traco();
			enfilera(F1_i,F1_f,No); // o processo é inserido de maior prioridade

			traco();
			printf("\nprocesso inserido na fila 1 de maior prioridade!!\n");
		
		}else if (p.prioridade == 2){    //se a prioridade do processo for 2
			enfilera(F2_i,F2_f,No); // o processo é inserido na fila 2 de prioridade menor
			traco();
			printf("\nprocesso inserido na fila 2 de menor prioridade!!\n");
		
		}else{                           //se a prioridade do processo for 3  
			enfilera(F3_i,F3_f,No); //  o processo é inserido na fila 3 de que possui menor prioridade de todas
			traco();
			printf("\nprocesso inserido na fila 3 que possui menor prioridade de todas!!\n");
		}
	}else{
		traco();
		printf("ERRO!!JA EXISTE PROCESSO COM ESTE CODIGO, NAO E PERMITIDO PROCESSOS COM CODIGO REPETIDO\n");
	}	


}


void menu(int *op){ //imprime menu
	
	traco();
	printf("\n1- Inserir processo \n");
	printf("2- Mostrar processos das filas\n");
	printf("3- Execultar processo\n");
	printf("4- Mostrar proximo processo que ira ultilizar o prcessador\n");
	printf("5- Mostrar quantidade de processos de cada Fila\n");
	printf("6- Mostrar quanto de tempo que falta para execultar processos de uma Fila\n");
	//printf("7- Mostrar quanto de tempo processamento falta para execultar determinado processo\n");
	printf("7- Mostrar quanto de tempo processamento falta para terminar cada fila e todas filas\n");
	printf("8- Sair \n");

	traco();
	
	printf("\ndigite opcao: ");
	scanf("%d",op);
}

void menu2(int *op){ //imprime menu
	
	traco();
	printf("Escolha a fila:\n");
	printf("\n1- fila 1 \n");
	printf("2- fila 2\n");
	printf("3- fila 3\n");
	printf("4- Sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);

	while(*op<1 || *op>4){
		printf("\nopcao invalida!!");
		printf("\ndigite opcao: ");
		scanf("%d",op);
	}
}


int main(){
	
	Fila *F1_i, *F1_f; //fila 1
	Fila *F2_i, *F2_f; //fila 2
	Fila *F3_i, *F3_f; //fila 3
	Fila *No;

	processo p;
	int op,op2,aux,aux2,aux3,tp;

	inicia(&F1_i, &F1_f);
	inicia(&F2_i, &F2_f);
	inicia(&F3_i, &F3_f);


	do{
		
		menu(&op);

		switch(op){
			case 1:
					
				inserir_processo(&F1_i, &F1_f,&F2_i, &F2_f,&F3_i, &F3_f);
					
				break;

			case 2:
				menu2(&op2);
				
				if(op2 == 1){
					mostrar_processo(&F1_i, &F1_f);
				}else if(op2 == 2){
					mostrar_processo(&F2_i, &F2_f);
				}else if(op2 == 3){
					mostrar_processo(&F3_i, &F3_f);
				}
				break;
			
			case 3:
				escalonador(&F1_i, &F1_f,&F2_i, &F2_f,&F3_i, &F3_f);
				
				break;

			case 4:
				mostrar_processo_execultar_cpu(F1_i,F2_i,F3_i);
				
				break;


			case 5:
				traco();
				printf("Fila 1 possui %d processos \n",quantidade_processos(&F1_i,&F1_f));
				printf("Fila 2 possui %d processos \n",quantidade_processos(&F2_i,&F2_f));
				printf("Fila 3 possui %d processos \n",quantidade_processos(&F3_i,&F3_f));
			

				break;

			case 6:

				menu2(&op2);

				traco();
				
				if(op2 == 1){
					aux = quant_tempo_execultar_processos(&F1_i, &F1_f);

					if (aux> 0){
						printf("quantidade tempo execultar processos da fila 1 : %d segundos\n",aux);
					}else{
						printf("Nao ah processos para execultar  da fila 1!!");
					}

				}else if(op2 == 2){
					aux = quant_tempo_execultar_processos(&F2_i, &F2_f);
					
					if (aux> 0){
						printf("Quantidade tempo execultar processos da fila 2 : %d segundos\n",aux);
					}else{
						printf("Nao ah processos para execultar  da fila 2!!");
					}

				}else if(op2 == 3){
					aux = quant_tempo_execultar_processos2(&F3_i, &F3_f);
					
					if (aux> 0){
						printf("Quantidade tempo execultar processos da fila 3 : %d segundos\n",aux);
					}else{
						printf("Nao ah processos para execultar  da fila 3 !!\n");
					}
					
				}
				
				break;

			/*case 7:
				printf("digite o codigo do processo: ");
				scanf("%d",&aux);

				if (verifica_processo(&F1_i, &F1_f,&F2_i, &F2_f,&F3_i, &F3_f,aux) == 1){
					
					tp = quant_tempo_execultar_processos_escolhido(&F1_i, &F1_f,&F2_i, &F2_f,&F3_i, &F3_f,aux);	

					printf("tempo de processamento: %d \n",tp );
				
				}else{
					printf("processso nao existie\n");
				}
				
				
				break;

			*/
			case 7:
				traco();
				printf("o tempo para execultar todos os processos das fila 1 é de: %d segundos \n",quant_tempo_execultar_processos(&F1_i,&F1_f));
				printf("o tempo para execultar todos os processos das fila 2 é de: %d segundos \n",quant_tempo_execultar_processos(&F2_i,&F2_f));
				printf("o tempo para execultar todos os processos das fila 3 é de: %d segundos \n",quant_tempo_execultar_processos2(&F3_i,&F3_f));
				traco();
				tp = quant_tempo_execultar_processos2(&F1_i,&F1_f) + quant_tempo_execultar_processos2(&F2_i,&F2_f)+ quant_tempo_execultar_processos2(&F3_i,&F3_f);

				printf("o tempo para execultar todos os processos das filas é de: %d segundos\n", tp);
				
				
				break;

			case 8:
				printf("\nsaindo.....\n");
				break;

			
			default:
				printf("ERRO: opcao invalida \n");
				break;

		}
	}while(op!=8);


	return 0;
}