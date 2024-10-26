#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livro {
    int codigo;
    char autor[100];
    char data_publicacao[20];
    char titulo[100];
} Livro;

typedef struct No {
    Livro livro;
    struct No* esquerda;
    struct No* direita;
} No;

void exibirLivro(Livro livro);

No* criarNo(Livro livro) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->livro = livro;
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

No* inserirNo(No* raiz, Livro livro) {
    if (raiz == NULL)
        return criarNo(livro);

    if (livro.codigo < raiz->livro.codigo)
        raiz->esquerda = inserirNo(raiz->esquerda, livro);
    else if (livro.codigo > raiz->livro.codigo)
        raiz->direita = inserirNo(raiz->direita, livro);

    return raiz;
}

No* buscarNo(No* raiz, int codigo) {
    if (raiz == NULL || raiz->livro.codigo == codigo)
        return raiz;

    if (codigo < raiz->livro.codigo)
        return buscarNo(raiz->esquerda, codigo);
    else
        return buscarNo(raiz->direita, codigo);
}

No* encontrarMinimo(No* raiz) {
    while (raiz && raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

No* removerNo(No* raiz, int codigo) {
    if (raiz == NULL) return NULL;

    if (codigo < raiz->livro.codigo)
        raiz->esquerda = removerNo(raiz->esquerda, codigo);
    else if (codigo > raiz->livro.codigo)
        raiz->direita = removerNo(raiz->direita, codigo);
    else {
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        No* temp = encontrarMinimo(raiz->direita);
        raiz->livro = temp->livro;
        raiz->direita = removerNo(raiz->direita, temp->livro.codigo);
    }
    return raiz;
}

void imprimirPreOrdem(No* raiz) {
    if (raiz != NULL) {
        exibirLivro(raiz->livro);
        imprimirPreOrdem(raiz->esquerda);
        imprimirPreOrdem(raiz->direita);
    }
}

void imprimirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        exibirLivro(raiz->livro);
        imprimirEmOrdem(raiz->direita);
    }
}

void imprimirPosOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimirPosOrdem(raiz->esquerda);
        imprimirPosOrdem(raiz->direita);
        exibirLivro(raiz->livro);
    }
}

void exibirLivro(Livro livro) {
    printf("\n");
    printf("Codigo: %d\n", livro.codigo);
    printf("Autor: %s\n", livro.autor);
    printf("Data de Publicacao: %s\n", livro.data_publicacao);
    printf("Titulo: %s\n", livro.titulo);
    printf("\n");
}

void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

Livro lerLivro() {
    Livro livro;
    printf("Digite o codigo do livro (ISBN/ISSN): ");
    scanf("%d", &livro.codigo);
    getchar();

    printf("Digite o autor: ");
    fgets(livro.autor, 100, stdin);
    livro.autor[strcspn(livro.autor, "\n")] = '\0';

    printf("Digite a data de publicacao: ");
    fgets(livro.data_publicacao, 20, stdin);
    livro.data_publicacao[strcspn(livro.data_publicacao, "\n")] = '\0';

    printf("Digite o titulo do livro: ");
    fgets(livro.titulo, 100, stdin);
    livro.titulo[strcspn(livro.titulo, "\n")] = '\0';

    return livro;
}

int main() {
    No* raiz = NULL;
    int opcao, codigo;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Inserir Livro\n");
        printf("2. Buscar Livro\n");
        printf("3. Remover Livro\n");
        printf("4. Imprimir em Ordem\n");
        printf("5. Imprimir em Pre-Ordem\n");
        printf("6. Imprimir em Pos-Ordem\n");
        printf("7. Sair\n");
        printf("\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Livro livro = lerLivro();
                raiz = inserirNo(raiz, livro);
                printf("Livro inserido com sucesso!\n");
                break;
            }
            case 2: {
                printf("Digite o codigo do livro para buscar: ");
                scanf("%d", &codigo);
                No* encontrado = buscarNo(raiz, codigo);
                if (encontrado != NULL) {
                    printf("==================================================\n");
                    printf("Livro encontrado:\n");
                    exibirLivro(encontrado->livro);
                } else {
                    printf("Livro nao encontrado.\n");
                }
                printf("=======================================================");
                break;
            }
            case 3: {
                printf("Digite o codigo do livro para remover: ");
                scanf("%d", &codigo);
                raiz = removerNo(raiz, codigo);
                printf("Livro removido com sucesso!\n");
                break;
            }

            case 4: {
                printf("=======================================================\n");
                printf("Livros na biblioteca:\n");
                imprimirEmOrdem(raiz);
                printf("========================================================");
                break;
            }
            case 5:
                printf("=========================================================\n");
                printf("Livros em Pre-Ordem:\n");
                imprimirPreOrdem(raiz);
                printf("=========================================================");
                break;
            case 6:
                printf("==========================================================\n");
                printf("Livros em Pos-Ordem:\n");
                imprimirPosOrdem(raiz);
                printf("===========================================================");
                break;
            case 7:
                printf("Saindo...\n");
                liberarArvore(raiz);
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 7);

    return 0;
}