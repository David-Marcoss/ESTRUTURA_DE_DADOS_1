#include<stdio.h>
#include<string.h>
#include<ctype.h>

int maiusculas(char *palavra); //
void quant_vogais(char *palavra, int *aux); //retorna por parametro a quantidade de vogais
int principal(char *palavra,char *palavra2,int *aux1, int *aux2); // recebe duas string e  retorna por referencia quntidade de caracteres maiuscos de cada palavra e a quantidade total de vogais das duas palavras

int main(){
	char palavra[50],palavra2[50];
	int vogais=0,vogais2=0,total_vogais; //vogais = quantidade de palavras maiusculas da palavra1 ,vogais = quantidade de palavras maiusculas da palavra1 total vogais = quantidade total de vogais das duas palavras


	scanf("%s",palavra); //recebe a palavra digitada pelo usuario
	scanf("%s",palavra2);//recebe a palavra digitada pelo usuario

	total_vogais = principal(palavra,palavra2,&vogais,&vogais2);

	printf("\npalavra1 tem %d letras maiusculas\npalavra2 tem %d letras maiusculas\npalavra1 e palavra2 tem total de %d vogais  \n",vogais,vogais2,total_vogais);
}

int maiusculas(char *palavra){ //recebe uma palavra por referencia e retorna quantidade de letras maiusculas
	int i,cont=0;

	for(i=0;i<strlen(palavra);i++){
		if(palavra[i] >= 65 && palavra[i] <=90) //cada caracter tem um valor decimal segundo a tabela ascii as letras maiusculas do alfabeto possuem valor entre 65 e 90 
			cont++;							   //entao a função verifica na palavra recebida tem caracteres que estao nesse intervalo
	}
	return cont;
}

void quant_vogais(char *palavra,int *aux){ //recebe uma palavra por referencia e uma variavel inteira para retonar quantidade de vogais da palavra
	char vogais[10]="aeiouAEIOU"; // declara uma string recebendo as vogais do alfabeto
	int i,j;


	for(i=0;i<strlen(palavra);i++){
		for(j=0;j<strlen(vogais);j++){  
			
			if(palavra[i] == vogais[j]) //compara caracter por caracter se existe vogais dentro da string digitada pelo usuario assim será gravado na variavel aux quantidade de vogais e retornara por referencia
				*aux+=1;

		}

	}
}

int principal(char *palavra,char *palavra2,int *aux1, int *aux2){ 
	int total_vogais,vogais1,vogais2;

	quant_vogais(palavra,aux1);
	quant_vogais(palavra2,aux2);

	total_vogais = (*aux1)+(*aux2);

	*aux1 = maiusculas(palavra);
	*aux2 = maiusculas(palavra2);

	return total_vogais;

}