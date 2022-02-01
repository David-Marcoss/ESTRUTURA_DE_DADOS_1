#include <stdio.h>
#include <string.h>
	
typedef struct{
	int matricula,idade;
	char nome[30];
	float altura;
}dados;   			//define uma estrutura do tipo dados que possui as variaveis matricula,idade,nome e altura

typedef struct{
	char nome[30]; //define uma estrutura do tipo dados2 que recebe um nome e servira para receber o nome dos alunos que tiverem idade igual a media
}dados2;


void mais_alto(dados *aluno, float *altura); //recebe por parametro um vetor de estrutura do tipo dados que ira receber os dados dos alunos e variavel altura que ira retornar por parametro a altura do aluno mais alto
void inserir(dados *aluno); // funçaõ que ira inserir dados no vetor de estrutura aluno
int mais_baixo(dados *aluno);//recebe por parametro um vetor de estrutura do tipo dados que ira receber os dados dos alunos e ira retornar pela funçao a idade do aluno mais baixo
float mediana(dados *aluno,dados2 *nomes, int *tam) ;//recebe por parametro um vetor de estrutura do tipo dados que ira receber os dados dos alunos e outra estrutura dados 2 que ira retornar o nome dos alunos com altura mediana e outra variavel tam que ira retornar quantos itens foram inseridos na estrutura dados2

int main(){	
	dados aluno[3];  // cria um vetor aluno do tipo dados com tamanho 3 que ira receber o dados dos alunos
	dados2 nomes[3];//cria um vetor nomes do tipo dados com tamanho 3 que ira receber o nome dos alunos que possuem altura mediana
	
	int tam=0,i; //cria varivel tam que sera usada na funçao mediana
	float altura=0;	//cria varivel tam que sera usada na funçao mais_alto
	
	inserir(aluno); // insere os dados na estrutura aluno	
	mais_alto(aluno,&altura); //chama a funçao mais_alto que passa como parametro a estrutura aluno e variavel altura que ira receber altura do aluno mais alto
	
	printf("aluno mais alto: %f\n",altura);
	printf("idade aluno mais baixo: %d\n",mais_baixo(aluno)); //da um print na função mais_baixo que retorna a idade do aluno mais baixo
	printf("media altura: %f\n",mediana(aluno,nomes,&tam)); //da um print na função mediana que retorna pela função a media das alturas dos alunos e retorna por parametro na estrutura nomes o nomes dos alunos que possuem altura mediana
	
	for(i=0;i<tam;i++){
		printf("%s\n",nomes[i].nome); // se possuir alunos com altura mediana será print os seus nomes no laço for
	}

	return 0;
}
void inserir(dados *aluno){ //insere dados
	int i;
	
	for(i=0;i<3;i++){
		 printf("digite os dados: ");   // ORDEM DE INSERÇÃO DOS DADOS 1 MARTICULA(INT),2 NOME(STRING),3 IDADE(INT),4 ALTURA(FLOAT)
		 scanf("%d",&aluno[i].matricula);
		 scanf("%s",aluno[i].nome);
		 scanf("%d%f",&aluno[i].idade,&aluno[i].altura);	
	}
	
}
void mais_alto(dados *aluno, float *altura){ //retorna altura do aluno mais alto
	int i;
	
	for(i=0;i<3;i++){ 
		if(*altura<aluno[i].altura)   //percorre todo o vetor e verifica se possui alunos que possuem altura maior que a variavel altura que inicia com 0
			*altura= aluno[i].altura; // se possuir a variavel altura ira recerber a altura deste alunos
	}
		
}
int mais_baixo(dados *aluno) { // retorna a idade do aluno mais baixo
	int i,idade = aluno[0].idade; //cria variavel idade que recebe idade que recebe a idade do aluno que estiver na primeira posiçao do vetor
	float altura = aluno[0].altura; //cria altura idade que recebe altura que recebe a idade do aluno que estiver na primeira posiçao do vetor
	
	for(i=1;i<3;i++){  // entao apartir dos dados do primeiro aluno[0] ira percorrer o vetor i verificar se existe aluno com altura mais baixa
		if(altura>aluno[i].altura){   
			altura= aluno[i].altura; //se possuir ira atribuir as variaveis altura e idade e no final retornara a idade do mais baixo
			idade = aluno[i].idade;
		}

	}
	
	return idade;
}
float mediana(dados *aluno,dados2 *nomes, int *tam) { //retorna a media das alturas do alunos pela função e o nome dos alunos com altura mediana por parametro 
	float media=0; //declara variavel media
	int i;
	
	for(i=0;i<3;i++){// percorre todo o vetor atribuido a soma da alturas dos alunos a variavel media
		media+= aluno[i].altura; 
	}
	media/=i; //calcula a media
	
	for(i=0;i<3;i++){ //percorre novamente o vetor
		if(media == aluno[i].altura ){ //verifica se possui alunos com altura igual a media
			strcpy(nomes[*tam].nome,aluno[i].nome); //se possuir armazena o nome do alunoo a estrutura nomes
			(*tam)+=1; //faz o tam+1 que ira definir quantos nomes foram inserido na estrutura nomes
		}
	}
	
	
	return media;//retorna a media
}