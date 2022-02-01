#include <stdio.h>
#include<string.h>
#include <ctype.h>
#define TAM 50

void converte(char *str, int i, int uni, int *valor){ //função recebe uma string e converte em numero
	int n;
	                                                    
	if(i >=0){   //a função ira percorrer a string do final ao inicio                                     
		if(isdigit(str[i])){ // e verificar se o caracter é um valor numerico
			n = str[i] - 48; // entao faz o calculo converte o caracter em um inteiro pegando o caracter e subraindo 48 que representa o valor do caracter 0 na tabela asc 
							//ex:str[i]= 1 o valor do caracter 1 pela tabela asc é 49 enta n = 49 - 48 = 1 que é o caracter convertido em int  
			converte(str,i-1, uni * 10, valor); //faz a chamada recursiva passando a string , decrementando o valor de i que é o indice , multiplicando 10 a unidade que servira para fazer a converção e o valor do caractre convertido
											   // a chamada deixa pendente o calculo final da converção
			*valor = *valor + (n * uni);  //valor recebera o valor da string convertida em inteiro
		}
		else converte(str,i-1, uni, valor); //se o caracter nao for um digito ele apenas decrementa o i
 	 }
}



int main(){
	char nome[50];
	int valor = 0,i=0;
	
	printf("Entrada: ");
	scanf("%s",nome);
		
	converte(nome,strlen(nome)-1,1,&valor);
		
	printf("saida = %d\n\n",valor);
	
	return 0;
}