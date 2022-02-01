#include <stdio.h>
#include <string.h>
#include <ctype.h>


typedef struct {
	int matricula;
	char nome[50];
	char curso[50];
	int periodo;
}dados;

void ler(dados *alunos,int i,int tam){ // ler valores i insere no vetor
	
	if(i<tam){
		printf("matricula: ");
		scanf("%d",&alunos[i].matricula);
		printf("nome: ");
		scanf("%s",alunos[i].nome);
		alunos[i].nome[0] = tolower(alunos[i].nome[0]);
		printf("curso: ");
		scanf("%s",alunos[i].curso);
		printf("periodo: ");
		scanf("%d",&alunos[i].periodo);
		ler(alunos,++i,tam);
	}
		
}
/*void funcao_A(dados *alunos,int i,int tam,int periodo,char *vet[20][50],int *tam2){
	
	if(i<tam){
		if(alunos[i].periodo == periodo){
			strcpy(vet[*tam2],alunos[i].nome);
			(*tam2)++;
		}
		funcao_A(alunos,++i,tam,periodo,vet,tam2);
	}	
}*/

void ordena(dados *alunos,int tam,int i,int j,int aux,char *aux1,char *aux2,int aux3){ // esta função ira ordenar o vetor pelo metodo da insercão esta função recebe como entrada
												  // um vetor , a quantidade de itens do vetor , variavei i e j que ira ajudar a percorrer o vetor e aux para auxilia as trocas de posiçoes				
   if(i <= tam-1){ // i ininia com o valor 1 e percorre ate o final do vetor
      
      aux = alunos[i].matricula;
      strcpy(aux1,alunos[i].nome);
      strcpy(aux2,alunos[i].curso);
      aux3= alunos[i].periodo; 
		// a variavel aux recebe o valor do segundo item do vetor  na primeira execulção 
      
      j = i - 1; // j recebe i - 1 que na primeira execulçao sera 0
      
      if(j >= 0 && aux < alunos[j].matricula) { // testa se j>=0 e o valor que estiver em aux for menor que o valor que estiver no vetor na poisição j
        
         alunos[j+1].matricula = alunos[j].matricula;
         strcpy(alunos[j+1].nome , alunos[j].nome);
         strcpy(alunos[j+1].curso , alunos[j].curso);
         alunos[j+1].periodo = alunos[j].periodo; // ele faz com que o valor que estiver na posiçao j+1 do vetor ou seja a posiçao que estiver afrente receba o valor do vetor na posição j 
        
         ordena(alunos,tam,i,--j,aux,aux1,aux2,aux3); // faz a chamada recursiva decrementando o j, esta chamada recusiva percorre o vetor para trás empurrando o número para o início do vetor
 	 	 	 	 	 			   // substituindo o laço while
	  }
      	 alunos[j+1].matricula = aux;
         strcpy(alunos[j+1].nome , aux1);
         strcpy(alunos[j+1].curso , aux2);
         alunos[j+1].periodo = aux3; // vet na posição j+1 vai receber o valor armazenado por aux
       
       ordena(alunos,tam,++i,j,aux,aux1,aux2,aux3); // faz a chamada recusiva incrementando o i, esta chamada recursiva substitui o laço for
   }
	
}
void funcao_B(dados *alunos,char *curso, int *num, int i, int tam){

	if (i<tam){
		if ( strcmp(alunos[i].curso,curso)== 0 ){
			(*num)++;
		}
		funcao_B(alunos,curso,num,++i,tam);
	}

}

int main(){
	int i,j,tam2=0,aux,aux3,periodo,num=0;
	char aux1[50],aux2[50],curso[50];
	char nomes[20][50];
	dados alunos[6]={{2,"David","sistemas",4},{1,"carlos","historia",8},{5,"caio","sistemas",4},{5,"cleito","medicina",1},{3,"maria","medicina",1},{4,"carla","direito",4}};
	
	//ler(alunos,0,2);
	//scanf("%d",&periodo);
	scanf("%s",curso);
	
	//funcao_A(alunos,0,6,periodo,nomes,&tam2);
	ordena(alunos,6,1,j,aux,aux1,aux2,aux3);
	
	funcao_B(alunos,curso,&num,0,6);
	
	for(i=0;i<6;i++){
		printf("%d %s %s %d \n",alunos[i].matricula,alunos[i].nome,alunos[i].curso,alunos[i].periodo);
		
	}
	printf("\nquantidade de alunos de %s = %d\n",curso,num);
	
	
	
	return 0;
}