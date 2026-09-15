#include <stdlib.h>
#include <stdio.h>




void tamanho_mes(char datI[],int *mes, int *tam);
void data(char *mes, int *codigo);





void data(char *mes, int *codigo){
	int mes_num,dia,ano,tam;
	tamanho_mes(mes,&mes_num,&tam);
	dia = ((mes[0] - '0')*10) + (mes[1] - '0');
	ano = ((mes[tam+4] - '0') *1000) + ((mes[tam+5] - '0') *100) + ((mes[tam+6] - '0')*10) + (mes[tam+7] - '0');
	*codigo = (ano * 10000) + (mes_num * 100) + dia;
}

void tamanho_mes(char datI[],int *mes, int *tam){
	int ind = 3;
		 
	if(datI[ind] == 'j'){
		if(datI[ind+1] == 'a'){
			*mes = 1;
			*tam = 7;
		}else{
			*mes = 6;
			*tam = 5;
		}
	}else{	
		if(datI[ind] == 'f'){
			*mes = 2;
			*tam = 9;
		}else{
			if(datI[ind] == 'm'){
				if(datI[ind+2]=='r'){
					*mes = 3;
					*tam = 5;
				}else{
					*mes = 5;
					*tam = 4;
				}
			}else{
				if(datI[ind] == 'a'){
					if(datI[ind+1]=='b'){
						*mes = 4;
						*tam = 5;
					}else{
						*mes = 8;
						*tam = 6;
					}
				}else{
					if(datI[ind] == 's'){
						*mes = 9;
						*tam = 8;
					}else{
						if(datI[ind] == 'o'){
							*mes = 10;
							*tam = 7;
						}else{
							if(datI[ind] == 'n'){
								*mes = 11;
								*tam = 8;
							}else{
								if(datI[ind] == 'd'){
									*mes = 12;
									*tam = 8;
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
}

int main(){
	int codigo;
	data("15/dezembro/2025",&codigo);
	printf("codigo: %i",codigo);
	return 0;
}






