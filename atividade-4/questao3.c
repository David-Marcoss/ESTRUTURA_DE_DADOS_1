#include<stdio.h>

void testa_repeticoes(int n ,int *vet1,int *tam){ // esta função ira verificar se um valor ja foi inserido no vetor se sim ele nao ira inserir o valor e se nao ele insere o valor no vetor
	int aux=0,cont=0;

	while(aux < (*tam)){ 
			if(n == vet1[aux]){ // este while percorre o vetor e verifica se o valor n ja foi inserido no vetor
				   	cont = 1;   		// se o valor ja foi inserido ele da o cont=1 e para o ciclo
					break;
			}
				aux++; 
			}
			
	if(cont == 0){ //se o cont for 0 quer dizer que o valor de n ainda nao foi inserido en vet  
		vet1[*tam] = n; //entao ele insere o valor
		(*tam)++;	//a variavel tam recebida por parametro ira receber a quantidade de iten inseridos em tam
	}
}

void ler(int *v, int *i){  // a funçã ler valores e insere no vetor e devolve o tamanho do mesmo
	int n;
	printf("digite -1 quando nao quiser inserir mais valores\n"); // se o usuario nao quiser preencher todas as posiçoes ele pode digitar -1 para parar de inserir valores  
	
	while(*i<5){
		printf("digite um numero: ");
		scanf("%d",&n);
		
		if(n>-1)
			v[*i] = n;
		else
			break;
		
		(*i)++;

	}

}
void quick_sort(int *v, int left, int right) { //esta função ira recebere um vetor e ordenalo usando o metodo de ondenção quicksort
    int i, j, x, y;
     
    i = left; //o i recebe o valor 0 que é a primeira posição do vetor
    j = right; // o i recebe o valor da ultima  posição do vetor
    x = v[(left + right) / 2];  // x recebe um valor inicial que neste codigo sera o valor que estiver no meio do vetor recebido e atraves desse valor
     							// posicionar todos elementos menores do que ele à sua esquerda.
    while(i <= j) { //ira percorrer todas o vetor enquanto o i for menor ou igual a J
        while((v[i]) < x && i < right) { // // enquanto o vetor da poisição i nao for menor que x este while ira percorer os valores da direita
            i++; // e incrementar o i
        }
        while(v[j] > x && j > left) {// enquanto o vetor da poisição j nao for maior que x este while ira percorer os valores da esquerda
            j--; // e decrementar o j
        }
        if(i <= j) { // se entrar nessa condição quer dizer que o i é menor ou igual a j ou que o v[i] é menor que x ou entao o v[j] é maior que X
            y = v[i];     //entao o y recebera o valor de V[i]
            v[i] = v[j]; //entao o v[i] recebera o valor de V[j]
            v[j] = y;   //entao o v[j] recebera o valor de y
            i++;       //incrementa o i
            j--;	  // e decrementa o j
        }
    } // entao quer dizer que ele ja ordenou uma parte do vetor , mas o vetor ainda pode nao esta completamente ordenado
     
    if(j > left) { //entao ele verifica se o j > left
        quick_sort(v, left, j); //faz a chamada recursiva e continuara ordenando os itens a esquerda
    }
    if(i < right) { // e se o i< rigth
        quick_sort(v, i, right); //faz a chamada recursiva e continuara ordenando os itens a direita
    }
}


void interseccao(int *v1,int *v2,int *v3,int i, int j,int tam,int tam2,int *tam3){ // esta função ira receber dois vetores contendo valore inteiros e ira devolver num 
																				  // terseiro vetor os valores da intersecção dos vetores
	
	if (i<tam){ //verifica se i é meno que tam , tam é a quantidade de valores inseridos no vetor 1
		if (j<tam2){ //verifica se j é meno que tam2 , tam 2é a quantidade de valores inseridos no vetor 2
					// o codigo ira testar se possui valores iguais nos vetores para isso ele pega um valor v1[i] e apartir de se valor verifica se tem um valor igual no v2[j]
			if (v1[i]==v2[j]){ //e ira comparar
				testa_repeticoes(v2[j],v3,tam3); //se encontrar valores iguais chama esta função e adiciona o valor no v3 se o valor nao ja tiver sido inserido
			}
			interseccao(v1,v2,v3,i,1+j,tam,tam2,tam3); // faz a chamada recursiva incrementando j para percorrer o v2
		}else{
			interseccao(v1,v2,v3,++i,0,tam,tam2,tam3);// faz a chamada recursiva incrementando i para percorrer o v1
		}
	}
}

int main(){
	int v1[5],v2[5],v3[10];
	int tam=0,tam2=0,tam3=0;

	ler(v1,&tam); //ler vetor 1
	ler(v2,&tam2);// ler vetor 2

	quick_sort(v1,0,tam-1);// ordena vetor 1
	quick_sort(v2,0,tam2-1);// ordena vetor 2


	interseccao(v1,v2,v3,0,0,tam,tam2,&tam3); //devolse um vetor con a intersecção de v1 e v2

	if (tam3>0){
		printf("\ninterseccao dos vetores v1 e v2: ");
		for (int i = 0; i < tam3; ++i){
			printf("%d, ",v3[i]);
		}
	}else{
		printf("os vetores v1 e v2 nao possuem interseccao.\n ");
	}
	printf("\n");

}