#include<stdio.h>
#include<string.h>
#include<ctype.h>

void transforma(char *palavra); //tranforma palavra em minuscula para que o codigo funcione corretamente para qualquer palavra digitada pelo usuario
void minusculo(char *palavra, int *aux); //retorna por parametro a quantidade de vogais
int minusculo2(char *palavra); // retorna pel função a quantidade de vogais

int main(){
	char palavra[50];
	int vogais=0;


	scanf("%s",palavra); //recebe a palavra digitada pelo usuario
	
	transforma(palavra);
	minusculo(palavra,&vogais);

	printf("palavra: %s tem %d vogais\n",palavra,minusculo2(palavra));
}

void transforma(char *palavra){ //recebe uma palavra por referencia e tranforma caracter por caracter em minusculo utilizando a função tolower
	int i;

	for(i=0;i<strlen(palavra);i++){
		palavra[i] = tolower(palavra[i]);

	}

}

void minusculo(char *palavra,int *aux){ //recebe uma palavra por referencia e uma variavel inteira para retonar quantidade de vogais da palavra
	char vogais[5]="aeiou"; // declara uma string recebendo as vogais do alfabeto
	int i,j;


	for(i=0;i<strlen(palavra);i++){
		for(j=0;j<strlen(vogais);j++){  
			
			if(palavra[i] == vogais[j]) //compara caracter por caracter se existe vogais dentro da string digitada pelo usuario assim será gravado na variavel aux quantidade de vogais e retornara por referencia
				*aux+=1;

		}

	}
}

int minusculo2(char *palavra){ // faz o mesmo que a função anterior porem esta fução ira retronar a quantidade de vogais pela propria função
	char vogais[5]="aeiou";
	int i,j,cont=0;


	for(i=0;i<strlen(palavra);i++){
		for(j=0;j<strlen(vogais);j++){
			
			if(palavra[i] == vogais[j])
				cont++;

		}

	}
	return cont;
}
