#include <stdio.h>//usado para funções básicas de entrada e saída.
#include <string.h>//usado para funções str para verificar comprimento, igualdade etc.
#include <ctype.h>//usado para verificação de ocorrencia de números e letras maiúsculas na senha.
#include <locale.h>//usado pra deixar bonitinho a escrita.

// Função de validação de senha.
int ValidacaoDeSenha(char *senha){
    int maiusc = 0;
    int num = 0;
    int tamanho = strlen(senha);

    if (tamanho <= 8){
        printf("\nA senha possui menos de 8 dígitos, tente novamente.\n");
        return 0;
    }

    for (int i=0;i<tamanho;i++){
        if (isupper(senha[i])){
            maiusc = 1;
        }
        if (isdigit(senha[i])){
            num++;
        }
    }

    if (maiusc == 0) {
        printf("\nA senha deve conter pelo menos uma letra MAIÚSCULA.\n");
        return 0;
    }

    if (num < 3){
        printf("\nA senha deve conter pelo menos 3 números.\n");
        return 0;
    }

    return 1;
}
//Função principal
int main(){
    char Cadastrousuario[100], Cadastrosenha[100], usuario[100], senha[100];
    
    setlocale(LC_ALL, "Portuguese");
    
//Escopo principal do cadastro
    printf("Para se cadastrar, deve-se digitar o nome de usuário e senha.\n");
    printf("-------------------------------------------------------------\n");
    printf("\nDigite o seu nome de usuário: ");
    if (fgets(Cadastrousuario, sizeof(Cadastrousuario), stdin) != NULL){
        Cadastrousuario[strcspn(Cadastrousuario, "\n")] = '\0';
    }
    printf("\nDigite sua senha (Deve conter pelo menos 8 dígitos, 3 números e pelo menos uma letra MAIÚSCULA): ");
    if (fgets(Cadastrosenha, sizeof(Cadastrosenha), stdin) != NULL){
        Cadastrosenha[strcspn(Cadastrosenha, "\n")] = '\0';
    }
    printf("\n-----------------------------------------------------------\n");
    if (!ValidacaoDeSenha(Cadastrosenha)){
        printf("Senha inválida!Tente novamente.\n");
        return 1;
    }
    printf("Cadastro efetuado!\n");

//Escopo do login
    printf("\nFaça o login.\n");
    printf("Digite o seu nome de usuário: ");
    if (fgets(usuario, sizeof(usuario), stdin) != NULL){
        usuario[strcspn(usuario, "\n")] = '\0';
    }
    printf("Digite a sua senha: ");
    if (fgets(senha, sizeof(senha), stdin) != NULL){
        senha[strcspn(senha, "\n")] = '\0';
    }

//Validação se o login corresponde ao cadastro
    if (strcmp(usuario, Cadastrousuario) == 0 && strcmp(senha, Cadastrosenha) == 0){
        printf("LOGIN bem-sucedido.\n");
    }else{
        printf("Falha ao logar. Verifique se o usuário ou a senha foram digitados corretamente.\n");
    }

    return 0;
}
