#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM_TITULO 100
#define TAM_AUTOR 100
#define TAM_ISBN 13
#define TAM 10

////////////////////////Criando a estrutura////////////////////////
typedef struct _livros{
    char titulo[TAM_TITULO];
    char autor[TAM_AUTOR];
    char isbn[TAM_ISBN];
}Livros;

////////////////////////Função Limpar Buffer////////////////////////
void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

////////////////////////Função Cadastro////////////////////////
void Cadastrar(Livros *plivros, int *pquantAtualLivros){
    Livros varLivro;

    puts("===========CADASTRO===========");
    printf("Título: ");
    fgets(varLivro.titulo, TAM_TITULO, stdin);
   
    printf("Autor: ");
    fgets(varLivro.autor, TAM_AUTOR, stdin);
    
    printf("ISBN: ");
    fgets(varLivro.isbn, TAM_ISBN, stdin);
    
    plivros[*pquantAtualLivros] = varLivro;
    (*pquantAtualLivros)++;
    printf(" Cadastro realizado com sucesso!\n");
}

////////////////////////Função Listar////////////////////////
void Listar(Livros *plivros, int quantAtualLivros){

    puts("===========Lista de livros===========\n");
    
    if(quantAtualLivros == 0){
        puts("      Nenhum livro cadastrado!");
        return;
    }
    for(int i = 0; i < quantAtualLivros; i++){
        printf("Livro: %d\n", i + 1);
        printf("Título: %s", plivros[i].titulo);
        printf("Autor: %s", plivros[i].autor);
        printf("ISBN: %s", plivros[i].isbn);

        printf("\n");
    }
}

////////////////////////Função Buscar////////////////////////
void Buscar(Livros *plivros, int quantAtualLivros){
    char buscarISBN[TAM_ISBN];

    int encontrado = 0;
    puts("=============Busca de livros=============");
    printf("Entre com o número de ISBN do livro: ");
    fgets(buscarISBN, TAM_ISBN, stdin);

    for(int i=0; i < quantAtualLivros; i++){
        if(strcmp(plivros[i].isbn,buscarISBN) == 0){
            puts("            Livro encontrado: ");
            printf("Título: %s", plivros[i].titulo);
            printf("Autor: %s", plivros[i].autor);
            printf("ISBN: %s", plivros[i].isbn);
            printf("\n");

            encontrado = 1;
            break;
        }
    }
    if(!encontrado){
        puts("         Livro não encontrado!");
    }

}

////////////////////////Função Atualizar////////////////////////
void Atualizar(Livros *plivros, int quantAtualLivros){
    char buscarISBN[TAM_ISBN];
    int encontrado = 0;

    printf("==========Atualização de Livro==========\n");
    printf("ISBN do livro que deseja atualizar: ");
    fgets(buscarISBN, TAM_ISBN, stdin);
 
    for (int i = 0; i < quantAtualLivros; i++) {
        if(strcmp(plivros[i].isbn,buscarISBN) == 0){
        puts("            Livro encontrado: ");
 
        printf("Título: ");
        fgets(plivros[i].titulo, TAM_TITULO, stdin);

        printf("Autor: ");
        fgets(plivros[i].autor, TAM_AUTOR, stdin);

        printf("Livro atualizado com sucesso!\n");
        encontrado = 1;
        break;
        }
    }  
    if(!encontrado) {
        puts("         Livro não encontrado!");
    }
}

////////////////////////Função Remover////////////////////////
void Remover(Livros *plivros, int *pquantAtualLivros){
    char buscarISBN[TAM_ISBN];

    puts("=============Remover livro=============");
    printf("ISBN do livro que deseja remover: ");
    fgets(buscarISBN, TAM_ISBN, stdin);

    int encontrado = 0;
    int i = 0;

    while (i < *pquantAtualLivros && !encontrado) {
        if (strcmp(plivros[i].isbn, buscarISBN) == 0) {
            plivros[i] = plivros[*pquantAtualLivros - 1];
            (*pquantAtualLivros)--;
            encontrado = 1;
        }
        i++;
    }

    if (encontrado) {
        puts("Livro removido com sucesso!");
    } else {
        puts("Livro não encontrado!");
    }
}

////////////////////////Menu////////////////////////
int main(){
    Livros livro[TAM];
    int quantAtualLivros = 0;

    FILE *f;

    f = fopen("livros.dat", "rb");
    if (f != NULL) {
        // Arquivo aberto com sucesso!
        fread(&quantAtualLivros, sizeof(int), 1, f);
        fread(livro, sizeof(Livros), quantAtualLivros, f);
    }

    int opcao;
    do{
        puts("==========AUREO BOOKS==========");
        puts("    1. Cadastrar livro");
        puts("    2. Listar livro");
        puts("    3. Buscar livro");
        puts("    4. Atualizar livro");
        puts("    5. Remover livro");
        puts("    0. Sair");
        printf("    Opção: ");
        scanf("%d", &opcao);
        limparBuffer();
    
        printf("\n");

        switch (opcao)
        {
            case 1:
                Cadastrar(livro, &quantAtualLivros);
                break;
            case 2:
                Listar(livro, quantAtualLivros);
                break;
            case 3:
                Buscar(livro, quantAtualLivros);
                break;
            case 4:
                Atualizar(livro, quantAtualLivros);
                break;
            case 5:
                Remover(livro, &quantAtualLivros);
                break;
            case 0:
                printf("Finalizando...");
                break;
            default:
                puts("Opção Inválida!");
                break;
        }
        printf("\n");

    } while(opcao != 0);

    f = fopen("livros.dat", "wb");
    if (f != NULL) {
        // Arquivo aberto com sucesso!
        fwrite(&quantAtualLivros, sizeof(int), 1, f);
        fwrite(livro, sizeof(Livros), quantAtualLivros, f);
        fclose(f);
    } else {
        printf("Erro abrindo o arquivo!");
    } 

    return 0;
}