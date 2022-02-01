#include<stdio.h>
#define TAM 5


void ler(int *vet,int i){ // ler valores i insere no vetor
	
	if(i<TAM){
		scanf("%d",&vet[i]);
		ler(vet,++i);
	}
	
	
}

void ordena(int *vet,int tam,int i,int j,int aux){ // esta função ira ordenar o vetor pelo metodo da insercão esta função recebe como entrada
												  // um vetor , a quantidade de itens do vetor , variavei i e j que ira ajudar a percorrer o vetor e aux para auxilia as trocas de posiçoes				
   if(i <= tam-1){ // i ininia com o valor 1 e percorre ate o final do vetor
      aux = vet[i]; // a variavel aux recebe o valor do segundo item do vetor  na primeira execulção 
      j = i - 1; // j recebe i - 1 que na primeira execulçao sera 0
      if(j >= 0 && aux < vet[j]) { // testa se j>=0 e o valor que estiver em aux for menor que o valor que estiver no vetor na poisição j
         vet[j+1] = vet[j]; // ele faz com que o valor que estiver na posiçao j+1 do vetor ou seja a posiçao que estiver afrente receba o valor do vetor na posição j 
         ordena(vet,tam,i,--j,aux); // faz a chamada recursiva decrementando o j, esta chamada recusiva percorre o vetor para trás empurrando o número para o início do vetor
 	 	 	 	 	 			   // substituindo o laço while
	  }
      vet[j+1] = aux; // vet na posição j+1 vai receber o valor armazenado por aux
      ordena(vet,tam,++i,j,aux); // faz a chamada recusiva incrementando o i, esta chamada recursiva substitui o laço for
   }
	
}

void insere(int *vet1,int *vet2,int *vet3,int i,int j,int aux,int *tam){ //insere valores do vetor 1 e 2 no vetor 3
	int cont=0;
	
	if(i<TAM*2){	//testa se i é menor que TAM * 2 que é o tamanho do vetor 1 * vetor 2 
		if(i<5){   // enquanto o i menor que 5 o codigo ira inserir itens do vetor 1 no vetor 3
			while(i>0 && aux<i){ 
				   if(vet1[i] == vet3[aux]){ // este while serve para verificar se o valor do vetor 2 ja foi inserido no vetor 3
				   		cont = 1;   		// se o valor ja foi inserido ele da o cont=1 e para o ciclo
						break;
				   }
				aux++; 
			}
			if(cont == 0){ //se o cont for 0 quer dizer que o valor de vet1 ainda nao foi inserido en vet 3 
				vet3[*tam] = vet1[i]; //entao ele insere o valor
				(*tam)++;	//a variavel tam recebida por parametro ira receber a quantidade de iten inseridos em tam
			}
		}else{
			// quando entra no else quer dizer o i maior que 5 o codigo ira inserir itens do vetor 2 no vetor 3
			aux=0;
			cont=0;
			while(aux<i){ 
				   if(vet2[j] == vet3[aux]){
				   		cont = 1;        //verifica se o valor do vetor 2 ja foi inserido no vetor 3 se sim ele nao insere o valor
						break;
				   }
				aux++;
			}
			if(cont == 0){
				vet3[*tam] = vet2[j]; // se o valor d0 o vetor 2 ainda nao foi inserido no vetor 3 ele  insere o valor
				(*tam)++;	
			}
			j++;
		}
		insere(vet1,vet2,vet3,++i,j,0,tam); // faz a chamada recursiva incrementando o i 
	}
	
	
}


int main(){
	int vet1[TAM],vet2[TAM],i,j,aux;
	int vet3[TAM*2],tam=0;
	
	ler(vet1,0); //ler os valores do vetor 1
	ler(vet2,0);//ler os valores do vetor 2
	
	ordena(vet1,TAM,1,j,aux); //ordena valores do vetor 1
	ordena(vet2,TAM,1,j,aux);//ordena valores do vetor 2
	
	insere(vet1,vet2,vet3,0,0,0,&tam); //insere valores do vetor 1 e 2 no vetor 3
	
	ordena(vet3,tam,1,j,aux); // ordena valores do vetor 3
	
	printf("\n");
	for(i=0;i<tam;i++){
		printf("%d\n",vet3[i]);
	}
	
	
	return 0;
}