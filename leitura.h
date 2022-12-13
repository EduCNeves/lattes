#ifndef __LEITURA__
#define __LEITURA__
     
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lista.h"
#include "dados.h"

#define LINESIZE 1024

void ler_qualis (char *qualis, lista_t *lista);
void ler_xml (struct dirent **arquivos, int quantidade_lattes, dados_t *pesquisadores, lista_t *lista_c, lista_t *lista_p);
void arrumar_string(FILE *arquivo, char *nome);
char *ler_nome_pesquisador(FILE *arquivo);
void ler_evento(FILE *arquivo, pesq_t *lista, lista_t *lista_c);
void ler_artigos(FILE *arquivo, pesq_t *lista, lista_t *lista_p);



int filtro (const struct dirent *dir);
     
#endif