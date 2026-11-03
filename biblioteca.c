#include <stdio.h>
#include "biblioteca.h"
#include <string.h>

int ler_codigo(void){
    int codigo;
    int resultado;
    int ch;

    while (1){
        printf("Insira o codigo: ");
        resultado = scanf("%d", &codigo);

        if (resultado == EOF) return -1;

        if (resultado != 1){
            printf("Entrada invalida. Apenas numeros, por favor\n");
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            if (ch == EOF) return -1;
            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        if (codigo < 100 || codigo > 999){
            printf("Entrada com mais ou menos de 3 digitos\n");
            if (ch == EOF) return -1;
            continue;
        }

        return codigo;
    }
}

int cadastrar_livro(Livro acervo[], int *quantidade, int capacidade){
    int cadastro_codigo;
    int resultado;
    
    if (*quantidade >= capacidade){
        printf("Biblioteca cheia. Nao eh possivel cadastrar novos livros agora");
        return 0;
    }

    cadastro_codigo = ler_codigo();
    if (cadastro_codigo == -1) return 0;
    do{    
        if (buscar_livro(acervo, *quantidade, cadastro_codigo) != -1){
                printf("Codigo ja em uso\n");
                cadastro_codigo = ler_codigo();
                if (cadastro_codigo == -1) return 0;
                
        }
    }while (buscar_livro(acervo, *quantidade, cadastro_codigo) != -1);
    acervo[*quantidade].codigo = cadastro_codigo;
    
    int texto_longo;
    int caractere;

    printf("Insira o titulo do livro, ate 100 caracteres: ");
    do{
        texto_longo = 0;
        if (fgets(acervo[*quantidade].titulo, sizeof(acervo[*quantidade].titulo), stdin) == NULL) return 0;
        if (strchr(acervo[*quantidade].titulo, '\n') == NULL &&
            strlen(acervo[*quantidade].titulo) == MAX_TITULO){
            caractere = getchar();
            if (caractere != '\n' && caractere != EOF){
                while (caractere != '\n' && caractere != EOF) caractere = getchar();
                texto_longo = 1;
                printf("Titulo muito grande, tente novamente: ");
            }
        }
    }while (texto_longo);
    acervo[*quantidade].titulo[strcspn(acervo[*quantidade].titulo, "\n")] = '\0';

    printf("Insira o nome do(a) autor(a) do livro, ate 80 caracteres: ");
    do{
        texto_longo = 0;
        if (fgets(acervo[*quantidade].autor, sizeof(acervo[*quantidade].autor), stdin) == NULL) return 0;
        if (strchr(acervo[*quantidade].autor, '\n') == NULL &&
            strlen(acervo[*quantidade].autor) == MAX_AUTOR){
            caractere = getchar();
            if (caractere != '\n' && caractere != EOF){
                while (caractere != '\n' && caractere != EOF) caractere = getchar();
                texto_longo = 1;
                printf("Autor muito grande, tente novamente: ");
            }
        }
    }while (texto_longo);
    acervo[*quantidade].autor[strcspn(acervo[*quantidade].autor, "\n")] = '\0';

    printf("Insira o ano de publicacao do livro: ");
    resultado = scanf("%d", &acervo[*quantidade].ano);
    do{
        if (resultado != 1){
            printf("Entrada nao numerica invalida\n");
            printf("Tente novamente: ");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            resultado = scanf("%d", &acervo[*quantidade].ano);
        }
    }while (resultado != 1);
    acervo[*quantidade].disponivel = 1;
    (*quantidade)++;

    return 1;
}

void exibir_livro(const Livro acervo[]){

    printf("\nCodigo: %d\n", acervo->codigo);
    printf("Titulo: %s\n", acervo->titulo);
    printf("Autor: %s\n", acervo->autor);
    printf("Ano: %d\n", acervo->ano);

    if (acervo->disponivel == 1) printf("Livro disponivel\n\n");
    else printf("Livro indisponivel\n\n");
}

void listar_livros(const Livro acervo[], int quantidade){
    if (quantidade == 0){ 
    printf("\nNenhum livro cadastrado\n\n"); 
    return;
    }    
    else{
        for (int i = 0; i < quantidade; i++){
            printf("\n---Livro %d---\n", i + 1);
            exibir_livro(&acervo[i]);
        }
    }
}

int buscar_livro(const Livro acervo[], int quantidade, int codigo){
    for (int i = 0; i < quantidade; i++){
        if (acervo[i].codigo == codigo) return i;
    }
    return -1;
}

int emprestar_livro(Livro acervo[], int quantidade, int codigo){
    int indice = buscar_livro(acervo, quantidade, codigo);
    if (indice == -1){
        printf("\nLivro nao encontrado\n\n");
        return 0;
    } else if (acervo[indice].disponivel == 1){
        acervo[indice].disponivel = 0;
        printf("\nOperacao realizada com sucesso\n\n");
        return 1;
    }else if (acervo[indice].disponivel == 0) {
        printf("\nLivro ja emprestado, tente novamente mais tarde\n\n");
    }
    return -1; 
}

int devolver_livro(Livro acervo[], int quantidade, int codigo){
    int indice = buscar_livro(acervo, quantidade, codigo);
    if (indice == -1){
        printf("\nLivro nao encontrado\n\n");
        return 0;
    } else if (acervo[indice].disponivel == 1){
        printf("\nLivro ja disponivel\n\n");
        return -1;
    }else if (acervo[indice].disponivel == 0) {
        printf("\nOperacao realizada com sucesso\n\n");
        acervo[indice].disponivel = 1;
    }
    return 1; 
}

void relatorio(const Livro acervo[], int quantidade){
    int disponiveis = 0;
    int emprestados;
    float percentual;
    
    for (int i = 0; i < quantidade; i++){
        if(acervo[i].disponivel == 1) disponiveis++;
    }
    emprestados = quantidade - disponiveis;

    if (quantidade > 0) percentual = (emprestados*100.0)/quantidade;
    else percentual = 0;

    printf("---RELATORIO DO ACERVO---\n");
    printf("Total de livros: %d\n", quantidade);
    printf("Livros disponiveis: %d\n", disponiveis);
    printf("Livros emprestados: %d\n", emprestados);
    printf("Taxa de emprestimo: %.1f%%\n", percentual);
    printf("============================\n");

    return;
}

int salvar_acervo(const Livro acervo[], int quantidade){
    int verificacao, verificacao_2;
    FILE *arquivo = fopen("acervo.dat", "wb");
    if (arquivo == NULL){
        printf("Falha ao abrir o arquivo\n");
        return 0;
    }

    verificacao = fwrite(&quantidade, sizeof(int), 1, arquivo);
    if (verificacao == 1) printf("Sucesso ao gravar quantidade de livros\n");
    else printf("Falha ao ler quantidade de livros\n");
    verificacao_2 = fwrite(acervo, sizeof(Livro), quantidade, arquivo);
    if (verificacao_2 == quantidade) printf("Sucesso ao gravar todos livros\n");
    else printf("Falha ao ler todos livros\n");

    int sucesso = (verificacao == 1 && verificacao_2 == quantidade);

    if (fclose(arquivo) == EOF) {
    printf("Erro ao fechar arquivo.\n");
    sucesso = 0;
    }

    return sucesso;
}

int carregar_acervo(Livro acervo[], int *quantidade, int capacidade){
    int quantidade_lida;
     FILE *arquivo = fopen("acervo.dat", "rb");
     if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return 0;
    }

    if (fread(&quantidade_lida, sizeof(int), 1, arquivo) != 1) {
        printf("Falha ao ler a quantidade de livros.\n");
        fclose(arquivo);
        return 0;
    }
    if (quantidade_lida < 0 || quantidade_lida > capacidade) {
        printf("Arquivo invalido: quantidade de livros incorreta.\n");
        fclose(arquivo);
        return 0;
    }
    size_t livros_lidos = fread(
        acervo,
        sizeof(Livro),
        quantidade_lida,
        arquivo
    );
    if (livros_lidos != (size_t)quantidade_lida) {
        printf("Falha ao carregar todos os livros.\n");
        fclose(arquivo);
        return 0;
    }
    if (fclose(arquivo) == EOF) {
        printf("Erro ao fechar arquivo.\n");
        return 0;
    }

    *quantidade = quantidade_lida;
    return 1;
}
