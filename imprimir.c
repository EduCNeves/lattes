#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "lista.h"
#include "cont.h"


void imprimir_por_pesquisadores(dados_t *pesq, int quant){
    
    for (int i = 0; i < quant; i++){
        printf( "Pesquisador: %s\n", pesq[i].nome);
        printf("+------------+------------+\n");
        printf("|Conferencias| Periódicos |\n");
        printf("+------------+------------+\n");
        printf("| A1: %d     |   A1: %d   |\n", pesq[i].conf.A1, pesq[i].perid.A1);
        printf("| A2: %d     |   A2: %d   |\n", pesq[i].conf.A2, pesq[i].perid.A2);
        printf("| A3: %d     |   A3: %d   |\n", pesq[i].conf.A3, pesq[i].perid.A3);
        printf("| A4: %d     |   A4: %d   |\n", pesq[i].conf.A4, pesq[i].perid.A4);
        printf("| B1: %d     |   B1: %d   |\n", pesq[i].conf.B1, pesq[i].perid.B1);
        printf("| B2: %d     |   B2: %d   |\n", pesq[i].conf.B2, pesq[i].perid.B2);
        printf("| B3: %d     |   B3: %d   |\n", pesq[i].conf.B3, pesq[i].perid.B3);
        printf("| B4: %d     |   B4: %d   |\n", pesq[i].conf.B4, pesq[i].perid.B4);
        printf("| C: %d      |   C: %d    |\n", pesq[i].conf.C, pesq[i].perid.C); 
        printf("+------------+------------+\n");

        
    }
}

void imprimir_tipo_c(dados_t *pesq, int quant){
    for (int i = 0; i < quant; i++){
        trabalho_t *aux = pesq[i].l_artigos->inicio;
        printf("periódicos classificados no nível C\n");
        for (int j = 0; j < pesq[i].l_artigos->tam; j++){
            if(strcmp(aux->qualis, "C") == 0){
                printf("%s\n", aux->revista_evento);
            }
            aux = aux->prox;
        }
        printf("eventos classificados no nível C\n");
        aux = pesq[i].l_eventos->inicio;
        for (int j = 0; j < pesq[i].l_eventos->tam; j++){
            if(strcmp(aux->qualis, "C") == 0){
                printf("%s\n", aux->revista_evento);
            }
            aux = aux->prox;
        }
    }

}

void imprimir_tipo_sc(dados_t *pesq, int quant){
    for (int i = 0; i < quant; i++){
        trabalho_t *aux = pesq[i].l_artigos->inicio;
        printf("periódicos sem classificacao\n");
        for (int j = 0; j < pesq[i].l_artigos->tam; j++){
            if(strcmp(aux->qualis, "sem classificacao") == 0){
                printf("%s\n", aux->revista_evento);
            }
            aux = aux->prox;
        }
        
    }

}