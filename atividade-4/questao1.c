#include <stdio.h>

/*void binario(int nro, int *i,char bin[8]){ // função retorna o i por ponteiro
		
	if (nro < 256){  
		
		if(nro / 2 > 0) {    
			
			binario(nro/2,i,bin);    
			bin[*i] = (nro % 2) + 48;    
			printf("bin[%d] = %c\n",*i,bin[*i]);
			(*i)++;  
		
		}else{
			
			bin[*i] = (nro % 2) + 48;
			printf("bin[%d] = %c\n",*i,bin[*i]);
			(*i)++;      
			
			}
		
		}

}*/

int binario2(int nro, int i,char *bin){ //função retornando o i pela propria função
		
	if (nro < 256){  // testa se o numero é menor que 256, esta função so ira converte os numeros para binarios de até 8 digitos entao a função so podera coverter numeros ate o 255
		
		if(nro / 2 > 0) { //testa se o numero dividido por 2 é maior que 0 se ele for quer dizer que o numero ainda pode ser dividido    
			
			i = binario2(nro/2,i,bin); //faz a chamada recursiva dividindo o numero por dois,como a função agora possui reorno i recebera a função , o i ira indicar quantas vezes o numero foi dividido e quantos digitos o numero em binario terá    
			bin[i] = (nro % 2) + 48;  // a função deixa pendente o calculo do resto e o bin receberá o resto da divisao que é um inteiro entao soma com 48 que representa o valor 0 em caracter
									 // entao se o resto for igaual a 0 ele soma com 48 que sera 0 em caracter e se for 1 soma com 48 que sera 1 em caracter
									// com o calculo esta penente  o bin[i] recebera o resto do numero invertidos em forma de pilha assim fazendo o calculo correto do numro em binario
			printf("bin[%d] = %c\n",i,bin[i]); // imprime o caracter transformado
			i++;  // e incrementa o i
		
		}else{ // se entrar no else quer dizer que chegou na ultima divisao e o numero nao podera mais ser dividido
				// na posição bin[0] ira receber o valor convertido a ultima divisao
			bin[i] = (nro % 2) + 48; // entao ele faz o calculo do resto e 
			printf("bin[%d] = %c\n",i,bin[i]); // e imprime o o resto convertido
			i++;      //incrementa o i

			//depois a função retorna fazendo os calculos que ficaram pendentes
			
			}
		
		}
		return i; // retorna o i que indica quantos valores foram inseridos em bin

}

int main(){
	
	int n, i = 0;
	char bin[9];

	printf("n: "); 
	scanf("%d",&n);

	if(n < 256){
	    i = binario2(n,i,bin); //i recebe quantos valores foram inseridos em bin
	    bin[i+1] = '\0'; // bin na posição i+1 recebe o '\0' para indicar o final da string
	    printf("O número binario e: %s\n",bin);
	 
	 }else  
		printf("O  maior  número  possível  com  8  dígitos  é 255.\n");
	


	return(0);
	
}