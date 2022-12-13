#define _DEFAULT_SOURCE
#include "leitura.h"
#include "lista.h"
#include "dados.h"
#include "cont.h"
#include "imprimir.h"

int main(int argc, char **argv){

    char d_home[LINESIZE];
    struct dirent **nome_lattes;

    lista_t *lista_c = cria_lista();
    lista_t *lista_p = cria_lista();



    char *diretorio = malloc (sizeof(char)*64);
    // strcpy(diretorio, "/");
    char *qualis_c = malloc (sizeof(char)*64);
    qualis_c[0] = '\0';
    char *qualis_p = malloc (sizeof(char)*64);
    qualis_p[0] = '\0';

    if (strcmp(argv[1],"-d") == 0)
        strcat(diretorio,argv[2]);
    if (strcmp(argv[3],"-c") == 0)
        strcat(qualis_c,argv[4]);
    if (strcmp(argv[5],"-p") == 0)
        strcat(qualis_p,argv[6]);

    //lendo arquivos
    ler_qualis(qualis_c, lista_c);
    ler_qualis(qualis_p, lista_p);


    getcwd(d_home, sizeof(d_home));


    int ret = chdir(diretorio);
    if ( ret != 0 ){
        fprintf(stderr, "Não foi possivel acessar  o diretorio %s\n", diretorio);
        exit(EXIT_FAILURE);
    }


    //contando quantos lattes tem no diretorio de lattes
    int quantidade_lattes = scandir(".", &nome_lattes, filtro, alphasort);

    if (quantidade_lattes <= 0){
        fprintf(stderr, "Erro quantidade de lattes");
        return 1;
    }
    printf("quant lattes %d\n", quantidade_lattes);

    dados_t *pesquisadores = malloc(sizeof(dados_t)*quantidade_lattes);

    for (int i=0; i<quantidade_lattes; i++){
        pesquisadores[i].nome = malloc (sizeof(char)*LINESIZE);
        pesquisadores[i].l_eventos = cria_dados();
        pesquisadores[i].l_artigos = cria_dados();
        zerar(&pesquisadores[i].conf);
        zerar (&pesquisadores[i].perid);
        
    }


    //leitura de arquivos xml
    printf("Lendo os arquivos ...\n");
    ler_xml(nome_lattes, quantidade_lattes, pesquisadores, lista_c,lista_p);

    //contando
    contador_conferencias(pesquisadores, quantidade_lattes);
    contador_periodicos(pesquisadores, quantidade_lattes);

    //imprimir
    imprimir_por_pesquisadores(pesquisadores, quantidade_lattes);
    imprimir_tipo_c(pesquisadores, quantidade_lattes);
    imprimir_tipo_sc(pesquisadores, quantidade_lattes);  
    
    libera_lista(lista_c);
    libera_lista(lista_p);
    for (int i=0; i<quantidade_lattes; i++){
        libera_dados(pesquisadores[i].l_artigos);
        libera_dados(pesquisadores[i].l_eventos); 
        free(pesquisadores[i].nome);
    }
    free(pesquisadores);
    return 0;
}