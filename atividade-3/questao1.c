#include<stdio.h>
#define TAM 6
/*
correção dos erros:

void inter(int V1[TAM], int V2[TAM], int V3[TAM],int i, int j,int q1, int q2,int *q3){ // comentando pontos que foram mudados para o funcionamento do codigo
	 if(i < q1 || j < q2){
		 if(V1[i] < V2[j])
		 	 q3 = inter(V1,V2,V3,i,j+1,q1,q2,q3); // mudança 1 como a funçao inter é do tipo void ela nao deve receber nenhum valor  e para que o codigo funcione corretamente tambem é necessario incrementar o i
		 else if(V1[i] > V2[j])
		 	 inter(V1,V2,V3,i,j+1,q1,q2,&q3); // mudança 2 como q3 é um ponteiro nao é necessario passar o &q3 so precisa ser passado o q3 sem o & e para que o codigo funcione corretamente tambem é necessario incrementar o i
		 else {V3[q3] = V1[j];
		 	 *q3 = q3 + 1;   // mudança 3 como q3 é um ponteiro e a maneira correta de incrementar q3 é *q3 = *q3 + 1
		 	 inter(V1,V2,V3,i+1,j+1,q1,q2,q3);
	  }
	return(q3); //como a funçao é do tipo void ela nao possui retorno
}*/


void inter(int V1[TAM], int V2[TAM], int *V3,int i, int j,int q1, int q2,int *q3){ // função recebe dois vetores edevolve a intersecção dos dois vetores em um terceiro vetor

						//codigo corrigido
	 
	 if(i < q1 || j < q2){                                      
	 	 if(V1[i] < V2[j])											
	 	 	 inter(V1,V2,V3,i+1,j+1,q1,q2,q3); 
	 	 else if(V1[i] > V2[j])
 	 	 	inter(V1,V2,V3,i+1,j+1,q1,q2,q3);   
	 	 else {
 	         V3[*q3] = V1[j]; //mudança3
 	  	     *q3 = *q3 + 1; 
	 	 	 inter(V1,V2,V3,i+1,j+1,q1,q2,q3);
	 	 }
	 }
	 

}

void inter2(int V1[TAM], int V2[TAM], int *V3,int i, int j,int q1, int q2,int *q3){ //codigo em recucividade
	 
	 while(i < q1 || j < q2){         // execulta enquanto o i<q1 ou j<q2                             
	 	 if( (V1[i] < V2[j]) || (V1[i] > V2[j]) ){ //verifica se V1[i] é maior que v2[j] ou se V1[i] é menor que v2[j]											
			i++; //se sim apenas incrementa i e j
		    j++;
		  }else{ //se nao quer dizer que os valores sao iguais
 	         V3[*q3] = V1[j]; // e armazena o valor no vetor V3
 	  	     *q3 = *q3 + 1; //incrementa o q3 que armazenara a quantidade de iten inseridos em V3
	 	 	 i++; //e incrementa I e J
	 	 	 j++;
	 	 }
	 }
	 

}


int main(){
	int V1[TAM]={1,4,7,10},V2[TAM]= {1,3,7,10,11},V3[TAM],i=0,j=0,q1=4,q2=5,q3=0;
	int aux;
	
	//inter(V1,V2,V3,i,j,q1,q2,&q3);
	inter2(V1,V2,V3,i,j,q1,q2,&q3);
	
	if (q3>0){
		printf("interseccao dos vetores: \n");
		for(i=0;i<q3;i++){
			 printf("%d, ",V3[i]);
	 	}

	}else{
		printf("os vetores v1 e v2 nao possuem interseccao.\n ");
	}
	
	printf("\n");
	
	return 0;
}