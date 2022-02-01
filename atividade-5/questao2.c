#include<stdio.h>
#include<string.h>
#include<ctype.h>


typedef struct { 
	char chassi[20];							//**	obs: essa estrutura lista é uma fila o nome esta lista         **//
	int placa;                                  //**	pq eu confundi na hora de declarar mas essa estrutura funciona**//
	char modelo[30];                            //**	como uma fila                                                **//                           
	char marca[30];  
	char cor[30];  
	int ano; 
	
}fila;  // define a estrutura fila  

void copia(fila *l1,fila *l2){ //copia os dados de l1 e insere em l2
	
	strcpy(l2->chassi,l1->chassi);
	l2->placa = l1->placa;
	strcpy(l2->modelo , l1->modelo );
	strcpy(l2->marca , l1->marca);
	strcpy(l2->cor, l1->cor);
	l2->ano = l1->ano;
}

void ler(fila *l1){ //ler dados da estrutura carros

		printf("\n\nchassi: ");
		scanf("%s",l1->chassi );
		printf("placa :");
		scanf("%d",&l1->placa );
		printf("modelo :");
		scanf("%s",l1->modelo );
		printf("marca :");
		scanf("%s",l1->marca );
		printf("cor :");
		scanf("%s",l1->cor );
		printf("ano :");
		scanf("%d",&l1->ano );

}

void imprimir(fila *l1){ //imprime dados da estrutura carros

	
		printf("\nchassi: %s\n",l1->chassi );
		printf("placa : %d\n",l1->placa );
		printf("modelo : %s\n",l1->modelo );
		printf("marca : %s\n",l1->marca );
		printf("cor : %s\n",l1->cor );
		printf("ano : %d\n\n",l1->ano );

}


void inicia_l(int *tras){ // inicia fila
	
	*tras = -1;

}

int l_vazia( int tras){ // verifica se a fila ta vazia
	
	if (tras<0 )
		
		return 1;   //retorna 1 se tiver
	
	else
		return 0; //retorna 0 se nao tiver
	

}

int l_cheia(int tras, int tam){ // verifica se a fila ta cheia
	
	if (tras == tam-1)       
		return 1;  //retorna 1 se tiver
	else
		return 0; //retorna 0 se nao tiver
}

void l_insere(fila *l , fila *aux ,int *tras, int tam){ //insere um valor na fila

	if (l_cheia(*tras,tam) == 1){  //verifica se a fila ta cheia
		printf("\nERRO: fila cheia\n");
	
	}else{  //se nao tiver insere o item na fila
		(*tras)++;
		copia(aux,&l[*tras]);

	}

}
void l_remove1(fila *l,int *tras ){ //remove o valor da primeira possição da fila
	int i;

	if (l_vazia(*tras) == 1 ){
		printf("\nERRO: lista vazia\n");	
	
	}else{
		for (i = 0; i <= *tras; ++i){  //remove o valor da primeira posição da fila
            copia(&l[i+1],&l[i]);     // puxa os valores para tras
		}

		(*tras)--;          //diminui o tamanho da fila
							  
	}
		
}

int remover_carro(fila *l,int *tras , int placa, char *chassi){ //remove um carro na fila e retorna o seu chassi
	int i,tras_auxiliar=-1,tam;
	int flag=0;

	tam = *tras +1;

	fila auxiliar[tam]; //cria uma fila auxiliar para armazenar os valores da fila de entrada

	if (l_vazia(*tras) == 1 ){
		printf("\nERRO: lista vazia\n");	
	
	}else{
		while(*tras>-1){                       //percorre a fila
			
			if ( l[0].placa == placa){       // se encontrar o veiculo com a aplaca digitada 
				strcpy(chassi,l[0].chassi); // devolve na variavel chassi o valor do chassi do carro removido
				l_remove1(l,tras);         // remove o valor da lista        
				flag = 1;                 // flag = 1 indica que o veiculo foi removido

			}else{ //se o carro nao é encontrdo
				l_insere(auxiliar,&l[0],&tras_auxiliar,tam); //insere o valor da primeira posição da fila na fila auxiliar
            	l_remove1(l,tras);          // e remove o primeiro valor da fila de entrada

			}
		
		}

		while(tras_auxiliar>-1){ // reinsere os valores da fila auxiliar na fila de entrada
				l_insere(l,&auxiliar[0],tras,tam);            //insere o valor
            	l_remove1(auxiliar,&tras_auxiliar);          // remove o valor da fila auxiliar

		}
		                                      //as remoçoes e comparações sao feitas pela primeira posição da fila
	}

	if (flag==1){

		return 1; //retorna 1 se o valor foi removido
	}

	return 0;  // retorna 0 se o veiculo nao foi removido

}

void l_dividir(fila *l1,int *tras1,fila *l2,int *tras2,fila *l3,int *tras3,int tam){ //recebe os valores da fila de carros de entrada e retorna duas filas contendo
	int i;																			   // em l2 os carros da fila de entrada com placas pares
																					   // e  l3 os carros da fila de entrada com placas impares
	if (l_vazia(*tras1) == 1 ){   
		printf("\nERRO: lista vazia\n");	//verifica se a fila de entrada nao esta vazia
	
	}else{
		
		while(*tras1>-1){  	 //percorre a fila de entrada enquento ela nao for vazia
							//o codigo ira testar sempre pelo primeiro valor da lista
      
            if (l1[0].placa % 2 == 0){ //se o numero da placa do carro é par
            	
            	l_insere(l2,&l1[0],tras2,tam); //o carro é inserido na fila l2
            	l_remove1(l1,tras1);          // e o valor  é removido da fila de entrada
           
            }else{ 							//se o numero for impar
            	
            	l_insere(l3,&l1[0],tras3,tam);  // os dados do carro sao inseridos na fila l3
            	l_remove1(l1,tras1);           // e o valor é removido da fila de entreda
            }
		

		}   
							  
	}


}



void l_imprimir(fila *p,int tras){  //imprime valores da fila
	int i;

	if (l_vazia(tras) == 1 ){
		printf("\nERRO: lista vazia\n");	
	
	}else{
		for(i=0;i<=tras;i++){
			imprimir(&p[i]); //imprime os dados que esta na posição i da fila
		}
	}

}

void menu(int *op){ //imprime menu
	
	printf("\n1- Inserir carros na fila \n");
	printf("2- Imprimir carros da fila\n");
	printf("3-Remover veiculo da fila\n");
	printf("4- Separar fila \n");
	printf("5- Sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}



int main(){
	int op=0,placa;                                    
	int tras1,tras2,tras3,tam=4;      //tras representa quanrros iten esta inseridos na fila                     
	int aux;                         //tra1 referese a fila de entrada, tras2 referese a carros_p e tras3 referese a carros_i
	char chassi[20];
	
	fila carros[tam];      //fila de entrada
	fila carros_p[tam];   //fila que ira guardar os carros com placas pares
	fila carros_i[tam];  //fila que ira guardar os carros com placas impares

	fila auxiliar;  //armazena os dados , que vao ser inseridos na fila                                  

	inicia_l(&tras1); //inicia as filas
	inicia_l(&tras2);
	inicia_l(&tras3);

	while(op!=5){
		
		menu(&op);

		switch(op){
			case 1:
				aux = 1;           //insere itens na fila 1 enquanto o ususario nao digitar 0 ou a fila ficar cheia
				while(aux != 0){


					printf("digite os dados do carro: ");
					ler(&auxiliar);

					l_insere(carros,&auxiliar,&tras1,tam);

					if (l_cheia(tras1,tam)==1){
						
						break;
					}			

					printf("\ndeseja inserir nova palavra (0-nao 1-sim): ");
					scanf("%d",&aux);
					

				}

				break;

			case 2:	 //imprime as filas 
				printf("\n1-fila de entrada dos carros \n2-fila dos carros com placa pares\n3-fila dos carros com placa impares\n\n");
				printf("digite a lista que vocer deseja imprimir: ");
				scanf("%d",&aux);
				
				if (aux==1){  //imprime fila de entrada
					printf("\n\n");
					l_imprimir(carros,tras1);
					
				}if (aux==2){
					l_imprimir(carros_p,tras2); //imprime fila contendo os carros com placas pares
				
				}if (aux==3){
					l_imprimir(carros_i,tras3); //imprime fila contendo os carros com placas impares
				}
				
				break;
			
			case 3:                                            //remove um carro pela sua placa
				printf("digite o numero da placa: ");
				scanf("%d",&placa);

				if(remover_carro(carros,&tras1,placa,chassi) == 1){
					printf("\nveiculo removido com sucesso! numero do chassi : %s \n",chassi);
				}else{
					printf("\nERRO! nao foi possivel remover veiculo\n");
				}

				break;
			
			case 4:  //divide a lista de entrada com carros_p contendo os carros com placas pares e carros_i contendo os carros com placas impares e remove a lista de entrada

				l_dividir(carros,&tras1,carros_p,&tras2,carros_i,&tras3,tam);
				printf("\noperação concluida!!\n");
				
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