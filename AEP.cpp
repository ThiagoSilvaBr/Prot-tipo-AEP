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
		printf("\nA senha possui menos de 8 dígitos, tente novamente.\n");
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
		printf("\nA senha deve conter pelo menos uma letra Maiúscula. \n");
		return 0;
	}
	
	if(num < 3){
		printf("\nA senha deve conter pelo menos 3 números. \n");
		return 0;
	}
	
	return 1;
}

int main(){
	char usuario [100], senha [100];
	int tamanho;
	
	
	
	
	setlocale(LC_ALL, "Portuguese");
	
	
	
	printf("Para se cadastrar, deve-se digitar o nome de usuário e senha.\n");
	printf("-------------------------------------------------------------\n");
	printf("\nDigite o seu nome de usuário: ");
	fgets(usuario, sizeof(usuario), stdin) != NULL;
	printf("\nDigite sua senha(Deve conter pelo menos 8 dígitos, 3 números e pelo menos uma letra MAIÚSCULA): ");
	fgets(senha, sizeof(senha), stdin);
	printf("\n-----------------------------------------------------------\n");
	
	if(ValidacaoDeSenha(senha)){
		printf("\nSenha valida!\n");
	}else{
		printf("\nSenha não valida!\n");
	}
	
	
	return 1;
}
