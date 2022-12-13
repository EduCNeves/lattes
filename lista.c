#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void insere_lista(lista_t *lista, char *elemento, char *tipo){
   
   Node *node = criaNode();
   node->nome = elemento;
   node->tipo = tipo;

   node->prox = lista->inicio;
   lista->inicio = node;

   lista->tam++;
   
}

lista_t *cria_lista(){

   lista_t *lista = (lista_t *) malloc(sizeof(lista_t));
   lista->inicio=NULL;
   lista->tam=0;

   return lista;
}

Node *criaNode(){

   Node *node = (Node *) malloc(sizeof(Node));
   node->prox = NULL;
   node->nome = NULL;
   node->tipo = NULL;

   return node;
}

void libera_lista(lista_t *lista){
   
   Node *aux = lista->inicio;

   while (lista->inicio == NULL){
      lista->inicio = lista->inicio->prox;
      free(aux->nome);
      free(aux->tipo);
      free(aux);
      aux = lista->inicio;
   }
   free(lista);
}

void exibe_lista(lista_t *lista){

   Node *aux = lista->inicio;

   for (int i = 0; i < lista->tam; i++){
      printf("%s\n", aux->nome);
      printf("%s\n", aux->tipo);
      aux = aux->prox; 
   }
   
}
 