#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "lista.h"

#define DIST 4

void insere_dados(pesq_t *lista, int ano, char *titulo, char *rev, char *tipo){

   trabalho_t *node = criaTrabalho();
   node->ano = ano;
   node->titulo = titulo;
   node->revista_evento = rev;
   node->qualis = tipo;

   node->prox = lista->inicio;
   lista->inicio = node;

   lista->tam++;
   
}

pesq_t *cria_dados(){

   pesq_t *lista = (pesq_t *) malloc(sizeof(pesq_t));
   lista->inicio=NULL;
   lista->tam=0;

   return lista;
}

trabalho_t *criaTrabalho(){

    trabalho_t *node = (trabalho_t *) malloc(sizeof(trabalho_t));
    node->prox = NULL;
    node->ano = 0;
    node->titulo = NULL;
    node->revista_evento = NULL;
    node->qualis = NULL;

   return node;
}

void libera_dados(pesq_t *lista){
   
   trabalho_t *aux = lista->inicio;

   while (lista->inicio == NULL){
      lista->inicio = lista->inicio->prox;
      free(aux->revista_evento);
      free(aux->titulo);
      free(aux->qualis);
      free(aux);
      aux = lista->inicio;
   }
   free(lista);
}

void exibe_dados(pesq_t *lista){

   trabalho_t *aux = lista->inicio;

   for (int i = 0; i < lista->tam; i++){
      printf("%d\n", i);
      printf("%s\n", aux->revista_evento);
      printf("%s\n", aux->titulo);
      printf("%d\n", aux->ano);
      printf("%s\n", aux->qualis);
      printf("-----------------------------------------\n");

      aux = aux->prox; 
   }
   
}
 
int distance (char *word1, char *word2){
  int len1 = strlen(word1);
  int len2 = strlen(word2);

  int matrix[len1 + 1][len2 + 1];
  int i;

  for (i = 0; i <= len1; i++)
    matrix[i][0] = i;

  for (i = 0; i <= len2; i++)
    matrix[0][i] = i;

  for (i = 1; i <= len1; i++){
    int j;
    char c1;

    c1 = word1[i-1];
    for (j = 1; j <= len2; j++){
      char c2;

      c2 = word2[j-1];
      if (c1 == c2)
        matrix[i][j] = matrix[i-1][j-1];

      else{
        int delete;
        int insert;
        int substitute;
        int minimum;

        delete = matrix[i-1][j] + 1;
        insert = matrix[i][j-1] + 1;
        substitute = matrix[i-1][j-1] + 1;
        minimum = delete;
        if (insert < minimum)
          minimum = insert;

        if (substitute < minimum)
          minimum = substitute;

        matrix[i][j] = minimum;
      }
    }
  }
  return (matrix[len1][len2]);
}

char *qualificar_evento(char *rev, lista_t *lista_c){

   Node *aux = lista_c->inicio;

   for (int i = 0; i < lista_c->tam; i++){
      if ( distance(aux->nome, rev) < strlen(aux->nome)/DIST ){
           return aux->tipo;
          break;
      }
      aux = aux->prox;
   }
   return "sem classificacao";
}

char *qualificar_artigos(char *rev, lista_t *lista_p){

   Node *aux = lista_p->inicio;

   for (int i = 0; i < lista_p->tam; i++){
      if ( distance(aux->nome, rev) < strlen(aux->nome)/DIST ){
           return aux->tipo;
          break;
      }
      aux = aux->prox;
   }
   return "sem classificacao";
}
