#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livro {
    int codigo;
    char titulo[100];
    char autor[100];
    char data_publicacao[11]; // Formato: "dd/mm/yyyy"
    int numero; // Numero de exemplares
} Livro;

typedef struct Node {
    Livro livro;
    struct Node *esquerdo;
    struct Node *direito;
} Node;

// Funcoes
Node* criarNo(Livro livro);
Node* inserir(Node* raiz, Livro livro);
Node* buscar(Node* raiz, int codigo);
Node* encontrarMinimo(Node* raiz);
Node* remover(Node* raiz, int codigo);
void exibirArvore(Node* raiz, int espacos, int nivel);
void liberarArvore(Node* raiz);

int main() {
    Node* raiz = NULL;
    Livro livro;

    // Definir o primeiro livro como a raiz
    livro.codigo = 30;
    strcpy(livro.titulo, "Estruturas de Dados");
    strcpy(livro.autor, "Autor C");
    strcpy(livro.data_publicacao, "03/03/2022");
    livro.numero = 2;
    raiz = inserir(raiz, livro);  // Inserir o primeiro livro como raiz

    // Inserir outros livros
    livro.codigo = 20;
    strcpy(livro.titulo, "Algoritmos em C");
    strcpy(livro.autor, "Autor B");
    strcpy(livro.data_publicacao, "02/02/2021");
    livro.numero = 3;
    raiz = inserir(raiz, livro);

    livro.codigo = 1;
    strcpy(livro.titulo, "Aprendendo C");
    strcpy(livro.autor, "Autor A");
    strcpy(livro.data_publicacao, "01/01/2020");
    livro.numero = 5;
    raiz = inserir(raiz, livro);

    livro.codigo = 8;
    strcpy(livro.titulo, "Estruturas de Dados Avancadas");
    strcpy(livro.autor, "Autor D");
    strcpy(livro.data_publicacao, "04/04/2023");
    livro.numero = 4;
    raiz = inserir(raiz, livro);

    livro.codigo = 10;
    strcpy(livro.titulo, "Programacao Estruturada");
    strcpy(livro.autor, "Autor E");
    strcpy(livro.data_publicacao, "05/05/2024");
    livro.numero = 6;
    raiz = inserir(raiz, livro);

    livro.codigo = 15;
    strcpy(livro.titulo, "Banco de Dados");
    strcpy(livro.autor, "Autor F");
    strcpy(livro.data_publicacao, "06/06/2025");
    livro.numero = 7;
    raiz = inserir(raiz, livro);

    // Exibir livros antes da remocao
    printf("Arvore antes da remocao:\n");
    exibirArvore(raiz, 0, 0);

    // Remover um livro (com codigo 8, por exemplo)
    raiz = remover(raiz, 8);

    // Exibir livros apos a remocao
    printf("\nArvore apos remocao do livro com Codigo 8:\n");
    exibirArvore(raiz, 0, 0);

    // Liberar a memoria
    liberarArvore(raiz);

    return 0;
}

// Funcao para criar um novo no
Node* criarNo(Livro livro) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (!novoNo) {
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }
    novoNo->livro = livro;
    novoNo->esquerdo = NULL;
    novoNo->direito = NULL;
    return novoNo;
}

// Funcao para inserir um livro na ABB
Node* inserir(Node* raiz, Livro livro) {
    if (raiz == NULL) {
        return criarNo(livro);
    }
    if (livro.codigo < raiz->livro.codigo) {
        raiz->esquerdo = inserir(raiz->esquerdo, livro);
    } else if (livro.codigo > raiz->livro.codigo) {
        raiz->direito = inserir(raiz->direito, livro);
    }
    return raiz;
}

// Funcao para buscar um livro na ABB
Node* buscar(Node* raiz, int codigo) {
    if (raiz == NULL || raiz->livro.codigo == codigo) {
        return raiz;
    }
    if (codigo < raiz->livro.codigo) {
        return buscar(raiz->esquerdo, codigo);
    }
    return buscar(raiz->direito, codigo);
}

// Funcao para encontrar o no com o valor minimo (para remocao)
Node* encontrarMinimo(Node* raiz) {
    while (raiz->esquerdo != NULL) {
        raiz = raiz->esquerdo;
    }
    return raiz;
}

// Funcao para remover um livro da ABB
Node* remover(Node* raiz, int codigo) {
    if (raiz == NULL) {
        return raiz;
    }
    if (codigo < raiz->livro.codigo) {
        raiz->esquerdo = remover(raiz->esquerdo, codigo);
    } else if (codigo > raiz->livro.codigo) {
        raiz->direito = remover(raiz->direito, codigo);
    } else {
        // Caso 1: No com apenas um filho ou sem filhos
        if (raiz->esquerdo == NULL) {
            Node* temp = raiz->direito;
            free(raiz);
            return temp;
        } else if (raiz->direito == NULL) {
            Node* temp = raiz->esquerdo;
            free(raiz);
            return temp;
        }

        // Caso 2: No com dois filhos
        Node* temp = encontrarMinimo(raiz->direito);
        raiz->livro = temp->livro;
        raiz->direito = remover(raiz->direito, temp->livro.codigo);
    }
    return raiz;
}

// Funcao para exibir a arvore em forma hierarquica com conexoes
void exibirArvore(Node* raiz, int espacos, int nivel) {
    if (raiz != NULL) {
        exibirArvore(raiz->direito, espacos + 6, nivel + 1);
        
        for (int i = 0; i < espacos; i++) {
            printf(" ");
        }
        
        printf("%d\n", raiz->livro.codigo);
        
        exibirArvore(raiz->esquerdo, espacos + 6, nivel + 1);
    }
}

// Funcao para liberar a memoria da arvore
void liberarArvore(Node* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerdo);
        liberarArvore(raiz->direito);
        free(raiz);
    }
}