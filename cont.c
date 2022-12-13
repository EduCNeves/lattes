#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "lista.h"
#include "cont.h"


void zerar(cont_t *cont){
  memset(cont, 0, sizeof(cont_t));
}

void tipo_qualis(char *tipo, cont_t *cont){
  if (strcmp(tipo, "A1") == 0){ cont->A1++; }
  if (strcmp(tipo, "A2") == 0) { cont->A2++;}
  if (strcmp(tipo, "A3") == 0) { cont->A3++;}
  if (strcmp(tipo, "A4") == 0) { cont->A4++;}
  if (strcmp(tipo, "B1") == 0) { cont->B1++;}
  if (strcmp(tipo, "B2") == 0) { cont->B2++;}
  if (strcmp(tipo, "B3") == 0) { cont->B3++;}
  if (strcmp(tipo, "B4") == 0) { cont->B4++;}
  if (strcmp(tipo, "C") == 0) { cont->C++;}
}

void contador_conferencias(dados_t *pesq, int quant){
    for (int i = 0; i < quant; i++){
        trabalho_t *aux = pesq[i].l_eventos->inicio;
        for (int j = 0; j < pesq[i].l_eventos->tam; j++){
            tipo_qualis( aux->qualis, &pesq[i].conf);
            
            aux = aux->prox;
        }
        
    }
}

void contador_periodicos(dados_t *pesq, int quant){
    for (int i = 0; i < quant; i++){
        trabalho_t *aux = pesq[i].l_artigos->inicio;
        for (int j = 0; j < pesq[i].l_artigos->tam; j++){
            tipo_qualis( aux->qualis, &pesq[i].conf);
            aux = aux->prox;
        }
        
    }
}