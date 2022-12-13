#ifndef __LISTA__
#define __LISTA__
     
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
 char *nome;
 char *tipo;
 struct Node *prox;
} Node;

typedef struct lista_t{
    Node *inicio;
    int tam;
}lista_t;

void insere_lista(lista_t *lista, char *elemento, char *tempo);
lista_t *cria_lista();
Node *criaNode();
void libera_lista(lista_t *lista);
void exibe_lista(lista_t *lista);

#endif