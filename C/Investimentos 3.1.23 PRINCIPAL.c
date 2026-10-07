#include <stdio.h>
#include <stdlib.h>
#include <locale.h>    //adicionar acentuação
//48.486,13
//atualizar a funçao investimento e criar a funcao venda
//criar a funçao ou arrumar um jeito de mostrar e guardar o total de rendimento anual por acao
//diferença de 662,34 pro nubank o valor de entrada (74.746,25) enquanto do nubank está (75.408,59)

/*obs: Sobre as açoes bônus:
Explicação Detalhada:
Aumento de Capital e Bonificação:
A Klabin realizou um aumento de capital, ou seja, a emissão de novas 
ações, e, para atrair investidores, pode ter optado por bonificar os acionistas 
existentes com essas novas ações. 
Proporção da Bonificação:
A bonificação pode ser realizada em uma proporção específica, como 1 nova ação
 para cada 10 ações detidas pelo acionista
*/

/* A ATUALIZAR....
0 - inserir a data atual
1 - converter a data para um codigo, facilitando descobrir se a data e menor ou maior a data atual
2 - criar uma funcao que receba a data com ao inves do numero de cotas
3 - fazer a data de compra uma lista duplamente encadeada, para percorrer do fim ate o inicio, economizando passos da ultima data 
de compra ate a data com, ou fazer ele percorrer a lista, mas não do inicio, e sim de uma data, voce pode "setar" a lista, determinando 
o primeiro no como a ultima data com, assim não precisa puxar desde 2023.
4 - a funcao irá retornar um valor, onde esse valor e o numero de cotas corretas dentro do prazo da data com
5 - ai sim usar a funcao atualproventos
*/

struct gancho{
	int ano;
	int investidores;
	int vendas;
	int compras;
	int recibos;
	struct investidor *i; //investidor
	struct dataCom *r; // recibo de dividendos!!
	struct dataCom *c; //compras
	struct dataCom *v; //vendas
	struct resultado *R; // resultados cuidado!!
};

struct acoes{  //criado para listar os ativos de cada usuario (nome do ativo, quantidade, valor total investido no ativo, total de proventos recebidos)
	char ativo[7];
	float qnt; //float para poder formatar o texto na hora de imprimir, caso consiga com int depois altero
	int ativobonus;
	float media;
	float P_media;
	float valorinvest;
	float pagamentoA; // oque o investidor recebeu real no ano atual por acao
	float pagamentoT; //oque o investidor recebeu real ao todo
	float pagamentoI; // oque o investidor recebeu por ter reinvestido;
	float base;
	float taxa; //taxa de corretagem
	int ano; // ano referente do resultado  OBS:desnecessario apos a criação do resultado
	float proventos; //em dinheiro total, proventos total
	float proventosA; // proventos anual
	float proventosU; // Ultimo valor pago
	float dividendos;
	float proventoPagoPorAtivo;
	float reinvestido;
	float nova; //novos ativos 
	float compranova; //valor investido anual
	struct acoes *prox;	
};

struct dataCom{  // criado para listar as datas das compras e as datas de proventos pagos (data da compra/recibo, nome do investidor e do ativo, preco pago ou valor recebido, quantidade de papeis comprado)
	
	char data[20];
	char nome[10];
	char ativo[7];
	char obs;
	float preco;
	float qnt;
	float media;
	struct dataCom *prox;
};

struct investidor{ // criado para listar os investidores  (nome do investidor, valor total do capital do investidor )
	int elementos_ativos;
	char nome[10];
	float saldo;
	float taxaBolsa;
	float ativos;
	float lucro;
	float perda;
	float fimobiliario;
	float valor;  //total investido
	float valorReinvestido; //reinvestido
	float valorDoanoatual; //total investido ano atual
	float valor2; //proventos recebidos ano atual
	float valor3; //proventos recebidos (TOTAL)
	float imposto;//pagos de jCP
	struct acoes *aprox;
	struct investidor *prox; 
};

struct resultado{
	int ano;
	struct investidor *prox;
	struct resultado *proximo;
};

void proventos_atual(struct gancho *g, char *nomei,char *nomea,char *data,float valorp,char dig,int qnt);
void proventos__atual(struct gancho *g, char *nomei,char *nomea,char *data,float valorp,char dig,int qnt,float IR); 
void investimento_atual(struct gancho *g,char *nome, int qnt, char *ativo, float preco, char *data, float tx); 
int verifica(char datI[]);
void media(char datI[] ,char datU[], struct dataCom *R,struct gancho *g);
void string(char *pont, char *nome,int qnt);
int verificar(char *prim, char *seg);
void mostrar(struct gancho *g, char *data);
void mostrarhtml(struct gancho *g, char *data);
void mostrarResultado(struct gancho *g);
void iniciarInvestidor(struct investidor *inicio);
void iniciarAtivo(struct acoes *acoes);
void iniciarDataCom(struct dataCom *compra);
void iniciaResultados(struct resultado *res);
void investimento(struct investidor *in, struct dataCom *c, char *nome, float preco, char *ativo, float valor, char *data);
void mostrarC(struct dataCom *compra);
void proventos(struct investidor *in,struct dataCom *r,struct resultado *resu, char *nomei,char *nomea,char *data,float valorp,float valort,float *saldo);
void mostrarR(struct dataCom *recibo);
void adicionarInvestimentos(struct gancho *g);
void adicionarVendas(struct gancho *g, char *nome_investidor, int qnt, char *nome_ativo, float preco, char *data ,float tx);
void i_gancho(struct gancho *g); //inicia o ponteiro
void gambiarra(struct investidor *in);
void bonus(struct gancho *g,char *investidor,int qnt,char *ativo,char *data);
void Compra2023(struct gancho *g);
void Compra2024(struct gancho *g);
void Compra2025(struct gancho *g);
void Compra2026(struct gancho *g);
void Proventos2023(struct gancho *g);
void Proventos2024(struct gancho *g);
void Proventos2025(struct gancho *g);
void Proventos2026(struct gancho *g);
void ordenar(struct gancho *g, int op);
void troca(struct investidor *in,struct acoes *a,struct acoes *pivo,struct gancho *g);
void reinvestimento(struct gancho *g,char *nome, int qnt, char *ativo, float preco, char *data, float tx);
void corrigirSaldo(struct gancho *g, char *nome, float valor);
void transferencia(struct gancho *g, char *vendedor, char *nomeativo,int qnt, char *comprador);
void iniciarinvestidor(struct investidor *inicio);
void split(struct gancho *g,char *nome, char *ativo, int x, int y, float valor);
void gambiarra2(struct gancho *g);
void escreverdados_compras(struct gancho *g);
void escreverdados_vendas(struct gancho *g);
void escreverdados_dividendos(struct gancho *g);
void calculo(int codigo_data,char *data,float *valorp,char dig,int qnt, float IR);
void teste(float valorp,char *nomei,char *nomea,char *data,char dig);
void add(struct investidor *in, struct acoes *a, float qnt, float valor, float tx);
void add_compra(struct dataCom *c, char *data, char *nome, char *ativo, float preco, float valor);
void arquivo_bin(struct gancho *g);
struct gancho* igancho();



struct gancho* igancho(){
	struct gancho *novo = (struct gancho*)malloc(sizeof(struct gancho));
	i_gancho(novo);	
	return novo;
}


int main(){
	setlocale(LC_ALL, "Portuguese"); // adicionar acentuação
	char datI[20] = {},datU[20] = {};
	string(datI,"03/agosto/2023",20); //30/junho/2023 começou os investimentos, porém passou da datacom, entao começa a contagem de agosto (03/08) anuciou, (21/08) datacom
	string(datU,"01/maio/2026",20); //  ******************* alterar a cada modificação
	
	struct gancho *atualg = NULL;
	
	atualg = igancho();   //adiciona compras
	adicionarInvestimentos(atualg);
	//system("cls");

	
	//escreverdados_compras(atualg);
	//escreverdados_vendas(atualg);
	//escreverdados_dividendos(atualg);
	
	int op = 6;
	/*
	1 - média (crescente)
	2 - quantidade (Decrescente)
	3 - valor total investido (Decrescente)
	4 - proventos pago por ação (Decrescente)
	5 - porcentagem pago em proventos do ano atual (Decrescente)
	6 - porcentagem do investimento ao todo (Decrescente)
	*/
	ordenar(atualg,op);
	//printf();
	mostrar(atualg,datU);
	
	printf("\n\n%i investidores\n%i compras\n%i vendas\n%i recibos\n\n",(*atualg).investidores,(*atualg).compras,(*atualg).vendas,(*atualg).recibos);
	
	//arquivo_bin(atualg);
	
	//mostrarhtml(atualg,datU);
	//mostrar(atualg,datU);
	//mostrarC((*atualg).r);
	//mostrarC((*atualg).c); // mostrar compras de açoes
	//mostrarR((*atualg).c); // mostrar proventos recebidos
	//media(datI,datU,(*atualg).r,atualg);
	
	//system("pause");
	return 0;
}


void arquivo_bin(struct gancho *g){
	
	FILE *arquivo = fopen("Carteira.bin","wb");

	if(arquivo != NULL){
		if(g!=NULL){
			
		}else{
			printf("\nlista vazia\n");
		}
	}else{
		printf("\nErro no arquivo bin\n");
	}
	fclose(arquivo);
}


void add(struct investidor *in, struct acoes *a, float qnt, float valor, float tx){
		(*a).qnt += qnt;
		(*a).nova+= qnt;
		(*a).compranova+= valor;
		(*a).valorinvest += valor;
		(*a).media = ((*a).valorinvest / ((*a).qnt)); //(*a).media = ((*a).valorinvest / ((*a).qnt - (*a).ativobonus));
		(*a).taxa += tx;
		(*in).taxaBolsa += tx;	
		if((*a).P_media == 0){
			(*a).P_media = (*a).media;
		}
}

void add_compra(struct dataCom *c, char *data, char *nome, char *ativo, float preco, float valor){
	string((*c).data,data,20);
	string((*c).nome,nome,10);
	string((*c).ativo,ativo,7);
	(*c).preco = preco;
	(*c).qnt = valor/preco;
	(*c).prox = NULL;
	
}

void escreverdados_compras(struct gancho *g){
	FILE *a = NULL;
	
	a = fopen("compras.txt","w");
	
	if(a==NULL){
		printf("\narquivo compras.txt não encontrado!!\n");
	}else{
		if(g==NULL){
			printf("\nNão tem oque escrever, lista vazia!! [compras]\n");
		}else{
			struct dataCom *c = (*g).c;
			int cont = 1;
			while(c!=NULL){
				
				fprintf(a," [%3.i]º Compra de %6s por %7.2f, [%3.f], data: %s\n",cont,(*c).ativo, (*c).preco , (*c).qnt, (*c).data);
				c = (*c).prox;
				cont++;
			};
			printf("\n arquivo [compras.txt] PRONTO!!\n");
			fclose(a);
			system("pause");
		}
		
	}	
}


void escreverdados_vendas(struct gancho *g){
	FILE *a = NULL;
	
	a = fopen("vendas.txt","w");
	
	if(g==NULL){
		printf("\nNão tem oque escrever, lista vazia!! [vendas]\n");
	}else{
		struct dataCom *v = (*g).v;
		int cont = 1;
		while(v!=NULL){
			fprintf(a,"[%i]° Venda de %s por %.2f (%.f) data: %s com média %.2f (%s)",cont,(*v).ativo, (*v).preco ,(*v).qnt,(*v).data,(*v).media,(*v).nome);
			fprintf(a," %.2f - %.2f = %.2f",(*v).preco * (*v).qnt, (*v).media * (*v).qnt,   ( ((*v).preco*(*v).qnt) -  ((*v).media*(*v).qnt) )    );
			if((*v).preco < (*v).media){
				fprintf(a," prejuízo\n");	
			}else{
				fprintf(a," Lucro\n");	
			}
			cont++;
			v = (*v).prox;
		};
		printf("\n arquivo [vendas.txt] PRONTO!!\n");
		fclose(a);
		system("pause");
	}
}

void escreverdados_dividendos(struct gancho *g){
	FILE *a = NULL;
	a = fopen("dividendos.txt","w");
	
	
	if(g==NULL){
		printf("\nNão tem oque escrever, lista vazia!! [dividendos]\n");
	}else{
		struct dataCom *d = (*g).r;
		int cont = 1;
		while(d!=NULL){
			fprintf(a,"[%3.i]° %-20s %-6s %10.2f %-10s       ",cont,(*d).data,(*d).ativo,(*d).preco,(*d).nome);
			
			printf("[%i] %c",cont,(*d).obs);
			if((*d).obs == 'D'|| (*d).obs == 'd'){
				fprintf(a,"Dividendos\n");
			}else{
				  if((*d).obs == 'J'|| (*d).obs == 'j'){
					fprintf(a,"Juros de capital próprio\n");
			    }else{
				   if((*d).obs == 'R'|| (*d).obs == 'r'){
					fprintf(a,"Rendimento\n");
					}else{
						printf("erro\n");
					}
				}
		}			
			d = (*d).prox;
			cont++;
		}
	}
	
	printf("PRONTO!!");
	fclose(a);
	system("pause");
}
void adicionarInvestimentos(struct gancho *g){
		//"Painel onde serão inseridos dados"
	Compra2023(g);
	Compra2024(g);
	Compra2025(g);
	Compra2026(g);
}

void media(char datI[],char datU[], struct dataCom *R,struct gancho *g){
	int i = (verifica(datI));  //sera sempre junho mesmo 
	int f,ano,tam,res = 0;
	float tot = 0,meses=0,TOT_IN;
	struct investidor *in;
 
	if((*g).i != NULL){
		in = (*g).i;	
		do{
			TOT_IN += (*in).valor+(*in).taxaBolsa;
			if((*in).prox != NULL){
				in = (*in).prox;
			}else{
				break;
			}
		}while(1);
	}
	for(tam = 0; datU[tam] != '\0'; tam++);
	ano = (1000 *(datU[tam-4]- '0')) + (100 *(datU[tam-3]- '0')) + (10*(datU[tam-2]- '0')) + ((datU[tam-1]- '0'));
	f = verifica(datU);
	
 	if(ano>2023){
		if(ano-2023>1){
			meses = (12 - i) + ((ano-(2023+1))*12) + f;
		}else{
			meses = 12 - i;
		}
	}else{
		printf("\nAlgo deu errado no cálculo da média dos meses!! [function media()]");
	}
		 
	 do{
	 	res = verificar((*R).nome,"Gilmar");
	 	if(res == 1){
	 	tot += (*R).preco;
	 	res = 0;
		 }
		 if((*R).prox == NULL){
			 break;
		 }
		 R = (*R).prox;
	 }while(1);
	 
	//printf("\n\n");
	printf("\n\nEm %.0f meses a média ganho por mês foi : R$:%.2f    >>%s<<\n",meses,tot/meses,datU); //tot e o total de dividendos     total e a quantidade de meses
	printf("\nMédia investido por mês: %.2f em um total de %.0f meses\n",TOT_IN/meses,meses);
}

int verifica(char datI[]){
	int mes, ind = 3;
		 
	if(datI[ind] == 'j'){
		if(datI[ind+1] == 'a'){
			mes = 1;
		}else{
			mes =  6;
		}
	}else{	
		if(datI[ind] == 'f'){
			mes = 2;
		}else{
			if(datI[ind] == 'm'){
				if(datI[ind+2]=='r'){
					mes = 3;
				}else{
					mes = 5;
				}
			}else{
				if(datI[ind] == 'a'){
					if(datI[ind+1]=='b'){
						mes = 4;
					}else{
						mes = 8;
					}
				}else{
					if(datI[ind] == 's'){
						mes = 9;
					}else{
						if(datI[ind] == 'o'){
							mes = 10;
						}else{
							if(datI[ind] == 'n'){
								mes = 11;
							}else{
								if(datI[ind] == 'd'){
									mes = 12;
								}
								else{
									printf("Não enontrado");
								}
							}
						}
					}
				}
			}
		}
	}
	return mes;
}

void investimento_atual(struct gancho *g,char *nome, int qnt, char *ativo, float preco, char *data, float tx){ //certo
	int res=0;
	struct acoes *a;
	struct investidor *in;
	struct dataCom *c;
	float valor = preco * qnt;
	
	if((*g).i==NULL){
		(*g).i = (struct investidor*)malloc(sizeof(struct investidor));
		in = (*g).i;
		(*g).investidores++;
		iniciarInvestidor(in);
	}else{
		in = (*g).i;
	}
	
	if((*g).c==NULL){
		(*g).c = (struct dataCom*)malloc(sizeof(struct dataCom));
		c = (*g).c;
		iniciarDataCom(c);
	}else{
		c = (*g).c;
	}

	if((*in).nome[0] == '\0'){ // se nome nao existe, senão... 
		string((*in).nome,nome,10); 
		(*in).valor += valor;
		(*in).valorDoanoatual += valor;
		(*in).aprox = NULL;	
		res = 0;
	}else{
		do{
			res = verificar((*in).nome,nome);  // se nome é igual o cadastrado
			if(res == 1){
				(*in).valor += valor;
				(*in).valorDoanoatual += valor;
				res = 0;
				break;
			}else{
				if((*in).prox == NULL){ 
					(*in).prox = (struct investidor*)malloc(sizeof(struct investidor));
					(*g).investidores++;
					in = (*in).prox;
					string((*in).nome,nome,20);
					iniciarinvestidor(in);
					(*in).valor = 0;
					(*in).valor2 = 0;
					(*in).valor += valor;
					(*in).valorDoanoatual += valor;
					(*in).prox = NULL;
					(*in).aprox = NULL; 
					break;
									
				}else{
					if((*in).prox!= NULL){
						in = (*in).prox;
					}else{
						printf("Algo deu errado em nome!!");
						break;
					}
				}
			}
		}while(1);
	}
	if((*in).aprox == NULL){ 
		(*in).aprox =(struct acoes*)malloc(sizeof(struct acoes));
		a = (*in).aprox;
		iniciarAtivo(a);
		string((*a).ativo,ativo,7);
		add(in,a,qnt,valor,tx);
	}else{
		a = (*in).aprox; 
		do{
			res = verificar((*a).ativo,ativo);
			if(res == 1){
				if((*a).qnt == 0){ //porque se vendi tudo, o ativo ficará guardado, entao ao comprar novamente eu zero o valor investido
					(*a).valorinvest = 0;
				}
				add(in,a,qnt,valor,tx);
				res = 0;
				break;
			}else{
					if((*a).prox==NULL){ //tx add
						(*a).prox = (struct acoes*)malloc(sizeof(struct acoes));
						a = (*a).prox;
						iniciarAtivo(a);
						string((*a).ativo,ativo,7);
						add(in,a,qnt,valor,tx);				
						break;
					}else{
						 if((*a).prox!=NULL){
							 a = (*a).prox;
						 }else{
							 printf("Algo deu errado em ativo!!");
							 break;
						 }
					}
			}
		}while(1);
	}
				
	if((*c).data[0] == '\0'){
		add_compra(c,data,nome,ativo,preco,valor);
		(*g).compras++;
	}else{
		do{
			if((*c).prox == NULL){
					(*c).prox = (struct dataCom*)malloc(sizeof(struct dataCom));
					c = (*c).prox;
					iniciarDataCom(c);
					add_compra(c,data,nome,ativo,preco,valor);
					(*g).compras++;
				break;
			}
		c =(*c).prox;
		}while(1);
	}
}

void reinvestimento(struct gancho *g,char *nome, int qnt, char *ativo, float preco, char *data, float tx){
	investimento_atual(g,nome,qnt,ativo,preco,data,tx);
	int res = 0;
	struct acoes *a;
	struct investidor *in;
	in = (*g).i;
	do{
		res = verificar((*in).nome,nome);  // se nome é igual o cadastrado
		if(res == 1){
			(*in).valorReinvestido += preco * qnt;
			break;
		}else{
			if((*in).prox!= NULL){
				in = (*in).prox;
			}else{
				printf("Algo deu errado em nome!!");
				break;
			}
		}
	}while(1);
	a = (*in).aprox; 
	res = 0;
		do{
			res = verificar((*a).ativo,ativo);
			if(res == 1){
				(*a).reinvestido += preco * qnt;
				break;
			}else{
				 if((*a).prox!=NULL){
					 a = (*a).prox;
				 }else{
					 printf("Algo deu errado em ativo!!");
					 break;
				 }	
			}
		}while(1);	
}

void string(char *pont, char *nome,int qnt){ // para inserir uma string em um vetor de char (vetor,string,tamanho da string)
	int i;
		for(i=0;i<qnt;i++){
			pont[i] = nome[i];
		}
};
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mostrar(struct gancho *g, char *data){ //aquii
	if(g == NULL){
		printf("\nLista vazia\n");
	}else{
		printf("\n");
		struct acoes *a;
		struct investidor *in;
		float totalproventos = 0, totalinvestido = 0, totaltotal = 0;
		int mes = 12,QA=0;
		float res;
		float divA=0,divB=0; //media total (considerando por açao)
		in = (*g).i;
		printf("\n");
		//system("MODE con cols=145 lines=60");
		//system("title versão 1.8");
		printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("\n");
		do{
			printf("\n");
			printf("Investidor: %s  Total investido: %.2f | Reinvestimento Total: %.2f || Investido no ano Atual: %.2f   TX: %.2f   --JCP pago [ %.2f ]",(*in).nome,(*in).valor,(*in).valorReinvestido,(*in).valorDoanoatual,(*in).taxaBolsa,(*in).imposto);
			printf("\n                ");		
			printf("Total:[ %.2f = %.2f%% ] ",(*in).valor2,((*in).valor2/(*in).valor)*100); //TOTAL RECEBIDOS
			printf("                          ");
			printf("Proventos recebidos %i: [ %.2f = %.2f%% | %.2f%%]  ",(*g).ano,(*in).valor3,((*in).valor3/(*in).valor)*100,((*in).valor3/( (*in).valor - (*in).valorReinvestido)*100)); //ANO ATUAL RECEBIDO
			printf("\n                ");
			if((*in).saldo > 0){
				printf("SALDO ATUAL: %.2f  ",(*in).saldo);
			}
			if((*in).lucro > 0.01){
				printf("Lucro:[ %.2f ]  ",(*in).lucro);
			} 
			
			if((*in).perda < 0) {
				printf("Perda:[ %.2f ]  ",((*in).perda)*-1);
			}
			
			printf("\n\n");
				totalinvestido += (*in).valor;
				totaltotal += (*in).valor2;
				totalproventos += (*in).valor3;
				a =(*in).aprox;
				printf("    ATIVO | QNT|NOVAS | INVESTID | DIV T. | MÉDIA  | DIF  | Reinvest.  |P.P.A| %% AA |  %%T.  |  P.P.A  | %% A.C. |  %%P.M  | Último  | N | Investido\n");
			do{
				if((*a).ativo[5]!= '\0'){ //para organizar os que possuem mais um caractere, apenas visual
					if((*a).nova == 0){
						printf(" >> %s%4.f [    ] : %8.2f ",(*a).ativo,(*a).qnt,(*a).valorinvest);
					}else{
						printf(" >> %s%4.f [%4.0f] : %8.2f ",(*a).ativo,(*a).qnt,(*a).nova,(*a).valorinvest);
					}
					if((*a).proventos > 0){
						printf("%8.2f",(*a).proventos);
					}else{
						printf("        ");
					}
				}else{
					if((*a).nova == 0){
						printf(" >> %s%5.f [    ] : %8.2f ",(*a).ativo,(*a).qnt,(*a).valorinvest);
					}else{
						printf(" >> %s%5.f [%4.0f] : %8.2f ",(*a).ativo,(*a).qnt,(*a).nova,(*a).valorinvest);
					}
					if((*a).proventos > 0){
						printf("%8.2f",(*a).proventos); //aquii
					}else{
						printf("        ");
					}
				}
		
			res = (((*a).pagamentoA/(*a).media)*100)/mes;
			
			printf("  ");
			if((*a).media > 0){
				printf(" %6.2f ",(*a).media);
				if((*a).P_media != (*a).media){
					//printf(" %6.2f ",(*a).P_media); 
					if((*a).media - (*a).P_media > 0){
						printf("+");
						//printf("%6.2f",(*a).P_media);
						printf("%6.2f",((*a).media) - (*a).P_media);
					}else{
						printf("-");
						//printf("%6.2f",(*a).P_media);
						printf("%6.2f",(((*a).media) - (*a).P_media)*-1);
					}
				}else{
					printf("       ");
					//printf("+ %6.2f ",(*a).P_media);
				}
				if((*a).reinvestido > 0){
					printf("  %8.2f  ",(*a).reinvestido);
				}else{
					printf("            ");	
				}
				if((*a).pagamentoA > 0){
				printf(" [%3.2f] ",(*a).pagamentoA); //Por Ativo anual
				
				
				
				divA += (*a).media;
				divB += (*a).pagamentoA;
				//printf(" : %2.2f ] ",(*a).pagamentoT); //Total Pago
				}else{
				
					printf("        ");
				}
				//printf("((%.2f)) ",(*a).taxa); //taxa da bolsa total
				if((*a).base > 0){
				//printf(">%8.2f ",((*a).base)*100); //base para calcular se esta rendendo + que a poupança (6%), OBS: E o que deveria render e não oque rendeu!!!
				//printf("%8.2f ",((*a).proventoPagoPorAtivo/(*a).media)*100); //porcentagem total
				
				printf("%5.2f ",((*a).pagamentoA / (*a).media)*100);
				//printf("%5.2f ",((*a).proventosA / ((*a).valorinvest - (*a).reinvestido))*100);
				
				printf(":%5.2f ",((*a).proventos/((*a).qnt *(*a).media))*100); //mostra o quanto rendeu (REAL) ao todo
				}else{
					printf("%5.2f ",((*a).proventosA / ((*a).valorinvest - (*a).reinvestido))*100);
					printf(":%5.2f ",((*a).proventos/((*a).qnt *(*a).media))*100);
					//printf("      ");
					//printf("      ");
				}
				if((*a).ano != 0){
					printf(" %8.2f ",(*a).proventosA);
					
					
					printf(" %8.2f ",((*a).valorinvest/(*in).valor)*100); //parte da carteira de investimentos
					if((*a).proventosA > 0){
						printf(" %8.2f ",(((*a).pagamentoA/(*a).media)*100)/mes); // ((pago por acao/ media)*100 )/ mes atual
						
					}else{
						printf("          ");
					}
				}else{
					printf("           %8.2f",((*a).valorinvest/(*in).valor)*100); //parte da carteira de investimentos
					if((*a).proventosA > 0){
					printf(" >%8.2f ",(((*a).pagamentoA/(*a).media)*100)/mes); // ((pago por acao/ media)*100 )/ mes atual
					printf(" %6.2f ",res); //porcentagem por mes
					}else{
						printf("              ");
					}
				}			
				if((*a).proventosU > 0){
					printf(" >> %6.2f",(*a).proventosU);
				}else{
					printf("       ");
				}
	  
				if(res > 1.5){
					printf("  A");
				}else{
					if(res > 1){
						printf("  B");
					}else{
						if(res >= 0.5){
							printf("  C");
						}else{
							printf("   ");
						}
					}
				}
				printf("  %8.2f",(*a).compranova);			
			}
			QA += (*a).qnt;
			if((*a).prox==NULL){
				break;
			}
			printf("\n");
			a = (*a).prox;
				
			}while(1);
			printf("\n");
			printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
			if((*in).prox==NULL){
				break;
			}
			in = (*in).prox;
		}while(1);
		//ate agosto
		float poupanca = 3.9583 + 0.6767 + 0.6731;/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		printf("\n >>>>>    Total investido [%.2f] e total de proventos [%.2f] do ano atual [%6.2f] total [%.2f] vs [%.2f] poupança   <<<<< [%.2f]  ",totalinvestido,totalproventos,totaltotal,(totalproventos/totalinvestido)*100,poupanca,(divB/divA)*100);
		printf("%i papéis",QA);
	}
}


void mostrarC(struct dataCom *compra){
	int i = 1;
	do{
		printf(" \n");
		printf("%i° Compra : %s  ",i,(*compra).data);
		printf("Investidor: %s ",(*compra).nome);
		printf("[ %s ] ",(*compra).ativo);
		printf(" preço: %.2f",(*compra).preco);
		printf("  Quantidade: %.0f",(*compra).qnt);
		i+=1;
		if((*compra).prox == NULL)
			break;
			compra = (*compra).prox;			
	}while(1);
}

void mostrarR(struct dataCom *recibo){
	int i = 1;
		printf(" \n\n");
	do{
		//printf(" \n\n");
		printf("%i° Provento pago : %s  ",i,(*recibo).data);
		printf("Investidor: %s ",(*recibo).nome);
		printf("[ %s ] ",(*recibo).ativo);
		printf(" Valor: %.2f\n",(*recibo).preco);
		i+=1;
		if((*recibo).prox == NULL)
			break;
			recibo = (*recibo).prox;			
	}while(1);
}

int verificar(char *prim, char *seg){  //recebe duas strings e verifica se são iguais, independente se existe alguma em maiusculo ou minusculo
	do{
		if(*prim != *seg){
			if(*prim<*seg && 32+(int)*prim == (int)*seg){
				return 1; //iguais 
			}else if(*prim>*seg && (int)*prim == 32+(int)*seg){
				return 1; //iguais
			}else{
				return 0; //alguma letra diferente
				break;
			}
		}
		if((int)*prim != (int)*seg);
		prim+=1;
		seg+=1;
	}while(*prim != '\0' || *seg != '\0');
	return 1;
}

void adicionarVendas(struct gancho *g, char *nome_investidor, int qnt, char *nome_ativo, float preco, char *data ,float tx){ //falta teste ao adicionar a data
	struct acoes *a; //6
	struct dataCom *r;
	struct investidor *i;
	float media = 0;
	int res;
	
	if((*g).v == NULL){
		(*g).v = (struct dataCom*)malloc(sizeof(struct dataCom));
		r = (*g).v;
	}else{
		r = (*g).v;
	}
	
	if((*g).i==NULL){
		printf("(*g).i==NULL");
	}else{
		i = (*g).i;
	}
	
	if((*i).nome[0] == '\0'){
		printf("\nERRO, Não existe investidores [%s]",nome_investidor); //1
	}else{
		do{ //repetição até "break"  busca o investidor
			res = verificar((*i).nome,nome_investidor); //2
			if(res ==1){
				a =(*i).aprox; //5
				do{ // busca o ativo!!
					res = verificar((*a).ativo,nome_ativo); //4
					if(res==1){
						if(qnt > (*a).qnt){
							printf("\nNão tem como vender %i ativos da [%s] pois só existem %.0f ativos!!\n",qnt,nome_ativo,(*a).qnt);
							system("pause");
							break;
						}else{
							if((*a).media < preco){ //lucro
								(*i).lucro += (qnt * preco) - ((*a).media * qnt); 
							}else{ //perda
								(*i).perda += (qnt * preco) - ((*a).media * qnt); 
							}
						media = (*a).media;	
						(*i).valor -= (media * qnt);
						(*i).valorDoanoatual -= (media * qnt);
						if((*i).valorDoanoatual <0) (*i).valorDoanoatual = 0;
						//aqui deveria ter um if, caso valor menor que zero(negativo)
						(*a).compranova -= (preco * qnt);//aqui/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						(*a).qnt = (*a).qnt - qnt;
						(*a).nova -= qnt;
						if((*a).nova < 0) (*a).nova = 0;
						(*a).valorinvest = (*a).valorinvest - (media * qnt);
						(*a).taxa += tx;
						if((*a).qnt > 0){
							(*a).media = (*a).valorinvest / (*a).qnt;
						}else{
							(*a).valorinvest = 0;
						}
						
						
						//corrigirSaldo(g,nome_investidor,((preco * qnt)-tx));
						 if((*a).qnt == 0){ //9
							 (*a).media = 0; //qnt / (*a).valorinvest;
						 }
						if((*a).qnt < 0){//8 esse aqui tem que ser antes das alteraçoes, não? (*i).valor -= (preco * qnt);
							printf("\n [erro] quantidade não pode ser um número negativo!!\n");
						}
						if((*r).data[0] == '\0'){ //nao existe cria o primeiro
							string((*r).data,data,20);
							string((*r).nome,nome_investidor,10);
							string((*r).ativo,nome_ativo,7);
							(*g).vendas++;
							(*r).preco = preco;
							(*r).media = media;
							(*r).qnt = qnt;
							(*r).prox = NULL;
						}else{
							do{
							if((*r).prox == NULL){  //proximo é nullo?
								(*r).prox = (struct dataCom*)malloc(sizeof(struct dataCom));
								r = (*r).prox;
								iniciarDataCom(r);
								string((*r).data,data,20);
								string((*r).nome,nome_investidor,10);
								string((*r).ativo,nome_ativo,7);
								(*g).vendas++;
								(*r).preco = preco;
								(*r).media = media;
								(*r).qnt = qnt;
								(*r).prox = NULL;
								break;
							}
							r =(*r).prox;
							}while(1);
						}
						}
					break;
						
					}else{
						if((*a).prox==NULL){
							printf("\nAtivo não esta inserido!! [%s]",nome_ativo);
							break;
						}else{
							a = (*a).prox;
						}
					}
				}while(1);				
				break;
			}else{
				if((*i).prox == NULL){ //3
					printf("\nInvestidor não encontrado!!!!! [%s]",nome_investidor);
					break;
				}else{
					i = (*i).prox;
				}
			}
		}while(1);
	}
};


void data(char *data, int codigo_matricula){
	
	
	
}



void calculo(int codigo_data,char *data,float *valorp,char dig,int qnt, float IR){
	
	if(dig=='D' || dig == 'd'){
		dig = 'd';
		*valorp = ((*valorp * qnt)+0.005); //aqui
		int numero = (int)(*valorp*100);
		*valorp = ((float)numero)/100;
	}else if(dig=='J' || dig == 'j'){ // o erro esta por não limitar as casas decimais exemplo: 0.129 arredondaria para 0.12
		dig = 'j';
		*valorp = ((*valorp * qnt)*(1 - IR))+0.005;
		int numero = (int)(*valorp*100);
		*valorp = ((float)numero)/100;
	}else if(dig=='R' || dig == 'r'){
		dig = 'r';
		*valorp = (*valorp * qnt)+0.005; //nada acontece
		int numero = (int)(*valorp*100);
		*valorp = ((float)numero)/100;
	}else{
		if(dig=='C' || dig=='c'){
			*valorp = (*valorp * qnt)+0.005; //nada acontece
			int numero = (int)(*valorp*100);
			*valorp = ((float)numero)/100;
		}else{
			printf("\n houve algum erro [parte de digitos]\n");
		}		
	}
		
}

void teste(float valorp,char *nomei,char *nomea,char *data,char dig){
	
	if(valorp>0 && (nomea[2]!=' ' &&  nomea[0]!=' ' && data[3]!='f' && data[7]!='i' && data[6]!='ç')){ 
		//printf("\n%.4f %s %s %s %c",valorp,nomei,nomea,data,dig); //aquii	codigo_data removido
	}
}


void proventos_atual(struct gancho *g, char *nomei,char *nomea,char *data,float valorp,char dig,int qnt){  //correto
	
	struct investidor *in;
	struct dataCom *r;
	struct acoes *a;
	float res = 0, pagamento = 0,dividendos = 0;
	int tam;
	int codigo_data = 0;
	float valorpp; 
	float IR = 0.15;
	float imposto = 0;
	
	if(dig == 'J'|| dig =='j'){
		imposto = ((valorp * qnt) * IR);
	}
		
	in = (*g).i;
	
	if((*g).r==NULL){//recibos
		(*g).r = (struct dataCom*)malloc(sizeof(struct dataCom));
		r = (*g).r;
		iniciarDataCom(r);
	}else{
		r = (*g).r;
	}
		
	for(tam = 0; data[tam] != '\0'; tam++);
	int ano = (1000 *(data[tam-4]- '0')) + (100 *(data[tam-3]- '0')) + (10*(data[tam-2]- '0')) + ((data[tam-1]- '0'));
	

	pagamento = valorp;
	calculo(codigo_data,data,&valorp,dig,qnt,IR);
	dividendos = valorp; //aquii
		
	//teste(valorp,nomei,nomea,data,dig);	 //aquii
	
	
	if(qnt == 0){
		valorpp = 0; 
	}else{
		valorpp = pagamento; 
	}
		
	do{
		res = verificar((*in).nome,nomei);
			if(res == 1){
				res = 0;
				a =(*in).aprox;
				do{
					res = verificar((*a).ativo,nomea);
					if(res == 1){
						(*in).valor2 += valorp;
						(*in).valor3 += valorp;
						(*in).imposto += imposto;
						(*a).proventos += valorp;  //valorp é o provento pago
						(*a).proventosA += valorp;
						(*a).dividendos += dividendos;
						if(dig == 'D' || dig == 'd' || dig == 'J' || dig == 'j' || dig =='r' || dig == 'R'){
							(*a).proventosU = valorp;
						}						
						if((*a).ano == 0){ //pode ser que o ativo que comprou seja novo, então cuidado
							(*a).ano = ano;
							(*a).proventoPagoPorAtivo = valorpp;
							(*a).pagamentoA = pagamento;
							(*a).base = (*a).pagamentoA / (*a).media;
						}else{
							if((*a).ano == ano){
							(*a).pagamentoA += pagamento;
							(*a).proventoPagoPorAtivo += valorpp;
							(*a).base = (*a).pagamentoA / (*a).media;
							}else{
								if((*a).ano != ano){
								(*a).ano = ano;
								(*a).pagamentoA = pagamento;
								(*a).proventoPagoPorAtivo = valorpp;
								(*a).base = (*a).pagamentoA / (*a).media;
								}else{
								printf("\n DEU PAU!!!");
								}
							}
						}
												
						(*a).pagamentoT += pagamento; //total
						break;
					}else{
						if((*a).prox!= NULL){
							a =(*a).prox;
						}else{
							printf("Ativo do Investidor %s não existe!![ %s ]",(*in).nome,nomea);
							break;
						}
					}
				}while(1);
				break;	
			}else{
				if((*in).prox != NULL){
					in = (*in).prox;
				}else{
					printf("Investidor não encontrado!!");
					break;
				}
			}
	}while(1);
	
	if(data[0] == '\0' || data[0] == ' ' ){
		//nao faz nada
	}else{
		
	if((*r).data[0] == '\0'){ //nao existe cria o primeiro
		string((*r).data,data,20);
		string((*r).nome,nomei,10);
		string((*r).ativo,nomea,7);
		(*g).recibos++;
		(*r).preco = valorp;
		(*r).obs = dig;
		(*r).prox = NULL;
	}else{
		do{
			if((*r).prox == NULL){  //proximo é nullo?
					(*r).prox = (struct dataCom*)malloc(sizeof(struct dataCom));
					r = (*r).prox;
					iniciarDataCom(r);
					string((*r).data,data,20);
					string((*r).nome,nomei,10);
					string((*r).ativo,nomea,7);
					(*g).recibos++;
					(*r).preco = valorp;
					(*r).obs = dig;
					(*r).prox = NULL;
				break;
			}
		r =(*r).prox;
		}while(1);
	}
	}
}

void proventos__atual(struct gancho *g, char *nomei,char *nomea,char *data,float valorp,char dig,int qnt, float IR){  //correto
	
	struct investidor *in;
	struct dataCom *r;
	struct acoes *a;
	float res = 0, pagamento = 0,dividendos = 0;
	int tam;
	int codigo_data = 0;
	float valorpp; 
	float imposto;
	if(dig == 'J'|| dig =='j'){
		imposto = ((valorp * qnt) * IR);
	}
		
	in = (*g).i;
	
	if((*g).r==NULL){//recibos
		(*g).r = (struct dataCom*)malloc(sizeof(struct dataCom));
		r = (*g).r;
		(*g).recibos++;
		iniciarDataCom(r);
	}else{
		r = (*g).r;
	}
		
	for(tam = 0; data[tam] != '\0'; tam++);
	int ano = (1000 *(data[tam-4]- '0')) + (100 *(data[tam-3]- '0')) + (10*(data[tam-2]- '0')) + ((data[tam-1]- '0'));
	pagamento = valorp;
	calculo(codigo_data,data,&valorp,dig,qnt,IR);
	dividendos = valorp;
	//teste(valorp,nomei,nomea,data,dig);	
	
	
	if(qnt == 0){
		valorpp = 0; 
	}else{
		valorpp = pagamento; 
	}
		
	do{
		res = verificar((*in).nome,nomei);
			if(res == 1){
				res = 0;
				a =(*in).aprox;
				do{
					res = verificar((*a).ativo,nomea);
					if(res == 1){
						(*in).valor2 += valorp;
						(*in).valor3 += valorp;
						(*in).imposto += imposto;
						(*a).proventos += valorp;  //valorp é o provento pago
						(*a).proventosA += valorp; 
						(*a).dividendos += dividendos;
						if(dig == 'D' || dig == 'd' || dig == 'J' || dig == 'j' || dig =='r' || dig == 'R'){
							(*a).proventosU = valorp;
						}						
						if((*a).ano == 0){ //pode ser que o ativo que comprou seja novo, então cuidado
							(*a).ano = ano;
							(*a).proventoPagoPorAtivo = valorpp;
							(*a).pagamentoA = pagamento;
							(*a).base = (*a).pagamentoA / (*a).media;
						}else{
							if((*a).ano == ano){
							(*a).pagamentoA += pagamento;
							(*a).proventoPagoPorAtivo += valorpp;
							(*a).base = (*a).pagamentoA / (*a).media;
							}else{
								if((*a).ano != ano){
								(*a).ano = ano;
								(*a).pagamentoA = pagamento; //ooo
								(*a).proventoPagoPorAtivo = valorpp;
								(*a).base = (*a).pagamentoA / (*a).media;
								}else{
								printf("\n DEU PAU!!!");
								}
							}
						}
												
						(*a).pagamentoT += pagamento; //total
						break;
					}else{
						if((*a).prox!= NULL){
							a =(*a).prox;
						}else{
							printf("Ativo do Investidor %s não existe!![ %s ]",(*in).nome,nomea);
							break;
						}
					}
				}while(1);
				break;	
			}else{
				if((*in).prox != NULL){
					in = (*in).prox;
				}else{
					printf("Investidor não encontrado!!");
					break;
				}
			}
	}while(1);
	
	if(data[0] == '\0' || data[0] == ' ' ){
		//nao faz nada
	}else{
		
	if((*r).data[0] == '\0'){ //nao existe cria o primeiro
		string((*r).data,data,20);
		string((*r).nome,nomei,10);
		string((*r).ativo,nomea,7);
		(*g).recibos++;
		(*r).preco = valorp;
		(*r).obs = dig;
		(*r).prox = NULL;
	}else{
		do{
			if((*r).prox == NULL){  //proximo é nullo?
					(*r).prox = (struct dataCom*)malloc(sizeof(struct dataCom));
					r = (*r).prox;
					iniciarDataCom(r);
					string((*r).data,data,20);
					string((*r).nome,nomei,10);
					string((*r).ativo,nomea,7);
					(*g).recibos++;
					(*r).preco = valorp;
					(*r).obs = dig;
					(*r).prox = NULL;
				break;
			}
		r =(*r).prox;
		}while(1);
	}
	}
}

void iniciarInvestidor(struct investidor *inicio){
	(*inicio).elementos_ativos = 0;
	(*inicio).nome[0] = '\0';
	(*inicio).saldo = 0;
	(*inicio).ativos = 0;
	(*inicio).taxaBolsa = 0;
	(*inicio).lucro = 0.0;
	(*inicio).perda = 0.0;
	(*inicio).fimobiliario = 0;
	(*inicio).valor = 0;
	(*inicio).valorReinvestido = 0;
	(*inicio).valorDoanoatual = 0;
	(*inicio).valor2 = 0;
	(*inicio).valor3 = 0;
	(*inicio).imposto = 0;
	(*inicio).aprox = NULL;
	(*inicio).prox = NULL;
};

void iniciarinvestidor(struct investidor *inicio){
	(*inicio).saldo = 0;
}

void iniciarAtivo(struct acoes *acoes){
	(*acoes).ativo[0] = '\0';
	(*acoes).qnt = 0;
	(*acoes).ativobonus = 0;
	(*acoes).media = 0;
	(*acoes).P_media = 0;
	(*acoes).valorinvest = 0;
	(*acoes).pagamentoA = 0;
	(*acoes).taxa = 0; 
	(*acoes).ano = 0;
	(*acoes).dividendos = 0;
	(*acoes).proventos = 0;
	(*acoes).proventosA = 0;
	(*acoes).proventosU = 0;
	(*acoes).proventoPagoPorAtivo = 0;
	(*acoes).base = 0;
	(*acoes).reinvestido = 0;
	(*acoes).nova = 0;
	(*acoes).compranova = 0;
	(*acoes).prox = NULL;	
}


void iniciarDataCom(struct dataCom *compra){
	(*compra).data[0] = '\0';
	(*compra).nome[0] = '\0';
    (*compra).ativo[0] = '\0';
    (*compra).obs = ' ';
	(*compra).preco = 0;
	(*compra).qnt = 0;
	(*compra).media = 0;
	(*compra).prox = NULL;
}

void iniciaResultados(struct resultado *res){
	(*res).ano = 0;
	(*res).prox = NULL;
	(*res).proximo = NULL;
}

void i_gancho(struct gancho *g){
	(*g).ano = 0;
	(*g).investidores = 0;
	(*g).vendas = 0;
	(*g).compras = 0;
	(*g).recibos = 0;
	(*g).c = NULL;
	(*g).i = NULL;
	(*g).r = NULL;
	(*g).v = NULL;
	(*g).R = NULL;
}

void observacoes(){
	printf("\n Tem 63 acoes de diferenca da klabin , adicionadas abaixo pois não comprei, mas consta la na b3\n");
	printf("\nTive que adiciona-las porque ia dar diferença no cálculo de proventos\n");
	printf("\nForam adicionadas antes da data 05/08/2024 (dataCom) porque recebi proventos dia \n 15 de agosto relacionado a (701) total sendo (638) compradas \n");
};


void bonus(struct gancho *g,char *investidor,int qnt,char *ativo,char *data){
	
	struct dataCom *c;
	struct investidor *i;
	struct acoes *a;
	int res = 0;
	
	i = (*g).i;
	c = (*g).c;
	
	do{
		res = verificar((*i).nome,investidor);
			if(res == 1){
				a = (*i).aprox;
				do{
					res = verificar((*a).ativo,ativo);
					if(res == 1){
					(*a).qnt += qnt;
					(*a).ativobonus = qnt;
					(*a).media = (*a).valorinvest / (*a).qnt;
					break;
					}else{
						if((*a).prox != NULL){
							a = (*a).prox;
						}else{
							printf("\nHouve algum erro ou não existe dados correspondentes ao [bonus]\n");
							break;
						}
					}
				}while(1);
				
			break;	
			}else{
				if((*i).prox != NULL){
					i = (*i).prox;
				}else{
					printf("\nHouve algum erro ou não existe dados correspondentes ao [bonus]\n");
					break;
				}
			}
	}while(1);
		
	if((*c).data[0] == '\0'){
		string((*c).data,data,20);
		string((*c).nome,investidor,10);
		string((*c).ativo,ativo,7);
		(*g).compras++;
		(*c).preco = 0;
		(*c).qnt = qnt;
		(*c).prox = NULL;
	}else{
		do{
			if((*c).prox == NULL){
					(*c).prox = (struct dataCom*)malloc(sizeof(struct dataCom));
					c = (*c).prox;
					iniciarDataCom(c);
					string((*c).data,data,20);
					string((*c).nome,investidor,10);
					string((*c).ativo,ativo,7);
					(*g).compras++;
					(*c).preco = 0;
					(*c).qnt = qnt;
					(*c).prox = NULL;
				break;
			}
		c =(*c).prox;
		}while(1);
	}
}

void gambiarra(struct investidor *in){ //resetar o valor pago por proventos DIVIDENDOS
	struct acoes *a;
	do{
		(*in).valor3 = 0;  //valor investido atual
		a = (*in).aprox;
		do{
			//(*a).proventosA = 0; //proventos pago por ativo atual
			if((*a).prox == NULL){
				break;
			}else{
				a = (*a).prox;
			}
		}while(1);
		if((*in).prox==NULL){
			break;
		}else{
			in = (*in).prox;
		}
	}while(1);
}

void gambiarra2(struct gancho *g){ //RESETAR AS AÇOES COMPRADAS NO ANO ATUAL
	//gambiarra
	struct investidor *in;
	
	in = (*g).i;
	
	struct acoes *a;
	
	do{
		(*in).valorDoanoatual = 0;
		a = (*in).aprox;
		do{
			(*a).nova = 0; // novas ações
			(*a).compranova = 0; //valor investido atualmente
			(*a).proventosA = 0;
			(*a).pagamentoA = 0; //ooo ano atual  //ooo
			(*a).reinvestido = 0;
			(*a).base = 0;
			(*a).P_media = (*a).media;
			if((*a).prox == NULL){
				break;
			}else{
				a = (*a).prox;
			}
		}while(1);
				
		if((*in).prox ==NULL){
			break;
		}else{
			in = (*in).prox;
		}
	}while(1);
	
}

void ordenar(struct gancho *g, int op){
	struct investidor *in;
	struct acoes *a,*pivo = NULL,*aux,*compara; 
	aux = NULL;
	/*
	 está percorrendo todos os elementos...
	*/
	
	if(op < 1 || op > 6){
		printf("\nOpção inválida!!\n");
	}else{
		
	in = (*g).i;
	do{ // investidores 
		a = (*in).aprox;
		do{	//ativos		
			if((*a).prox == NULL){
				break;
			}else{
				compara = (*a).prox;
			}
			do{// elemento de comparaçao
				
				if(op == 1){
						if(pivo == NULL){
							if((*a).media > (*compara).media){ //media como referencia
							pivo = compara;
							  }	
						}else{
							if((*pivo).media > (*compara).media){
							pivo = compara;
							}
						}
						if((*compara).prox != NULL){
							compara = (*compara).prox;
						}else{
							break;
						}
				}else{
					if(op == 2){
						if(pivo == NULL){
							if((*a).qnt < (*compara).qnt){ 
							pivo = compara;
							  }	
						}else{
							if((*pivo).qnt < (*compara).qnt){
							pivo = compara;
							}
						}
						if((*compara).prox != NULL){
							compara = (*compara).prox;
						}else{
							break;
						}
					}else{
						if(op == 3){
							if(pivo == NULL){
							if((*a).valorinvest < (*compara).valorinvest){ 
							pivo = compara;
							  }	
						}else{
							if((*pivo).valorinvest < (*compara).valorinvest){
							pivo = compara;
							}
						}
						if((*compara).prox != NULL){
							compara = (*compara).prox;
						}else{
							break;
						}
						}
						else{
							if(op == 4 ){
								if(pivo == NULL){
									if((*a).pagamentoA < (*compara).pagamentoA){ 
									pivo = compara;
				  	  	  	  	  }	
							}else{
								if((*pivo).pagamentoA < (*compara).pagamentoA){
								pivo = compara;
								}
							}
							if((*compara).prox != NULL){
								compara = (*compara).prox;
								}else{
									break;
								}
							}else{
								if(op == 5){
									   if(pivo == NULL){
										if((*a).base < (*compara).base){ 
										pivo = compara;
							  	  	  }	
									}else{
										if((*pivo).base < (*compara).base){
										pivo = compara;
										}
									}
									if((*compara).prox != NULL){
										compara = (*compara).prox;
									}else{
										break;
				  	  	  	        }	  	
								}
								else{
									if(op == 6){
									   if(pivo == NULL){
										if((((*a).valorinvest/(*in).valor)*100) < (((*compara).valorinvest/(*in).valor)*100)){ 
										pivo = compara;
	  	  	  	  	  	  	  	  	    }	
									}else{
										if((((*pivo).valorinvest/(*in).valor)*100) < (((*compara).valorinvest/(*in).valor)*100)){
										pivo = compara;
										}
									}
									if((*compara).prox != NULL){
										compara = (*compara).prox;
									}else{
										break;
				  	  	  	        }	
									}else{
									printf("\nOpção inválida!![%i]\n",op);
									break;
									}
								}
							}
						}
					}
				}
			}while(1); // elemento de comparaçao
			if(pivo!= NULL){
				//printf("\nEle irá trocar %s por %s",(*pivo).ativo,(*a).ativo);
				struct acoes *aux = pivo;
				troca(in,a,pivo,g);//// in = inicio da lista // a = elemento da lista // pivo é o elemento a ficar em primeiro!! // g possui todas as listas 
				a = aux;
			}
			if((*a).prox != NULL){
				a = (*a).prox;
			}else{
				break;
			}
			pivo = NULL;
		}while(1); //ativos
		if((*in).prox != NULL){
			in = (*in).prox;
		}else{
			break;
		}
	}while(1);
	}
}

void troca(struct investidor *in,struct acoes *a,struct acoes *pivo,struct gancho *g){
	struct acoes *aux1 = NULL,*aux2 = NULL,*cont;
	cont = (*in).aprox;
	do{
		if((*cont).prox == a){ //para pegar o nó antes do 1° elemento a ser comparado
			aux1 = cont;
		}
		if((*cont).prox == pivo){ // para pegar o nó antes do 2° elemento a ser comparado [pivô] 
			aux2 = cont;
		}
		if((*cont).prox != NULL){ // para percorrer a lista até o fim
			cont = (*cont).prox;
		}else{
			break; // chegou ao fim, sai do loop
		}
	}while(1);
	//o elemento a ser trocado é o primeiro e o comparado não é vizinho!!	
	if(aux1 == NULL && aux2 != a){ // sabe que o elemento de troca é o primeiro elemento!!
		struct acoes *aux3; // para guardar o endereço do nó seguinte ....
		//aux3 = (*pivo).prox;    abaixo
	   	 aux3 = (*pivo).prox; 
		(*in).aprox = pivo;
		(*pivo).prox = (*a).prox;
		(*aux2).prox = a;
		(*a).prox = aux3;
	}else{
		//os elementos a serem trocados sao vizinhos e um deles é o primeiro
		if(aux1 == NULL){
			struct acoes *aux3;
			aux3 = (*pivo).prox; 
			(*in).aprox = pivo;
			(*pivo).prox = a;
			(*a).prox = aux3;
		}else{		
			if(aux2 == a){
				//os elementos a serem trocados sao vizinhos e !!
				 struct acoes *aux3;
				aux3 = (*pivo).prox;
				(*aux1).prox = pivo;
				(*pivo).prox = a;
				(*a).prox = aux3;
			}
			else{
				// o elemento a ser trocado é o último
				//printf("\no elemento a ser trocado é o último\n");
				// os elementos a serem trocados são distantes e no meio da lista!!
				struct acoes *aux3;
				aux3 = (*pivo).prox;
				(*aux1).prox = pivo;
				(*pivo).prox = (*a).prox;
				(*aux2).prox = a;
				(*a).prox = aux3;
			}
		}		
	}
}

void corrigirSaldo(struct gancho *g, char *nome, float valor){
	struct investidor *in;
	int res = 0;
	in = (*g).i;
	
	do{
		res = verificar((*in).nome,nome); 
		if(res ==1){
			(*in).saldo += valor;
			res = 0;
		break;
		}else{
			if((*in).prox != NULL){
				in = (*in).prox;
			}else{
				printf("\nInvestidor não encontrado para corrigir saldo");
				system("pause");
			}
		}
	}while(1);
}

void split(struct gancho *g,char *nome, char *ativo, int x, int y,float valor){
	int res = 0;
	struct acoes *a;
	struct investidor *in;
	in = (*g).i;
	int multiplicador;
	do{
		res = verificar((*in).nome,nome); 
		if(res == 1){
			res = 0;
				a = (*in).aprox;
				do{
					res = verificar((*a).ativo,ativo);
					if(res==1){
						multiplicador = (*a).qnt * (y - x);
						(*a).qnt +=  multiplicador;
						(*a).media = (*a).media/y;
						int temp =((int)(100*((*a).pagamentoA/y)));
						float temp2 = (float)temp;
						temp2 = temp2/100;
						///O CORRETO SERIA CORRIGIR TODOS OS VALORES RECEBIDOS POR ATIVO, Já QUE È UMA MÈTRICA DE QUANTO ESTÀ RECEBENDO EM %
						(*a).pagamentoA = ((*a).pagamentoA - valor) + temp2;
						(*a).proventoPagoPorAtivo = ((*a).proventoPagoPorAtivo - valor) +temp2;
						(*a).base = (*a).pagamentoA / (*a).media;
						break;
/////////////////////					
					}else{
						if((*a).prox != NULL){
							a = (*a).prox;
						}else{
							printf("\n Ativo não encontrado para a alteração!! ");
						}
					}
				}while(1);
			break;
		}else{
			if((*in).prox != NULL){
				in = (*in).prox;
			}else{
				printf("\ninvestidor não encontrado para transferência");
			}
		} 	
	}while(1);	
}

void transferencia(struct gancho *g, char *vendedor, char *nomeativo,int qnt, char *comprador){
	
	int res = 0;
	struct acoes *a;
	struct investidor *in;
	in = (*g).i;
	float saldo = 0;
	do{
		res = verificar((*in).nome,vendedor); 
		if(res == 1){
			res = 0;
				a = (*in).aprox;
				do{
					res = verificar((*a).ativo,nomeativo);
					if(res==1){
						if((*a).qnt < qnt){
							printf("\n transferência não concluída porque possui menos ativos que a quantidade para retirar");
						}else{
							(*a).qnt -= qnt;
							(*a).valorinvest -= ((*a).media * qnt);
							saldo = (*a).media * qnt;
							(*in).valorDoanoatual -= saldo;
							(*in).valor -= saldo;
							(*in).saldo += saldo;
						}
						break;
					}else{
						if((*a).prox != NULL){
							a = (*a).prox;
						}else{
							printf("\n Ativo não encontrado para transferência!! ");
						}
					}
				}while(1);
			break;
		}else{
			if((*in).prox != NULL){
				in = (*in).prox;
			}else{
				printf("\ninvestidor não encontrado para transferência");
			}
		} 	
	}while(1);
	investimento_atual(g,comprador,qnt,nomeativo,(*a).media,"troca",0);
}

void Compra2023(struct gancho *g){
	investimento_atual(g,"Gilmar",66,"PETR4",29.41203007518797,"30/junho/2023",0.64); 
	investimento_atual(g,"Getúlio",67,"PETR4",29.41203007518797,"30/junho/2023",0.64); 
	investimento_atual(g,"Gilmar",69,"PETR4",28.22,"17/julho/2023",0.69);
	investimento_atual(g,"Gilmar",203,"KLBN4",4.52,"02/agosto/2023",0.31);		
	investimento_atual(g,"Gilmar",179,"CXSE3",10.91402234636872,"04/agosto/2023",0.65);
	investimento_atual(g,"Gilmar",435,"KLBN4",4.50,"18/agosto/2023",0.65);
	investimento_atual(g,"Gilmar",1,"PETR4",32.35,"04/setembro/2023",0.02);
	investimento_atual(g,"Gilmar",100,"PETR4",33.24,"05/setembro/2023",1.09);
	investimento_atual(g,"Gilmar",83,"PETR4",35.27,"01/novembro/2023",0.96);
	investimento_atual(g,"Gilmar",98,"PETR4",34.92298245614035,"07/novembro/2023",1.12);
	investimento_atual(g,"Gilmar",15,"PETR4",34.92298245614035,"07/novembro/2023",0.18);
	investimento_atual(g,"Gilmar",1,"PETR4",34.92298245614035,"07/novembro/2023",0.02);
	Proventos2023(g);
}

void Compra2024(struct gancho *g){
	gambiarra2(g);
	bonus(g,"Gilmar",63,"KLBN4","17/abril/2024"); 
	investimento_atual(g,"Gilmar",12,"PETR4",35.94,"02/agosto/2024",0.14);
	investimento_atual(g,"Gilmar",200,"BMGB4",3.96,"06/dezembro/2024",0.26); 
	investimento_atual(g,"Gilmar",50,"TAEE4",11.04,"26/dezembro/2024",0.18);
	investimento_atual(g,"Gilmar",50,"RURA11",7.49,"26/dezembro/2024",0.13);
	investimento_atual(g,"Gilmar",43,"CMIG4",11.01,"30/dezembro/2024",0.16);
	Proventos2024(g);
}

void Compra2025(struct gancho *g){
	gambiarra2(g);
	investimento_atual(g,"Gilmar",57,"CMIG4",10.91,"06/janeiro/2025",0.18); 
	investimento_atual(g,"Gilmar",50,"TAEE4",10.98,"06/janeiro/2025",0.18);	
	investimento_atual(g,"Gilmar",50,"BBAS3",24.34,"07/janeiro/2025",0.40);
	investimento_atual(g,"Gilmar",50,"TAEE4",11.11,"07/janeiro/2025",0.18);
	investimento_atual(g,"Gilmar",99,"KLBN4",4.44,"09/janeiro/2025",0.15);
	investimento_atual(g,"Gilmar",14,"PETR4",34.50,"10/março/2025",0.16);
	investimento_atual(g,"Eliana",86,"PETR4",34.50,"10/março/2025",0.96);  //(2.973,88)
	investimento_atual(g,"Gilmar",100,"PETR4",34.50,"10/março/2025",1.12);
	investimento_atual(g,"Gilmar",300,"KLBN4",3.89,"12/março/2025",0.38);
	investimento_atual(g,"Gilmar",50,"RURA11",7.84,"26/março/2025",0.13);
	investimento_atual(g,"Gilmar",100,"KLBN4",3.83,"26/março/2025",0.13);
	adicionarVendas(g,"Gilmar",100,"CMIG4",10.86,"24/março/2025",0.35);  //venda
	adicionarVendas(g,"Gilmar",200,"BMGB4",3.88,"28/março/2025",0.25);  //venda
	investimento_atual(g,"Gilmar",200,"KLBN4",3.88,"28/março/2025",0.25);
	investimento_atual(g,"Gilmar",50,"BBDC3",11.13,"02/abril/2025",0.18);
	investimento_atual(g,"Gilmar",50,"BRBI11",13.60,"02/abril/2025",0.22);
	investimento_atual(g,"Gilmar",50,"PETR4",32.90,"08/abril/2025",0.54);
	investimento_atual(g,"Eliana",64,"PETR4",30.95,"19/abril/2025",0.54);  // (1.974,4)
	investimento_atual(g,"Eliana",32,"PETR4",30.57,"24/abril/2025",0.32);  //(978,24)
	investimento_atual(g,"Eliana",37,"BBAS3",27.50,"24/abril/2025",0.33); // (1.017,5)
	investimento_atual(g,"Gilmar",26,"CXCE11",39.00,"24/maio/2025",0.33);
	investimento_atual(g,"Gilmar",150,"RZAG11",8.93,"30/maio/2025",0.44);
	investimento_atual(g,"Gilmar",150,"XPCA11",7.81,"30/maio/2025",0.39);
	investimento_atual(g,"Gilmar",147,"RURA11",8.69,"30/maio/2025",0.37);
	investimento_atual(g,"Gilmar",6,"PETR4",31.60,"30/maio/2025",0.07);
	investimento_atual(g,"Eliana",115,"RURA11",8.69,"30/maio/2025",0.37);  //(999,35)
	investimento_atual(g,"Gilmar",200,"RZAG11",8.83,"04/junho/2025",0.58);
	investimento_atual(g,"Gilmar",50,"CMIG4",10.76,"04/junho/2025",0.18);
	investimento_atual(g,"Gilmar",15,"BBAS3",22.70266666666667,"04/junho/2025",0.04);
	investimento_atual(g,"Gilmar",24,"CXCE11",39.90416666666667,"04/junho/2025",0.31);
	investimento_atual(g,"Gilmar",200,"BMGB4",3.71,"04/junho/2025",0.24); 
	investimento_atual(g,"Gilmar",10,"BBAS3",22.39,"05/junho/2025",0.08);
	investimento_atual(g,"Gilmar",10,"PETR4",29.52,"05/junho/2025",0.10);
	investimento_atual(g,"Gilmar",10,"BBAS3",21.80,"06/junho/2025",0.08);
	investimento_atual(g,"Gilmar",10,"BBAS3",21.83,"09/junho/2025",0.08);
	investimento_atual(g,"Gilmar",50,"XPCA11",7.78,"09/junho/2025",0.13);
	investimento_atual(g,"Gilmar",50,"SYNE3",5.554,"11/junho/2025",0.07);
	investimento_atual(g,"Gilmar",9,"KLBN4",3.61,"12/junho/2025",0.02);
	investimento_atual(g,"Gilmar",12,"KLBN4",3.67,"13/junho/2025",0.02);
	investimento_atual(g,"Gilmar",10,"PETR4",32.62,"16/junho/2025",0.11);
	investimento_atual(g,"Gilmar",10,"BBAS3",22.03,"16/junho/2025",0.08);
	investimento_atual(g,"Gilmar",79,"KLBN4",3.682025316455696,"16/junho/2025",0.08);
	investimento_atual(g,"Gilmar",20,"RURA11",8.23,"16/junho/2025",0.06);
	investimento_atual(g,"Gilmar",15,"BBAS3",21.93,"17/junho/2025",0.11);
	investimento_atual(g,"Gilmar",10,"KLBN4",3.61,"17/junho/2025",0.02);
	investimento_atual(g,"Gilmar",10,"BBSE3",35.52,"18/junho/2025",0.12);
	investimento_atual(g,"Gilmar",50,"SYNE3",6.04,"18/junho/2025",0.10);
	investimento_atual(g,"Gilmar",60,"KLBN4",3.58,"18/junho/2025",0.07);
	investimento_atual(g,"Gilmar",50,"RZAG11",8.88,"18/junho/2025",0.15);
	investimento_atual(g,"Gilmar",10,"BBAS3",21.80,"18/junho/2025",0.07);
	investimento_atual(g,"Gilmar",18,"RURA11",8.20,"20/junho/2025",0.05);
	investimento_atual(g,"Gilmar",45,"BBAS3",21.652,"20/junho/2025",0.04);
	investimento_atual(g,"Gilmar",100,"KLBN4",3.54,"20/junho/2025",0.12);
	investimento_atual(g,"Gilmar",5,"DIRR3",42.00,"20/junho/2025",0.07);
	investimento_atual(g,"Gilmar",5,"VALE3",50.00,"20/junho/2025",0.08);
	investimento_atual(g,"Gilmar",10,"BBAS3",21.17,"23/junho/2025",0.07);
	investimento_atual(g,"Gilmar",10,"PETR4",32.43,"23/junho/2025",0.11);
	investimento_atual(g,"Gilmar",50,"KLBN4",3.50,"25/junho/2025",0.06);
	investimento_atual(g,"Gilmar",10,"BBAS3",21.41,"26/junho/2025",0.07);
	investimento_atual(g,"Gilmar",50,"CXCE11",38.894,"03/julho/2025",0.63);
	investimento_atual(g,"Gilmar",150,"RURA11",8.16,"03/julho/2025",0.40);
	investimento_atual(g,"Gilmar",110,"XPCA11",7.88,"03/julho/2025",0.29);
	investimento_atual(g,"Gilmar",2,"FLRY3",12.98,"03/julho/2025",0.01);
	investimento_atual(g,"Gilmar",123,"RURA11",8.18,"07/julho/2025",0.33);
	investimento_atual(g,"Gilmar",87,"XPCA11",7.91,"07/julho/2025",0.23);
	investimento_atual(g,"Gilmar",1,"KLBN4",3.80,"07/julho/2025",0.01);
	investimento_atual(g,"Gilmar",100,"KLBN4",3.70,"09/julho/2025",0.12);
	investimento_atual(g,"Gilmar",53,"XPCA11",7.93,"09/julho/2025",0.14);
	investimento_atual(g,"Gilmar",150,"VGIA11",9.25,"09/julho/2025",0.45);
	investimento_atual(g,"Gilmar",21,"CXSE3",14.57,"10/julho/2025",0.10);
	investimento_atual(g,"Gilmar",100,"CXSE3",14.57,"10/julho/2025",0.48);
	reinvestimento(g,"Gilmar",11,"RURA11",8.17,"14/julho/2025",0.03); 
	investimento_atual(g,"Gilmar",40,"CXSE3",14.43,"15/julho/2025",0.19);
	reinvestimento(g,"Gilmar",10,"KLBN4",3.83,"15/julho/2025",0.02);
	investimento_atual(g,"Gilmar",71,"BMGB4",3.74,"16/julho/2025",0.09); 
	transferencia(g,"Eliana","BBAS3",12,"Gilmar");// Gilmar comprou de eliana 12 ações por 27,50 cada cota 06/08/25 (330,00)
	corrigirSaldo(g,"Eliana",-330);
	investimento_atual(g,"Eliana",40,"RURA11",8.13,"06/agosto/2025",0.11);
	investimento_atual(g,"Gilmar",30,"KLBN4",3.61,"06/agosto/2025",0.04);
	investimento_atual(g,"Gilmar",5,"BBAS3",18.76,"06/agosto/2025",0.04);
	investimento_atual(g,"Gilmar",10,"VGIA11",9.07,"07/agosto/2025",0.03);
	investimento_atual(g,"Gilmar",14,"VGIA11",9.13,"11/agosto/2025",0.05);
	split(g,"Gilmar","DIRR3",1,3,2.0); //11 de agosto de 2025  o último valor é o valor a ser corrigido, pode inserir o total!!
	reinvestimento(g,"Gilmar",5,"BBAS3",19.98,"15/agosto/2025",0.04); 
	reinvestimento(g,"Gilmar",5,"PETR4",30.05,"15/agosto/2025",0.05); 
	reinvestimento(g,"Gilmar",14,"RURA11",8.09,"19/agosto/2025",0.04);
	reinvestimento(g,"Gilmar",5,"PETR4",30.324,"20/agosto/2025",0.05);
	reinvestimento(g,"Gilmar",5,"BBAS3",19.75,"20/agosto/2025",0.04); 
	reinvestimento(g,"Gilmar",22,"RURA11",8.06,"22/agosto/2025",0.06); 
	reinvestimento(g,"Gilmar",15,"VGIA11",9.19,"04/setembro/2025",0.05); 
	investimento_atual(g,"Gilmar",50,"VGIA11",9.27,"05/setembro/2025",0.15);
	reinvestimento(g,"Gilmar",26,"KLBN4",3.70,"12/setembro/2025",0.04); // de xpca11 e rzag11
	investimento_atual(g,"Gilmar",5,"PETR4",31.29,"15/setembro/2025",0.06);
	investimento_atual(g,"Gilmar",5,"CXCE11",40.728,"15/setembro/2025",0.07);
	investimento_atual(g,"Gilmar",100,"KLBN4",3.68,"15/setembro/2025",0.12);
	investimento_atual(g,"Gilmar",5,"BBAS3",22.20,"15/setembro/2025",0.04);
	investimento_atual(g,"Gilmar",5,"BBSE3",32.004,"15/setembro/2025",0.06);
	investimento_atual(g,"Gilmar",15,"RURA11",8.21,"15/setembro/2025",0.04);
	investimento_atual(g,"Gilmar",27,"KLBN4",3.67,"16/setembro/2025",0.04);
	reinvestimento(g,"Gilmar",7,"RURA11",8.22,"22/setembro/2025",0.02); //da petr4
	reinvestimento(g,"Gilmar",27,"RURA11",8.18,"03/outubro/2025",0.08); //da Syne3
	investimento_atual(g,"Gilmar",50,"RURA11",8.18,"06/outubro/2025",0.14);
	investimento_atual(g,"Gilmar",10,"PETR4",31.00,"06/outubro/2025",0.10);
	investimento_atual(g,"Gilmar",30,"VGIA11",9.70,"07/outubro/2025",0.10);
	investimento_atual(g,"Gilmar",20,"RURA11",8.19,"07/outubro/2025",0.06);
	reinvestimento(g,"Gilmar",29,"KLBN4",3.50,"14/outubro/2025",0.04); // RZAG11 e XPCA11
	reinvestimento(g,"Gilmar",14,"KLBN4",3.50,"15/outubro/2025",0.02); //CXCE11
	investimento_atual(g,"Gilmar",14,"RURA11",8.23,"22/outubro/2025",0.04);
	investimento_atual(g,"Gilmar",2,"PETR4",30.35,"23/outubro/2025",0.02);
	investimento_atual(g,"Gilmar",4,"PETR4",29.90,"28/outubro/2025",0.04);
	adicionarVendas(g,"Gilmar",493,"RURA11",8.13,"03/novembro/2025",1.29);
	adicionarVendas(g,"Gilmar",200,"RZAG11",9.06,"03/novembro/2025",0.58);
	investimento_atual(g,"Gilmar",5,"RZTR11",91.94,"04/novembro/2025",0.15);
	investimento_atual(g,"Gilmar",25,"PETR4",30.038,"04/novembro/2025",0.10);
	investimento_atual(g,"Gilmar",10,"RZTR11",91.99,"05/novembro/2025",0.30);
	investimento_atual(g,"Gilmar",300,"KLBN4",3.61,"10/novembro/2025",0.24);
	investimento_atual(g,"Gilmar",10,"BBAS3",22.85,"10/novembro/2025",0.08);
	investimento_atual(g,"Gilmar",10,"PETR4",32.15,"10/novembro/2025",0.11);
	investimento_atual(g,"Gilmar",20,"SYNE3",4.90,"10/novembro/2025",0.04);
	investimento_atual(g,"Gilmar",100,"KLBN4",3.60,"10/novembro/2025",0.12);
	investimento_atual(g,"Gilmar",20,"KLBN4",3.60,"14/novembro/2025",0.03);
	investimento_atual(g,"Gilmar",1,"RZTR11",93.94,"17/novembro/2025",0.04);
	investimento_atual(g,"Gilmar",1,"RZTR11",93.52,"19/novembro/2025",0.04);
	investimento_atual(g,"Gilmar",3,"RZTR11",94.17,"21/novembro/2025",0.10);
	investimento_atual(g,"Gilmar",12,"KLBN4",3.53,"21/novembro/2025",0.02);
	investimento_atual(g,"Gilmar",100,"KLBN4",3.53,"24/novembro/2025",0.12);
	investimento_atual(g,"Gilmar",100,"KLBN4",3.64,"04/dezembro/2025",0.12);
	investimento_atual(g,"Gilmar",1,"RZTR11",94.49,"05/dezembro/2025",0.04);
	investimento_atual(g,"Gilmar",18,"KLBN4",3.74,"05/dezembro/2025",0.03);
	investimento_atual(g,"Gilmar",4,"RZTR11",94.45,"08/dezembro/2025",0.13);
	investimento_atual(g,"Gilmar",10,"PETR4",31.59,"08/dezembro/2025",0.11);
	investimento_atual(g,"Gilmar",100,"KLBN4",3.75,"08/dezembro/2025",0.12);
	investimento_atual(g,"Gilmar",5,"CXCE11",40.85,"08/dezembro/2025",0.07);
	investimento_atual(g,"Gilmar",5,"BBAS3",21.59,"08/dezembro/2025",0.04);
	investimento_atual(g,"Gilmar",20,"CMIG4",11.15,"08/dezembro/2025",0.08);
	investimento_atual(g,"Gilmar",9,"BBAS3",21.50,"09/dezembro/2025",0.07);
	investimento_atual(g,"Gilmar",20,"SYNE3",5.58,"12/dezembro/2025",0.04);
	investimento_atual(g,"Gilmar",10,"CMIG4",11.06,"19/dezembro/2025",0.04);
	investimento_atual(g,"Gilmar",2,"DIRR3",13.99,"19/dezembro/2025",0.01);
	investimento_atual(g,"Gilmar",3,"KLBN4",3.72,"19/dezembro/2025",0.01);
	bonus(g,"Gilmar",28,"KLBN4","19/dezembro/2025");
	reinvestimento(g,"Gilmar",20,"CMIG4",11.13,"23/dezembro/2025",0.08);
	reinvestimento(g,"Gilmar",3,"DIRR3",13.72,"23/dezembro/2025",0.02);
	reinvestimento(g,"Gilmar",4,"BBAS3",21.61,"23/dezembro/2025",0.03);
	investimento_atual(g,"Gilmar",1,"PETR4",30.79,"29/dezembro/2025",0.01);
	Proventos2025(g);
}

void Compra2026(struct gancho *g){
	gambiarra2(g);
	investimento_atual(g,"Gilmar",3,"PETR4",30.65,"02/janeiro/2026",0.03);
	investimento_atual(g,"Gilmar",6,"BBAS3",22.03,"02/janeiro/2026",0.04);
	investimento_atual(g,"Gilmar",25,"KLBN4",3.78,"02/janeiro/2026",0.04);
	investimento_atual(g,"Gilmar",5,"BBAS3",21.68,"05/janeiro/2026",0.04);
	investimento_atual(g,"Gilmar",6,"PETR4",29.86,"05/janeiro/2026",0.06);
	investimento_atual(g,"Gilmar",50,"MXRF11",9.529,"05/janeiro/2026",0.10);  
	investimento_atual(g,"Gilmar",5,"PETR4",30.19,"06/janeiro/2026",0.05);
	investimento_atual(g,"Gilmar",20,"MXRF11",9.54,"06/janeiro/2026",0.07);
	investimento_atual(g,"Gilmar",9,"MXRF11",9.53,"08/janeiro/2026",0.03);
	investimento_atual(g,"Gilmar",3,"MXRF11",9.50,"20/janeiro/2026",0.01);
	investimento_atual(g,"Gilmar",9,"MXRF11",9.51,"26/janeiro/2026",0.03);
	investimento_atual(g,"Gilmar",4,"MXRF11",9.51,"28/janeiro/2026",0.02);
	investimento_atual(g,"Gilmar",50,"RZAG11",9.06,"06/fevereiro/2026",0.15);
	investimento_atual(g,"Gilmar",30,"KLBN4",3.89,"06/fevereiro/2026",0.04);
	investimento_atual(g,"Gilmar",55,"MXRF11",9.582,"06/fevereiro/2026",0.16); 
	investimento_atual(g,"Gilmar",2,"VGIA11",10.19,"06/fevereiro/2026",0.01);
	investimento_atual(g,"Gilmar",12,"RZAG11",9.09,"13/fevereiro/2026",0.01);
	investimento_atual(g,"Gilmar",50,"MXRF11",9.75,"06/março/2026",0.16);
	investimento_atual(g,"Gilmar",5,"BBSE3",33.93,"06/março/2026",0.06);
	reinvestimento(g,"Gilmar",25,"GARE11",8.31,"24/março/2026",0.07);
	reinvestimento(g,"Gilmar",1,"RZTR11",94.55,"25/março/2026",0.04);
	investimento_atual(g,"Gilmar",50,"RURA11",8.88,"07/abril/2026",0.15);
	investimento_atual(g,"Gilmar",1,"RZTR11",93.94,"08/abril/2026",0.04);
	investimento_atual(g,"Gilmar",25,"GARE11",8.48,"08/abril/2026",0.07);
	investimento_atual(g,"Gilmar",1,"RZTR11",94.21,"15/abril/2026",0.04);
	investimento_atual(g,"Gilmar",6,"GARE11",8.39,"15/abril/2026",0.02);
	investimento_atual(g,"Gilmar",5,"GARE11",8.37,"20/abril/2026",0.02);
	investimento_atual(g,"Gilmar",20,"GARE11",8.28,"07/maio/2026",0.06);
	investimento_atual(g,"Gilmar",1,"RZTR11",90.97,"07/maio/2026",0.03);
	investimento_atual(g,"Gilmar",7,"KLBN4",3.40,"08/maio/2026",0.01);
	investimento_atual(g,"Gilmar",10,"GARE11",8.30,"08/maio/2026",0.03);
	adicionarVendas(g,"Getúlio",67,"PETR4",29.41,"12/maio/2026",0); //para comprar outra
	adicionarVendas(g,"Eliana",13,"PETR4",32.56,"12/maio/2026",0); //para comprar outra
	investimento_atual(g,"Getúlio",22,"RZTR11",89.47,"14/maio/2026",0.64); corrigirSaldo(g,"Getúlio",-1968.98);
	investimento_atual(g,"Eliana",50,"MXRF11",8.30,"14/maio/2026",0.16); corrigirSaldo(g,"Eliana",-415);
	reinvestimento(g,"Gilmar",9,"BBAS3",20.00,"14/maio/2026",0.07);
	reinvestimento(g,"Gilmar",23,"SNEL11",8.55,"14/maio/2026",0.07);
	reinvestimento(g,"Gilmar",100,"GARE11",8.26,"14/maio/2026",0.27);
	reinvestimento(g,"Gilmar",7,"SNEL11",8.56,"15/maio/2026",0.02);
	reinvestimento(g,"Gilmar",9,"GARE11",8.31,"15/maio/2026",0.03);
	reinvestimento(g,"Gilmar",18,"GARE11",8.33,"15/maio/2026",0.05);
	reinvestimento(g,"Gilmar",3,"GARE11",8.34,"27/maio/2026",0.01);
	investimento_atual(g,"Gilmar",49,"GGRC11",10.06,"01/junho/2026",0.16);
	investimento_atual(g,"Gilmar",10,"CMIG4",10.76,"06/junho/2026",0.04);
	investimento_atual(g,"Gilmar",59,"GARE11",8.24,"06/junho/2026",0.17);  ///a corrigir
	investimento_atual(g,"Gilmar",51,"GGRC11",9.93,"06/junho/2026",0.17); 
	investimento_atual(g,"Gilmar",70,"SNEL11",8.45,"06/junho/2026",0.14); ///a corrigir
	investimento_atual(g,"Gilmar",13,"SNEL11",8.42,"06/junho/2026",0.04);
	investimento_atual(g,"Gilmar",11,"SNEL11",8.45,"13/junho/2026",0.03);
	reinvestimento(g,"Gilmar",20,"GARE11",8.15,"15/junho/2026",0.06);
	reinvestimento(g,"Gilmar",8,"SNEL11",8.43,"15/junho/2026",0.03);
	reinvestimento(g,"Gilmar",5,"PORD11",8.25,"18/junho/2026",0.02);
	reinvestimento(g,"Gilmar",20,"PORD11",8.35,"22/junho/2026",0.06);
	reinvestimento(g,"Gilmar",10,"GGRC11",9.90,"22/junho/2026",0.04);
	reinvestimento(g,"Gilmar",2,"PORD11",8.44,"25/junho/2026",0.01);
	reinvestimento(g,"Gilmar",3,"PORD11",8.50,"30/junho/2026",0.01);
	investimento_atual(g,"Gilmar",40,"SNEL11",8.41,"03/julho/2026",0.11);
	investimento_atual(g,"Gilmar",9,"SNEL11",8.38,"06/julho/2026",0.03);
	reinvestimento(g,"Gilmar",14,"SNEL11",8.39,"07/julho/2026",0.04);
	reinvestimento(g,"Gilmar",2,"SNEL11",8.38,"08/julho/2026",0.01);
	reinvestimento(g,"Gilmar",10,"SNEL11",8.38,"09/julho/2026",0.03);
	reinvestimento(g,"Gilmar",1,"SNEL11",8.39,"10/julho/2026",0.01);
	reinvestimento(g,"Gilmar",10,"GGRC11",9.72,"14/julho/2026",0.04);
	reinvestimento(g,"Gilmar",1,"GARE11",8.14,"14/julho/2026",0.01);
	reinvestimento(g,"Gilmar",6,"GARE11",8.17,"15/julho/2026",0.02);
	reinvestimento(g,"Gilmar",4,"GARE11",8.14,"17/julho/2026",0.02);
	adicionarVendas(g,"Gilmar",200,"MXRF11",9.66,"21/julho/2026",0.62); // lucro 
	investimento_atual(g,"Gilmar",50,"GARE11",8.16,"23/julho/2026",0.14);
	investimento_atual(g,"Gilmar",50,"GGRC11",9.89,"23/julho/2026",0.16);
	investimento_atual(g,"Gilmar",70,"PORD11",8.50,"23/julho/2026",0.20);
	investimento_atual(g,"Gilmar",5,"RBRR11",76.07,"23/julho/2026",0.13);
	investimento_atual(g,"Gilmar",6,"SNEL11",8.34,"23/julho/2026",0.02);
	adicionarVendas(g,"Gilmar",12,"VGIA11",8.44,"24/julho/2026",0.04); // prejuizo
	adicionarVendas(g,"Gilmar",20,"VGIA11",8.52,"24/julho/2026",0.06); // prejuizo
	investimento_atual(g,"Gilmar",3,"PORD11",8.47,"24/julho/2026",0.01);
	investimento_atual(g,"Gilmar",18,"GARE11",8.16,"28/julho/2026",0.05);
	investimento_atual(g,"Gilmar",20,"SNEL11",8.32,"03/agosto/2026",0.06);
	investimento_atual(g,"Gilmar",2,"GARE11",8.19,"03/agosto/2026",0.01);
	investimento_atual(g,"Gilmar",6,"SNEL11",8.27,"05/agosto/2026",0.02);
	investimento_atual(g,"Gilmar",5,"CXCE11",40.38,"07/agosto/2026",0.07);
	investimento_atual(g,"Gilmar",100,"KLBN4",3.58,"07/agosto/2026",0.12);
	investimento_atual(g,"Gilmar",2,"RBRR11",76.44,"07/agosto/2026",0.05);
	investimento_atual(g,"Gilmar",19,"GARE11",8.16,"07/agosto/2026",0.06);
	investimento_atual(g,"Gilmar",17,"PORD11",8.35,"07/agosto/2026",0.05);
	investimento_atual(g,"Gilmar",15,"CMIG4",10.97,"07/agosto/2026",0.06);
	investimento_atual(g,"Gilmar",50,"SNEL11",8.37,"07/agosto/2026",0.14);
	investimento_atual(g,"NAN",5,"CMIG4",10.81,"10/agosto/2026",0.02);
	investimento_atual(g,"NAN",5,"BRBI11",13.11,"10/agosto/2026",0.03);
	investimento_atual(g,"NAN",5,"CXCE11",40.30,"10/agosto/2026",0.07);
	investimento_atual(g,"NAN",30,"GGRC11",9.65,"10/agosto/2026",0.10);
	investimento_atual(g,"NAN",80,"SNEL11",8.38,"10/agosto/2026",0.22);
	investimento_atual(g,"NAN",5,"BRBI11",12.73,"10/agosto/2026",0.03);
	investimento_atual(g,"NAN",10,"CMIG4",10.71,"10/agosto/2026",0.04);
	investimento_atual(g,"NAN",56,"KLBN4",3.57,"10/agosto/2026",0.07);
	investimento_atual(g,"NAN",57,"KLBN4",3.51,"10/agosto/2026",0.07);
	adicionarVendas(g,"Gilmar",250,"XPCA11",7.07,"17/agosto/2026",0.56); //prejuizo
	investimento_atual(g,"Gilmar",10,"BBAS3",18.20,"17/agosto/2026",0.06);
	investimento_atual(g,"Gilmar",30,"SNEL11",8.18,"17/agosto/2026",0.08);
	investimento_atual(g,"Gilmar",20,"GGRC11",9.09,"17/agosto/2026",0.06);
	investimento_atual(g,"Gilmar",30,"KLBN4",3.46,"17/agosto/2026",0.04);
	investimento_atual(g,"Gilmar",10,"BBAS3",17.91,"18/agosto/2026",0.06);
	investimento_atual(g,"Gilmar",30,"GGRC11",9.14,"19/agosto/2026",0.09);
	investimento_atual(g,"Gilmar",8,"SNEL11",8.13,"19/agosto/2026",0.03);
	investimento_atual(g,"Gilmar",20,"GARE11",8.12,"19/agosto/2026",0.06);
	investimento_atual(g,"Gilmar",5,"BBAS3",18.09,"19/agosto/2026",0.03);
	investimento_atual(g,"Gilmar",10,"CMIG4",10.20,"19/agosto/2026",0.04);
	investimento_atual(g,"Gilmar",20,"GGRC11",9.17,"19/agosto/2026",0.06);
	investimento_atual(g,"Gilmar",30,"GGRC11",9.17,"19/agosto/2026",0.09);
	investimento_atual(g,"Gilmar",7,"SNEL11",8.15,"19/agosto/2026",0.02);
	investimento_atual(g,"Gilmar",30,"PORD11",8.22,"20/agosto/2026",0.08);
	investimento_atual(g,"Gilmar",3,"RBRR11",74.34,"21/agosto/2026",0.08);
	investimento_atual(g,"Gilmar",16,"PORD11",8.22,"21/agosto/2026",0.05);
	investimento_atual(g,"Gilmar",85,"SNEL11",8.19,"08/setembro/2026",0.23);
	investimento_atual(g,"Gilmar",34,"PORD11",8.39,"08/setembro/2026",0.10);
	
	adicionarVendas(g,"Gilmar",50,"RURA11",8.08,"16/setembro/2026",0.13); //prejuizo
	adicionarVendas(g,"Gilmar",39,"VGIA11",8.77,"16/setembro/2026",0.11); //prejuizo
	investimento_atual(g,"Gilmar",5,"RECR11",75.16,"16/setembro/2026",0.13);
	investimento_atual(g,"Gilmar",4,"PCIP11",72.27,"16/setembro/2026",0.10);
	investimento_atual(g,"Gilmar",1,"RECR11",75.65,"17/setembro/2026",0.03);
	investimento_atual(g,"Gilmar",1,"RECR11",75.26,"17/setembro/2026",0.03);
	investimento_atual(g,"Gilmar",5,"HGLG11",147.83,"17/setembro/2026",0.24);
	investimento_atual(g,"Gilmar",1,"RECR11",75.45,"18/setembro/2026",0.03);
	investimento_atual(g,"Gilmar",1,"RECR11",75.11,"18/setembro/2026",0.03);
	reinvestimento(g,"Gilmar",3,"RECR11",76.11,"21/setembro/2026",0.08); // da petr4
	reinvestimento(g,"Gilmar",3,"PORD11",8.24,"21/setembro/2026",0.01);
	reinvestimento(g,"Gilmar",1,"RECR11",75.00,"22/setembro/2026",0.03);
	reinvestimento(g,"Gilmar",1,"PORD11",8.26,"22/setembro/2026",0.01);
	adicionarVendas(g,"Gilmar",50,"BRBI11",14.52,"25/setembro/2026",0.28);
	adicionarVendas(g,"NAN",10,"BRBI11",14.52,"25/setembro/2026",0.28);
	reinvestimento(g,"Gilmar",3,"KLBN4",3.62,"25/setembro/2026",0.01);
	reinvestimento(g,"Gilmar",5,"WIZC3",7.85,"25/setembro/2026",0.02);
	reinvestimento(g,"Gilmar",10,"SPXB11",17.82,"28/setembro/2026",0.06);
	reinvestimento(g,"Gilmar",10,"SAPR4",6.58,"28/setembro/2026",0.03);
	reinvestimento(g,"Gilmar",6,"PORD11",8.38,"30/setembro/2026",0.02);
	reinvestimento(g,"Gilmar",2,"KLBN4",3.61,"01/outubro/2026",0.01);
	investimento_atual(g,"Gilmar",5,"RECR11",76.19,"06/outubro/2026",0.13);
	investimento_atual(g,"Gilmar",25,"SNEL11",7.96,"06/outubro/2026",0.07);
	investimento_atual(g,"Gilmar",25,"PORD11",8.49,"06/outubro/2026",0.07);
	investimento_atual(g,"Gilmar",18,"SNEL11",7.97,"06/outubro/2026",0.05);
	investimento_atual(g,"Gilmar",2,"KLBN4",3.70,"06/outubro/2026",0.01);
	
	
	Proventos2026(g);
	}
	
void Proventos2023(struct gancho *g){
	gambiarra((*g).i);
	(*g).ano = 2023;
	//PERDIDOS POR QUE INVESTI DEPOIS DA DATA COM****  
	proventos_atual(g,"Gilmar","PETR4"," ",5.64,'D',0);
	proventos_atual(g,"Gilmar","PETR4"," ",0.67,'J',0);
	proventos_atual(g,"Gilmar","PETR4"," ",0.13,'R',0);
	proventos_atual(g,"Gilmar","KLBN4"," ",0.01,'J',0);
	proventos_atual(g,"Gilmar","KLBN4"," ",0.07,'D',0);
	proventos_atual(g,"Gilmar","CXSE3"," ",0.50,'D',0);
	proventos_atual(g,"Gilmar","CXSE3"," ",0.01,'R',0);
	///////////////////////////////////////////////////////
	proventos_atual(g,"Gilmar","KLBN4","15/agosto/2023",0.04872,'D',203);
	proventos_atual(g,"Gilmar","KLBN4","14/novembro/2023",0.05782,'J',638);
	proventos_atual(g,"Gilmar","CXSE3","06/novembro/2023",0.50,'D',179);
	proventos_atual(g,"Gilmar","PETR4","21/novembro/2023",0.209158,'D',135);
	proventos_atual(g,"Getúlio","PETR4","21/novembro/2023",0.209158,'D',67);
	proventos_atual(g,"Gilmar","PETR4","21/novembro/2023",0.365476,'J',135);
	proventos_atual(g,"Getúlio","PETR4","21/novembro/2023",0.365476,'J',67);
	proventos_atual(g,"Gilmar","PETR4","15/dezembro/2023",0.57460,'D',135);
	proventos_atual(g,"Getúlio","PETR4","15/dezembro/2023",0.57460,'D',67);
	
}

void Proventos2024(struct gancho *g){
	gambiarra((*g).i);
	(*g).ano = 2024;
	//PERDIDOS POR QUE INVESTI DEPOIS DA DATA COM****
	proventos_atual(g,"Gilmar","CMIG4"," ",0.74,'D',0);
	proventos_atual(g,"Gilmar","CMIG4"," ",0.98,'J',0);
	proventos_atual(g,"Gilmar","CMIG4"," ",0.30,'D',0);
	proventos_atual(g,"Gilmar","TAEE4"," ",0.76,'J',0);
	proventos_atual(g,"Gilmar","TAEE4"," ",2.10,'D',0);
	proventos_atual(g,"Gilmar","BMGB4"," ",0.71,'J',0);
	proventos_atual(g,"Gilmar","RURA11"," ",1.17,'D',0);
	///////////////////////////////////////////////////////
	proventos_atual(g,"Gilmar","PETR4","20/fevereiro/2024",0.00278,'R',433); 
	proventos_atual(g,"Getúlio","PETR4","20/fevereiro/2024",0.00278,'R',67);
	proventos_atual(g,"Gilmar","PETR4","20/fevereiro/2024",0.0049,'R',433);
	proventos_atual(g,"Getúlio","PETR4","20/fevereiro/2024",0.0049,'R',67);
	proventos_atual(g,"Gilmar","PETR4","20/fevereiro/2024",0.24328,'D',433); 
	proventos_atual(g,"Getúlio","PETR4","20/fevereiro/2024",0.24328,'D',67);
	proventos_atual(g,"Gilmar","PETR4","20/fevereiro/2024",0.429388,'J',433);
	proventos_atual(g,"Getúlio","PETR4","20/fevereiro/2024",0.429388,'J',67);
	proventos_atual(g,"Gilmar","PETR4","20/março/2024",0.67266,'D',433);
	proventos_atual(g,"Getúlio","PETR4","20/março/2024",0.67266,'D',67);
	proventos_atual(g,"Gilmar","PETR4","20/março/2024",0.01238,'R',433);
	proventos_atual(g,"Getúlio","PETR4","20/março/2024",0.01238,'R',67);
	proventos_atual(g,"Gilmar","PETR4","20/maio/2024",0.55014,'D',433);
	proventos_atual(g,"Getúlio","PETR4","20/maio/2024",0.55014,'D',67);
	proventos_atual(g,"Gilmar","PETR4","20/maio/2024",0.02678,'R',433);
	proventos_atual(g,"Getúlio","PETR4","20/maio/2024",0.02678,'R',67);
	proventos_atual(g,"Gilmar","PETR4","20/maio/2024",0.01734,'R',433);
	proventos_atual(g,"Getúlio","PETR4","20/maio/2024",0.01734,'R',67);
	proventos_atual(g,"Gilmar","PETR4","20/maio/2024",0.84962,'D',433);
	proventos_atual(g,"Getúlio","PETR4","20/maio/2024",0.84962,'D',67);
	proventos_atual(g,"Gilmar","PETR4","20/junho/2024",0.55014,'D',433);
	proventos_atual(g,"Getúlio","PETR4","20/junho/2024",0.55014,'D',67);
	proventos_atual(g,"Gilmar","PETR4","20/junho/2024",0.02118,'R',433);
	proventos_atual(g,"Getúlio","PETR4","20/junho/2024",0.02118,'R',67);
	proventos_atual(g,"Gilmar","PETR4","20/junho/2024",0.03272,'R',433);
	proventos_atual(g,"Getúlio","PETR4","20/junho/2024",0.03272,'R',67);
	proventos_atual(g,"Gilmar","PETR4","20/junho/2024",0.84962,'D',433);
	proventos_atual(g,"Getúlio","PETR4","20/junho/2024",0.84962,'D',67);
	proventos_atual(g,"Gilmar","PETR4","20/agosto/2024",0.52162,'J',433);
	proventos_atual(g,"Getúlio","PETR4","20/agosto/2024",0.52162,'J',67);
	proventos_atual(g,"Gilmar","PETR4","20/setembro/2024",0.44806,'D',433);
	proventos_atual(g,"Getúlio","PETR4","20/setembro/2024",0.44806,'D',67);
	proventos_atual(g,"Gilmar","PETR4","20/setembro/2024",0.07355,'J',433);	
	proventos_atual(g,"Getúlio","PETR4","20/setembro/2024",0.07355,'J',67);
	proventos_atual(g,"Gilmar","PETR4","21/novembro/2024",0.11384,'D',445);
	proventos_atual(g,"Getúlio","PETR4","21/novembro/2024",0.11384,'D',67);
	proventos_atual(g,"Gilmar","PETR4","21/novembro/2024",0.41275,'J',445);
	proventos_atual(g,"Getúlio","PETR4","21/novembro/2024",0.41275,'J',67); 
	proventos_atual(g,"Gilmar","PETR4","20/dezembro/2024",0.526583,'D',445);
	proventos_atual(g,"Getúlio","PETR4","20/dezembro/2024",0.526583,'D',67);
	proventos_atual(g,"Gilmar","PETR4","23/dezembro/2024",1.5517383,'D',445);
	proventos_atual(g,"Getúlio","PETR4","23/dezembro/2024",1.5517383,'D',67);
	proventos_atual(g,"Gilmar","KLBN4","26/fevereiro/2024",0.03480,'D',638);
	proventos_atual(g,"Gilmar","KLBN4","26/fevereiro/2024",0.03099,'J',638);
	proventos_atual(g,"Gilmar","KLBN4","16/maio/2024",0.05971,'D',638);
	proventos_atual(g,"Gilmar","KLBN4","15/agosto/2024",0.06743,'D',701);
	proventos_atual(g,"Gilmar","KLBN4","21/novembro/2024",0.06990,'J',701);
	proventos_atual(g,"Gilmar","CXSE3","08/maio/2024",0.55056,'D',179);
	proventos_atual(g,"Gilmar","CXSE3","08/maio/2024",0.01224,'R',179);
	proventos_atual(g,"Gilmar","CXSE3","15/agosto/2024",0.28,'D',179);
	proventos_atual(g,"Gilmar","CXSE3","18/novembro/2024",0.23397,'D',179);
}

void Proventos2025(struct gancho *g){
	gambiarra((*g).i);
	(*g).ano = 2025;
	//PERDIDOS POR QUE INVESTI DEPOIS DA DATA COM****
	proventos_atual(g,"Gilmar","BRBI11"," ",0.18,'D',0); 
	proventos_atual(g,"Gilmar","VGIA11"," ",0.7,'D',0);
	proventos_atual(g,"Gilmar","RZAG11"," ",0.595,'D',0); 
	proventos_atual(g,"Gilmar","XPCA11"," ",0.42,'D',0);
	proventos_atual(g,"Gilmar","CXCE11"," ",2.20778644,'D',0);
    proventos_atual(g,"Gilmar","VALE3"," ",2.14184748,'D',0);  
    proventos_atual(g,"Gilmar","VALE3"," ",0.52053100,'J',0);                                
	proventos_atual(g,"Gilmar","BBDC3"," ",0.56061219,'J',0);
	proventos_atual(g,"Gilmar","DIRR3"," ",0.42333333,'D',0);
	proventos_atual(g,"Gilmar","DIRR3"," ",0.15333333,'D',0);
	proventos_atual(g,"Gilmar","BMGB4"," ",0.10,'J',0);
	proventos_atual(g,"Gilmar","BBSE3"," ",2.32016121,'D',0); 
	proventos_atual(g,"Gilmar","CMIG4"," ",0.6588119,'D',0);
	proventos_atual(g,"Gilmar","CMIG4"," ",0.68678764,'J',0);
	proventos_atual(g,"Gilmar","FLRY3"," ",0.46613950,'D',0);
	proventos_atual(g,"Gilmar","TAEE4"," ",0.13331183,'J',0);
	proventos_atual(g,"Gilmar","TAEE4"," ",0.08968770,'D',0);
	proventos_atual(g,"Gilmar","SYNE3"," ",0.45858200,'D',0);
	proventos_atual(g,"Gilmar","RZTR11"," ",11.4,'D',0);
	///////////////////////////////////////////////////////
	proventos_atual(g,"Gilmar","RURA11","08/janeiro/2025",0.06,'D',50); 
	proventos_atual(g,"Gilmar","RURA11","07/fevereiro/2025",0.07,'D',50); 
    proventos_atual(g,"Gilmar","RURA11","11/março/2025",0.0850,'D',50); 
    proventos_atual(g,"Gilmar","RURA11","07/abril/2025",0.085,'D',100);  
	proventos_atual(g,"Gilmar","RURA11","08/maio/2025",0.10,'D',100); 
	proventos_atual(g,"Gilmar","RURA11","06/junho/2025",0.10,'D',247); 
    proventos_atual(g,"Eliana","RURA11","06/junho/2025",0.10,'D',115); 
    proventos_atual(g,"Gilmar","RURA11","07/julho/2025",0.10503,'D',285);
	proventos_atual(g,"Eliana","RURA11","07/julho/2025",0.10500,'D',115);
	proventos_atual(g,"Gilmar","RURA11","07/agosto/2025",0.10500000,'D',569);
	proventos_atual(g,"Eliana","RURA11","07/agosto/2025",0.10500000,'D',115);
    proventos_atual(g,"Gilmar","RURA11","05/setembro/2025",0.105000,'D',605);
	proventos_atual(g,"Eliana","RURA11","05/setembro/2025",0.105050,'D',155); 
	proventos_atual(g,"Gilmar","RURA11","07/outubro/2025",0.11000000,'D',627);
	proventos_atual(g,"Eliana","RURA11","07/outubro/2025",0.11000000,'D',155); 	
	proventos_atual(g,"Gilmar","RURA11","07/novembro/2025",0.11000000,'D',738); 
	proventos_atual(g,"Eliana","RURA11","07/novembro/2025",0.11000000,'D',155);
	proventos_atual(g,"Gilmar","RURA11","05/dezembro/2025",0.11000000,'D',245);
	proventos_atual(g,"Eliana","RURA11","05/dezembro/2025",0.11000000,'D',155); 
	proventos_atual(g,"Gilmar","RZTR11","05/dezembro/2025",1.00000000,'D',20); 	
	proventos_atual(g,"Gilmar","VGIA11","17/julho/2025",0.12500000,'D',150);
    proventos_atual(g,"Gilmar","VGIA11","19/agosto/2025",0.13000000,'D',174);
    proventos_atual(g,"Gilmar","VGIA11","17/setembro/2025",0.13000000,'D',239);
	proventos_atual(g,"Gilmar","VGIA11","17/outubro/2025",0.14000000,'D',269); 
	proventos_atual(g,"Gilmar","VGIA11","19/novembro/2025",0.15000000,'D',269); 
	proventos_atual(g,"Gilmar","VGIA11","17/dezembro/2025",0.140000,'D',269);
    proventos_atual(g,"Gilmar","RZAG11","13/junho/2025",0.125,'D',150); 
    proventos_atual(g,"Gilmar","RZAG11","14/julho/2025",0.12500000,'D',400);
    proventos_atual(g,"Gilmar","RZAG11","14/agosto/2025",0.1250000,'D',400);
    proventos_atual(g,"Gilmar","RZAG11","12/setembro/2025",0.1250000,'D',400);
	proventos_atual(g,"Gilmar","RZAG11","14/outubro/2025",0.1250000,'D',400);
    proventos_atual(g,"Gilmar","RZAG11","14/novembro/2025",0.1250000,'D',400);
    proventos_atual(g,"Gilmar","RZAG11","12/dezembro/2025",0.1250000,'D',200);
    proventos_atual(g,"Gilmar","XPCA11","13/junho/2025",0.11,'D',150); //
    proventos_atual(g,"Gilmar","XPCA11","14/julho/2025",0.11000000,'D',200);
    proventos_atual(g,"Gilmar","XPCA11","14/agosto/2025",0.110000,'D',450);
    proventos_atual(g,"Gilmar","XPCA11","12/setembro/2025",0.110000,'D',450);
    proventos_atual(g,"Gilmar","XPCA11","14/outubro/2025",0.110000,'D',450);
    proventos_atual(g,"Gilmar","XPCA11","14/novembro/2025",0.110000,'D',450);
    proventos_atual(g,"Gilmar","XPCA11","12/dezembro/2025",0.110000,'D',450);
    proventos_atual(g,"Gilmar","CXCE11","13/junho/2025",0.440152,'D',26); 
    proventos_atual(g,"Gilmar","CXCE11","15/julho/2025",0.4502,'D',50);
    proventos_atual(g,"Gilmar","CXCE11","15/agosto/2025",0.4577,'D',100);
    proventos_atual(g,"Gilmar","CXCE11","15/setembro/2025",0.4598,'D',100);
    proventos_atual(g,"Gilmar","CXCE11","15/outubro/2025",0.42305,'D',105);
    proventos_atual(g,"Gilmar","CXCE11","14/novembro/2025",0.48190,'D',105);
    proventos_atual(g,"Gilmar","CXCE11","15/dezembro/2025",0.47381,'D',105);
	proventos_atual(g,"Gilmar","BRBI11","23/maio/2025",0.30,'D',50);
    proventos_atual(g,"Gilmar","BRBI11","21/agosto/2025",0.36,'D',50);
    proventos_atual(g,"Gilmar","BRBI11","26/novembro/2025",1.02,'D',50);
	proventos_atual(g,"Gilmar","CXSE3","17/janeiro/2025",0.31,'D',179);
	proventos_atual(g,"Gilmar","CXSE3","17/janeiro/2025",0.001340782122905,'R',179);
	proventos_atual(g,"Gilmar","CXSE3","15/maio/2025",0.320,'D',179);
	proventos_atual(g,"Gilmar","CXSE3","15/maio/2025",0.03,'R',1);
	proventos_atual(g,"Gilmar","CXSE3","15/agosto/2025",0.310,'D',340);  
	proventos_atual(g,"Gilmar","CXSE3","17/novembro/2025",0.32000000,'D',340);
	proventos_atual(g,"Gilmar","KLBN4","12/março/2025",0.041472182596291,'J',701);
	proventos_atual(g,"Gilmar","KLBN4","14/março/2025",0.008875,'D',800);
	proventos_atual(g,"Gilmar","KLBN4","22/maio/2025",0.0457571428571429,'D',1400);
	proventos_atual(g,"Gilmar","KLBN4","19/agosto/2025",0.05018892,'D',1861);
	proventos_atual(g,"Gilmar","KLBN4","19/novembro/2025",0.0521536,'D',2057);
	proventos_atual(g,"Gilmar","PETR4","20/fevereiro/2025",0.66411,'J',445);
	proventos_atual(g,"Getúlio","PETR4","20/fevereiro/2025",0.66411,'J',67);
	proventos_atual(g,"Gilmar","PETR4","20/fevereiro/2025",0.00880859375,'R',445);
	proventos_atual(g,"Getúlio","PETR4","20/fevereiro/2025",0.00880859375,'R',67);
	proventos_atual(g,"Gilmar","PETR4","20/março/2025",0.01055,'J',445);
	proventos_atual(g,"Getúlio","PETR4","20/março/2025",0.01055,'J',67);
	proventos_atual(g,"Gilmar","PETR4","20/março/2025",0.00021484375,'R',445);
	proventos_atual(g,"Getúlio","PETR4","20/março/2025",0.00021484375,'R',67);
	proventos_atual(g,"Gilmar","PETR4","20/março/2025",0.01322265625,'R',445);
	proventos_atual(g,"Getúlio","PETR4","20/março/2025",0.01322265625,'R',67);
	proventos_atual(g,"Gilmar","PETR4","20/março/2025",0.6535546875,'D',445);
	proventos_atual(g,"Getúlio","PETR4","20/março/2025",0.6535546875,'D',67); 
	proventos_atual(g,"Gilmar","PETR4","20/maio/2025",0.3547637795275591,'D',609);
	proventos_atual(g,"Getúlio","PETR4","20/maio/2025",0.3547637795275591,'D',67);  
	proventos_atual(g,"Eliana","PETR4","20/maio/2025",0.3547637795275591,'D',86);  
	proventos_atual(g,"Gilmar","PETR4","20/maio/2025",0.0132152230971129,'R',609);
	proventos_atual(g,"Gilmar","PETR4","20/maio/2025",0.01,'R',1);
	proventos_atual(g,"Getúlio","PETR4","20/maio/2025",0.0132152230971129,'R',67);
	proventos_atual(g,"Eliana","PETR4","20/maio/2025",0.0132152230971129,'R',86);
	proventos_atual(g,"Gilmar","PETR4","20/junho/2025",0.0166798,'R',609); 
	proventos_atual(g,"Getúlio","PETR4","20/junho/2025",0.0166798,'R',67);  
	proventos_atual(g,"Eliana","PETR4","20/junho/2025",0.0166798,'R',86); 
	proventos_atual(g,"Gilmar","PETR4","20/junho/2025",0.3547637,'D',609); 
	proventos_atual(g,"Getúlio","PETR4","20/junho/2025",0.3547637,'D',67); 
	proventos_atual(g,"Eliana","PETR4","20/junho/2025",0.3547637,'D',86); 
	proventos_atual(g,"Gilmar","PETR4","20/agosto/2025",0.454583,'J',615); 
	proventos_atual(g,"Eliana","PETR4","20/agosto/2025",0.454583,'J',182);  
	proventos_atual(g,"Getúlio","PETR4","20/agosto/2025",0.454583,'J',67);  
	proventos_atual(g,"Gilmar","PETR4","22/setembro/2025",0.3084375,'D',615);  
	proventos_atual(g,"Gilmar","PETR4","22/setembro/2025",0.146135,'J',615); 
	proventos_atual(g,"Eliana","PETR4","22/setembro/2025",0.3084375,'D',182); 
	proventos_atual(g,"Getúlio","PETR4","22/setembro/2025",0.3084375,'D',67); 
	proventos_atual(g,"Eliana","PETR4","22/setembro/2025",0.146135,'J',182); 
	proventos_atual(g,"Getúlio","PETR4","22/setembro/2025",0.146135,'J',67); 
	proventos_atual(g,"Gilmar","PETR4","21/novembro/2025",0.33596205,'J',655);
	proventos_atual(g,"Eliana","PETR4","21/novembro/2025",0.33596205,'J',182);
	proventos_atual(g,"Getúlio","PETR4","21/novembro/2025",0.33596205,'J',67); 
	proventos_atual(g,"Gilmar","PETR4","22/dezembro/2025",0.13504029,'J',655);
	proventos_atual(g,"Gilmar","PETR4","22/dezembro/2025",0.20092175,'D',655);
	proventos_atual(g,"Eliana","PETR4","22/dezembro/2025",0.13504029,'J',182);
	proventos_atual(g,"Eliana","PETR4","22/dezembro/2025",0.20092175,'D',182);
	proventos_atual(g,"Getúlio","PETR4","22/dezembro/2025",0.13504029,'J',67); 
	proventos_atual(g,"Getúlio","PETR4","22/dezembro/2025",0.20092175,'D',67); 
	proventos_atual(g,"Gilmar","BBAS3","20/março/2025",0.3425882,'J',50); 
	proventos_atual(g,"Gilmar","BBAS3","20/março/2025",0.136,'D',50); 
	proventos_atual(g,"Gilmar","BBAS3","20/março/2025",0.0028,'R',50); 
	proventos_atual(g,"Gilmar","BBAS3","20/março/2025",0.007,'R',50); 
	proventos_atual(g,"Gilmar","BBAS3","21/março/2025",0.1494117,'J',50); 
	proventos_atual(g,"Gilmar","BBAS3","12/junho/2025",0.334258,'J',50); 
	proventos_atual(g,"Eliana","BBAS3","12/junho/2025",0.334258,'J',37); 
	proventos_atual(g,"Gilmar","BBAS3","12/junho/2025",0.090446,'J',50); 
	proventos_atual(g,"Gilmar","BBAS3","12/junho/2025",0.01,'R',1);
	proventos_atual(g,"Eliana","BBAS3","12/junho/2025",0.090446,'J',37); 
	proventos_atual(g,"Gilmar","BBAS3","11/dezembro/2025",0.07192713,'J',237);
	proventos_atual(g,"Eliana","BBAS3","11/dezembro/2025",0.07192713,'J',25);
	proventos_atual(g,"Gilmar","BBAS3","12/dezembro/2025",0.04583263,'J',237);
	proventos_atual(g,"Eliana","BBAS3","12/dezembro/2025",0.04583263,'J',25);
	proventos_atual(g,"Gilmar","TAEE4","28/maio/2025",0.1844,'D',150);
	proventos_atual(g,"Gilmar","TAEE4","27/agosto/2025",0.182174,'J',150);
	proventos_atual(g,"Gilmar","TAEE4","27/novembro/2025",0.10726666,'D',150); 
	proventos_atual(g,"Gilmar","TAEE4","27/novembro/2025",0.07666666,'D',150); 
	proventos_atual(g,"Gilmar","TAEE4","27/novembro/2025",0.21294117,'J',150);
	proventos_atual(g,"Gilmar","BBDC3","02/junho/2025",0.01741176,'J',50); 
	proventos_atual(g,"Gilmar","BBDC3","01/julho/2025",0.01741176,'J',50);
	proventos_atual(g,"Gilmar","BBDC3","01/agosto/2025",0.01741176,'J',50);
	proventos_atual(g,"Gilmar","BBDC3","01/setembro/2025",0.01741176,'J',50);
	proventos_atual(g,"Gilmar","BBDC3","01/outubro/2025",0.01741176,'J',50);
	proventos_atual(g,"Gilmar","BBDC3","03/novembro/2025",0.01741176,'J',50);
	proventos_atual(g,"Gilmar","BBDC3","01/dezembro/2025",0.01741176,'J',50);
	proventos_atual(g,"Gilmar","DIRR3","04/julho/2025",2.0,'D',5); 
	proventos_atual(g,"Gilmar","DIRR3","23/dezembro/2025",1.55,'D',15);	
	proventos_atual(g,"Gilmar","BMGB4","21/agosto/2025",0.10,'J',271); 
	proventos_atual(g,"Gilmar","BMGB4","25/novembro/2025",0.10,'J',271);
	proventos_atual(g,"Gilmar","BMGB4","23/dezembro/2025",0.10,'J',271);
	proventos_atual(g,"Gilmar","BBSE3","26/agosto/2025",1.94209516,'D',10); 
	proventos_atual(g,"Gilmar","VALE3","03/setembro/2025",1.8941176,'J',5); 
	proventos_atual(g,"Gilmar","SYNE3","30/setembro/2025",2.16188600,'D',100);
	proventos_atual(g,"Gilmar","SYNE3","19/dezembro/2025",0.360694,'D',140);
	proventos_atual(g,"Gilmar","SYNE3","19/dezembro/2025",0.058580,'D',140);
	proventos_atual(g,"Gilmar","FLRY3","03/outubro/2025",0.31009900,'J',2);
	proventos_atual(g,"Gilmar","FLRY3","19/dezembro/2025",0.23485747618,'J',2);
	proventos_atual(g,"Gilmar","CMIG4","30/dezembro/2025",0.14575,'D',80);
}

void Proventos2026(struct gancho *g){
	gambiarra((*g).i);
	(*g).ano = 2026;   //aquii

	//proventos_atual(g,"Gilmar","BBDC3","xx/xx/xx",0.270146,'J',50); //11,48
	//proventos_atual(g,"Gilmar","BBDC3","xx/xx/xx",0.270146,'J',50); //11,48
	//proventos_atual(g,"Gilmar","CMIG4","xx/xx/xx",0.104303,'J',50); //4,43
	//proventos_atual(g,"Gilmar","CMIG4","xx/xx/xx",0.104303,'J',50); //4,43
	//proventos_atual(g,"Gilmar","CMIG4","xx/xx/xx",0.105698,'J',50); //4,49
	//proventos_atual(g,"Gilmar","CMIG4","xx/xx/xx",0.105698,'J',50); //4,49
	//proventos_atual(g,"Gilmar","FLRY3","xx/xx/xx",0.403658,'D',2); //0.80
	//proventos_atual(g,"Gilmar","FLRY3","xx/xx/xx",0.130271,'D',2); //0.26
	//proventos_atual(g,"Gilmar","FLRY3","xx/xx/xx",0.130271,'D',2); //0.26
	
	//PERDIDOS POR QUE INVESTI DEPOIS DA DATA COM****
	//proventos_atual(g,"Gilmar","GARE11"," ",0.0830*3,'R',0); 
	
	proventos_atual(g,"Gilmar","BBDC3","02/janeiro/2026",0.01741176,'J',50);
	proventos_atual(g,"Gilmar","VALE3","07/janeiro/2026",1.244102486,'D',5);
	proventos_atual(g,"Gilmar","RURA11","08/janeiro/2026",0.11000000,'D',245);
	proventos_atual(g,"Eliana","RURA11","08/janeiro/2026",0.11000000,'r',155);
	proventos_atual(g,"Gilmar","RZTR11","08/janeiro/2026",1.00000000,'D',25);
	proventos_atual(g,"Gilmar","BMGB4","14/janeiro/2026",0.14700000,'J',271);
	proventos_atual(g,"Gilmar","RZAG11","15/janeiro/2026",0.15000000,'D',200);
	proventos_atual(g,"Gilmar","CXCE11","15/janeiro/2026",0.47793340,'D',110);
	proventos_atual(g,"Gilmar","XPCA11","15/janeiro/2026",0.11000000,'D',450);
	proventos_atual(g,"Gilmar","CXSE3","16/janeiro/2026",0.35000000,'D',340);
	proventos_atual(g,"Gilmar","CXSE3","16/janeiro/2026",0.001647058,'r',340);
	proventos_atual(g,"Gilmar","VGIA11","20/janeiro/2026",0.140000,'D',269);
	proventos_atual(g,"Gilmar","TAEE4","28/janeiro/2026",0.139843137,'J',150);
	proventos_atual(g,"Gilmar","TAEE4","28/janeiro/2026",0.172984,'D',150);
	proventos_atual(g,"Gilmar","BBDC3","30/janeiro/2026",0.270146,'J',50);
	
	proventos__atual(g,"Gilmar","BBDC3","02/fevereiro/2026",0.0172121,'J',50,0.175);
	proventos_atual(g,"Gilmar","RURA11","06/fevereiro/2026",0.12000000,'D',245);
	proventos_atual(g,"Eliana","RURA11","06/fevereiro/2026",0.12000000,'r',155);
	proventos_atual(g,"Gilmar","RZTR11","06/fevereiro/2026",1.00000000,'D',25);
	proventos_atual(g,"Gilmar","CXCE11","13/fevereiro/2026",0.47963636,'r',110);
	proventos_atual(g,"Gilmar","MXRF11","13/fevereiro/2026",0.10000000,'R',95);
	proventos_atual(g,"Gilmar","XPCA11","13/fevereiro/2026",0.12000000,'D',450);
	proventos_atual(g,"Gilmar","RZAG11","13/fevereiro/2026",0.12000000,'D',200);
	proventos_atual(g,"Gilmar","VGIA11","20/fevereiro/2026",0.145000,'r',271);
	proventos_atual(g,"Gilmar","PETR4","20/fevereiro/2026",0.47160377,'J',721);
	proventos_atual(g,"Getúlio","PETR4","20/fevereiro/2026",0.47160377,'J',67);
	proventos_atual(g,"Eliana","PETR4","20/fevereiro/2026",0.47160377,'J',182);
	proventos_atual(g,"Gilmar","KLBN4","27/fevereiro/2026",0.04559717,'D',2807);
	
	proventos__atual(g,"Gilmar","BBDC3","02/março/2026",0.01721212,'J',50,0.175); // aquii
	proventos_atual(g,"Gilmar","BBSE3","02/março/2026",0.044,'R',15);
	proventos_atual(g,"Gilmar","BBSE3","02/março/2026",2.549334,'D',15);
	proventos_atual(g,"Gilmar","VALE3","04/março/2026",0.768133538,'D',5);
	proventos_atual(g,"Gilmar","VALE3","04/março/2026",1.569535033,'J',5);
	proventos__atual(g,"Gilmar","BBAS3","05/março/2026",0.21630740,'J',266,0.175);  
	proventos__atual(g,"Eliana","BBAS3","05/março/2026",0.21630740,'J',25,0.175);
	proventos_atual(g,"Gilmar","BBAS3","05/março/2026",0.0040206,'r',266);
	proventos_atual(g,"Eliana","BBAS3","05/março/2026",0.0040206,'r',25);
	proventos_atual(g,"Gilmar","RURA11","06/março/2026",0.12000000,'D',245); 
	proventos_atual(g,"Eliana","RURA11","06/março/2026",0.12000000,'D',155);
	proventos_atual(g,"Gilmar","RZTR11","06/março/2026",1.00000000,'D',25);
	proventos__atual(g,"Gilmar","BBAS3","11/março/2026",0.070144746,'J',266,0.175); 
	proventos__atual(g,"Eliana","BBAS3","11/março/2026",0.070144746,'J',25,0.175); 
	proventos_atual(g,"Gilmar","XPCA11","13/março/2026",0.12000000,'D',450);
	proventos_atual(g,"Gilmar","CXCE11","13/março/2026",0.472454545,'r',110);
	proventos_atual(g,"Gilmar","MXRF11","13/março/2026",0.10000000,'R',150);
	proventos_atual(g,"Gilmar","RZAG11","13/março/2026",0.12000000,'D',262);
	proventos_atual(g,"Gilmar","VGIA11","18/março/2026",0.145000,'r',271);
	proventos_atual(g,"Gilmar","PETR4","20/março/2026",0.175182,'J',721);
	proventos_atual(g,"Getúlio","PETR4","20/março/2026",0.175182,'J',67);
	proventos_atual(g,"Eliana","PETR4","20/março/2026",0.175182,'J',182); 
	proventos_atual(g,"Gilmar","PETR4","20/março/2026",0.29641237113,'D',721);
	proventos_atual(g,"Getúlio","PETR4","20/março/2026",0.29641237113,'D',67);
	proventos_atual(g,"Eliana","PETR4","20/março/2026",0.29641237113,'D',182);
	proventos_atual(g,"Gilmar","PETR4","20/março/2026",0.0069381443298969,'R',721);
	proventos_atual(g,"Getúlio","PETR4","20/março/2026",0.0069381443298969,'R',67);
	proventos_atual(g,"Eliana","PETR4","20/março/2026",0.0069381443298969,'R',182); 
	proventos_atual(g,"Gilmar","PETR4","20/março/2026",0.00410309,'R',721);
	proventos_atual(g,"Getúlio","PETR4","20/março/2026",0.00410309,'R',67);
	proventos_atual(g,"Eliana","PETR4","20/março/2026",0.00410309,'R',182); 
	
	proventos__atual(g,"Gilmar","BBDC3","01/abril/2026",0.01721212,'J',50,0.175);
	proventos_atual(g,"Gilmar","GARE11","07/abril/2026",0.083,'r',25);
	proventos_atual(g,"Gilmar","RURA11","08/abril/2026",0.12000000,'r',245); 
	proventos_atual(g,"Eliana","RURA11","08/abril/2026",0.12000000,'r',155);
	proventos_atual(g,"Gilmar","RZTR11","08/abril/2026",1.00000000,'D',26);
	proventos_atual(g,"Gilmar","XPCA11","15/abril/2026",0.11000000,'r',450);
	proventos_atual(g,"Gilmar","CXCE11","15/abril/2026",0.47709090909,'r',110);
	proventos_atual(g,"Gilmar","MXRF11","15/abril/2026",0.09500000,'R',200);
	proventos_atual(g,"Gilmar","RZAG11","15/abril/2026",0.12000000,'r',262);
	proventos_atual(g,"Gilmar","VGIA11","18/abril/2026",0.140000,'r',271);
	proventos_atual(g,"Gilmar","BBDC3","30/abril/2026",0.270117647,'J',50); 
	
	//parei aqui
	
	proventos__atual(g,"Gilmar","BBDC3","04/maio/2026",0.01721212,'J',50,0.175);
	proventos_atual(g,"Gilmar","FLRY3","05/maio/2026",0.04,'D',2);
	proventos_atual(g,"Gilmar","GARE11","08/maio/2026",0.083,'r',61);
	proventos_atual(g,"Gilmar","RURA11","08/maio/2026",0.113000,'r',245); 
	proventos_atual(g,"Eliana","RURA11","08/maio/2026",0.113000,'r',155);
	proventos_atual(g,"Gilmar","RZTR11","08/maio/2026",1.00000000,'D',28);
	proventos_atual(g,"Gilmar","CXCE11","15/maio/2026",0.4566363,'r',110);
	proventos_atual(g,"Gilmar","CXSE3","15/maio/2026",0.33,'D',340);
	proventos_atual(g,"Gilmar","MXRF11","15/maio/2026",0.1000000,'R',200);
	proventos_atual(g,"Gilmar","RZAG11","15/maio/2026",0.12000000,'r',262);
	proventos_atual(g,"Gilmar","XPCA11","15/maio/2026",0.10000000,'r',450);
	proventos_atual(g,"Gilmar","KLBN4","20/maio/2026",0.04559717,'D',2807);
	proventos_atual(g,"Gilmar","PETR4","20/maio/2026",0.31311454,'J',735); 
	proventos_atual(g,"Getúlio","PETR4","20/maio/2026",0.31311454,'J',67); 
	proventos_atual(g,"Eliana","PETR4","20/maio/2026",0.31311454,'J',182);
	proventos_atual(g,"Gilmar","PETR4","20/maio/2026",0.0105583756345178,'r',735); 
	proventos_atual(g,"Getúlio","PETR4","20/maio/2026",0.0105583756345178,'r',67); 
	proventos_atual(g,"Eliana","PETR4","20/maio/2026",0.0105583756345178,'r',182);
	proventos_atual(g,"Gilmar","VGIA11","20/maio/2026",0.13,'R',271);
	proventos__atual(g,"Gilmar","BMGB4","21/maio/2026",0.10,'J',271,0.175);
	proventos_atual(g,"Gilmar","SNEL11","25/maio/2026",0.10,'R',30);
	proventos_atual(g,"Gilmar","TAEE4","27/maio/2026",0.051133333,'D',150);
	proventos_atual(g,"Gilmar","TAEE4","27/maio/2026",0.2517333333,'D',150);
	proventos_atual(g,"Gilmar","BRBI11","29/maio/2026",0.180,'D',50);

	proventos__atual(g,"Gilmar","BBDC3","01/junho/2026",0.01721212,'J',50,0.175);
	proventos_atual(g,"Gilmar","RURA11","08/junho/2026",0.110000,'r',295); 
	proventos_atual(g,"Eliana","RURA11","08/junho/2026",0.110000,'r',155);
	proventos_atual(g,"Gilmar","GARE11","08/junho/2026",0.083000,'r',218); 
	proventos_atual(g,"Gilmar","RZTR11","08/junho/2026",1.00000000,'r',29);
	proventos_atual(g,"Getúlio","RZTR11","08/junho/2026",1.00000000,'r',22);
	proventos_atual(g,"Gilmar","GGRC11","09/junho/2026",0.100000000,'r',49);
    proventos__atual(g,"Gilmar","BBAS3","11/junho/2026",0.08157785203,'J',266,0.175);
	proventos__atual(g,"Eliana","BBAS3","11/junho/2026",0.08157785203,'J',25,0.175);  
	proventos_atual(g,"Gilmar","RZAG11","15/junho/2026",0.12000000,'r',262); 
	proventos_atual(g,"Gilmar","XPCA11","15/junho/2026",0.10000000,'r',450);
	proventos_atual(g,"Gilmar","MXRF11","15/junho/2026",0.1000000,'R',200);
	proventos_atual(g,"Eliana","MXRF11","15/junho/2026",0.1000000,'R',50);
	proventos_atual(g,"Gilmar","CXCE11","15/junho/2026",0.47257116,'r',110);
	proventos_atual(g,"Gilmar","VGIA11","18/junho/2026",0.130000,'r',271);
	proventos_atual(g,"Gilmar","PETR4","22/junho/2026",0.31311454,'J',735);
	proventos_atual(g,"Getúlio","PETR4","22/junho/2026",0.31311454,'J',67); 
	proventos_atual(g,"Eliana","PETR4","22/junho/2026",0.31311454,'J',182);
	proventos_atual(g,"Gilmar","PETR4","22/junho/2026",0.0105583756345178,'r',735);
	proventos_atual(g,"Getúlio","PETR4","22/junho/2026",0.0105583756345178,'r',67); 
	proventos_atual(g,"Eliana","PETR4","22/junho/2026",0.0105583756345178,'r',182);
	proventos_atual(g,"Gilmar","SNEL11","25/junho/2026",0.10,'R',124);
	proventos_atual(g,"Gilmar","CMIG4","30/junho/2026",0.1056,'J',50);
	proventos_atual(g,"Gilmar","CMIG4","30/junho/2026",0.1043,'J',50);
	proventos_atual(g,"Gilmar","CMIG4","30/junho/2026",0.11847058,'J',100);
    proventos_atual(g,"Gilmar","CMIG4","30/junho/2026",0.1181,'D',100);
	 
	// rztr11 rura11 gare11 mxrf11 cxce11 rzag11 xpca11 ggrc11 vgia11 snel11
	proventos__atual(g,"Gilmar","BBDC3","01/julho/2026",0.01721212,'J',50,0.175);
	proventos_atual(g,"Gilmar","RURA11","07/julho/2026",0.110000,'r',295); 
	proventos_atual(g,"Eliana","RURA11","07/julho/2026",0.110000,'r',155);
	proventos_atual(g,"Gilmar","RZTR11","07/julho/2026",0.90000000,'r',29);
	proventos_atual(g,"Getúlio","RZTR11","07/julho/2026",0.90000000,'r',22);
	proventos_atual(g,"Gilmar","GARE11","07/julho/2026",0.083000,'r',300);
	proventos_atual(g,"Gilmar","PORD11","07/julho/2026",0.0980,'r',30);
	proventos_atual(g,"Gilmar","GGRC11","08/julho/2026",0.100000000,'r',110);
	proventos_atual(g,"Gilmar","RZAG11","14/julho/2026",0.12000000,'r',262); 
	proventos_atual(g,"Gilmar","XPCA11","14/julho/2026",0.10000000,'r',450);
	proventos_atual(g,"Gilmar","MXRF11","14/julho/2026",0.1000000,'R',200);
	proventos_atual(g,"Eliana","MXRF11","14/julho/2026",0.1000000,'R',50);
	proventos_atual(g,"Gilmar","CXCE11","15/julho/2026",0.45994000,'r',110);
	proventos_atual(g,"Gilmar","VGIA11","17/julho/2026",0.13,'r',271);
	proventos_atual(g,"Gilmar","SNEL11","24/julho/2026",0.10,'R',208);
	proventos_atual(g,"Gilmar","BBDC3","31/julho/2026",0.351190,'J',50);
	
	proventos__atual(g,"Gilmar","BBDC3","03/agosto/2026",0.01721212,'J',50,0.175);
	proventos_atual(g,"Gilmar","RURA11","07/agosto/2026",0.110000,'r',295); 
	proventos_atual(g,"Eliana","RURA11","07/agosto/2026",0.110000,'r',155);
	proventos_atual(g,"Gilmar","RZTR11","07/agosto/2026",0.90000000,'r',29);
	proventos_atual(g,"Getúlio","RZTR11","07/agosto/2026",0.90000000,'r',22);
	proventos_atual(g,"Gilmar","GARE11","07/agosto/2026",0.083000,'r',379);
	proventos_atual(g,"Gilmar","PORD11","07/agosto/2026",0.0980,'r',103);
	proventos_atual(g,"Gilmar","GGRC11","10/agosto/2026",0.100000000,'r',170);
	proventos_atual(g,"Gilmar","RZAG11","14/agosto/2026",0.13000000,'r',262); 
	proventos_atual(g,"Gilmar","XPCA11","14/agosto/2026",0.10000000,'r',450);
	proventos_atual(g,"Eliana","MXRF11","14/agosto/2026",0.1000000,'R',50);
	proventos_atual(g,"Gilmar","CXCE11","14/agosto/2026",0.47948000,'r',110);
	proventos_atual(g,"Gilmar","CXSE3","17/agosto/2026",0.35,'D',340);
	proventos_atual(g,"Gilmar","RBRR11","18/agosto/2026",0.9,'D',7);
	proventos_atual(g,"Gilmar","KLBN4","19/agosto/2026",0.04559717,'D',2807);
	proventos_atual(g,"Gilmar","VGIA11","19/agosto/2026",0.13,'r',239);
	proventos__atual(g,"Gilmar","PETR4","20/agosto/2026",0.35048636,'J',735,0.175);
	proventos__atual(g,"Getúlio","PETR4","20/agosto/2026",0.35048636,'J',67,0.175);
	proventos__atual(g,"Eliana","PETR4","20/agosto/2026",0.35048636,'J',182,0.175);
	proventos_atual(g,"Gilmar","SNEL11","24/agosto/2026",0.10,'R',290);
	proventos_atual(g,"NAN","SNEL11","24/agosto/2026",0.10,'R',80);
	proventos__atual(g,"Gilmar","TAEE4","26/agosto/2026",0.186332,'j',150,0.175);
	proventos_atual(g,"Gilmar","BRBI11","28/agosto/2026",0.18,'d',50);
	

	proventos__atual(g,"Gilmar","BBDC3","01/setembro/2026",0.01721212,'J',50,0.175);
	proventos__atual(g,"Gilmar","VALE3","02/setembro/2026",1.56870581,'J',5,0.175);
	proventos_atual(g,"Gilmar","VALE3","02/setembro/2026",0.46201609,'D',5);
	proventos__atual(g,"Gilmar","BMGB4","04/setembro/2026",0.10,'J',271,0.175);
	proventos_atual(g,"Gilmar","RURA11","08/setembro/2026",0.105000,'r',295);                 //////////
	proventos_atual(g,"Eliana","RURA11","08/setembro/2026",0.105000,'r',155);                 //////////
	proventos_atual(g,"Gilmar","GARE11","08/setembro/2026",0.083000,'r',420);               //////////
	proventos_atual(g,"Gilmar","PORD11","08/setembro/2026",0.098000,'r',166);               //////////
	proventos_atual(g,"Gilmar","RZTR11","08/setembro/2026",0.85000000,'r',29);              //////////
	proventos_atual(g,"Getúlio","RZTR11","08/setembro/2026",0.85000000,'r',22);             //////////
	proventos_atual(g,"Gilmar","GGRC11","09/setembro/2026",0.10000000,'r',270);             //////////
	proventos_atual(g,"NAN","GGRC11","09/setembro/2026",0.10000000,'r',30);                 //////////
	proventos__atual(g,"Gilmar","BBAS3","11/setembro/2026",0.10413811686,'J',275,0.175);  //////////
	proventos__atual(g,"Eliana","BBAS3","11/setembro/2026",0.10413811686,'J',25,0.175);
	proventos__atual(g,"Gilmar","BBAS3","11/setembro/2026",0.00281400,'R',275,0.175);  //////////
	proventos__atual(g,"Eliana","BBAS3","11/setembro/2026",0.00281400,'R',25,0.175);
	proventos__atual(g,"Gilmar","BBAS3","11/setembro/2026",0.03450628,'J',275,0.175);  //////////
	proventos__atual(g,"Eliana","BBAS3","11/setembro/2026",0.03450628,'J',25,0.175);
	proventos_atual(g,"Gilmar","CXCE11","15/setembro/2026",0.4758,'r',115);               ///////////
	proventos_atual(g,"NAN","CXCE11","15/setembro/2026",0.4758,'r',5);                    //////////
	proventos_atual(g,"Eliana","MXRF11","15/setembro/2026",0.1000000,'R',50);             //////////
	proventos__atual(g,"Gilmar","BBDC3","15/setembro/2026",0.31535904,'J',50,0.175);
	proventos__atual(g,"Gilmar","BBDC3","15/setembro/2026",0.27030774,'J',50,0.175);
	proventos_atual(g,"Gilmar","XPCA11","15/setembro/2026",0.10000000,'r',200);            //////////
	proventos_atual(g,"Gilmar","RZAG11","15/setembro/2026",0.12500000,'r',262);            /////////
	proventos_atual(g,"Gilmar","RBRR11","17/setembro/2026",0.9,'D',10);
	proventos__atual(g,"Gilmar","PETR4","21/setembro/2026",0.35048636,'J',735,0.175);
	proventos__atual(g,"Getúlio","PETR4","21/setembro/2026",0.35048636,'J',67,0.175); //pg
	proventos__atual(g,"Eliana","PETR4","21/setembro/2026",0.35048636,'J',182,0.175); //pg
	proventos_atual(g,"Gilmar","SNEL11","24/agosto/2026",0.10,'R',420);
	proventos_atual(g,"NAN","SNEL11","24/setembro/2026",0.10,'R',80);
	proventos__atual(g,"Gilmar","BBDC3","31/setembro/2026",0.35119075,'J',50,0.175);
	
	 
	proventos__atual(g,"Gilmar","BBDC3","01/outubro/2026",0.01721212,'J',50,0.175);
	proventos__atual(g,"Gilmar","FLRY3","02/outubro/2026",0.400732,'J',2,0.175);
	proventos_atual(g,"Gilmar","FLRY3","02/outubro/2026",0.130271,'d',2);
	proventos_atual(g,"Gilmar","PORD11","07/outubro/2026",0.098000,'r',210);
	proventos_atual(g,"Gilmar","RURA11","07/outubro/2026",0.100000,'r',245);                
	proventos_atual(g,"Eliana","RURA11","07/outubro/2026",0.100000,'r',155);
	proventos_atual(g,"Gilmar","RZTR11","07/outubro/2026",0.85000000,'r',29);              //////////
	proventos_atual(g,"Getúlio","RZTR11","07/outubro/2026",0.85000000,'r',22);
	proventos_atual(g,"Gilmar","GARE11","07/outubro/2026",0.083000,'r',420);
	proventos_atual(g,"Gilmar","GGRC11","08/outubro/2026",0.10000000,'r',270);             //////////
	proventos_atual(g,"NAN","GGRC11","08/outubro/2026",0.10000000,'r',30); 
	proventos_atual(g,"Gilmar","XPCA11","15/outubro/2026",0.10000000,'r',200);           
	proventos_atual(g,"Gilmar","RZAG11","15/outubro/2026",0.12500000,'r',262);
	proventos_atual(g,"Eliana","MXRF11","15/outubro/2026",0.1000000,'R',50); 
	proventos_atual(g,"Gilmar","HGLG11","15/outubro/2026",1.1700000,'R',5); 
	proventos_atual(g,"Gilmar","CXCE11","15/outubro/2026",0.4795,'r',115);               ///////////
	proventos_atual(g,"NAN","CXCE11","15/outubro/2026",0.4795,'r',5);
	
	
	proventos__atual(g,"Gilmar","BBDC3","03/novembro/2026",0.01702,'J',50,0.175);
	proventos_atual(g,"Gilmar","KLBN4","12/novembro/2026",0.04559717,'D',2807);
	proventos_atual(g,"Gilmar","CXSE3","17/novembro/2026",0.35,'D',340);
	proventos__atual(g,"Gilmar","PETR4","23/novembro/2026",0.67407131,'J',736,0.175);
	proventos__atual(g,"Eliana","PETR4","23/novembro/2026",0.67407131,'J',169,0.175); //pg
	
	proventos__atual(g,"Gilmar","BBDC3","01/dezembro/2026",0.01702,'J',50,0.175);
	proventos_atual(g,"Gilmar","PETR4","21/dezembro/2026",0.47156696,'D',736);
	proventos_atual(g,"Eliana","PETR4","21/dezembro/2026",0.47156696,'D',169); //pg
	proventos__atual(g,"Gilmar","PETR4","21/dezembro/2026",0.20250435,'J',736,0.175); 
	proventos__atual(g,"Eliana","PETR4","21/dezembro/2026",0.20250435,'J',169,0.175); //pg
	
	proventos__atual(g,"Gilmar","CMIG4","30/dezembro/2026",0.105698,'J',50,0.175);
    proventos_atual(g,"Gilmar","CMIG4","30/dezembro/2026",0.118177,'D',100);
	proventos__atual(g,"Gilmar","CMIG4","30/dezembro/2026",0.104303,'J',50,0.175);
	proventos__atual(g,"Gilmar","CMIG4","30/dezembro/2026",0.118401,'J',100,0.175);
	
}

/*
proventos__atual(g,"Gilmar","CMIG4","30/junho/2027",0.1150,'J',100,0.175);
proventos__atual(g,"Gilmar","CMIG4","30/junho/2027",0.110202,'J',110,0.175);
proventos__atual(g,"Gilmar","CMIG4","30/junho/2027",0.06991340114,'J',110,0.175);
proventos_atual(g,"Gilmar","FLRY3","02/setembro/2027",0.130271,'d',2);
proventos__atual(g,"Gilmar","CMIG4","30/dezembro/2027",0.1150,'J',100,0.175);
proventos__atual(g,"Gilmar","CMIG4","30/dezembro/2027",0.110202,'J',110,0.175);
proventos__atual(g,"Gilmar","CMIG4","30/dezembro/2027",0.06991340114,'J',110,0.175);
*/


