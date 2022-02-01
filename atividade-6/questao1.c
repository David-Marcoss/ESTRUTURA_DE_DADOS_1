#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _Pilha{
	
	int codigo; 
	char titulo[30]; 
	char artista[30]; 
	int ano;
	struct _Pilha *ant;

}Pilha;


void aloca(Pilha **No){ // aloca uma estrutura e devolve por parametro
      Pilha *novo;      //cria uma strutura do tipo pilha

      novo = NULL;

      novo = (Pilha*)malloc(sizeof(Pilha));  //aloca essa estrutura

      *No = novo; //e faz o no receber a estrutura alocada

}

void empilha(int codigo ,char *titulo ,char *artista ,int ano ,Pilha **topo, Pilha *No){ //empilha um valo na pilha recebida
	
	if (No != NULL){  			//se o no for diferente de NULL quer dizer que o valor foi alocado corretamente
		
		(*No).codigo = codigo;   		// faz o no receber o valor
		strcpy((*No).titulo , titulo);
		strcpy((*No).artista , artista);
		(*No).ano = ano;


		(*No).ant = *topo;    //  e o no anterior recebe o topo
		*topo = No;          // o topo recebe o conteudo do no


	}

}

void desempilha(int *codigo ,char *titulo ,char *artista ,int *ano ,Pilha **topo){ //desempilha o valor do topo da pilha recebida
	Pilha *aux;

	if(*topo != NULL){	 			// se o topo nao for nulo
	    
	    *codigo = (**topo).codigo; 	
		strcpy( titulo, (**topo).titulo);
		strcpy( artista, (**topo).artista);
		*ano = (**topo).ano;
									// o valor recebe o conteudo que ta no topo
		aux = *topo;                // auxiliar aopmnta pro topo
		*topo = (**topo).ant;      // o topo a ponta para o valor que ta na posição anterior

		free(aux);             // e da um free no topo

		
	}

}

void insere(Pilha **topo){ //ler os dados do CD e empilha na pilha recebida
	Pilha *No;
	int N;
	int codigo; 
	char titulo[30]; 
	char artista[30]; 
	int ano;
	
	do{
		printf("codigo: ");
		scanf("%d",&codigo);
		printf("Titulo: ");
		scanf("%s",titulo);
		printf("Artista: ");
		scanf("%s",artista);
		printf("ano: ");
		scanf("%d",&ano);
			 

		aloca(&No);
		empilha(codigo,titulo,artista,ano,topo,No);
		
		printf("digite 1 para continuar e 0 para parar: ");
		scanf("%d",&N);
	
	}while (N != 0);

			 	

}

void retirar(Pilha **topo,Pilha **Ano_lancamento ,int ano_lan){ 
 	Pilha *auxiliar;
 	Pilha *No;                            // insere cds na pilha Ano_lancamento e retira da pilha recebida
 										 //  se o ano de lancamento do cds for igual ao ano recebido 
 	int codigo;  
	char titulo[30]; 
	char artista[30]; 
	int ano;

	auxiliar = NULL;
	
	
	while (*topo !=NULL){

	     desempilha(&codigo,titulo,artista,&ano,topo); //desempilha o valor do topo

		 if (ano == ano_lan){ // se o ano da pilha topo for igual o ano de lancamento recebido
		 	aloca(&No);     
	     	empilha(codigo,titulo,artista,ano,Ano_lancamento,No); //empilha na pilha Ano_lancamento
		 
		 	
		 }else{ 			// se nao for
		 	aloca(&No);
	     	empilha(codigo,titulo,artista,ano,&auxiliar,No); //empilha numa pilha auxiliar
		 }

	}
	while (auxiliar !=NULL){ //desempilha a pilha auxiliar e reinsere os valores da pilha de cds

	     desempilha(&codigo,titulo,artista,&ano,&auxiliar); 
		 aloca(&No);
	     empilha(codigo,titulo,artista,ano,topo,No);
		 

	}
	

}


		 
void Imprimir(Pilha **topo){  // desenpilha os dados da pilha e imprime

	Pilha *auxiliar;
 	Pilha *No;                            // insere cds na pilha Ano_lancamento e retira da pilha recebida
 										 //  se o ano de lancamento do cds for igual ao ano recebido 
 	int codigo;  
	char titulo[30]; 
	char artista[30]; 
	int ano;

	auxiliar = NULL;
	
	
	while (*topo !=NULL){

	     desempilha(&codigo,titulo,artista,&ano,topo); //desempilha o valor do topo

	     printf("\ncodigo: %d\n",codigo);             // imprime os dados
		 printf("Titulo: %s\n",titulo);
		 printf("Artista: %s\n",artista);
		 printf("ano: %d\n\n",ano);


		 aloca(&No);
	     empilha(codigo,titulo,artista,ano,&auxiliar,No); //empilha numa pilha auxiliar

	}
	while (auxiliar !=NULL){ //desempilha a pilha auxiliar e reinsere os valores da pilha de cds

	     desempilha(&codigo,titulo,artista,&ano,&auxiliar); 
		 aloca(&No);
	     empilha(codigo,titulo,artista,ano,topo,No);
		 

	}
	

}

void criar_pilha(int estilo ,Pilha **pop ,Pilha **rock ,Pilha **sertanejo , Pilha **forro, Pilha **axe){
	
	switch (estilo){                                          //cria a pilha e insere cds de acordo com o estilo musical escolhido pelo usuario
		case 1:
			printf("\ndigite os dados para Inserir Cds na pilha pop\n");
			insere(pop);

		break;

		case 2:	 
			printf("\ndigite os dados para Inserir Cds na pilha rock\n");
			insere(rock);
				
				
			break;
			
		case 3:                                            
			printf("\ndigite os dados para Inserir Cds na pilha sertanejo\n");
			insere(sertanejo);
				
				
			break;
			
		case 4:  
			printf("\ndigite os dados para Inserir Cds na pilha Forro\n");
			insere(forro);
			break;

		case 5:
			printf("\ndigite os dados para Inserir Cds na pilha Axe\n");
			insere(axe);
			break;

			
		default:
			printf("ERRO: opcao invalida \n");
			
			break;

	}


}
void imprimir_pilha(int estilo ,Pilha **cds,Pilha **pop ,Pilha **rock ,Pilha **sertanejo , Pilha **forro, Pilha **axe,Pilha **Ano_lancamento){
	
	switch (estilo){            //imprime cds da pilha escolhida pelo usuario
		
		case 1:
			if( *cds != NULL){
				printf("\nCds da pilha cds\n");
				Imprimir(cds);
			}else{
				printf("\nERRO! pilha de cds vazia\n");
			}

		break;

		case 2:
			if( *pop != NULL){
				printf("\nCds da pilha pop\n");
				Imprimir(pop);
			}else{
				printf("\nERRO! esta pilha nao foi criada\n");
			}

		break;

		case 3:	 
			
			if( *rock != NULL){
				printf("\nCds da pilha rock\n");
				Imprimir(rock);
			}else{
				printf("\nERRO! esta pilha nao foi criada\n");
			}	
				
			break;
			
		case 4:                                            
			
			if( *sertanejo != NULL){
				printf("\nCds da pilha sertanejo\n");
				Imprimir(sertanejo);
			}else{
				printf("\nERRO! esta pilha nao foi criada\n");
			}	
			break;
			
		case 5:  
			
			if( *forro != NULL){
				printf("\nCds da pilha forro\n");
				Imprimir(forro);
			}else{
				printf("\nERRO! esta pilha nao foi criada\n");
			}

			break;
		case 6:
			
			if( *axe != NULL){
				printf("\nCds da pilha axe\n");
				Imprimir(axe);
			}else{
				printf("\nERRO! esta pilha nao foi criada\n");
			}
			break;

		case 7:
			
			if( *Ano_lancamento != NULL){
				printf("\nCds da pilha Ano lancamento\n");
				Imprimir(Ano_lancamento);
			}else{
				printf("\nERRO! esta pilha nao foi criada\n");
			}

			break;

			
		default:
			printf("\nERRO: opcao invalida \n");
			
			break;

	}


}


void menu(int *op){ //imprime menu
	
	printf("\n1- Inserir Cds\n");
	printf("2- criar pilha por estilo musical\n");
	printf("3- Imprimir cds\n");
	printf("4- criar pilha apartir do ano \n");
	printf("5- Sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}

void menu2(int *op){ //imprime menu
	
	printf("\nEscolha para qual estilo musical voce deseja criar uma pilha:\n");
	printf("\n1- pop\n");
	printf("2- rock\n");
	printf("3- sertanejo\n");
	printf("4- forro \n");
	printf("5- axe\n");
	
	printf("\ndigite opcao: ");
	scanf("%d",op);
}

void menu3(int *op){ //imprime menu
	
	printf("\nEscolha para qual pilha voce deseja Imprimir :\n");
	printf("\n1- pilha cds\n");
	printf("\n2- pilha pop\n");
	printf("3- pilha rock\n");
	printf("4- pilha sertanejo\n");
	printf("5- pilha forro \n");
	printf("6- pilha axe\n");
	printf("7- pilha Ano lancamento\n");
	
	printf("\ndigite opcao: ");
	scanf("%d",op);
}

void Pilha_ano_lancamento(int ano_lan ,Pilha **cds,Pilha **pop ,Pilha **rock ,Pilha **sertanejo , Pilha **forro, Pilha **axe,Pilha **Ano_lancamento){

	retirar(cds, Ano_lancamento,ano_lan);
	retirar(pop, Ano_lancamento,ano_lan);
	retirar(rock, Ano_lancamento,ano_lan);
	retirar(sertanejo, Ano_lancamento,ano_lan);
	retirar(forro, Ano_lancamento,ano_lan);
	retirar(axe, Ano_lancamento,ano_lan);


}

int main(){
	Pilha *cds,*pop,*rock,*sertanejo,*forro,*axe; //cria as pilhas
	Pilha *Ano_lancamento;
	

	int op,op2,ano_lan;

	Ano_lancamento = NULL;  // define as pilhas criadas apontando para um valor nulo
	cds = NULL;
	pop = NULL;
	rock = NULL;
	sertanejo = NULL;
	forro = NULL;
	axe = NULL;



	while(op!=5){
		
		menu(&op);

		switch(op){
			case 1:
					
				insere(&cds); //insere cds na pilha cd
					
				break;

			case 2:	 
				menu2(&op2); //pede para o usuario escolher quan o estilo de musica para criar a pilha
				criar_pilha(op2,&pop,&rock,&sertanejo,&forro,&axe);  // insere valores na piha de acordo com o estilo musical escolhido
				
				
				break;
			
			case 3:                                            //imprime  a pilha escolhida pelo usuario
				menu3(&op2);
				imprimir_pilha(op2,&cds,&pop,&rock,&sertanejo,&forro,&axe,&Ano_lancamento);
				
				break;
			
			case 4:
				printf("digite o ano de lancamento: "); // ler um ano de lançamento
				scanf("%d",&ano_lan);
															// e retira os cds das pilhas criadas que tiverem o ano de lançamento escolhido pelo usuario
				Pilha_ano_lancamento(ano_lan,&cds,&pop,&rock,&sertanejo,&forro,&axe,&Ano_lancamento);  //e insere os cds na pilha Ano_lançamento de acordo com o ano passado
				
				if (Ano_lancamento != NULL){
					printf("\npilha de Cds apartir do Ano_lancamento criada\n");
				
				}else{
					printf("\nERRO! nao foi encontrado cds com o Ano lancamento passado\n");

				}

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