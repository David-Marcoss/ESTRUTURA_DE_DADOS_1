#include <stdio.h>
#include <ctype.h>
#define TAM 50
#include<string.h>

void misterio1(char str[TAM], int i, int uni, int *valor){ //essa fun��o ira receber uma string e ela ira verificar se possuem digitos numericos
	int n;												 // na sting se posuir ela ira transformar os digitos numericos em um valor inteiro que sera armazenado na variavel valor
	                                                   // exemplo a func�ao recebe a string "A1B345" ela ira devovel na variavel valor o inteiro 1345 que representa os 
	if(i >=0){                                        // valores numericos contidos na string.
		if(isdigit(str[i])){ 
			n = str[i] - 48;
			*valor = *valor + (n * uni);
			printf("str= %c  valor = %d n= %d uni= %d\n",str[i],*valor,n,uni);
			misterio1(str,i-1, uni * 10, valor);
		}
		else misterio1(str,i-1, uni, valor);
 	 }
}

void misterio2(char str[TAM], int i, int uni, int *valor){ // sem recur��o 
	int n;
	
	while(i >=0){ // roda enquanto I >= 0 ou seja
		if(isdigit(str[i])){ //verifica se o caractere na possi�ao i da string � numerico
			n = str[i] - 48; // se sim ele ele faz a subtra��o por 48 exemplo se o caracter for 1 ele possui um valor inteiro = 49 subraindo 49-48
							// obtem-se o valor 1 entao subtranindo digito por 48 obtem o seu valor em inteiro
			*valor = *valor + (n * uni); // valor recebe a soma de valor com o digito transformado em inteiro vezes a sua baze que � definido por sua posi��o no vetor 
										// exemplo o digito n=2 for o ultimo digito encontrado na string ele � multiplicado por uni=1 se ele for o penutimo n=2 ele sera multiplicado por uni=10 e somado com valor=21 e asim sucesivamente 
			uni *=10; //incrementa o uni
			 
		}
		i--; //decrementa o i o calculo inicia da ultima possi��o da string ate a primeira posi�ao
 	 }
}

int main(){
	char nome[50];
	int valor = 0,i=0;
	
	for(i;i<3;i++){
		valor=0;
		printf("Entrada: ");
		scanf("%s",nome);
		
		misterio2(nome,strlen(nome)-1,1,&valor);
		
		printf("saida = %d\n\n",valor);
	}
	return 0;
}