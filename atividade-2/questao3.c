#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void altera(char *nome){

	printf("digite o novo nome: ");
	scanf("%s",nome);

}

int main() {
	int n=1;
	char *nome,*cpf; //declara um ponteiro para nome e cpf

	while(n!=0){   // repete enquanto o usuario nao digitar 1

		nome = (char *) malloc(sizeof(char)); //aloca um espaço na memoria para o nome
		cpf = (char *) malloc(sizeof(char)); //aloca um espaço na memoria para o cpf

	
		printf("digite os dados: "); //recebe os dados 
		scanf("%s",nome); 
		scanf("%s",cpf);

		printf("\n%p %p %s  %s  \n",nome,cpf,nome,cpf); // imprimi o endereco de memoria e depois os conteudos

		altera(nome); // chama a função altera para alterar um nome

		printf("\n%p %p %s  %s  \n\n",nome,cpf,nome,cpf); // imprime novamente endereço e dados

		printf("digite 0 para sair ou 1 para continuar: ");
		scanf("%d",&n);
	
	
	}

	free(nome); //libera espaços alocados
	free(cpf);


	return(0); 

} 
