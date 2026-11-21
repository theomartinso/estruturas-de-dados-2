/*
 * Árvore Binária de Busca (ABB) em C
 *
 * Operações implementadas: inserção, busca, remoção
 * (com tratamento de 0, 1 e 2 filhos, usando o sucessor em ordem),
 * percurso em ordem e liberação de memória.
 *
 * Valores duplicados são ignorados na inserção.
 * Complexidade: O(h), onde h é a altura da árvore
 * (O(log n) se balanceada, O(n) no pior caso).
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct no {
    int valor;
    struct no *esquerda;
    struct no *direita;
} No;

No *criarNo(int valor) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o nó.\n");
        exit(1);
    }
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

No *inserirNo(No *raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserirNo(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserirNo(raiz->direita, valor);
    }
    return raiz;
}

No *buscarNo(No *raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }
    if (valor < raiz->valor) {
        return buscarNo(raiz->esquerda, valor);
    } else {
        return buscarNo(raiz->direita, valor);
    }
}

No *removerNo(No *raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }
    if (valor < raiz->valor) {
        raiz->esquerda = removerNo(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = removerNo(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL) {
            No *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        No *temp = raiz->direita;
        while (temp && temp->esquerda != NULL) {
            temp = temp->esquerda;
        }
        raiz->valor = temp->valor;
        raiz->direita = removerNo(raiz->direita, temp->valor);
    }
    return raiz;
}

No *liberarArvore(No *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
    return NULL;
}

void imprimirEmOrdem(No *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimirEmOrdem(raiz->direita);
    }
}


int main() {
    No *raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        raiz = inserirNo(raiz, valores[i]);
    }

    printf("Em ordem: ");
    imprimirEmOrdem(raiz);
    printf("\n");

    No *achado = buscarNo(raiz, 60);
    printf("Busca por 60: %s\n", achado ? "encontrado" : "nao encontrado");

    raiz = removerNo(raiz, 50);
    printf("Apos remover 50: ");
    imprimirEmOrdem(raiz);
    printf("\n");

    raiz = liberarArvore(raiz);
    return 0;
}