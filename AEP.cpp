#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

int  ValidacaoDeSenha(char *senha){
	int maiusc = 0;
	int num = 0;
	int tamanho = strlen(senha);
	
	
	
	if(tamanho <= 8){
		printf("\nA senha possui menos de 8 d�gitos, tente novamente.\n");
		return 0;
	}
	
	for(int i=0;i<tamanho;i++){
		if(isupper(senha[i])){
			maiusc = 1;
			break;
		}
		if(isdigit(senha[i])){
			num++;
		}
	}
	
	if(maiusc == 0){
		printf("\nA senha deve conter pelo menos uma letra Mai�scula. \n");
		return 0;
	}
	
	if(num < 3){
		printf("\nA senha deve conter pelo menos 3 n�meros. \n");
		return 0;
	}
	
	return 1;
}

int main(){
	char usuario [100], senha [100];
	int tamanho;
	
	
	
	
	setlocale(LC_ALL, "Portuguese");
	
	
	
	printf("Para se cadastrar, deve-se digitar o nome de usu�rio e senha.\n");
	printf("-------------------------------------------------------------\n");
	printf("\nDigite o seu nome de usu�rio: ");
	fgets(usuario, sizeof(usuario), stdin) != NULL;
	printf("\nDigite sua senha(Deve conter pelo menos 8 d�gitos, 3 n�meros e pelo menos uma letra MAI�SCULA): ");
	fgets(senha, sizeof(senha), stdin);
	printf("\n-----------------------------------------------------------\n");
	
	if(ValidacaoDeSenha(senha)){
		printf("\nSenha valida!\n");
	}else{
		printf("\nSenha n�o valida!\n");
	}
	
	
	return 1;
}
