#include <stdio.h>
#include <errno.h>
#include "biblioteca.h"

int main(){

    Livro acervo[MAX_LIVROS];
    int quantidade = 0;
    int opcao = 0;
    int codigo_busca;
    int indice;
    int leitura;

    int estado = carregar_acervo(acervo, &quantidade, MAX_LIVROS);

    if (estado == -1) {
        printf("Nao foi possivel recuperar o acervo.\n");
        printf("O arquivo original sera preservado.\n");
        return 1;
    }

    if (estado == 0) {
        printf("Nenhum arquivo encontrado. Biblioteca vazia.\n");
    } else {
        printf("Acervo recuperado com sucesso!\n");
    }
    do{

        printf("---Biblioteca Vilanova---\n");
        printf("Suas opcoes: \n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Listar livros\n");
        printf("3 - Buscar codigo\n");
        printf("4 - Pegar livro emprestado\n");
        printf("5 - Devolver livro\n");
        printf("6 - Relatorio\n");
        printf("0 - Sair\n");
        printf("Escolha um numero: ");
        leitura = scanf("%d", &opcao);

        if (leitura != 1) {
            if (leitura == EOF) break;
            printf("\nDigite uma opcao numerica.\n\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            continue;
        }

        switch(opcao){

            case 1:
                cadastrar_livro(acervo, &quantidade, MAX_LIVROS);
                break;

            case 2:
                listar_livros(acervo, quantidade);
                break;
                
            case 3:
                codigo_busca = ler_codigo();
                if (codigo_busca == -1){
                    opcao = 0;
                    break;
                }
            
                indice = buscar_livro(acervo, quantidade, codigo_busca);
                if (indice != -1) exibir_livro(&acervo[indice]);
                else printf("\nCodigo nao encontrado\n\n");
                break;

            case 4:
                codigo_busca = ler_codigo();
                if (codigo_busca == -1){
                    opcao = 0;
                    break;
                }

                emprestar_livro(acervo, quantidade, codigo_busca);
                break;

            case 5:
                codigo_busca = ler_codigo();
                if (codigo_busca == -1){
                    opcao = 0;
                    break;
                }

                devolver_livro(acervo, quantidade, codigo_busca);
                break;

            case 6:
                relatorio(acervo, quantidade);
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida\n\n");
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {
                }
                continue;
        }
    }while (opcao != 0);

    if (salvar_acervo(acervo, quantidade)) {
        printf("Acervo salvo com sucesso!\n");
    } else {
        printf("Falha ao salvar o acervo.\n");
    }
    return 0;
}