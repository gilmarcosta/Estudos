#include <stdio.h>
#include <stdlib.h>
#include <locale.h>    //adicionar acentuação

struct acao{
	int quantidade;
	float valorInvestido;
	float media;
};

void adicionar(struct acao *res, float preco, int qnt);
void criar(struct acao *res);
void mostrar(struct acao res);

int main(){
	setlocale(LC_ALL, "Portuguese");
	struct acao a;
	
	criar(&a);
	
	
	
	adicionar(&a,35,100);
	mostrar(a);
	adicionar(&a,31.50,200);
	mostrar(a);
	mostrar(a);
	//adicionar(&a,20,10);
	//adicionar(&a,1,1);
	
	
	//mostrar(a);
	
	getchar();
	
	return 0;
}


void adicionar(struct acao *res, float preco, int qnt){
	(*res).quantidade += qnt; 
	(*res).valorInvestido += qnt * preco;
	(*res).media = (*res).valorInvestido / (*res).quantidade;
}

void criar(struct acao *res){
	(*res).quantidade = 0;
	(*res).valorInvestido = 0; 
	(*res).media = 0;
}

void mostrar(struct acao res){
	printf("Quantidade: %i \n",(res).quantidade);
	printf("Valor Investido :%.2f \n",(res).valorInvestido);
	printf("Média:%.4f \n",(res).media);
	printf("\n");
}