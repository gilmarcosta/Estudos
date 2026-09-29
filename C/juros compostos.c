#include <stdio.h>
#include <stdlib.h>

int main(){
	int cont = 0;
	float digito = 100000.00f;
	long long pivor = (long long)((((7.0/12)/100)+1)*100000);
	printf("%I64d\n",pivor);
	long long valor = (long long) (digito * 100);
	
	while(cont<12){
		valor = (valor * pivor)/100000;
		cont ++;
		printf("%I64d \n",valor);
	}
	
	
	int centavos = valor%100;
	long long real = valor /100; //exclui os centavos
	int unidade = real % 1000;
	int milhar = (real/1000) % 1000;
	
	
	printf("%03d.%03d,%02d\n",milhar,unidade,centavos);
	
	return 0;
}