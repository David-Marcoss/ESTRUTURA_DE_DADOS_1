#include<stdio.h>
#include<string.h>

#define T 5
#define N 25

typedef struct{  // ESTRURURA CURSO
	int codigo;
	char nome[N];
	int periodo;
	int carga_horaria;
	char turno[20];
	int dic;        //dic for 1 quer dizer que o curso possui diciplinas cadrastadas	
}curso;

typedef struct{ //ESTRUTRURA DISCIPLINA

	int codigo;
	int codigo_curso;
	char nome[N];
	int periodo;
	int carga_horaria; // Múltiplo de 15	

}disciplina;

void traco(){
	printf("\n--------------------------------------------------------------------\n\n");
}

void menu();
/* funçoes relacionadas ao curso */

void copia(curso *x, curso *v);                                  // copia dados de um curso e guarda numa estrutura auxiar 
void cadastrar_curso(curso *p , int *quant_cursos);  			//cadrasta um curso
void imprimir_curso(curso *p , int *quant_cursos); 		 	   //imprime um curso
void quick_sort1(curso *v, int left, int right);			  //ordena o vetor curso
int busca_cod(curso *vetor, int inicio, int fim, int cod, int *flag); //// dado um codigo verifica se um existe

/*funções relacionadas a disciplina	*/

void cadastrar_disciplina(disciplina *dic, int *quant_dic,curso *curso, int quant_cursos);              //cadrasta disciplina
int busca_dic(disciplina *vetor, int inicio, int fim, int cod, int *flag);							   // busca uma disciplina
void imprimir_disciplina(disciplina *dic , int *quant_dic);											  // imprime uma disciplina
void copia2(disciplina *x, disciplina *v); 															 // copia os dados de uma disciplina para uma etrutura auxiliar
void quick_sort2(disciplina *v, int left, int right);												// ordena vetor disciplina
void imprimir_disciplina_curso(disciplina *dic, int quant_dic,curso *curso, int quant_cursos);	   // imprime disciplinas cadrastada num curso
void imprimir_turno(curso *curso, int quant_cursos);                                              // imprime cursos de um turno
void imprimir_disciplina_periodo(disciplina *dic, int quant_dic,curso *curso, int quant_cursos); //remove uma disciplina
void remover_dic(disciplina *dic,int *quant_dic,curso *curso, int quant_cursos);				//remove um curso
void remover_curso(curso *curso,int *quant_cursos);



int main(){
	
	int quant_cursos=0 ; //servira para dizer quantos cursos foram cadrastados
	int quant_dic=0 ; //servira para dizer quantos disciplinas foram cadrastados
	int op=1;

	curso cursos[T];

	disciplina disciplinas[T];

	int saida = -1;

	menu();
	
	while(op!=10){

		printf("\nDigite 0 para ver o Menu.\n");
		printf("\nDigite a opcao: ");
		scanf("%d",&op);
		
		switch (op){

			case 0:
				menu();
				
				break;
		
			case 1:
				cadastrar_curso(cursos,&quant_cursos); //insere um curso

				if (quant_cursos>1){                           // se quant_curso for maior que 1
									                          // quer dizer que tem mais de um curso ja cadrastado
					quick_sort1(cursos, 0, quant_cursos-1);	 // entao apartir dai entao a cada inserção de um novo curso 
															// o vetor vai ser ordenado
				}
				
				break;
			
			case 2:
				
				if (quant_cursos == 0){
					traco();
					printf("Nao a cursos cadrastados!!Nao será possivel inserir disciplina!!\n");
					traco();
				
				}else{

					cadastrar_disciplina(disciplinas,&quant_dic,cursos,quant_cursos); //insere um curso

					if (quant_dic>1){                               // se quant_dic for maior que 1
										                           // quer dizer que tem mais de uma diciplina ja cadrastado
						quick_sort2(disciplinas, 0, quant_dic-1); // entao apartir dai entao a cada inserção de uma nova disciplina 
																 // o vetor vai ser ordenado
					}
				}

				break;
			
			case 3:
				
				if (quant_cursos == 0){
					traco();
					printf("Nao a cursos cadrastados!!Nao será possivel imprimir curso !!\n");
					traco();
				
				}else{

					imprimir_curso(cursos,&quant_cursos);
				}
				
				break;

			case 4:

				if (quant_cursos == 0 || quant_dic == 0){
					traco();
					printf("Nao será possivel imprimir disciplina !!\n");
					printf("verifique se ha curso e disciplinas cadrastadas \n");
					traco();
				
				}else{

					imprimir_disciplina(disciplinas,&quant_dic);
				}
				
				break;
			
			case 5:
				
				if (quant_cursos == 0){
					traco();
					printf("Nao a cursos cadrastados!!Nao será possivel realizar esta operacao!!\n");
					traco();
				
				}else{
					traco();
					imprimir_turno(cursos,quant_cursos);
					traco();
				}
				
				
				break;
			
			case 6:
				
				if (quant_cursos == 0 || quant_dic == 0){
					traco();
					printf("Nao será possivel realizar esta operacao!!\n");
					printf("verifique se ha curso e disciplinas cadrastadas \n");
					traco();
				
				}else{

					imprimir_disciplina_curso(disciplinas,quant_dic,cursos,quant_cursos);
				}
				
				break;

			case 7:
				if (quant_cursos == 0 || quant_dic == 0){
					traco();
					printf("Nao será possivel realizar esta operacao !!\n");
					printf("verifique se ha curso e disciplinas cadrastadas \n");
					traco();
				
				}else{
				
					imprimir_disciplina_periodo(disciplinas,quant_dic,cursos,quant_cursos);
				}

				
				break;

			case 8:

				if (quant_cursos == 0 || quant_dic == 0){
					traco();
					printf("Nao será possivel realizar esta operacao !!\n");
					printf("verifique se ha curso e disciplinas cadrastadas \n");
					traco();
				
				}else{


					remover_dic(disciplinas,&quant_dic,cursos,quant_cursos);//remove uma disciplina
					
					if (quant_dic>1){  // e depois reordena o vetor                             
																	// se quant_dic for maior que 1
										                           // quer dizer que tem mais de uma diciplina ja cadrastado
						quick_sort2(disciplinas, 0, quant_dic-1); // entao apartir dai entao a cada inserção de uma nova disciplina 
																 // o vetor vai ser ordenado
					}
				}
				
				break;	

			case 9:
				if (quant_cursos == 0){
					traco();
					printf("Nao será possivel realizar esta operacao !!\n");
					printf("verifique se ha curso cadrastados \n");
					traco();
				
				}else{
					remover_curso(cursos,&quant_cursos);

					if (quant_cursos>1){                           // se quant_curso for maior que 1
										                          // quer dizer que tem mais de um curso ja cadrastado
						quick_sort1(cursos, 0, quant_cursos-1);	 // entao apartir dai entao a cada curso removido 
																// o vetor vai ser ordenado
					}
				}

				
				break;	

			case 10:

				traco();
				printf("saindo...\n");
				traco();
				
				break;
			
			default:
				traco();
				printf("opcao invalida!!digite 0 para ver o menu!!\n\n");
				traco();

				break;
		}	  
	
	}
	
	
	return 0;
}

void menu(){
	
	traco();
	printf("1 - cadastrar curso\n");
	printf("2 - cadastrar disciplina\n");
	printf("3 - Imprimir curso\n");
	printf("4 - Imprimir disciplinas\n");
	printf("5 - Imprimir cursos de um turno\n");
	printf("6 - Imprimir disciplinas de um curso \n");
	printf("7 - Imprimir disciplinas de um periodo do curso\n");
	printf("8 - remover disciplina\n");
	printf("9 - remover curso\n");
	printf("10 - Finalizar\n");
	traco();

}
/*------------------------------------------------------------------------------------------*/
// funções relacionadas ao curso
void cadastrar_curso(curso *p , int *quant_cursos){ //parametros cadrastar_curso(vetor contendo os cursos, numeros de cursos inseridos no vetor)
	
	int codigo, tam = *quant_cursos,flag=0;

	traco();
	printf("Preencha os dados para cadastrar o curso:\n\n");
	traco();

	//printf("Codigo do curso: ");
	scanf("%d",&codigo);

	if ( (busca_cod(p , 0, tam , codigo ,&flag) == 1) && (tam > 0) ){
		printf("\nEste codigo ja foi cadrastado !!\n");
		traco();
		
	}else{

		p[tam].codigo = codigo;


		printf("Nome do curso: ");
		scanf("%s",p[tam].nome);

		printf("Quantidade de periodos: ");
		scanf("%d",&p[tam].periodo );

		printf("Carga horaria do curso: ");
		scanf("%d",&p[tam].carga_horaria);

		printf("Turno do curso: ");
		scanf("%s",p[tam].turno);

		(*quant_cursos)++; //quntidade de cursos inseridos
		p[tam].dic = 0;  //se curso.dic for = 0 quer dizer que nao possui disciplinas cadrastadas

		traco();
		printf("\nCurso cadrastada com sucesso!\n");	
		traco();

	}


	
}
void imprimir_curso(curso *p , int *quant_cursos){ //parametros cadrastar_curso(vetor contendo os cursos, numeros de cursos inseridos no vetor)
	int codigo;
	int flag=1;

	printf("Codigo do curso: ");
	scanf("%d",&codigo);

	flag = busca_cod(p , 0, *quant_cursos, codigo,&flag);

	if (flag==0){
		traco();
		printf("\nCodigo invalido!! curso nao encontrado\n");
		traco();
	}

	
}

void copia(curso *x, curso *v){ 	 //  x e v sao estruturas simples do tipo curso e nao sao vetores
									//copia(estrutura x que ira receber dados da estrutura  v) 

	x->codigo = v->codigo;
	
	strcpy(x->nome,v->nome);
	
	x->periodo = v->periodo;
	
	x->carga_horaria = v->carga_horaria;
	
	strcpy(  x->turno,  v->turno);

	x->dic = v->dic;

}

void quick_sort1(curso *v, int left, int right){ //esta função ira recebere um vetor de struct contendo cursos e ordenalo usando o metodo de ondenção quicksort
    int i, j;
    curso x;
    curso y;
     
    i = left; //o i recebe o valor 0 que é a primeira posição do vetor
    j = right; // o i recebe o valor da ultima  posição do vetor
    
    copia(&x , &v[(left + right) / 2]);  // x recebe um valor inicial que neste codigo sera o valor que estiver no meio do vetor recebido e atraves desse valor
     							// posicionar todos elementos menores do que ele à sua esquerda.

    while(i <= j) { //ira percorrer todas o vetor enquanto o i for menor ou igual a J
        
        while(v[i].codigo < x.codigo && i < right) {   // afunção compara ira retornar -1 se a palavra v[i].palavar for menor que a palavra x.
        													// enquanto o vetor da poisição i nao for menor que x este while ira percorer os valores da direita
            i++; // e incrementar o i
        }
        while(v[j].codigo  > x.codigo && j > left) {   // afunção compara ira retornar 1 se a palavra v[i].palavar for maior que a palavra x.
        													// enquanto o vetor da poisição j nao for maior que x este while ira percorer os valores da esquerda
            j--; // e decrementar o j
        }
        if(i <= j) {                                // se entrar nessa condição quer dizer que o i é menor ou igual a j ou que o v[i] é menor que x ou entao o v[j] é maior que X
            copia(&y , &v[i]);              //entao o y recebera o valor de V[i]
            copia(&v[i] , &v[j]);  //entao o v[i] recebera o valor de V[j]
            copia(&v[j], &y);            //entao o v[j] recebera o valor de y
            i++;                                //incrementa o i
            j--;	                           // e decrementa o j
        }
    } // entao quer dizer que ele ja ordenou uma parte do vetor , mas o vetor ainda pode nao esta completamente ordenado
     
    if(j > left) { 				 		 //entao ele verifica se o j > left
        quick_sort1(v, left, j); 		//faz a chamada recursiva e continuara ordenando os itens a esquerda
    }
    if(i < right) { 				   // e se o i< rigth
        quick_sort1(v, i, right);      //faz a chamada recursiva e continuara ordenando os itens a direita
    }
}

int busca_cod(curso *vetor, int inicio, int fim, int cod, int *flag){ // busca_cod(vetor de estrutura, inicio do vetor=0 , fim do vetor = quant_curso , e o cod para busca)
    
    /* Índice representando o meio do sub-vetor begin->end */
    int i = (fim + inicio) / 2;

    if (inicio > fim){  /* Ponto de parada. Item não está no vetor */

    	if (*flag<0){
			printf("\nCodigo nao encontrado!!Este curso nao existe\n");
			traco();
			
		}
        
        return 0;      // retorna 1 se nao encontrar codigo
    }

    if (vetor[i].codigo == cod) {  /* Item encontrado */                                             //flag = 0 a função retorna 0 se o codigo nao existir e 1 se encontrar o codigo
        
        if (*flag == 1){
        																							//flag = 1 a função imprime os dados do curso se o curso existir
        	traco();

	        printf("Codigo do curso: %d \n",vetor[i].codigo);										// flag < 0 a função função retorna 0 se o codigo nao existir e imprime uma mensagem

			printf("Nome do curso: %s \n",vetor[i].nome);										   //	e se o codigo existir flag devolve o indice do curso						

			printf("Quantidade de periodos: %d\n",vetor[i].periodo);

			printf("Carga horaria do curso: %d \n",vetor[i].carga_horaria);

			printf("Turno do curso: %s \n", vetor[i].turno);

			traco();
        	
        }
        if(*flag<0){

        	*flag = i;
        }



        return 1;				// retorna 1 se  encontrar codigo
    }

    if (vetor[i].codigo < cod) {  /* Item está no sub-vetor à direita */
        return busca_cod(vetor, i + 1, fim, cod,flag);


    } else {  /* vector[i] > item. Item está no sub-vetor à esquerda */
        return busca_cod(vetor, inicio, i - 1, cod,flag);
    }

}
/*------------------------------------------------------------------------------------------*/

void cadastrar_disciplina(disciplina *dic, int *quant_dic,curso *curso, int quant_cursos){ //  parametros(vetor diciplina,qunatidade de diciplinas cadrastadas, vetor curso, qunatidade de cursos cadrastadas)
	int flag=-1;
	int flag2 = 0;
	int aux;
	int cod_curso,cod_dic,tam = *quant_dic;

	traco();
	printf("\nPreencha os dados para cadastrar a disciplina:\n");
	traco;    

	printf("digite o codigo do curso: ");
	scanf("%d",&cod_curso);

	aux = busca_cod(curso,0,quant_cursos,cod_curso,&flag); //retorna se o curso existe e se existir retorna em flag o indice do curso
												  // busca_cod retorna 1 se o codigo do curso ja foi inserido
												 // e retorna 0 se o codigo nao existir
												// se o valor de flag for menor que 1 flag recebe a indice do curso
	if (*quant_dic == 0){
		curso[flag].dic = 0;
	}

	if (aux==1){
		
		dic[tam].codigo_curso = cod_curso;

		traco();
        printf("\nDisciplina sera cadrastada no curso : %s \n",curso[flag].nome);
        traco();


		printf("Digite o codigo da disciplina: ");
		scanf("%d",&cod_dic);

		if ( busca_dic(dic,0,tam,cod_dic,&flag2) == 0 || tam<1){ // busca_dic retorna 0 se o codigo ainda nao foi inserido na disciplina
			dic[tam].codigo = cod_dic;

			printf("\nNome da disciplina: ");
			scanf("%s",dic[tam].nome);
			
			printf("\nPeriodo da disciplina: ");
			scanf("%d",&dic[tam].periodo);

			while(dic[tam].periodo> curso[flag].periodo || dic[tam].periodo < 1 ){

				traco();
				printf("\nPeriodo invalido!! Este curso so possui %d periodos \n",curso[flag].periodo);
				
				printf("\ndigite um periodo valido (entre 1 e %d) ",curso[flag].periodo);
				scanf("%d",&dic[tam].periodo);

			}
			
			printf("\ncarga horaria da disciplina: ");
			scanf("%d",&dic[tam].carga_horaria);

			(*quant_dic)++; // devolve quantidade de disciplinas cadrastadas
			curso[flag].dic += 1; //indica que possui diciplinas cadrastadas em curso

			traco();
			printf("\nDisciplina cadrastada com sucesso!\n");	
			traco();		
		
		}else{
			printf("Este codigo ja foi cadrastado!!Nao é possivel inserir disciplina\n");
			traco();
		}
		
		
	}

}
int busca_dic(disciplina *vetor, int inicio, int fim, int cod, int *flag){ // busca_cod(vetor de estrutura, inicio do vetor=0 , fim do vetor = quant_curso , e o cod para busca)
    
    /* Índice representando o meio do sub-vetor begin->end */
    int i = (fim + inicio) / 2;

    if (inicio > fim){  /* Ponto de parada. Item não está no vetor */

    	if (*flag<0){
    		printf("\ncodigo invalido!! Essa disciplina nao existe \n");
    	}

        
        return 0;      // retorna 1 se nao encontrar codigo
    }

    if (vetor[i].codigo == cod) {  /* Item encontrado */
        
        if (*flag < 0){

        	traco();

	        printf("Codigo da disciplina: %d \n",vetor[i].codigo);

	        printf("Codigo do curso onde a disciplina foi cadrastada: %d \n",vetor[i].codigo_curso);

			printf("Nome da disciplina: %s \n",vetor[i].nome);

			printf("Periodos da disciplina: %d\n",vetor[i].periodo);

			printf("Carga horaria da disciplina: %d \n",vetor[i].carga_horaria);

			traco();
        	
        }else{

        	*flag = i; //retorna o indece da disciplina
        }



        return 1;				// retorna 1 se  encontrar codigo
    }

    if (vetor[i].codigo < cod) {  /* Item está no sub-vetor à direita */
        return busca_dic(vetor, i + 1, fim, cod,flag);


    } else {  /* vector[i] > item. Item está no sub-vetor à esquerda */
        return busca_dic(vetor, inicio, i - 1, cod,flag);
    }

}

void imprimir_disciplina(disciplina *dic , int *quant_dic){ //parametros cadrastar_curso(vetor contendo os cursos, numeros de cursos inseridos no vetor)
	int codigo;
	int flag= -1;

	printf("Codigo da disciplina: ");
	scanf("%d",&codigo);

	
	flag = busca_dic(dic , 0,*quant_dic, codigo,&flag);

	

}


void copia2(disciplina *x, disciplina *v){ 	 //  x e v sao estruturas simples do tipo disciplina e nao sao vetores
									//copia(estrutura x que ira receber dados da estrutura  v) 
	x->codigo = v->codigo;

	x->codigo_curso = v->codigo_curso;
	
	strcpy(x->nome,v->nome);
	
	x->periodo = v->periodo;
	
	x->carga_horaria = v->carga_horaria;

}


void quick_sort2(disciplina *v, int left, int right){ //esta função ira recebere um vetor de struct contendo cursos e ordenalo usando o metodo de ondenção quicksort
    int i, j;
    disciplina x;  //cria uma estrutura do tipo discplina para armazenar temporariamente os dados do vetor
    disciplina y;
     
    i = left; //o i recebe o valor 0 que é a primeira posição do vetor
    j = right; // o i recebe o valor da ultima  posição do vetor
    
    copia2(&x , &v[(left + right) / 2]);  // x recebe um valor inicial que neste codigo sera o valor que estiver no meio do vetor recebido e atraves desse valor
     							// posicionar todos elementos menores do que ele à sua esquerda.

    while(i <= j) { //ira percorrer todas o vetor enquanto o i for menor ou igual a J
        
        while(v[i].codigo < x.codigo && i < right) {   // afunção compara ira retornar -1 se a palavra v[i].palavar for menor que a palavra x.
        													// enquanto o vetor da poisição i nao for menor que x este while ira percorer os valores da direita
            i++; // e incrementar o i
        }
        while(v[j].codigo  > x.codigo && j > left) {   // afunção compara ira retornar 1 se a palavra v[i].palavar for maior que a palavra x.
        													// enquanto o vetor da poisição j nao for maior que x este while ira percorer os valores da esquerda
            j--; // e decrementar o j
        }
        if(i <= j) {                                // se entrar nessa condição quer dizer que o i é menor ou igual a j ou que o v[i] é menor que x ou entao o v[j] é maior que X
            copia2(&y , &v[i]);              //entao o y recebera o valor de V[i]
            copia2(&v[i] , &v[j]);  //entao o v[i] recebera o valor de V[j]
            copia2(&v[j], &y);            //entao o v[j] recebera o valor de y
            i++;                                //incrementa o i
            j--;	                           // e decrementa o j
        }
    } // entao quer dizer que ele ja ordenou uma parte do vetor , mas o vetor ainda pode nao esta completamente ordenado
     
    if(j > left) { 				 		 //entao ele verifica se o j > left
        quick_sort2(v, left, j); 		//faz a chamada recursiva e continuara ordenando os itens a esquerda
    }
    if(i < right) { 				   // e se o i< rigth
        quick_sort2(v, i, right);      //faz a chamada recursiva e continuara ordenando os itens a direita
    }
}


void imprimir_disciplina_curso(disciplina *dic, int quant_dic,curso *curso, int quant_cursos){
	int flag = -1,cod_curso;
	int aux,i,cont=0;


	printf("digite o codigo do curso: ");
	scanf("%d",&cod_curso);

	aux = busca_cod(curso,0,quant_cursos,cod_curso,&flag);

	if (aux == 1 && quant_dic > 0){ //se o curso existir e tiver diciplinas cadrastadas em
		traco();
		printf("Diciplinas cadrastadas no curso de %s: \n",curso[flag].nome );
		traco();
		
		for(i=0 ; i<quant_dic; i++){		


		     if (dic[i].codigo_curso == cod_curso) {  /* Item encontrado */


			    printf("Codigo da disciplina: %d \n",dic[i].codigo);

			    printf("Codigo do curso onde a disciplina foi cadrastada: %d \n",dic[i].codigo_curso);

				printf("Nome da disciplina: %s \n",dic[i].nome);

				printf("Periodos da disciplina: %d\n",dic[i].periodo);

				printf("Carga horaria da disciplina: %d \n",dic[i].carga_horaria);

				traco();
		        	
		        cont = 1;
		            
		    }
		}
		if (cont==0){
		        printf("\nNao ha disciplina cadrastadas neste curso!!\n");
		        traco();
		   
		}
	}
		
}

void imprimir_turno(curso *curso, int quant_cursos){
	int flag = -1;
	int aux,i,cont=0;
	char turno[30];   

		
		printf("\nDigite turno do curso: ");
		scanf("%s",turno);

		traco();

		printf("\nCursos do turno da %s: \n",turno);
		traco();

		for(i=0 ; i<quant_cursos; i++){		


		     if ( strcmp(curso[i].turno,turno) == 0) {  /* Item encontrado */


				printf("Codigo do curso: %d \n",curso[i].codigo);										// flag < 0 a função função retorna 0 se o codigo nao existir e imprime uma mensagem

				printf("Nome do curso: %s \n",curso[i].nome);										   //	e se o codigo existir flag devolve o indice do curso						

				printf("Quantidade de periodos: %d\n",curso[i].periodo);

				printf("Carga horaria do curso: %d horas \n",curso[i].carga_horaria);

				printf("Turno do curso: %s \n", curso[i].turno);

				traco();
		        	
		        cont = 1;
		            
		    }
		}
		if (cont==0){
		        printf("\nNao ha cursos cadrastados neste turno!!\n");
		        traco();
		   
		}
		
}

void imprimir_disciplina_periodo(disciplina *dic, int quant_dic,curso *curso, int quant_cursos){
	int flag = -1,cod_curso;
	int aux,i,cont=0;
	int periodo;


	printf("digite o codigo do curso: ");
	scanf("%d",&cod_curso);

	aux = busca_cod(curso,0,quant_cursos,cod_curso,&flag);

	if (aux == 1 && quant_dic > 0){ //se o curso existir e tiver diciplinas cadrastadas em
		traco();
		printf("\ndigite o periodo: ");
		scanf("%d",&periodo);
		
		while(periodo> curso[flag].periodo || periodo < 1 ){
			traco();
			
			printf("\nPeriodo invalido!! Este curso so possui %d periodos \n",curso[flag].periodo);
				
			printf("\ndigite um periodo valido (entre 1 e %d): ",curso[flag].periodo);
			scanf("%d",&periodo);

		}


		traco();
		printf("Diciplinas cadrastadas no periodo %d: \n",periodo);
		traco();
		
		for(i=0 ; i<quant_dic; i++){		


		     if (dic[i].periodo == periodo && cod_curso == dic[i].codigo_curso) {  /* Item encontrado */


			    printf("Codigo da disciplina: %d \n",dic[i].codigo);

			    printf("Codigo do curso onde a disciplina foi cadrastada: %d \n",dic[i].codigo_curso);

				printf("Nome da disciplina: %s \n",dic[i].nome);

				printf("Periodos da disciplina: %d\n",dic[i].periodo);

				printf("Carga horaria da disciplina: %d \n",dic[i].carga_horaria);

				traco();
		        	
		        cont = 1;
		            
		    }
		}
		if (cont==0){
		        printf("\nNao ha disciplina cadrastadas neste periodo!!\n");
		        traco();
		   
		}
	}



}
void remover_dic(disciplina *dic,int *quant_dic,curso *cursos, int quant_cursos){
	int codigo;
	int flag= 1;
	int tam = *quant_dic-1; // tam recebe o valor da ultima posição do vetor 
	int aux2,flag2 = -1;

	disciplina aux;

	printf("Codigo da disciplina: ");
	scanf("%d",&codigo);

	

	if ( busca_dic(dic , 0,*quant_dic, codigo,&flag) == 1 ){
		
		aux2 = busca_cod(cursos,0,quant_cursos,dic[flag].codigo_curso,&flag2); //busca o indice do curso da disciplina

		cursos[flag2].dic-=1 ; // diminui 1 a variavel cursos dic que indica quantas disciplinas estao inseridas no curso



		traco();
		printf("\nRemovendo disciplina........\n");
		traco();

		dic[flag].codigo = -1;

		printf("\nA disciplina %s foi remivida!!", dic[flag].nome);


		if (flag != *quant_dic){ //se a disciplina nao for a ultima do vetor
			
			copia2(&aux, &dic[tam]); // copia os dados da ultima disciplina e armazena em aux
			copia2(&dic[flag], &dic[tam] ); // joga os dados da disciplina que vai ser removida para a ultima posição
			copia2(&dic[tam],&aux); // e depois reinsere os dados guardados em aux na posição da disciplina removida
		}
		(*quant_dic)--; //dininui a quantidade de disciplinas no vetor

		traco();
		
	}else{
		traco();
		printf("codigo invalido!!Esta disciplina nao existe");
		traco();
	}

	

}
void remover_curso(curso *cursos,int *quant_cursos){
	
	int codigo;
	int flag= -1,aux2;
	int tam = *quant_cursos-1; // tam recebe o valor da ultima posição do vetor 

	curso aux;


	printf("Codigo do curso: ");
	scanf("%d",&codigo);

	aux2 = busca_cod(cursos , 0,*quant_cursos, codigo,&flag);

	


	if ( aux2 == 1 && cursos[flag].dic == 0 ){
		traco();
		printf("\nRemovendo curso........\n");
		traco();

		printf("\nCurso de %s removida com sucesso !!",cursos[flag].nome);

		cursos[flag].codigo = -1;


		if (flag != *quant_cursos){                    //se a disciplina nao for a ultima do vetor
			
			copia(&aux, &cursos[tam]);               //  copia os dados do ultimo curso e armazena em aux
			copia(&cursos[flag], &cursos[tam] );    // joga os dados do curso  que vai ser removida para a ultima posição
			copia(&cursos[tam], &aux);              // e depois reinsere os dados guardados em aux na posição do curso removida
		}
		(*quant_cursos)--;                           //dininui a quantidade de cursos no vetor

		
		traco();
		
	}else{
		traco();
		printf("Nao é possivel excluir curso");
		traco();
	}

	

}















