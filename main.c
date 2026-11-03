#include <stdio.h>
#include "biblioteca.h"

int main(){

    Livro acervo[MAX_LIVROS];
    int quantidade = 2;
    int opcao = 0;
    int codigo_busca;
    int indice;
    int leitura;
    acervo[0] = (Livro){
        777,
        "Biblia Sagrada",
        "Inspirados por Deus",
        100,
        1
    };
    //exibir_livro(&acervo[0]);
    acervo[1] = (Livro){
        934,
        "Harry Potter e a Pedra Filosofal",
        "J. K. Rowling",
        1997,
        1
    };
    
    //exibir_livro(&acervo[1]);
    //listar_livros(&acervo[0], quantidade);
    //cadastrar_livro(acervo, &quantidade, MAX_LIVROS);

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