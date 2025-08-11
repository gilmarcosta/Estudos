#include <stdio.h>
#include <stdlib.h>
#include <locale.h>    //adicionar acentuação

typedef struct Celula{
	int mes;  //referenciar o mes para depois pôr por extenso
	char mese[10];  //mes por extenso
	int ano;     //ano 
	float saldo;  //saldo do ultimo dia do mês atual  
	float depositos; //depositos realizados no mês atual
	float saques;   //saques do mês atual
	float rend; //diferença do mês atual para o anterior //uma mensagem rendeu + ou - sairá tbm diante do resultado
	float porc; //poncentagem de rendimento
	float saldoi; //???
	struct Celula *prox;
}celula;

void extras(celula *inicio);
char *escrever (char *pont,char *pont2);
char *vetint(int ano,char *veti);
void insere(celula *li,int mes, int ano, float saldoi, float saldof, float depositos, float saques, float *rend);  //primeiro elemento
celula* inserir(celula *anterior, celula *atual, float saldo, float depositos, float saques, float *rend); //proximas inserções
void mostrar(celula *atual);
void extenso(char *pont, char *nome,int qnt);
void data(char x[],int num);
void fparas(float valor,char *vet);

int main(){
	setlocale(LC_ALL, "Portuguese"); // adicionar acentuação
	float saldo = 0; ////////////////////////////////////////
	char linha[100]={0};
	float r,saldo_inicial;
	
	//char aux[15] = {0};
	//char vetorAux[10]={0};
	/*
	FILE *file = fopen("extrato.txt","a");  //FALTA DESENVOLVER ESSA PARTE
	if(file == NULL){
		printf("Arquivo não pode ser executado");
		return 1;
	}
	*/
	celula celula,*inicio,*atual,*anterior; // cria uma celula do tipo célula(struct) ();  3 ponteiros: 
	/* 
	inicio >>> irá guardar o endereço da primeira celula
	anterior >> terá o endereço da celula anterior à atual 
	atual >>   aponta a célula que será manipulada
	
	precisa de ponteiros porque até então a celula foi criada em um lugar aleatório da memória,
	como ela não será a única celula, como iria saber onde ela está? logo o ponteiro terá essa função,
	ele irá guardar o endereço dela antes do algoritmo "pular para a outra", e evitar que o local do "dado" seja perdido.
	
	*/
	inicio = &celula;  //como citado, o ponteiro guarda o endereço da primeira celula.
	atual = inicio;   //o ponteiro atual recebe o endereço do início, ja que "inicio" contém o endereço da primeira celula.
	anterior = NULL;
//  atual = &celula; também traria o mesmo resultado. (lembrando que, ponteiro recebe endereço, por isso '&' )
  	
	  
	  
	/*  
	OBS: valor do ultimo dia aniversario do mês sempre!!
	
	  PRIMEIRO EXECUTE ESSE AQUI:
		insere(celula *li, int mes, int ano, float saldoi, float saldof, float depositos, float saques)  >>  Como deve ser inserido os dados respectivamente
	  APÓS O RESTO SERÁ ESSES COMANDOS:	
	    inserir(celula *anterior, celula *atual, float saldo, float depositos, float saques);
	    inserir(celula *anterior, celula *atual, float saldo, float depositos, float saques);
	*/
	
	
	
	(*atual).prox = NULL;
	printf("\n\n");
	mostrar(inicio);
	
	extras(inicio);
	puts(linha);
	//fclose(file);
	//getchar();
	
	return 0;
}

//CERTO
void insere(celula *atual, int mes, int ano, float saldoi, float saldof, float depositos, float saques, float *r){ // falta configurar saque
	(*atual).mes=mes;
    data((*atual).mese,mes);	
	(*atual).ano=ano;
	(*atual).saldoi = saldoi + depositos; //inicio do mes
	(*atual).depositos = depositos;
	(*atual).saques=saques;
	(*atual).rend = (*atual).saldo - saldoi - (*atual).depositos ;
	(*atual).porc = (*atual).rend / saldof;   
	(*atual).prox = (celula*)malloc(sizeof(celula));
	*r += (*atual).rend;
}


//CERTO
celula* inserir(celula *anterior, celula *atual, float saldo, float depositos, float saques, float *r){ 
	anterior = atual;     // antes da linha a seguir, precisa guardar o endereço da celula anterior a seguinte.
	atual = (*atual).prox; // atual irá receber o endereço da celula seguinte que se encontra no ponteiro dentro da célula definida na função insere.
	if((*anterior).mes < 12){
		(*atual).mes = (*anterior).mes + 1;
		(*atual).ano = (*anterior).ano;
		data((*atual).mese,(*atual).mes);
	}else{
		(*atual).mes = 1;
		(*atual).ano = (*anterior).ano + 1;
		data((*atual).mese,(*atual).mes);
	}
	(*atual).saldo = saldo;
	(*atual).depositos = depositos;
	(*atual).saques = saques;
	(*atual).saldoi = (*anterior).saldo;
	if(saques > 0 && depositos > 0){
			(*atual).rend = ((*atual).saldo  + (*atual).saques - (*atual).depositos) - (*anterior).saldo; // houve saques e depositos
			(*atual).porc = (*atual).rend / ((*atual).saldo - (*atual).depositos + (*atual).saques);
	}else 
		if(saques > 0){	
			(*atual).rend = (*atual).saldo  + (*atual).saques - (*anterior).saldo ;   //apenas saque
			(*atual).porc = (*atual).rend / ((*atual).saldo + (*atual).saques );
			
	}else{
			(*atual).rend = (*atual).saldo - (*anterior).saldo - (*atual).depositos; //apenas depositos
			(*atual).porc = (*atual).rend / ((*atual).saldo - (*atual).depositos);
	}
	*r += (*atual).rend;
	//printf("\n %f\n",(*atual).dife);
	//getchar();
	(*atual).prox = (celula*)malloc(sizeof(celula));
	return atual;
}

// (ctrl + /) na linha vira comentarios =D


//PRECISA ELABORAR
void mostrar(celula *inicio){
		celula *atual = inicio;
		int sinal = 0; //sinal e para sair do loop, se nao existir proxima celula, ele para
		float tot = 0;
		printf("Saldo anterior  Rendim.     Mês       Ano     Depósitos      Saques  porcentagens decimal e fracionário Saldo Atual\n\n");
	while(sinal==0){	//entra no loop
		if((*atual).prox!= NULL){ // se proximo for diferente de nulo...
			printf(" %8.2f",(*atual).saldoi);
			printf("    ");
			printf("%7.2f",(*atual).rend);
			printf("    ");
			printf(" %s",(*atual).mese);
			printf(" %i ",(*atual).ano);
			printf(" %8.2f",(*atual).depositos);
			printf("    ");
			printf(" %8.2f",(*atual).saques);
			printf("       ");
			printf(" %7.5f",(*atual).porc);
			printf(" %7.2f %%",100*(*atual).porc);
			printf("    ");
			printf(" %8.2f",(*atual).saldo);
			printf("\n");
			tot += (*atual).porc;
			if((*atual).mes == 12){
				//printf("                                                                           %7.3f\n",100*tot);
				//printf("total = %.4f\n",tot*100); //temporario
				tot = 0;
			}
			atual = (*atual).prox; //pula para outra celula
			sinal = 0;
		}else{ //se proximo for nulo, .....
			printf(" %8.2f",(*atual).saldoi);
			printf("    ");
			printf("%7.2f",(*atual).rend);
			printf("    ");
			printf(" %s",(*atual).mese);
			printf(" %i ",(*atual).ano);
			printf(" %8.2f",(*atual).depositos);
			printf("    ");
			printf(" %8.2f",(*atual).saques);
			printf("       ");
			printf(" %7.5f",(*atual).porc);
			printf(" %7.2f %%",100*(*atual).porc);
			printf("    ");
			printf(" %8.2f",(*atual).saldo);
			printf("\n");
			tot += (*atual).porc;
			//printf("total = %.4f\n",tot*100);
			if((*atual).mes == 12){
				//printf("                                                                           %7.3f\n",100*tot);
				printf("\n"); //temporario
				tot = 0;
			}
			//printf("                                                                           %7.3f\n",100*tot);	
			printf("\n"); //temporario
			sinal = 1; // a condiçao para parar e validada..
		}
	}
}



void extenso(char *pont, char *nome,int qnt){ // recebendo um endereço do tipo CHAR e nao STRUCT
	int i;
	for(i=0;i<qnt;i++){
		pont[i] = nome[i];
	}
};

void extras(celula *inicio){
	celula *atual = inicio;
	float saldototal = 31904.92, diferenca = 0, rendimentototal = 0, deptotal = 0, saqtotal = 0;;
	
	while((*atual).prox!= NULL){
		
		rendimentototal += (*atual).rend;
		deptotal += (*atual).depositos;
		saqtotal += (*atual).saques;
		
		
		atual = (*atual).prox;
	}
		rendimentototal += (*atual).rend;
		deptotal += (*atual).depositos;
		saqtotal += (*atual).saques;
		diferenca = deptotal - saqtotal;
		
		
		saldototal += rendimentototal + diferenca;
		
		printf("Total de saques :%7.2f\n",saqtotal);
		printf("Total de depósitos :%7.2f\n",deptotal);
		printf("Diferença entre saque e depósitos:%7.2f\n",diferenca);
		printf("Total de rendimento :%7.2f\n",rendimentototal);
		printf("Saldo atual: %7.2f\n ",saldototal);
		
}


void data(char *x,int num){ //ponteiro de vetor do tipo char
	switch(num)
	{
	case 1:
		extenso(x,"JANEIRO  ",10); //vetor passado, nao precisa * e nem [] !!
		break;
	case 2:
		extenso(x,"FEVEREIRO",10);
		break;
	case 3:
		extenso(x,"MARÇO    ",10);
		break;
	case 4:
		extenso(x,"ABRIL    ",10);
		break;
	case 5:
		extenso(x,"MAIO     ",10);
		break;
	case 6:
		extenso(x,"JUNHO    ",10);
		break;
	case 7:
		extenso(x,"JULHO    ",10);
		break;
	case 8:
		extenso(x,"AGOSTO   ",10);
		break;
	case 9:
		extenso(x,"SETEMBRO ",10);
		break;
	case 10:
		extenso(x,"OUTUBRO  ",10);
		break;
	case 11:
		extenso(x,"NOVEMBRO ",10);
		break;
	case 12:
		extenso(x,"DEZEMBRO ",10);
		break;
	default:
		break;
	}	
}