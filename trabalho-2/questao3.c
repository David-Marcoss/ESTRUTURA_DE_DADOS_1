#include<stdio.h>
#include<string.h>
#include<ctype.h>
# define tam 100


typedef struct { 
	char caracter[100];
	int topo;
	
}pilha;  // define a estrutura pilha

typedef struct{
	char exp[10];


}expressao;


void inicia_p(pilha *p){ // inicia pilha

	p->topo = -1;

}

int p_vazia(pilha *p){ // verifica se a pilha ta vazia
	
	if (p->topo < 0)
		
		return 1;   //retorna 1 se tiver
	
	else
		return 0; //retorna 0 se nao tiver
	

}

int p_cheia(pilha *p){ // verifica se a pilha ta cheia
	
	if (p->topo == tam-1)       
		return 1;  //retorna 1 se tiver
	else
		return 0; //retorna 0 se nao tiver
}

void empilha(pilha *p , char valor){ //insere um valor na pilha

	if (p_cheia(p) == 1){  //verifica se a pilha ta cheia
		printf("\nERRO: pilha cheia\n");
	
	}else{  //se nao tiver insere o item na pilha
		p->topo++;
		p->caracter[p->topo] = valor;

	}

}

char desempilhar(pilha *p){ //desempilha um carcter e retorna
	char c;

	if (p_vazia(p) == 0){
		
		c = p->caracter[p->topo];
		p->topo--;
	}

	return c;
}

int eh_numero(char c){
	int flag;

	if (c >= 48 && c <= 57){
		flag = 0;
	}else{
		flag = 1;
	}

	return flag;

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

	pilha p; //declara pilha
	
	int i=0,j=0;
	char aux;
	
	inicia_p(&p); // pilha auxiliar armazena operadores e parenteses
 
	while(exp[i] != '\0'){ // percorre a string enquanto ela nao encontra caracter nulo

		if (exp[i] == '('){  //se o caracter for '(' 

			empilha(&p,exp[i]);  //empilha o caracter
			
		
		}else if ( exp[i] == ')' ){  					//se o caracter for ')'

			while(p_vazia(&p) != 1 && p.caracter[p.topo] != '('){     // perrcorre a pilha enquanto nao encontrar o '('

				aux = desempilhar(&p);               // desenpilha o caractre do topo da pilha

				if (aux != '('){   			       // se o caracter nao for "("
					pos_fixa[j] = aux; 		      //joga o caracter na string pos fixa
					j++;

					pos_fixa[j] = ' '; 
					j++;
				}

			}

			aux = desempilhar(&p);
			
		
		}else if (exp[i] == '+' || exp[i] == '-'){ //se o caracter for um operador '+' ou '-'
			
			while(p_vazia(&p) != 1 && p.caracter[p.topo] != '('){  //se a pilha nao for nula 
												 // desenpilha os caracteres da pilha enquanto nao encontrar o "(" 
				aux = desempilhar(&p);

				if (aux != '('){         // se o caracter nao for '(' 
					pos_fixa[j] = aux;  //joga o caracter na pos fixa
					j++;

					pos_fixa[j] = ' ';
					j++;
				}

			} 
			empilha(&p, exp[i]); //depois empilha o caracter da string de entrada

		}else if (exp[i] == '*' || exp[i] == '/'){ //se o caracter for um operador '*' ou '/'

			while(p_vazia(&p) != 1 && p.caracter[p.topo] != '(' && p.caracter[p.topo] != '+' && p.caracter[p.topo] != '-' ){ //se a pilha nao for nula
																					   // desenpilha os caracteres da pilha enquanto nao encontrar o "(" ou
																					  // encontrar um operador de menor precedencia como '+' ou '-'
				aux = desempilhar(&p);	

				if (aux != '('){           // se o caracter nao for '('
					pos_fixa[j] = aux;    //joga o caracter na pos fixa
					j++;

					pos_fixa[j] = ' ';
					j++;
				}

			}
			empilha(&p, exp[i]); //depois empilha o caracter da string de entrada

			
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

	while(p_vazia(&p) != 1){	 //se a pilha nao tiver vazia
						// quer dizer que a string chegou no fim 
					   // e sobrou algum oprador na pilha

			aux = desempilhar(&p); //desenpilha o operador

		if (aux != '('){
			pos_fixa[j] = aux; //joga o caracter na pos fixa
			j++;
			pos_fixa[j] = ' ';
			j++;
		}
	}


	pos_fixa[j] = '\0'; // faz a string pos-fixa receber '\0' para indicar o fim da string

}

int valida_expressao(expressao *ex, int TAM){
	int i = 0,flag = 0;
	char ant,prox, parenteses;

	pilha p; //declara pilha 

	inicia_p(&p);  // inicia pilha
			  // p ira armazenar parenteses

	while(i < TAM && flag != 1 ){ //percorre o vetor de strings
		
		ant = ex[i].exp[0];      //ant o primeiro recebe o caracter do vetor na posição i 

		if (eh_operador(ant) == 0 && i == 0){ 
			flag = 1;
		}
		
		prox = ex[i+1].exp[0];  //ant o primeiro recebe o caracter do vetor na posição i + 1
		
		i++;  // incrementa o i

		if (ant == '('){ // se o ant for '(''

			if (prox == '('){ //verifica se o prox tambem é '('
				
				empilha(&p,prox); // se for enpilha o prox
				i++; //incrementa o i 
				
			}

			else if (eh_numero(prox) ==  1){ // se nao entrou no caso acima verifica se o prox é um numero
				flag = 1; //se nao for o flag recebe 1
			
			}
			
			empilha(&p,ant); //emprilha o ant
			

		}else if (eh_numero(ant) ==  0){ //neste caso se o ant for um numero
				
				if (prox != '\0'){ // se o prox for diferente de '/0'

					parenteses = ' ';  // esvazia o valor de parenteses

					if (prox == ')'){ // se o prox for ')'

						parenteses = desempilhar(&p); // desempilha o caracter

						

						if (parenteses != '('){ //verifica se prox e parenteses formam um par
							flag = 1;  // se nao formar flag recebe 1
						}
						i++; //incrementa o i
						
					
					}else if ( eh_operador(prox) == 1 && i < TAM){ //verifica se o prox nao é operador
							flag = 1; //se nao for flag recebe q
					
					}else{
						    //se nao entrar em nehum dos casos acima apenas incrementa o i
						i++;
					}
				}

		
		}else if (ant ==  ')'){ //se o ant for ')'

			parenteses = ' '; //esvazia o valor 

			parenteses = desempilhar(&p);	//desempilha caracter

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

	if (p_vazia(&p) == 0){ // verifica se a pilha de parenteses esta vazia
		flag = 1; //se nao tiver flag recebe 1
		
	}
	
	return flag;  //flag 1 a expressao é invalida
				 //flag 0 a expressao é valida

}


int divide_expressao( char exp[], expressao *aux, int *TAM){ //recebe a expressao e retorna a expressao em um vetor de strings
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
	

	*TAM = j; // tam devolve a quantidade de elementos do vetor

	return flag; // flag devolve 1 se tiver algum erro
				// devolve flag 0 se a operação foi bem concluida
}

int main(){
	char exp[100], pos[100];
	int i = 0,TAM=0,flag;

	 expressao aux[100];

	printf("digite a expressao: "); //le a expressao
	scanf("%[^\n]",exp);

	 flag = divide_expressao(exp, aux,&TAM); //divide a expressao num vetor que ira
	 										//conter os numeros , operadores e parenteses da expressap

	if (flag == 0){ 

		flag = valida_expressao(aux, TAM); // valida a expressao

		if (flag == 0){ // se a expressao for valida 

			in_fixa(exp,pos); //devolve uma string contendo a expressao convertida para pos-fixa

			printf("\nexpressao in-fixa: %s\n",exp);
			printf("expressao pos-fixa: %s\n\n",pos);
			
		}else{ // se nao entrar no caso acima a expressao é invalida
			
			printf("Ha expressao e invalida !!\n");
		}
		
	}else{

		printf("Ha expressao e invalida !!\n");
	}



	return 0;
}