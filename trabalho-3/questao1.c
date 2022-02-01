#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10



typedef struct {
	char var;
	int coeficiente;
	int potencia;
	
}termo;


typedef struct l{
	termo p;
	struct l *prox;
	
}lista;

typedef struct {

	int cod;

	lista *i;
	lista *f;
	
}polinomios;



void ler_termo(termo *p, char var){  			  //recebe um polinomio e um caracter que indica a 
													 //	variavel do termo que pode ser (X, Y ou Z)
	p->var = var;								   	// e ler o coeficiente e potencia e armazena o termo
	printf("\ndigite o coeficiente de %c :",var);
	scanf("%d",&p->coeficiente);

	printf("\ndigite a potencia de %c :",var);
	scanf("%d",&p->potencia);


}



void inicia(lista **inicio, lista **fim){
		*inicio = *fim = NULL;
}


void aloca(lista **No, termo p){
	lista *novo;

	novo = (lista*)malloc(sizeof(lista));
	novo->p = p;
	novo->prox = NULL;

	*No = novo;

}

void insere(lista **inicio, lista **fim, lista **No){
	lista *ant,*aux;
	
	ant = NULL;
	aux = *inicio;

	if (*inicio == NULL){       //primeiro caso
		
		*inicio = *fim = *No;
		(**No).prox = *inicio;    // faz o NO apontar para o Inicio

		
	}else{  //insere no fim 
		
		(**No).prox = *inicio; //faz o NO.prox apaontar para o inicio
		
		(**fim).prox = *No;
		*fim = *No;
	}


}

void imprimir_representacao(lista *inicio){ //imprime a lista
	lista *aux;
	
	aux = inicio;
	printf("\npolinomio: ");

	do{
		printf("%d%c^%d ",aux->p.coeficiente,aux->p.var,aux->p.potencia);
		
		if (aux->prox != inicio && aux->prox->p.coeficiente > -1){
			printf(" + ");
		}
		aux = aux->prox;
		
	}while(aux != inicio);

	printf("\n");

}
 
void cadrastar_polinomio(lista **inicio, lista **fim){  //insere valores na lista
	lista *No;
	termo termo;

	char var[4] = {'x','y','z'};
	int i;

		for (i = 0; i < strlen(var); ++i){

			ler_termo(&termo,var[i]);

			aloca(&No,termo);

			insere(inicio,fim,&No);


			
		}

}

int pot(int coeficiente , int potencia){
	int i,pot=1;

	for (i = 0; i < potencia; ++i){
		pot*= coeficiente;
	}

	return pot;

}

int calcula_polinomio(lista *inicio,int valores[]){
	int resul=0 ,i=0;

	lista *aux;

	aux = inicio;

	do{
		resul += aux->p.coeficiente * pot(valores[i],aux->p.potencia);

		aux = aux->prox;
		i++;

	}while(aux != inicio);

	return resul;
}

void avaliar_polinomio(lista *inicio){
	int valores[4],i=0,resul;

	printf("\ndigite o valor para x: ");
	scanf("%d",&valores[i]);
	i++;

	printf("digite o valor para y: ");
	scanf("%d",&valores[i]);
	i++;

	printf("digite o valor para z: ");
	scanf("%d",&valores[i]);

	printf("\nresul: %d\n",calcula_polinomio(inicio,valores));



}

int busca_polinomio(polinomios pol[] ,int tam , int cod){  //recebe um vetor de polinomios , a quantidade de elementos do vetor
														// e um cod e verifica se o codigo ja foi cardastado no vetor
	int i=0,flag=-1;                                   // se encontrar o codigo devolve a posição do vetor aonde foi encontrado o cod
													  // se nao encontar devolve -1
	while(i < tam && flag < 0){

		if (pol[i].cod == cod){
			flag = i;
		}

		i++;

	}

	return flag;

}

/*void soma_polinomios(lista *inicio1,lista *inicio2){ // recebe o incicio de duas listas circulares comtendo os polinomios
	int resul=0 ,i=0;

	lista *p1;
	lista *p2;

	lista *inicio,*fim,*no;

	p1 = inicio1;
	p2 = inicio2;

	termo aux;

	printf("\nresultado da soma: ");

	do{  //percorre os termos do polinomios

		if (p1->p.var == p2->p.var  && p1->p.potencia == p2->p.potencia){  //se o polinomios tiverem variaveis e potencias iguais
			                                                              // soma os coeficientes e matem variavel e potencia
			aux.var = p1->p.var;
			aux.coeficiente = p1->p.coeficiente + p2->p.coeficiente;
			aux.potencia = p1->p.potencia;

			printf(" %d%c^%d ",aux.coeficiente,aux.var,aux.potencia);

			if (p2->prox->p.coeficiente > -1  && p1->prox != inicio1){
				printf(" + ");
			}

		}else{ //se nao 

			printf(" %d%c^%d ",p1->p.coeficiente,p1->p.var,p1->p.potencia); //apenas mantem os polinomios da mesma forma

			if (p2->p.coeficiente > -1){
				printf(" + ");
			}

			printf(" %d%c^%d ",p2->p.coeficiente,p2->p.var,p2->p.potencia);

			if (p1->prox->p.coeficiente + p2->prox->p.coeficiente > -1 && p1->prox != inicio1){
				printf(" + ");
			}

		}



		p1 = p1->prox;
		p2 = p2->prox;
		
	}while(p1 != inicio1);

	printf("\n");

	
}*/

void soma_polinomios(lista *inicio1,lista *inicio2){ // recebe o incicio de duas listas circulares comtendo os polinomios
	int resul=0 ,i=0;

	lista *p1;
	lista *p2;

	lista *inicio,*fim,*No;

	p1 = inicio1;
	p2 = inicio2;

	termo aux;

	inicia(&inicio,&fim);

	do{  //percorre os termos do polinomios

		if (p1->p.var == p2->p.var  && p1->p.potencia == p2->p.potencia){  //se o polinomios tiverem variaveis e potencias iguais
			                                                              // soma os coeficientes e matem variavel e potencia
			aux.var = p1->p.var;
			aux.coeficiente = p1->p.coeficiente + p2->p.coeficiente;
			aux.potencia = p1->p.potencia;

			aloca(&No,aux);                                  //insere os termos do resultado da operação

			insere(&inicio,&fim,&No);                      // numa lista auxiliar


		}else{ //se nao mantem-se os termos dos polinomios

			aloca(&No,p1->p);

			insere(&inicio,&fim,&No);

			aloca(&No,p2->p);

			insere(&inicio,&fim,&No);



		}



		p1 = p1->prox;
		p2 = p2->prox;
		
	}while(p1 != inicio1);

	imprimir_representacao(inicio);  //imprime o resiultado da operação

	
}

void mult_polinomios(lista *inicio1,lista *inicio2){ // recebe o incicio de duas listas circulares comtendo os polinomios
	int resul=0 ,i=0;
	int coeficiente;

	lista *p1; 
	lista *p2; 

	p1 = inicio1; //p1 recebe polinomio1
	p2 = inicio2; //p2 recebe polinomio2

	termo aux; //declara um termo auxiliar

	printf("\nResultado multiplicacao: ");

	do{ //percorre os termos do polinomio 1

		do{ //e multiplica o termo do pilimomio 1 por todos os termos do polinomio 2

			if (p1->p.var == p2->p.var){   //se os termos possuirem variaveis iguais
										  // mantem-se a variavel e multiplica os coeficientes e soma as potencias
				aux.var = p1->p.var;
				aux.coeficiente = p1->p.coeficiente * p2->p.coeficiente;
				aux.potencia = p1->p.potencia + p2->p.potencia;

				printf(" %d%c^%d ",aux.coeficiente,aux.var,aux.potencia);  

			
			}else{ //se nao possuirem variaveis iguais

				coeficiente = p1->p.coeficiente * p2->p.coeficiente;   // multiplica se os coeficientes

				printf(" %d%c^%d%c^%d ",coeficiente,p1->p.var,p1->p.potencia,p2->p.var,p2->p.potencia); //e mantem as variaveis e potencias
			
			}

			if (p1->p.coeficiente * p2->prox->p.coeficiente  > -1 && p2->prox != inicio2){
					printf(" + ");
			}


			p2 = p2->prox;

		}while(p2 != inicio2); //percorre a lista até chegar novamente no inicio


		p1 = p1->prox;

		if (p1->p.coeficiente * p2->p.coeficiente > -1 && p1 != inicio1){
			printf(" + ");
		}
	
	}while(p1 != inicio1); 


	printf("\n");
}

void derivada_parcial(lista *inicio, char var){ //recebe um polinomio e uma variavel e calcula sua derivada parcial
	int flag = 0;
	int coeficiente;

	lista *p1;

	p1 = inicio;

	termo aux;
	
	do{ //perrcorre o polinomio
		
		if (p1->p.var == var){ //se o termo tiver variavel igual avariavel recebida

			if (p1->p.potencia > 0){ //calcula e mostra derivada parcial em relaçao a variavel
		
				coeficiente = p1->p.potencia;
				aux.var = var;
				aux.coeficiente = p1->p.coeficiente;
				aux.potencia = p1->p.potencia - 1;

				printf("\nderivada parcial em relacao a %c :  %d*%d*%c^%d \n",var,aux.coeficiente,coeficiente,aux.var,aux.potencia);
			
			}else{
				printf("\nderivada parcial em relacao a %c : 0 \n",var);
			}

			flag = 1;
			
		}
		 				//nos demais termos sao constantes que sao igauis a 0

		p1 = p1->prox;

	}while(p1 != inicio && flag != 1);

} 


void menu(int *op){ //imprime menu
	
	printf("\n1- cadrastar polinomio\n");
	printf("2- Imprimir a representação de um polinômio \n");
	printf("3- Imprimir a representação de todos polinômio \n");
	printf("4- avaliar polinômio\n");
	printf("5- somar polinomios \n");
	printf("6- multiplicar polinomios \n");
	printf("7- calcular derivada parcial de um polinomio \n");
	printf("8- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}

void flush_in(){ 
	int ch;
	while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}

int main(){
	
	lista *inicio,*fim; 
	int op=1,aux,cod,cod2;

	int tam = 0; //indica quantos polinomios foram cadrastados

	polinomios pol[MAX];

	char var;

	while(op!=8){
		
		menu(&op);

		switch(op){
			
			case 1:
				
				printf("digite o codigo do polinomio: ");
				scanf("%d",&pol[tam].cod);

				if (busca_polinomio(pol,tam,pol[tam].cod) < 0 ){
					
					inicia(&pol[tam].i,&pol[tam].f);
					cadrastar_polinomio(&pol[tam].i,&pol[tam].f); 

					tam++;
				
					
				}else{
					printf("\ncodigo ja cardastado!! nao é possivel cadrastar polinomio\n");
				}

					
				break;

			case 2:

				if (tam > 0){

					printf("digite o codigo do polinomio: ");
					scanf("%d",&cod);

					aux = busca_polinomio(pol,tam,cod);

					if (aux != -1){
						
						if (pol[aux].i != NULL){
							imprimir_representacao(pol[aux].i);
						}else
							printf("\nlista vazia!!\n");	 
					
					}else
						printf("\ncodigo nao encontrado!!\n");


				}else
					printf("\nNao ha polinomios cadrastados!!\n");
				
						
				
				break;
		

			case 3:

				if (tam > 0){
					
					for (int i = 0; i < tam; ++i){
						
						imprimir_representacao(pol[i].i);
	 
					}
				}else
					printf("\nNao ha polinomios cadrastados!!\n");
				
				break;


			
			case 4:

				if (tam > 0){

					printf("digite o codigo do polinomio: ");
					scanf("%d",&cod);

					aux = busca_polinomio(pol,tam,cod);

					if (aux != -1)
						avaliar_polinomio(pol[aux].i);
							 
					else
						printf("\ncodigo nao encontrado!!\n");
					
				}else
					printf("\nNao ha polinomios cadrastados!!\n");
				
				
				break;

			case 5:

				if (tam > 0){

					printf("digite o codigo do polinomio 1: ");
					scanf("%d",&cod);


					printf("digite o codigo do polinomio 2: ");
					scanf("%d",&cod2);

					cod = busca_polinomio(pol,tam,cod);
					cod2 = busca_polinomio(pol,tam,cod2);
					
					if (cod != -1 && cod2 != -1)
						
						soma_polinomios(pol[cod].i, pol[cod2].i);
							 
					else
						printf("\ncodigo nao encontrado!!\n");
					
				}else
					printf("\nNao ha polinomios cadrastados!!\n");
				
				
				break;


			case 6:

				if (tam > 0){

					printf("digite o codigo do polinomio 1: ");
					scanf("%d",&cod);


					printf("digite o codigo do polinomio 2: ");
					scanf("%d",&cod2);

					cod = busca_polinomio(pol,tam,cod);
					cod2 = busca_polinomio(pol,tam,cod2);
					
					if (cod != -1 && cod2 != -1)
						
						mult_polinomios(pol[cod].i, pol[cod2].i);
							 
					else
						printf("\ncodigo nao encontrado!!\n");
					
				}else
					printf("\nNao ha polinomios cadrastados!!\n");
				
				
				break;

			case 7:

				if (tam > 0){

					printf("digite o codigo do polinomio: ");
					scanf("%d",&cod);

					aux = busca_polinomio(pol,tam,cod);

					if (aux != -1){

						flush_in();

						printf("digite a variavel (x, y ou z): ");
						scanf("%c",&var);
						
						if (var != 'x' && var != 'y' && var != 'z' ){
							
							printf("\nvariavel invalida!!\n");
					
						}else
							derivada_parcial(pol[aux].i,var);
						
					}else
						printf("\ncodigo nao encontrado!!\n");


				}else
					printf("\nNao ha polinomios cadrastados!!\n");

				break;
			
	
			case 8:
				printf("\nsaindo.....\n");
				break;


			
			default:
				printf("ERRO: opcao invalida \n");
				break;

		}
	}

	return 0;
}