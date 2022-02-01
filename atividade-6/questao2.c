#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct F{   //declara a estrutura fila
	
	int Matricula; 
	char Nome[30]; 
	int Ano_Escolar;
	int Idade;

	struct F *prox;

}Fila;

void aloca(Fila **No, int Matricula , char *Nome , int Ano_Escolar, int Idade){  // aloca um estrutura do tipo fila

	*No = 	(Fila*) malloc( sizeof(Fila) );  //aloca estrutura
	
	(**No).Matricula = Matricula;
	strcpy((**No).Nome, Nome);
	(**No).Ano_Escolar = Ano_Escolar;
	(**No).Idade = Idade;                   // armazena o valor na estrutura alocada
	
	(**No).prox = NULL;                    // e faz o ponteiro prox apontar para null

}

void incia(Fila **Inicio, Fila **Fim){  //inicia um fila fazendo o inicio e o fim receber NUll
	 
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

void desenfilera(Fila **Inicio, Fila **Fim, int *Matricula , char *Nome , int *Ano_Escolar, int *Idade){   //retira um valor da fila sempre é retirado pelo inicio
	Fila *aux;
	

	if (*Inicio != NULL){     // se o inicio nao for nulo
		aux = *Inicio;       // retorna os dados que vao ser retirados da fila

		*Matricula = (**Inicio).Matricula;
		strcpy(Nome,(**Inicio).Nome);
		*Ano_Escolar = (**Inicio).Ano_Escolar;
		*Idade = (**Inicio).Idade;
		
		if ((**Inicio).prox != NULL){ //se o inicio.prox nao for nulo quer dizer que o ponteiro que ta na proxima posição nao é nulo
			*Inicio = (**Inicio).prox;  // entao faz o inicio apontar para o inicio.prox
		
		}else{ // se o inicio.prox  for nulo  quer dizer que esta na ultima posisao da fila
			*Inicio = *Fim = (**Inicio).prox;  // entao modifica o inicio e o fim faz conque eles sejam nulos

		}
		free(aux); //libera o espaçõ alocado
	
	}

}

void insere(Fila **Inicio, Fila **Fim){
	Fila *No;
	int N;
	int Matricula,Idade,Ano_Escolar; 
	char Nome[30]; 
	
	do{
		printf("\ndigite a Matricula: ");
		scanf("%d",&Matricula);
		printf("digite o Nome: ");
		scanf("%s",Nome);
		printf("digite o Ano_Escolar: ");
		scanf("%d",&Ano_Escolar);
		
		while(Ano_Escolar<5 || Ano_Escolar>9){
			printf("\nErro!! aluno so pode ser cadrastado do 5 ao 9 Ano\n");
			printf("digite o Ano_Escolar valido: ");
			scanf("%d",&Ano_Escolar);

		}
		printf("digite a Idade: ");
		scanf("%d",&Idade);


		aloca(&No,Matricula,Nome,Ano_Escolar,Idade);

		enfilera(Inicio,Fim,No);



		printf("\ndigite 1 para continuar e 0 para parar: ");
		scanf("%d",&N);


	}while(N != 0 ); //enfileira valores enquanto o valor nao for negativo

}

void imprimir(Fila **Inicio, Fila **Fim){  //desenfileira os dados da fila e imprime
	int Matricula,Idade,Ano_Escolar;
	char Nome[30];
	
	Fila *I_aux, *F_aux,*No;									

	incia(&I_aux,&F_aux);

	while(*Inicio != NULL){     // se o inicio nao for nulo
		       
		desenfilera(Inicio,Fim,&Matricula,Nome,&Ano_Escolar,&Idade);

		printf("\nMatricula: %d\n",Matricula );
		printf("Nome: %s\n",Nome );
		printf("Ano_Escolar: %d\n",Ano_Escolar );
		printf("Idade: %d\n",Idade );

		aloca(&No,Matricula,Nome,Ano_Escolar,Idade);

		enfilera(&I_aux,&F_aux,No);
		
	
	}

	*Inicio = I_aux; 				//faz com que a fila de entrada receba a fila auxiliar
	*Fim = F_aux;
}

int Sair_fila(Fila **Inicio, Fila **Fim, int mat){
	
	int Matricula,Idade,Ano_Escolar,flag = 0; 
	char Nome[30]; 
	Fila *F_aux, *I_aux, *No; 			//cria um fila auxiliar
	
	incia(&I_aux,&F_aux); 				//inicia a fina auxilia


	while(*Inicio != NULL){ //enqunato tiver valores na fila

		desenfilera(Inicio,Fim,&Matricula,Nome,&Ano_Escolar,&Idade); //desenfileira e recebe os dados do aluno que esta na primeira posição da fila
		
		if (mat != Matricula){                                 // se a matricula for diferente da matricula procurada
			aloca(&No,Matricula,Nome,Ano_Escolar,Idade);      // os dados sao alocados

			enfilera(&I_aux,&F_aux,No); 	// e é enfileirado numa fila auxiliar

		}else{   // se a matricula for igaula matricula procurada
				// o aluno é retirado da fila
			flag = 1; //indica que o aluno foi removido
		}

	}
									 // por fim
	*Inicio = I_aux; 				//faz com que a fila de entrada receba a fila auxiliar
	*Fim = F_aux;

	return flag;

}
void dividir(Fila **Inicio, Fila **Fim, Fila **I_EF, Fila **F_EF, int Ano){

	int Matricula,Idade,Ano_Escolar; 
	char Nome[30]; 
	Fila *F_aux, *I_aux, *No; 			//cria um fila auxiliar
	
	incia(&I_aux,&F_aux); 				//inicia a fina auxilia


	while(*Inicio != NULL){ //enqunato tiver valores na fila

		desenfilera(Inicio,Fim,&Matricula,Nome,&Ano_Escolar,&Idade); //desenfileira e recebe os dados do aluno que esta na primeira posição da fila
		aloca(&No,Matricula,Nome,Ano_Escolar,Idade);
		
		if (Ano_Escolar == Ano){                                 // se o ano escolar for igual ao ano procurado
	     
			enfilera(I_EF,F_EF,No); 	// e é enfileirado os dados em I_Ef e F_EF

		}else{   // se o ano nao for igual ao procurado
				// apenas enfilera o aluno na fila auxiliar
			enfilera(&I_aux,&F_aux,No);
			
		}

	}
									 // por fim
	*Inicio = I_aux; 				//faz com que a fila de entrada receba a fila auxiliar
	*Fim = F_aux;



}

void dividir_fila(Fila **Inicio, Fila **Fim, Fila **I_EF5, Fila **F_EF5,Fila **I_EF6, Fila **F_EF6,Fila **I_EF7, Fila **F_EF7,Fila **I_EF8, Fila **F_EF8,Fila **I_EF9, Fila **F_EF9){

	                                    // retira alunos da fila de entrada e divide em filas de acordo com o ano escolar

	dividir(Inicio,Fim,I_EF5,F_EF5,5); // faz fila I_EF5 e F_EF5 receba a fila de alunos do 5 ano
	dividir(Inicio,Fim,I_EF6,F_EF6,6); // faz fila I_EF6 e F_EF6 receba a fila de alunos do 6 ano
	dividir(Inicio,Fim,I_EF7,F_EF7,7); // faz fila I_EF7 e F_EF7 receba a fila de alunos do 7 ano
	dividir(Inicio,Fim,I_EF8,F_EF8,8); // faz fila I_EF8 e F_EF8 receba a fila de alunos do 8 ano
	dividir(Inicio,Fim,I_EF9,F_EF9,9); // faz fila I_EF9 e F_EF9 receba a fila de alunos do 9 ano

}




void menu(int *op){ //imprime menu
	
	printf("\n1- Inserir alunos na fila\n");
	printf("2- imprimir fila de alunos\n");
	printf("3- tirar aluno da fila\n");
	printf("4- dividir fila de acordo com o ano Ano Escolar  \n");
	printf("5- Sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}

void menu_imprimir(int *op){ //imprime menu

	printf("\n escolha a fila que voce deseja imprimir\n");
	printf("\n1- Fila de entrada\n");
	printf("2- fila de alunos do 5 ano\n");
	printf("3- fila de alunos do 6 ano\n");
	printf("4- fila de alunos do 7 ano \n");
	printf("5- fila de alunos do 8 ano \n");
	printf("6- fila de alunos do 9 ano \n");

	printf("\ndigite opcao: ");
	scanf("%d",op);
}

void imprimir_filas(Fila **Inicio, Fila **Fim, Fila **I_EF5, Fila **F_EF5,Fila **I_EF6, Fila **F_EF6,Fila **I_EF7, Fila **F_EF7,Fila **I_EF8, Fila **F_EF8,Fila **I_EF9, Fila **F_EF9){
	int op;
	menu_imprimir(&op);
	
	switch (op){            //imprime fila  escolhida pelo usuario
		
		case 1:
			if( *Inicio != NULL){
				
				printf("\nfila de entrada\n");
				imprimir(Inicio,Fim);
			
			}else{
				printf("\nERRO! nao possui alunos nesta fila\n");
			}

		break;
		
		case 2:
			if( *I_EF5 != NULL){
					
					printf("\nFila de alunos do 5 ano\n");
					imprimir(I_EF5,F_EF5);
				
				}else{
					printf("\nERRO! nao possui alunos nesta fila\n");
				}
			break;
		
		case 3:
			if( *I_EF6 != NULL){
					
					printf("\nFila de alunos do 6 ano\n");
					imprimir(I_EF6,F_EF6);
				
				}else{
					printf("\nERRO! nao possui alunos nesta fila\n");
				}
			break;

		case 4:
			if( *I_EF7 != NULL){
					
					printf("\nFila de alunos do 7 ano\n");
					imprimir(I_EF7,F_EF7);
				
				}else{
					printf("\nERRO! nao possui alunos nesta fila\n");
				}
			break;

		case 5:
			if( *I_EF8 != NULL){
					
					printf("\nFila de alunos do 8 ano\n");
					imprimir(I_EF8,F_EF8);
				
				}else{
					printf("\nERRO! nao possui alunos nesta fila\n");
				}
			break;

		case 6:
			if( *I_EF9 != NULL){
					
					printf("\nFila de alunos do 9 ano\n");
					imprimir(I_EF9,F_EF9);
				
				}else{
					printf("\nERRO! nao possui alunos nesta fila\n");
				}
			break;

		
			
		default:
			printf("\nERRO: opcao invalida \n");
			
			break;

	}

}



int main(){
	Fila *No;
	Fila *Inicio,*Fim;  //fila de entrada
	Fila *I_f5,*F_f5;  // fila alunos EF 5
	Fila *I_f6,*F_f6;  // fila alunos EF 6
	Fila *I_f7,*F_f7;  // fila alunos EF 7
	Fila *I_f8,*F_f8;  // fila alunos EF 8
	Fila *I_f9,*F_f9;  // fila alunos EF 9


	int valor,op=1,mat,flag;

	incia(&Inicio,&Fim); //inicia filas
	incia(&I_f5,&F_f5);
	incia(&I_f6,&F_f6);
	incia(&I_f7,&F_f7);
	incia(&I_f8,&F_f8);
	incia(&I_f9,&F_f9);



	while(op!=5){
		
		menu(&op);

		switch(op){
			case 1:
					
				insere(&Inicio,&Fim);; //insere alunos na fila
					
				break;

			case 2:	 
				imprimir_filas(&Inicio,&Fim,&I_f5,&F_f5,&I_f6,&F_f6,&I_f7,&F_f7,&I_f8,&F_f8,&I_f9,&F_f9);
				
				break;
			
			case 3:
				printf("digite a Matricula: "); //ler uma matricula
				scanf("%d",&mat);

				flag = Sair_fila(&Inicio,&Fim,mat); // retira o aluno da fila de a cordo com a matricula

				if (flag == 1){      // se flag for 1 indica que o aluno saiu da fila
					printf("\naluno saiu da fila!\n");
				}else{
					printf("\nERRO! Matricula invalida\n"); //se flag nao for 1 quer dizer que o aluno nao esta na fila
				}
				                                            
				break;
			
			case 4:
				dividir_fila(&Inicio,&Fim,&I_f5,&F_f5,&I_f6,&F_f6,&I_f7,&F_f7,&I_f8,&F_f8,&I_f9,&F_f9); // divide a fila de entrada em 5 filas de acordo com o ano escolar

				printf("\noperação concluida!\n");
		

				break;


			case 5:
				printf("\nsaindo.....\n");
				break;

			
			default:
				printf("ERRO: opcao invalida \n");
				break;

		}
	}


	return 0;
}
