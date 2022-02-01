#include<stdio.h>
#include<string.h>
#include<ctype.h>


typedef struct { 
	char palavra[50];
	
}pilha;  // define a estrutura pilha

void inicia_p(int *topo){ // inicia pilha

	*topo = -1;

}

int p_vazia(int *topo ){ // verifica se a pilha ta vazia
	
	if (*topo < 0)
		
		return 1;   //retorna 1 se tiver
	
	else
		return 0; //retorna 0 se nao tiver
	

}

int p_cheia(int *topo, int tam){ // verifica se a pilha ta cheia
	
	if (*topo == tam-1)       
		return 1;  //retorna 1 se tiver
	else
		return 0; //retorna 0 se nao tiver
}

void p_insere(pilha *p , char *n,int *topo, int tam){ //insere um valor na pilha

	if (p_cheia(topo,tam) == 1){  //verifica se a pilha ta cheia
		printf("\nERRO: pilha cheia\n");
	
	}else{  //se nao tiver insere o item na pilha
		(*topo)++;
		strcpy(p[*topo].palavra,n);

	}

}
int consoantes(char l){  //recebe um caracter e devolve 1 se ele for consoante
	int i;				//e devolve 0 se ele nao for consoante
	char c[] = "aeiou" ;

	for (i = 0; i < strlen(c); ++i){

		if ( (tolower(l) == c[i] ) || (  tolower(l) <96 || tolower(l) > 122 ) ){
			return 0;
		}
	}

	return 1;

}

int p_remove(pilha *p,int *topo, char *str, int tam){ //remove items na pilha de entrada que iniciam com consoante
	int flag=0,topo_aux=-1;
	pilha aux[tam];  //cria uma pilha auxiliar para guardar o valores da pilha de entrada que nao iniciam com consoante

	while(p_vazia(topo) != 1){ //perrcorre a pilha enquanto ela nao é vazia

		if (consoantes(p[*topo].palavra[0]) == 1){ // verifica se o valor da pilha inicia com consoante
			strcpy(str,p[*topo].palavra);         // se sim retorna em str a palavra 
			(*topo)--;                           //  e remove a palavra da pilha
			flag = 1;                           // flag 1 indica que uma palavra foi removida
			break;	                           // para de percorrer a pilha
		
		}else{                                // se nao encontrar a palavra que inicia com consoante
			p_insere(aux,p[*topo].palavra,&topo_aux,tam);   //insere a palavra na pilha auxiliar
			(*topo)--;                                      // e remove o valor da pilha de entrada
		}												  // e continua perrcorendo a pilha ate achar uma palvra 
		                                                 // que inicia com consoante ou ate a pilha de entrada ser vazia
	}
	while(p_vazia(&topo_aux) == 0){                    // se tiver sido inserido valores na pilha auxiliar
		p_insere(p,aux[topo_aux].palavra,topo,tam);   // reinsere os valores na pilha de entrada ou seja insere na pilha de entrada as palavras que nao inicia com consoante
		topo_aux--;                                  // desenpilha a pilha auxiliar

	}
	if (flag==1){
		return 1;  // retorna 1 se  uma palavra foi removida
	
	}else{

		return 0; // retorna 0 se  uma palavra nao foi removida
	}

}
void p_imprimir(pilha *p,int *topo){  //imprime valores da pilha
	int aux;

	if (p_vazia(topo) == 1){
		printf("\nERRO: pilha vazia\n");
	}else{
		aux = *topo;
		while(aux >= 0){
			printf("%s \n",p[aux].palavra );
			aux--;
		}
	}

}

void menu(int *op){ //imprime menu
	
	printf("\n1- inserir pilha 1\n");
	printf("2- inserir pilha 2\n");
	printf("3- imprimir pilha\n");
	printf("4- gerar piha 3\n");
	printf("5- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}



int main(){
	int op=0;
	char plv[50];                                        //topo1 representa o topo da pilha 1, tam1 tamanho da pilha 1
	int topo1,topo2,topo3,tam1,tam2,tam3;               //topo2 representa o topo da pilha 2, tam2 tamanho da pilha 2
	int aux,aux2=1;                                    //topo3 representa o topo da pilha 3, tam3 tamanho da pilha 3


	printf("digite o tamanho da pilha 1: "); //le o tamanho da pilha1 de entrada
	scanf("%d",&tam1);

	pilha str1[tam1]; //cria a pilha2 de entrada 

	printf("digite o tamanho da pilha 2: "); //le o tamanho da pilha2 de entrada
	scanf("%d",&tam2);

	pilha str2[tam2]; //cria a pilha de entrada 
	
	tam3 = tam1+tam2; //tamanho da pilha 3 vai ser o tamanho da pilha 1 + pilha 2

	pilha str3[tam3]; //cria a pilha 3


	inicia_p(&topo1);  //inicia as pilhas
	inicia_p(&topo2);
	inicia_p(&topo3);



	while(op!=5){
		menu(&op);

		switch(op){
			case 1:
				aux2 = 1;           //insere itens na pilha 1 enquanto o ususario nao digitar 0 ou a pilha ficar cheia
				while(aux2 != 0){			
					printf("\ndigite uma palavra: ");
					scanf("%s",plv);
					p_insere(str1,plv,&topo1,tam1);
					printf("\ndeseja inserir nova palavra (0-nao 1-sim): ");
					scanf("%d",&aux2);

				}

				break;

			case 2:	
				aux2 = 1;         //insere itens na pilha 2 enquanto o ususario nao digitar 0 ou a pilha ficar cheia
				while(aux2 != 0){
					printf("digite uma palavra: ");
					scanf("%s",plv);
					p_insere(str2,plv,&topo2,tam2);
					printf("\ndeseja inserir nova palavra (0-nao 1-sim): ");
					scanf("%d",&aux2);
				}

				break;
			
			case 3:                                            //imprime as pilha 1 para imprimir pilha 1,2 para imprimir pilha 2 e 3 para imprimir pilha 3
				printf("\n1-pilha1\n2-pilha 2\n3-pilha 3\n");
				printf("digite a pilha que vocer deseja imprimir: ");
				scanf("%d",&aux);
				
				if (aux==1){
					printf("\nvalores pilha1: \n");
					p_imprimir(str1,&topo1);
					
				}if (aux==2){
					printf("\nvalores pilha2: \n");
					p_imprimir(str2,&topo2);
					
				
				}if (aux==3){
					printf("\nvalores pilha3: \n");
					p_imprimir(str3,&topo3);
					
				}

				break;
			
			
			case 4: //referente a letra d da questao
				aux = tam3; //aux recebe o tamanho da pilha 3

				while(aux>=0){  //percorre enquanto aux nao for negativo
					
					if (p_vazia(&topo1)== 0){                       // se a pilha 1 nao for vazia
						if (p_remove(str1,&topo1,plv,tam1) == 1){  //verifica se possui palavra com inicial consoantes 
							p_insere(str3,plv,&topo3,tam3);       // se sim remove retorna 1 e retorna a palavra
																 // chama a função pilha insere para inserir a palavra na pilha 3
						}
					}
					
					if (p_vazia(&topo2)== 0){ // se a pilha 2 nao for vazia 
						
						if (p_remove(str2,&topo2,plv,tam2)== 1){  //sera feito o mesmo procedimento explicado acima so que com  a pilha
							p_insere(str3,plv,&topo3,tam3);
					
						}
					}                                        //objetivo desta implementação foi busca palavra na pilha 1 e inserir na pilha 3
															//depos busca palavra na pilha 2 e inserir na pilha 3 


					aux--;
				}
				printf("\nOperacao concluida!\n");

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