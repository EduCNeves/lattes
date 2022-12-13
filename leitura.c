#define _DEFAULT_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "leitura.h"
#include "lista.h"
#include "dados.h"

#define LINESIZE 1024

void ler_qualis (char *qualis, lista_t *lista){

  FILE *arq;
  char *line = malloc (sizeof(char)*LINESIZE);
  char *final_copy = malloc (sizeof(char)*LINESIZE);
  char *final = malloc (sizeof(char)*LINESIZE);
  char aux;
  int i=0;
  // abre o arquivo em leitura    
  arq = fopen (qualis, "r") ;
  if ( !arq ){
    perror ("Erro ao abrir arquivo") ;
    exit (1) ;
  }

  fgets (line, LINESIZE, arq);


  line[strcspn(line, "\n")] = '\0';
  final_copy = strrchr(line, ' ');
  do {
    aux=final_copy[i+1];
    final_copy[i]=final_copy[i+1];
    final[i]=final_copy[i];
    i++;
  } while (aux != '\0');
  final_copy[0] = '\0';
  
  insere_lista(lista, line, final);


  while (! feof (arq)){
    
    line = malloc (sizeof(char)*LINESIZE); 
    final_copy = malloc (sizeof(char)*LINESIZE);
    final = malloc (sizeof(char)*LINESIZE);

    fgets (line, LINESIZE, arq);

    line[strcspn(line, "\n")] = '\0';
    final_copy = strrchr(line, ' ');
    i=0;
    aux=1;// aux não pode ser \0
    while(aux!='\0'){
      aux=final_copy[i+1];
      final_copy[i]=final_copy[i+1];
      final[i]=final_copy[i];
      i++;
    }
    final_copy[0] = '\0';


    insere_lista(lista, line, final);


  }

    
  fclose (arq); 
}

void arrumar_string(FILE *arquivo, char *nome){

  char *ptr = malloc(sizeof(char)*LINESIZE);

  while (nome[strlen(nome)-1] != '"' ){
    fscanf(arquivo, "%s", ptr);
    strcat(nome, " ");
    strcat(nome, ptr);
  }
  nome[strlen(nome)-1] = '\0'; 
  ptr = strchr(nome, '"'); 
  (ptr)++;

  int i;
  for (i=0; ptr[i]!='\0' ;i++)
    nome[i] = ptr[i];
  nome[i] = '\0';

}

//lendo o nome dos pesquisadores
char *ler_nome_pesquisador(FILE *arquivo){

  char *nome = malloc(sizeof(char)*LINESIZE);

  fscanf(arquivo, "%s", nome);
  while (!strstr(nome, "NOME-COMPLETO=")){
    fscanf(arquivo, "%s", nome);
  }
  arrumar_string(arquivo,nome);

  return nome;
}

//lendo dados do evento que o pesq participou
void ler_evento(FILE *arquivo, pesq_t *lista, lista_t *lista_c){

  char *aux = malloc(sizeof(char) * LINESIZE);

  //titulo do evento
  fscanf(arquivo, "%s", aux);
  while ( !strstr(aux, "TITULO-DO-TRABALHO=") )
    fscanf(arquivo, "%s", aux);

  arrumar_string(arquivo, aux);

  char *titulo = malloc(sizeof(char) * (strlen(aux)+1));
  strncpy(titulo, aux, strlen(aux)+1);

  //ano do evento
  fscanf(arquivo, "%s", aux);
  while ( !strstr(aux, "ANO-DO-TRABALHO=") )
    fscanf(arquivo, "%s", aux);

  arrumar_string(arquivo, aux);
  int ano = atoi(aux);

  //nome do evento
  fscanf(arquivo, "%s", aux);
  while ( !strstr(aux, "NOME-DO-EVENTO=") )
    fscanf(arquivo, "%s", aux);

  arrumar_string(arquivo, aux);

  char *rev = malloc( sizeof(char) * (strlen(aux)+1) );
  strncpy(rev, aux, strlen(aux)+1);

  char *tipo = malloc( sizeof(char) * (strlen(aux)+1) );
  tipo = qualificar_evento(rev, lista_c);//qualificar o evento

  insere_dados(lista, ano, titulo, rev, tipo);
}

//lendo os artigos 
void ler_artigos(FILE *arquivo, pesq_t *lista, lista_t *lista_p){

  char *aux = malloc(sizeof(char) * LINESIZE);


  //titulo do artigos
  fscanf(arquivo, "%s", aux);
  while ( !strstr(aux, "TITULO-DO-ARTIGO=") )
    fscanf(arquivo, "%s", aux);

  arrumar_string(arquivo, aux);

  char *titulo = malloc(sizeof(char) * (strlen(aux)+1));
  strncpy(titulo, aux, strlen(aux)+1);

  //ano do artigos
  fscanf(arquivo, "%s", aux);
  while ( !strstr(aux, "ANO-DO-ARTIGO=") )
    fscanf(arquivo, "%s", aux);

  arrumar_string(arquivo, aux);
  int ano = atoi(aux);

  //nome do artigos
  fscanf(arquivo, "%s", aux);
  while ( !strstr(aux, "TITULO-DO-PERIODICO-OU-REVISTA=") )
    fscanf(arquivo, "%s", aux);

  arrumar_string(arquivo, aux);

  char *rev = malloc( sizeof(char) * (strlen(aux)+1) );
  strncpy(rev, aux, strlen(aux)+1);

  char *tipo = malloc( sizeof(char) * (strlen(aux)+1) );
  tipo = qualificar_artigos(rev, lista_p);//qualificar o artigo

  insere_dados(lista, ano, titulo, rev, tipo);


}

//lendo o arquivo xml
void ler_xml (struct dirent **arquivos, int quantidade_lattes, dados_t *pesquisadores, lista_t *lista_c, lista_t *lista_p){

  FILE *arq;
  int i;
 
  // abre o arquivo em leitura
  for(i=0; i < quantidade_lattes; i++ ){
    
    arq = fopen (arquivos[i]->d_name, "r") ;
    if ( !arq ){
      perror ("Erro ao abrir arquivo") ;
      exit (1) ;
    }

    strcpy(pesquisadores[i].nome,ler_nome_pesquisador(arq)); //lendo o nome do pesquisador

    char *ptr = malloc( sizeof(char) * LINESIZE );
        while ( fscanf(arq, "%s", ptr) != EOF ){

          //leitura de todos os eventos
          if ( strstr(ptr, "<TRABALHO-EM-EVENTOS") ){
            ler_evento(arq, pesquisadores[i].l_eventos, lista_c);
          }

          //leitura de todos os eventos
          if ( strstr(ptr, "<ARTIGO-PUBLICADO") )
            ler_artigos(arq, pesquisadores[i].l_artigos, lista_p);

        }
        free(ptr);
  }

 
}

//filtro para aquivos .xml
int filtro (const struct dirent *dir){

  int size = strlen(dir->d_name);

  // se o tamanho for invalido ou nao for um arquivo
  if ( size < 1 || dir->d_type != DT_REG )
    return 0;
  
  // se tiver .xml no final do arquivo
  if ( dir->d_name[size - 4] == '.' && dir->d_name[size - 3] == 'x'
    && dir->d_name[size - 2] == 'm' && dir->d_name[size - 1] == 'l' ){
    return 1;
  }

  return 0;
}
