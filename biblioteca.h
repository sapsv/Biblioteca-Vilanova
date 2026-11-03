#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#define MAX_LIVROS 100
#define MAX_TITULO 100
#define MAX_AUTOR 80

typedef struct{

    int codigo;
    char titulo[MAX_TITULO + 1];
    char autor[MAX_AUTOR + 1];
    int ano;
    int disponivel;

} Livro;

void exibir_livro(const Livro acervo[]);
void listar_livros(const Livro acervo[], int quantidade);
int buscar_livro(const Livro acervo[], int quantidade, int codigo);
int cadastrar_livro(Livro acervo[], int *quantidade, int capacidade);
int emprestar_livro(Livro acervo[], int quantidade, int codigo);
int devolver_livro(Livro acervo[], int quantidade, int codigo);
int ler_codigo(void);
void relatorio(const Livro acervo[], int quantidade);
int salvar_acervo(const Livro acervo[], int quantidade);

#endif