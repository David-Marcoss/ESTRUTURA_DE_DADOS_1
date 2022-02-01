#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _Pilha{
	char valor;
	struct _Pilha *ant;

}Pilha;

typedef struct{
	char exp[10];


}expressao;

void aloca(Pilha **No){
      Pilha *novo;      //cria uma strutura do tipo pilha

      novo = NULL;

      novo = (Pilha*)malloc(sizeof(Pilha));  //aloca essa estrutura

      *No = novo; //e faz o no receber a estrutura alocada

}

void empilha(char valor,Pilha **topo, Pilha *No){
	
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

int eh_numero(char c){
	int flag;

	if (c >= 48 && c <= 57){
		flag = 0; 
	}else{
		flag = 1;
	}

	return flag; //retorna o se for numero e 1 se nao

}

int eh_operador(char c){
	char aux[] = "+-*/";

	int flag=1 , i=0;

	while(i < strlen(aux) && flag != 0){

		if (c == aux[i]){
			flag = 0;
		}
		i++;
	}

	return flag; // flag == 1 nao é operador
				// flag == 0  é operador

}

void in_fixa(char exp[], char *pos_fixa){ //recebe uma expressao pos-fixa 
	        							  // e devolve na string pos_fixa a expressao convertida para in-fixa

	Pilha *p,*No; //declara pilha
	
	int i=0,j=0;
	char aux;
	
	p = NULL; // pilha auxiliar armazena operadores e parenteses
 
	while(exp[i] != '\0'){ // percorre a string enquanto ela nao encontra caracter nulo

		if (exp[i] == '('){  //se o caracter for '(' 
			aloca(&No);

			empilha(exp[i], &p, No);  //empilha o caracter
			
		
		}else if ( exp[i] == ')' ){  					//se o caracter for ')'

			while(p != NULL && p->valor != '('){     // perrcorre a pilha enquanto nao encontrar o '('

				aux = desempilha(&p);               // desenpilha o caractre do topo da pilha

				if (aux != '('){   			       // se o caracter nao for "("
					pos_fixa[j] = aux; 		      //joga o caracter na string pos fixa
					j++;

					pos_fixa[j] = ' '; 
					j++;
				}

			}

			aux = desempilha(&p);
			
		
		}else if (exp[i] == '+' || exp[i] == '-'){ //se o caracter for um operador '+' ou '-'
			
			while(p != NULL && p->valor != '('){  //se a pilha nao for nula 
												 // desenpilha os caracteres da pilha enquanto nao encontrar o "(" 
				aux = desempilha(&p);

				if (aux != '('){         // se o caracter nao for '(' 
					pos_fixa[j] = aux;  //joga o caracter na pos fixa
					j++;

					pos_fixa[j] = ' ';
					j++;
				}

			}
			aloca(&No); 
			empilha(exp[i], &p, No); //depois empilha o caracter da string de entrada

		}else if (exp[i] == '*' || exp[i] == '/'){ //se o caracter for um operador '*' ou '/'

			while(p != NULL && p->valor != '(' && p->valor != '+' && p->valor != '-' ){ //se a pilha nao for nula
																					   // desenpilha os caracteres da pilha enquanto nao encontrar o "(" ou
																					  // encontrar um operador de menor precedencia como '+' ou '-'
				aux = desempilha(&p);	

				if (aux != '('){           // se o caracter nao for '('
					pos_fixa[j] = aux;    //joga o caracter na pos fixa
					j++;

					pos_fixa[j] = ' ';
					j++;
				}

			}
			aloca(&No);
			empilha(exp[i], &p, No); //depois empilha o caracter da string de entrada

			
		}else if (eh_numero(exp[i]) == 0){ // se o caracter for um numero 
			
			while(eh_numero(exp[i]) == 0){ //enquanto o caracter for numero
				pos_fixa[j] = exp[i];      //joga o caracter na pos fixa
				j++;
				i++;                      //incrementa o i da string de entrada
			
			}

			pos_fixa[j] = ' ';
			j++;
			i--; // no fim o i é incrementado mais vezes do que o necessario
				// entao o i é decrementado 
		}


		i++; 	// incrementa o i para passar para o proximo caracter da string de entrada
				// se nao entrar em nenhum dos casos quer dizer que o caracter é um espaço
				// entao nao faz nada
	}

	while(p != NULL){	 //se a pilha nao tiver vazia
						// quer dizer que a string chegou no fim 
					   // e sobrou algum oprador na pilha

			aux = desempilha(&p); //desenpilha o operador

		if (aux != '('){
			pos_fixa[j] = aux; //joga o caracter na pos fixa
			j++;
			pos_fixa[j] = ' ';
			j++;
		}
	}


	pos_fixa[j] = '\0'; // faz a string pos-fixa receber '\0' para indicar o fim da string

}

int valida_expressao(expressao *ex, int tam){
	int i = 0,flag = 0;
	char ant,prox, parenteses;

	Pilha *p,*No; //declara pilha 

	p = NULL;  // inicia pilha
			  // p ira armazenar parenteses

	while(i < tam && flag != 1 ){ //percorre o vetor de strings
		
		ant = ex[i].exp[0];      //ant o primeiro recebe o caracter do vetor na posição i 

		if (eh_operador(ant) == 0 && i == 0){ 
			flag = 1;
		}
		
		prox = ex[i+1].exp[0];  //ant o primeiro recebe o caracter do vetor na posição i + 1
		
		i++;  // incrementa o i

		if (ant == '('){ // se o ant for '(''

			if (prox == '('){ //verifica se o prox tambem é '('
				aloca(&No);
				empilha(prox,&p,No); // se for enpilha o prox
				i++; //incrementa o i 
				
			}

			else if (eh_numero(prox) ==  1){ // se nao entrou no caso acima verifica se o prox é um numero
				flag = 1; //se nao for o flag recebe 1
			
			}
			
			aloca(&No); // se nao 
			empilha(ant,&p,No); //emprilha o ant
			

		}else if (eh_numero(ant) ==  0){ //neste caso se o ant for um numero
				
				if (prox != '\0'){ // se o prox for diferente de '/0'

					parenteses = ' ';  // esvazia o valor de parenteses

					if (prox == ')'){ // se o prox for ')'

						parenteses = desempilha(&p); // desempilha o caracter

						

						if (parenteses != '('){ //verifica se prox e parenteses formam um par
							flag = 1;  // se nao formar flag recebe 1
						}
						i++; //incrementa o i
						
					
					}else if ( eh_operador(prox) == 1 && i < tam){ //verifica se o prox nao é operador
							flag = 1; //se nao for flag recebe q
					
					}else{
						    //se nao entrar em nehum dos casos acima apenas incrementa o i
						i++;
					}
				}

		
		}else if (ant ==  ')'){ //se o ant for ')'

			parenteses = ' '; //esvazia o valor 

			parenteses = desempilha(&p);	//desempilha caracter

			if (parenteses != '('){ //verifica se formam par
				flag = 1; //se nao formar flag receb 1
			}


		}

		else if (eh_operador(ant) == 0 && eh_operador(prox) == 0 ){ //verifica se posui dois operadores seguidos na expreção
			flag = 1; //se tiver flag recebe 1
		
		
		}else if(eh_operador(ant) != 0 && eh_numero(prox) != 0){ 
			flag = 1;
		}

	} //sai do laço

	if (eh_operador(prox) == 0){ // verifica se o ultimo elemento é um operador
		flag = 1; //se for flag recebe 1
		
		
	}

	if (p!= NULL){ // verifica se a pilha de parenteses esta vazia
		flag = 1; //se nao tiver flag recebe 1
		
	}
	
	return flag;  //flag 1 a expressao é invalida
				 //flag 0 a expressao é valida

}

int divide_expressao( char exp[], expressao *aux, int *tam){ //recebe a expressao e retorna a expressao em um vetor de strings
	int i=0,j=0,flag = 0,k=0, indica=0;                    // o vetor vai conter os numeros , operadores e parenteses da expressap
	 
	char c;

	while(exp[i] != '\0' && flag != 1){ //perrcorre enqunto a expressao nao for nula


		if (exp[i] != ' ' && exp[i] != '\0'){ // se o caracter for diferente de espaçõ
			
			if (eh_numero(exp[i]) == 0){ // verifica se é numero

				while(eh_numero(exp[i]) != 1){

					aux[j].exp[k] = exp[i]; // se for armazena o numero no vetor string


					k++;
					i++;

				}
				if (exp[i] != ' ' && exp[i] != ')' && exp[i] != '\0'){ //seencontrar algum caracter que nao é numero
					flag = 1;  //flag recebe 1


				
				}else{
					aux[j].exp[k] = '\0'; //finaliza a string
					k = 0;
					j++; //incrementa o j
						// para passar para a proxima posição do vetor
				}

				
				if (exp[i] == ')'){ // se o caracter for ')' amazena o caracter no vetor
					
					aux[j].exp[0] = exp[i];
					aux[j].exp[1] = '\0';
					j++;
				}

 
			}else if (exp[i] == '(' || exp[i] == ')'){ // se o caracter for ')' ou '(' amazena o caracter no vetor
				aux[j].exp[0] = exp[i];
				aux[j].exp[1] = '\0';

				j++;
			
			}else if (eh_operador(exp[i]) == 0){ // se o caracter for operador amazena o caracter no vetor
				aux[j].exp[0] = exp[i];
				aux[j].exp[1] = '\0';

				j++;
			
			}
		}
		i++;
	}
	

	*tam = j; // tam devolve a quantidade de elementos do vetor

	return flag; // flag devolve 1 se tiver algum erro
				// devolve flag 0 se a operação foi bem concluida
}

int main(){
	char exp[100], pos[100];
	int i = 0,tam=0,flag;

	 expressao aux[100];

	printf("digite a expressao: "); //le a expressao
	scanf("%[^\n]",exp);

	flag = divide_expressao(exp, aux,&tam); //divide a expressao num vetor que ira
	 										//conter os numeros , operadores e parenteses da expressap

	if (flag == 0){ 

		flag = valida_expressao(aux, tam); // valida a expressao

		if (flag == 0){ // se a expressao for valida 

			in_fixa(exp,pos); //devolve uma string contendo a expressao convertida para pos-fixa

			printf("\nexpressao in-fixa: %s\n",exp);
			printf("expressao pos-fixa: %s\n\n",pos);
			
		}else{ // se nao entrar no caso acima a expressao é invalida
			
			printf("Ha expressao e invalida!!\n");
		}
		
	}else{

		printf("Ha expressao e invalida!!\n");
	}


	return 0;
}







