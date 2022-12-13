#ifndef __CONT__
#define __CONT__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

typedef struct cont_t{

    int A1;
    int A2;
    int A3;
    int A4;
    int B1;
    int B2;
    int B3;
    int B4;
    int C;


} cont_t;

void zerar(cont_t *cont);

void tipo_qualis(char *tipo, cont_t *cont);
struct dados_t;
void contador_conferencias( struct dados_t *pesq, int quant);
void contador_periodicos( struct dados_t *pesq, int quant);



#endif