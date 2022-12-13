#ifndef __DADOS__
#define __DADOS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "lista.h"
#include "cont.h"

typedef struct trabalho_t{
 
    char *titulo;
    char *revista_evento;
    char *qualis;
    int ano;
    struct trabalho_t *prox;
} trabalho_t;

typedef struct pesq_t{
    trabalho_t *inicio;
    int tam;
}pesq_t;

typedef struct dados_t{
    
    char *nome;
    pesq_t *l_eventos;
    pesq_t *l_artigos;
    cont_t conf;
    cont_t perid;
    
}dados_t;

void insere_dados(pesq_t *lista, int ano, char *titulo, char *rev, char *tipo);
pesq_t *cria_dados();
trabalho_t *criaTrabalho();
void libera_dados(pesq_t *lista);
void exibe_dados(pesq_t *lista);
char *qualificar_evento(char *rev, lista_t *lista_c);
char *qualificar_artigos(char *rev, lista_t *lista_p);
int distance (char *word1, char *word2);



#endif