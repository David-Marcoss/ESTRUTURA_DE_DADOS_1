#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define TAM 3

typedef struct {

	char palavra[50]; //ESTRUTURA AXILIAR SERVIRA PARA AUXILIAR NA ORDENAÇÃO DA MATRIZ
	
}palavras;

//-------------------------------------------------------------------------------------------------------------------------------------\\

//** FUNÇÕES AUXILIARES DE LEITURA ESCRITA E ETC  **\\

void menu(int *op){  //imprime o menu e devolve uma opção escolhida pelo usuario

	printf("1 - ler matriz \n");
	printf("2 - ordenar matriz\n");
	printf("3 - mostrar matriz antes e depois de ordenar \n");
	printf("4 - verificar quantos digitos e letras maiusculas\n");
	printf("5 - verificar numero de strings que iniciam com consoantes \n");
	printf("6 -  sair\n\n");

	while(*op<1 || *op>6){
		printf("digite a opcao: ");
		scanf("%d",&(*op));

	}

	printf("\n\n");

}
void imprimir_mat(char mr[TAM][TAM][50] ,char mat[TAM][TAM][50],int coluna){  //imprime as colunas das matrizes
	int i,j;																 // mostrando as colunas antes e depois de ordenar

	printf("\nvalores coluna [ %d ] \n",coluna);

	for(i=0;i<TAM;i++){
			printf("%s          %s\n",mat[i][coluna],mr[i][coluna]);
	}	
	
	printf("\n");
	

}

void ler_mat(char mat[TAM][TAM][50]){ //ler os valores da matriz de entrada
	int i,j;

	for(i=0;i<TAM;i++){
		for(j=0;j<TAM;j++){
			scanf("%s",mat[i][j]);

		}
	}

}

//-------------------------------------------------------------------------------------------------------------------------------------\\

//** FUNÇÕES REFERENTES A ORDENAÇÃO DA MATRIZ **\\

void copia(char mat[TAM][TAM][50], palavras *palavras,int coluna,int tipo){
	int i;

	if(tipo == 0){                                          // se tipo for igual a 0 ele copia as strings da coluna matriz que estiverem na posição passada  
		for(i=0;i<TAM;i++){                                // e passa para o vetor de struct palavra
			strcpy(palavras[i].palavra,mat[i][coluna]);
		}
	}else{                                              // se tipo for diferente a 0 ele faz o procedimento inverso 
													   // ele copia as strings do vetor de struct palavra
		for(i=0;i<TAM;i++){							  //  e insere na coluna da matriz passada pela funçâo
			strcpy( mat[i][coluna] , palavras[i].palavra);
		}
	}



}


void minusculo(char *palavra, char *aux){ 		//recebe duas string e faz com que a segunda string receba
	int i;										//recebe a string 1 com seus caracteres em minusculo

	for (i = 0; i < strlen(palavra); ++i){
		aux[i] = tolower(palavra[i]);
	}
	aux[i] = '\0';

}

int compara(char *p1 , char *p2 ){ // compara duas strings pela ordem alfabetica comparando seus caracteres
	int i,tam;	
	char aux1[50],aux2[50]; 

	tam = strlen(p1);

	if (tam<strlen(p2))
		tam = strlen(p2);
	

	minusculo(p1,aux1);  //aux1 recebe p1 com seus caracteres em minusculos
	minusculo(p2,aux2); //aux2 recebe p2 com seus caracteres em minusculos

	for (i = 0; i < tam; ++i){
		
		if(aux1[i]<aux2[i]){  // compara o caracteres das strings 

			return -1;  // se o caracter da srtring 1 vinher antes na ordem na tabela asc retorna -1
		}

		if(aux1[i]>aux2[i]){ 

			return 1; // se o caracter da srtring 2 vinher antes na ordem da tabela asc retorna 1
		}

	}

	return 0; //retorna 0 se as strings forem igauis
}
void quick_sort(palavras *v, int left, int right) { //esta função ira recebere um vetor de struct contendo palavras e ordenalo usando o metodo de ondenção quicksort
    int i, j;
    char x[50], y[50];
     
    i = left; //o i recebe o valor 0 que é a primeira posição do vetor
    j = right; // o i recebe o valor da ultima  posição do vetor
    strcpy(x , v[(left + right) / 2].palavra);  // x recebe um valor inicial que neste codigo sera o valor que estiver no meio do vetor recebido e atraves desse valor
     							// posicionar todos elementos menores do que ele à sua esquerda.

    while(i <= j) { //ira percorrer todas o vetor enquanto o i for menor ou igual a J
        
        while( compara(v[i].palavra,x) < 0 && i < right) {   // afunção compara ira retornar -1 se a palavra v[i].palavar for menor que a palavra x.
        													// enquanto o vetor da poisição i nao for menor que x este while ira percorer os valores da direita
            i++; // e incrementar o i
        }
        while(compara(v[j].palavra , x) > 0 && j > left) {   // afunção compara ira retornar 1 se a palavra v[i].palavar for maior que a palavra x.
        													// enquanto o vetor da poisição j nao for maior que x este while ira percorer os valores da esquerda
            j--; // e decrementar o j
        }
        if(i <= j) {                                // se entrar nessa condição quer dizer que o i é menor ou igual a j ou que o v[i] é menor que x ou entao o v[j] é maior que X
            strcpy(y , v[i].palavra);              //entao o y recebera o valor de V[i]
            strcpy(v[i].palavra , v[j].palavra);  //entao o v[i] recebera o valor de V[j]
            strcpy(v[j].palavra , y);            //entao o v[j] recebera o valor de y
            i++;                                //incrementa o i
            j--;	                           // e decrementa o j
        }
    } // entao quer dizer que ele ja ordenou uma parte do vetor , mas o vetor ainda pode nao esta completamente ordenado
     
    if(j > left) { 				 		 //entao ele verifica se o j > left
        quick_sort(v, left, j); 		//faz a chamada recursiva e continuara ordenando os itens a esquerda
    }
    if(i < right) { 				   // e se o i< rigth
        quick_sort(v, i, right);      //faz a chamada recursiva e continuara ordenando os itens a direita
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------\\

//** FUNÇÕES PARA SOLUÇÃO DA OPÇÃO 4 **\\

int digitos(char *p1, int *dig,int *mai){ //devolve por parametro quantidade de digitos e letras maiusculas 
	int i;								 //de uma string 

	for (i = 0; i < strlen(p1); ++i){
		if (isdigit(p1[i]))
			(*dig)++;   			  // dig recebe quantidade de digitos da string
		if(p1[i]>=65 && p1[i]<=90)
			(*mai)++;   			// mai recebe quantidade de letras miusculas da string
	}

}
//-------------------------------------------------------------------------------------------------------------------------------------\\

//** FUNÇÕES PARA SOLUÇÃO DA OPÇÃO 5 **\\

int consoantes(char l){  //recebe um caracter e devolve 1 se ele for consoante
	int i;				//e devolve 0 se ele nao for consoante
	char c[] = "aeiou" ;

	for (i = 0; i < strlen(c); ++i){

		if ( (tolower(l) == c[i] ) || (  tolower(l) <96 || tolower(l) > 122 ) ){
			return 0;
		}
	}

	return 1;

}
void quant_consoantes(char mat[TAM][TAM][50]){  //esta função mostra a quantidade de letras que iniciam com consoantes  das strings
	int i,coluna,cont=0;                       // na coluna passada pelo usuario             
	

	printf("escolha a  coluna (0,%d ): ",TAM-1); //ler a coluna
	scanf("%d",&coluna);

	if ( coluna<0 || coluna>TAM-1 ){
		printf("\nvalores invalidos !!\n\n");
	
	}else{
		for (i = 0; i < TAM; ++i){                //percorre a coluna e chama função consoantes
			cont+=consoantes(mat[i][coluna][0]); //consoantes retorna 1 se for consoante e 0 se nao 
											    // cont a quntidade de  letras que iniciam com consoantes  das strings			
		}
		printf("\nquantidade de de strings que iniciam com consoantes na coluna[%d] : %d\n\n",coluna,cont);	 // mostra a saida pro usuario
	}

}

//-------------------------------------------------------------------------------------------------------------------------------------\\


int main(){
	int op,i,j,flag=0,dig=0,mai=0;
	char mat[TAM][TAM][50];
	char mat_resultante [TAM][TAM][50]; // recebe os valores da matriz de entrada ordenada


	/* matriz ja preenchida para teste
	   pros testes funcionarem com esta matriz a variavel flag=1
	
	char mat[TAM][TAM][50]={ { {"bola"},{"Carro"},{"13"},{"2-eduardo"} },{ {"Arvore"},{"Geladeira"},{"130"},{"3-Carlos"} }, { {"CAbra"},{"Vaca"},{"0"},{"1-Marcos"} },{ {"Bicicleta"},{"MOto"},{"12"},{"4-joao"} } };
	
	*/
	palavras palavras[TAM]; //armazena os valores de uma coluna da matriz de entrada


	while(op!=6){

		op = 0;
		menu(&op);

		switch (op){
			case 1:
				ler_mat(mat); // ler a matriz
				printf("\n");
				flag++;

				break;

			case 2:

				if (flag==0){
					printf("\nA matriz está vazia !! Nao e possivel ordenar valores na matriz!\n");
					printf("Escolha a opção 1, para inserir valores \n\n");

					break;										 // se a matriz ja estive preenchida
					
				}
				for(j=0;j<TAM;j++){                           //perrcorre as colunas da matriz
					
					copia(mat,palavras,j,0);                //copia as strings da coluna j da matriz e armazena as palavras no vetor de struct palavra
					quick_sort(palavras,0,TAM-1);          //ordena o vetor de struc pela ordem alfabetica

					copia(mat_resultante,palavras,j,1);  //depos reincere os valores da estruct palavras na coluna da matiz
														// neste caso o codigo insere os valores da matriz de entrada ordenada numa matriz resultante
				}
				printf("Matriz Ordenada.\n\n");

				flag++;
				
				break;

			case 3:

				if (flag ==0 ){
					printf("\nA matriz está vazia !! Nao e possivel acessar esta opcao !\n");
					printf("Escolha a opção 1, para inserir valores  \n\n");

					break;	
				}

				if (flag == 1 ){
					printf("\nA matriz Nao esta ordenada!\n");
					printf("Escolha a opção 2, para ordenar matriz \n\n");

					break;	
				}
				printf("Antes e depois Ordenar colunas: \n");

				for(j=0;j<TAM;j++){                      //se a matriz de entrada ja estiver preenchida e ordenada
					
					imprimir_mat(mat_resultante,mat,j); // ele imprime as colunas da matriz antes e depois da ordenação
	
				}


				break;

			case 4:

				if (flag==0){                       //se a matriz de entrada ja estiver preenchida
					
					printf("\nA matriz está vazia !! Nao e possivel ordenar valores na matriz!\n");
					printf("Escolha a opção 1, para inserir valores \n\n");
					break;
				}

										 	 // esta opção ira mostrar a quantdade de digitos e letras maiusculas
											//  de uma determinada linha e coluna

			    printf("escolha a  linha (0,%d ): ",TAM-1);  //ler a linha 
				scanf("%d",&i);
				printf("escolha a  coluna (0,%d ): ",TAM-1); //ler a coluna
				scanf("%d",&j);

				if ( (i<0 || i>TAM-1) || (j<0 || j>TAM-1) ){
					printf("\nvalores invalidos !!\n\n");
				
				}else{
				           
					digitos(mat[i][j],&dig,&mai);     //digitos retorna na variavel dig= quantidade de digitos da string
														// e na variavel mai quantidade de letras maiusculas			
				}
					printf("\nquantidade de digitos da palavras[%d][%d] %s : %d \n",i,j,mat[i][j],dig); //mostra o resultado para o usuario
					printf("quantidade de letras maiusculas: %d \n\n",mai);
				
				break;

			case 5:

				if (flag==0){                       //se a matriz de entrada ja estiver preenchida
					
					printf("\nA matriz está vazia !! Nao e possivel ordenar valores na matriz!\n");
					printf("Escolha a opção 1, para inserir valores \n\n");
					break;
				}

				quant_consoantes(mat); // mostra a quantidade de strings que iniciam com consoantes em uma coluna



				
				break;

			case 6:
				printf("Saindo..........\n");

				break;
		}
	}



	return 0;
}