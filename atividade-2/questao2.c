#include<stdio.h>
#include<stdlib.h>

void altera1(int **p, int *a) {
	 **p = *a;   // ponteiro p recebe p velor do ponteiro a **p tinha o velor 500 e agora posuu i o valor 700
	 *a = *a +50; // o ponteiro a recebe o valor *a+50, ponteiro *a = 700 entao *a agora é 750  
} 
void altera2(int **p, int *b) { 
	*p = b;  //*p agora aponta para o endereço de memoria de b
 	*b = *b +300; //o ponteiro *b recebe o valor de *b + 300
} 
int main() { 
	 int x,y, *px, *py;

	 px = (int *) malloc(sizeof(int)); //aloca um espaço na memoria 
	 py = (int *) malloc(sizeof(int)); //aloca um espaço na memoria

	 *px = 500; 
	 *py = *px + 200; 
	
	printf("x = %d, End. x = %p, px = %p, y = %d \n",*px,&px, px,*py); 
	altera1(&px, py); 
	
	printf("x = %d, End. x = %p, px = %p, y = %d \n",*px,&px, px,*py); 
	getchar(); 
	
	printf("y = %d, End. y = %p, py = %p, x = %d \n",*py,&py, py,*px); 
	altera2(&py, px); 
	
	printf("y = %d, End. y = %p, py = %p, x = %d \n",*py,&py, py,*px); 
	
	getchar();
	 
	return(0); 

} 
