#include<stdio.h>

void diagonal_principal(int mat[3][5], int loop, int produto1, int linha, int coluna , int ordem ,int *dp){ //percorre os valores da diagonal princípal e retorna 

																										  // na variavel dp o calculo dos valores da diagonal  principal
		if( loop > 0 ){  
					
			if(linha < ordem){
				produto1 *= mat[linha][coluna];

				diagonal_principal(mat,loop,produto1,++linha,++coluna,ordem,dp);
			}else{
					
				(*dp) += produto1;
				coluna -= 2;
				loop--;
				diagonal_principal(mat,loop,1,0,coluna,ordem,dp);
			}
		}
				
}

void diagonal_secundaria(int mat[3][5], int loop, int produto1, int linha, int coluna, int ordem,int *ds){ //percorre os valores da diagonal secundaria e retorna 
																										 // na variavel ds o calculo dos valores da diagonal  secundaria
	if( loop > 0 ){ //percorre enqunto o lopp for maior que 0
					
		if(linha >= 0){ 
			produto1 *= mat[linha][coluna];

			diagonal_secundaria(mat,loop,produto1,--linha,++coluna,ordem,ds);
		}else{		
			(*ds) += produto1;
			coluna -= 2;
			loop--;
			linha = ordem-1;

			diagonal_secundaria(mat,loop,1,linha,coluna,ordem,ds);

		}
	}

}


int main(){
	int ordem,i,j,dp=0,ds=0,determinante;
	int mat[4][5],aux1=0,aux2=0;
	int l=0,c=0;
	
	int mat_aux[3][5];

	while(1){
		printf("digite a ordem da matriz (1 a 4): ");  //le a ordem da matriz
		scanf("%d",&ordem);
		
		if (ordem>4 || ordem<1)
			printf("A ordem da matriz so pode ser de 1 a 4!! \n");
		else
			break;
	}
	if (ordem==1){				  // mostra o calculo da matriz de ordem 1
		scanf("%d",&mat[0][0]);  // se a ordem for 1 , o determinante é o proprio valor lido
		printf("determinante matriz de ordem %d = %d\n",ordem,mat[0][0]);
	}

	if(ordem == 2 ){ // mostra o calculo da matriz de ordem 2
		
		for (i = 0; i < ordem; ++i){      // le a matriz[2][2]
			for (j = 0; j < ordem; ++j){
				scanf("%d",&mat[i][j]);
			}
		}

		
		determinante = ( mat[0][1]* mat[1][0]) - (mat[0][0]*mat[1][1]); // faz o calculo direto do determinante 

		printf("determinante matriz de ordem %d = %d\n",ordem,determinante); // mostra o resultado
	
	}
	if(ordem==3){							// mostra o calculo da matriz de ordem 3
		for (i = 0; i < ordem; ++i){
			for (j = 0; j < ordem; ++j){	// le a matriz[3][3]
				scanf("%d",&mat[i][j]);
			}
		}		
											// converte a matriz[3][3] para matriz[3][5] para que o calculo do detreminante seja feito
		for (i=0; i < ordem; ++i){         // insere os valores da primeira e segunda coluna e passa pra quarta e quinta coluna
			for (j = ordem ; j < 5; ++j){ // para que possa ser feito o calculo da determinante
				mat[i][j]=mat[aux1][aux2];
				aux2++;
			}
			aux1++;
			aux2=0;
		}
														         // diagonal principal retorna em dp = o calculo dos valores da diagonal principal 
		diagonal_principal(mat,ordem,1,0,0,ordem,&dp);          // parametros (matriz,quantidade de linhas=3 ,linha = 0, coluna =0 ,produto=1,ordem = quantidade de linhas=3 , dp = resultado do calculo da diagonal principal)
														       // diagonal secundaria retorna em ds = o calculo dos valores da diagonal secundaria
		diagonal_secundaria(mat,ordem,1,ordem-1,0,ordem,&ds); // parametros (matriz,quantidade de linhas=3 , linha = ordem-1 = 2, coluna =0 ,produto=1,ordem = quantidade de linhas=3 , dp = resultado do calculo da diagonal secundaira)

						 	   //calcula o determinante
		determinante = dp-ds; //resultado do calculo da diagona principal - secundaria

		printf("determinante matriz de ordem %d = %d\n",ordem,determinante);

		
	}
		if (ordem == 4){ //mostra o determinante da matriz de ordem 4
				
				for (i = 0; i < ordem; ++i){   //le a matriz[4][4]
					for (j = 0; j < ordem; ++j){
						scanf("%d",&mat[i][j]);
					}
				}
					
					int num = 4, saida; // Condições de saída para os loops
					int reserva[3][5], pos1, pos2, compara1 = 0, compara2 = 0; // Referente à matriz "reserva"
					int res = 0, calculo = 1, cofator; // Associadas ao resultado final
					int l = 0, c = 0; // Referente à "matriz"
					int lugar1 = 0, lugar2 = 0, i = 1, j = 1; // Referente aos elementos de "matriz"
					
					while( num > 0 ){
						saida = 0;
						pos1 = 0;
						pos2 = 0;
					     
					     // PREENCHE A MATRIZ "RESERVA"
						//  neste caso pegamos a matriz [4][4] e elimamos uma coluna e uma linha 
					   //   tratendo a matriz para que seja feito os calculos cos cofatores da matriz
					  //	para isso gerendo uma matriz reserva 

						for( l = 0; l < ordem; l++ ){
							if( saida == 1 ){
								pos1++;
							}
																
							for( c = 0; c < ordem; c++ ){	
								if( (l != compara1) && (c != compara2) ){
									 reserva[pos1][pos2] = mat[l][c];
									 pos2++;
									 saida = 1;
								}
							}
										
							pos2 = 0;
						}
									
						compara2++;
				
						// EXIBIÇÃO DA MATRIZ "RESERVA"

						aux1=0;
						aux2=0;
															  // transfoma a matriz[3][3] em matriz[3][5] para que seja calculado o determinante da matriz gerada
						for (l=0; l < ordem-1; ++l){         // pega os valores da primeira e segunda coluna e passa pra quarta e quinta coluna
							for (c = ordem-1 ; c < 5; ++c){ // para que possa ser feito o calculo da determinante
								reserva[l][c]=reserva[aux1][aux2];
								aux2++;
							}
							aux1++;
							aux2=0;
						}						 					
						
						num--;
					
					
					// CÁLCULO DO COFATOR DE CADA ELEMENTO
					
				    // Determinante da matriz "RESERVA":
		    		// "reserva" como parâmetro da diagonal_principal (X1)
				    // "reserva" como parâmetro da diagonal_secundária (X2)
				    // Diferença entre os dois resultados (X1 - X2)

					dp = 0;
					ds = 0;

					diagonal_principal(reserva,ordem-1,1,0,0,ordem-1,&dp); // diagonal principal retorna em dp = o calculo dos valores da diagonal principal
		            diagonal_secundaria(reserva,ordem-1,1,ordem-2,0,ordem-1,&ds); // diagonal secundaria retorna em ds = o calculo dos valores da diagonal secundaria

		            determinante = dp-ds; //calcula o determinante da matriz gerada
					
					if( ((i + j) % 2) == 0 ){                // faz o calculo do cofator
						res += mat[i-1][j-1] * determinante; 
					}else{
						 res += mat[i-1][j-1] * (-1 * determinante);
					}
					  
					j++;  
					
				}
				printf("diagonal matriz de ordem %d : %d\n",ordem,res ); //mostra o resultado do determinante da matriz de ordem 4
			}

	return 0;
}