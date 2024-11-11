//Comente cada parte que forem fazer para que possamos entender o que cada um fez :)

#include <stdio.h>//usa as funções básicas
#include <string.h>//usa funções de comparações e de tamanho
#include <ctype.h>//usa verificação de tamanho de números, letras mauiúsculas etc
#include <locale.h>//deixa o texto bonitinho

//Função para validar a senha
int ValidacaoDeSenha(char *senha){
    int maiusc = 0;
    int num = 0;
    int tamanho = strlen(senha);

    if (tamanho < 8){
        printf("\nA senha deve conter pelo menos 8 dígitos.\n");
        return 0; 
    }

    for (int i= 0;i<tamanho;i++){
        if (isupper(senha[i])){
            maiusc = 1;
        }
        if (isdigit(senha[i])){
            num++;
        }
        if (maiusc && num >= 3) break;//Arrumei o nosso erro mudando a posição do break.
    }

    if (maiusc == 0){
        printf("\nA senha deve conter pelo menos uma letra MAIÚSCULA.\n");
        return 0;
    }

    if (num < 3){
        printf("\nA senha deve conter pelo menos 3 números.\n");
        return 0;
    }

    return 1;
}

//Função da criptografia em XOR
int CifraXOR(char *mensagem, char chave){
    for (int i = 0; mensagem[i] != '\0'; i++){
        mensagem[i] = mensagem[i] ^ chave; 
    }
}

//Função para arrumar o erro de leitura
int limparBuffer(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função para exibir a criptografia para o funcionário
int exibirArquivoCriptografado(const char *arquivo, char chave){
    FILE *f = fopen(arquivo, "r");
    if (f == NULL){
        printf("Erro ao abrir o arquivo %s. Verifique se o arquivo existe e as permissões estão corretas.\n", arquivo);
        return 1;
    }

    char linha[256];
    printf("\nConteúdo criptografado %s:\n", arquivo);
    while (fgets(linha, sizeof(linha), f)){
        CifraXOR(linha, chave);  // Criptografa a linha antes de mostrar
        printf("%s", linha);
    }

    fclose(f);
}

//Função para criar a cópia de um arquivo e criptografar ela
int criarCopiaCriptografada(const char *arquivoOriginal, const char *arquivoDestino, char chave){
    FILE *original = fopen(arquivoOriginal, "r");
    if (original == NULL){
        printf("Erro ao abrir o arquivo original %s.\n", arquivoOriginal);
        return 1;
    }

    FILE *destino = fopen(arquivoDestino, "w");
    if (destino == NULL){
        printf("Erro ao abrir o arquivo %s.\n", arquivoDestino);
        fclose(original);
        return 1;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), original)){
        CifraXOR(linha, chave);
        fprintf(destino, "%s", linha);
    }

    fclose(original);
    fclose(destino);
    printf("Cópia criptografada criada com sucesso em %s.\n", arquivoDestino);
}

int main(){
    char Cadastrousuario[100], Cadastrosenha[100], usuario[100], senha[100];
    char nivelAcesso[10], mensagem[200];
    char chaveXOR = 0xAA;  

    setlocale(LC_ALL, "Portuguese");

//Escopo principal do cadastro
    printf("Para se cadastrar, deve-se digitar o nome de usuário, senha e nível de acesso.\n");
    printf("-------------------------------------------------------------\n");

    printf("\nDigite o seu nome de usuário: ");
    if (fgets(Cadastrousuario, sizeof(Cadastrousuario), stdin) != NULL){
        Cadastrousuario[strcspn(Cadastrousuario, "\n")] = '\0';
    }
    limparBuffer();  

    printf("\nDigite sua senha (Deve conter pelo menos 8 dígitos, 3 números e pelo menos uma letra MAIÚSCULA): ");
    if (fgets(Cadastrosenha, sizeof(Cadastrosenha), stdin) != NULL){
        Cadastrosenha[strcspn(Cadastrosenha, "\n")] = '\0';
    }
    limparBuffer();  

    if (!ValidacaoDeSenha(Cadastrosenha)){
        printf("Senha inválida! Tente novamente.\n");
        return 1;
    }

    printf("\nEscolha o nível de acesso (funcionario, gerente, RH): ");
    if (fgets(nivelAcesso, sizeof(nivelAcesso), stdin) != NULL){
        nivelAcesso[strcspn(nivelAcesso, "\n")] = '\0';
        for (int i=0;nivelAcesso[i];i++){
            nivelAcesso[i] = tolower(nivelAcesso[i]);
        }
    }
    limparBuffer();  

    printf("\n-----------------------------------------------------------\n");
    printf("Cadastro efetuado com sucesso!\n");

//Escopo para registrar todos os cadastros no arquivo 
    FILE *arquivo = fopen("cadastros.txt", "a");
    if (arquivo != NULL){
        fprintf(arquivo, "Usuário: %s, Senha: %s, Nível de Acesso: %s\n", Cadastrousuario, Cadastrosenha, nivelAcesso);
        fclose(arquivo);
        printf("Cadastro registrado no arquivo de RH (cadastros.txt).\n");

        // Criar cópia criptografada de 'cadastros.txt' para 'cadastros_criptografado.txt'
        criarCopiaCriptografada("cadastros.txt", "cadastros_criptografado.txt", chaveXOR);
    }else{
        printf("Erro ao abrir o arquivo de cadastros.\n");
    }

//Escopo do login
    printf("\nFaça o login.\n");
    printf("Digite o seu nome de usuário: ");
    if (fgets(usuario, sizeof(usuario), stdin) != NULL){
        usuario[strcspn(usuario, "\n")] = '\0';
    }
    limparBuffer();  // Limpar o buffer após a entrada

    printf("Digite a sua senha: ");
    if (fgets(senha, sizeof(senha), stdin) != NULL){
        senha[strcspn(senha, "\n")] = '\0';
    }
    limparBuffer();  // Limpar o buffer após a entrada

//Validação se o login é igual ao cadastro
    if (strcmp(usuario, Cadastrousuario) == 0 && strcmp(senha, Cadastrosenha) == 0){
        printf("LOGIN bem-sucedido.\n");

//Se o usuário for um funcionário, exibir o conteúdo criptografado do arquivo do gerente
        if (strcmp(nivelAcesso, "funcionario") == 0){
            printf("Acesso ao arquivo: gerente_criptografado.txt\n");
            exibirArquivoCriptografado("gerente_criptografado.txt", chaveXOR);
        } 
//Se o usuário for um gerente, ele pode escrever no arquivo e criar uma cópia criptografada que será mostrada para outros cargos
        else if (strcmp(nivelAcesso, "gerente") == 0){
            printf("Acesso ao arquivo: gerente.txt\n");
            printf("Digite uma mensagem para registrar no arquivo de gerente:\n");
            if (fgets(mensagem, sizeof(mensagem), stdin) != NULL){
                mensagem[strcspn(mensagem, "\n")] = '\0';  // Remove a quebra de linha
            }

            arquivo = fopen("gerente.txt", "a");
            if (arquivo != NULL){
                fprintf(arquivo, "Gerente %s escreveu: %s\n", usuario, mensagem);
                fclose(arquivo);
                printf("Mensagem escrita no arquivo de gerente com sucesso.\n");

// Criar uma cópia do arquivo do gerente criptografando ela
                arquivo = fopen("gerente_criptografado.txt", "a");
                if (arquivo != NULL){

                    CifraXOR(mensagem, chaveXOR);
                    fprintf(arquivo, "Gerente %s escreveu: %s\n", usuario, mensagem);
                    fclose(arquivo);
                    printf("Mensagem criptografada copiada para 'gerente_criptografado.txt'.\n");
                }
            }else{
                printf("Erro ao abrir o arquivo de gerente.\n");
            }
        } 
    }else{
        printf("Falha ao logar. Verifique se o usuário ou a senha foram digitados corretamente.\n");
    }

    return 0;
}

