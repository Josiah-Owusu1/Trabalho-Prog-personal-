#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serie.h"
#include "util.h"


// Forward declaration para o TAD opaco
 struct Serie {
    char id[10];
    char titulo[101];
    TipoAssinatura restricaoAssinatura;
    TipoUsuario restricaoIdade;
    int anoLancamento;
    int duracaoPorEpisodio;     // Duração de um único episódio em minutos
    int numEpisodios;           // Quantidade de episódios
    char idioma[4];
    float notaMedia;
    char produtora[101]; 
 };

/// @brief Cria uma variável do tipo tSerie a partir de uma linha de dados.
/// @param linhaSerie A string lida do teclado com as informações de uma série (sem o 'S').
/// @return Um ponteiro para o objeto tSerie* criado.
tSerie* criaSerie(char *linhaSerie){
    tSerie* serie = (tSerie*) malloc(sizeof(tSerie));
    if (serie == NULL) {
        printf("Erro na alocacao de memoria para a serie!\n");
        exit(1);
    }

    // Formato esperado: #ID;TITULO;RESTR_ASSIN;RESTR_IDADE;ANO;DUR_EP;NUM_EPS;IDIOMA
    // Exemplo: #123456793;OS ANEIS DE PODER;0;1;2022;70;8;DL
    int restrAssinaturaInt, restrIdadeInt;

    sscanf(linhaSerie, "%[^;];%[^;];%d;%d;%d;%d;%d;%s",
           serie->id,
           serie->titulo,
           &restrAssinaturaInt,
           &restrIdadeInt,
           &serie->anoLancamento,
           &serie->duracaoPorEpisodio,
           &serie->numEpisodios,
           serie->idioma);

    serie->restricaoAssinatura = (TipoAssinatura)restrAssinaturaInt;
    serie->restricaoIdade = (TipoUsuario)restrIdadeInt;

    serie->notaMedia = 0.0;
    strcpy(serie->produtora, "PRODUTORA INDEFINIDA");

    return serie;
}

/// @brief Libera a memória alocada dinamicamente para uma série.
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tSerie* e liberado.
void liberaSerie(void *dado){
        tSerie* serie = (tSerie*) dado;
    if (serie != NULL) {
        free(serie);
    }
}

/// @brief Imprime as informações de uma série no formato especificado.
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tSerie*.
void printaSerie(void *dado){
    tSerie* serie = (tSerie*) dado;
    
    int duracaoTotal = serie->duracaoPorEpisodio * serie->numEpisodios;
    int horas = 0, minutos = 0;
    converteMinutos(duracaoTotal, &horas, &minutos);
    const char* descIdioma = descricaoIdioma(serie->idioma);
    
    // NOVO FORMATO (Funcionalidade 4): TIPO #ID; NOME; HH:MM; IDIOMA; ANO
    printf("SERIE %s; %s; %02d:%02d; %s; %d\n",
        serie->id, 
        serie->titulo, 
        horas, 
        minutos, 
        descIdioma, 
        serie->anoLancamento);
}

/// @brief Atualiza o número de episódios de uma série existente.
/// @param dado Um ponteiro para uma série.
/// @param novoTotalEpisodios O novo número total de episódios.
void atualizaEpisodiosSerie(void *dado, int novoTotalEpisodios){
     tSerie* serie = (tSerie*) dado;
    serie->numEpisodios = novoTotalEpisodios;
}

// --- Funções "get" para os callbacks do TAD Conteudo ---

char getTipoSerie(){
     return 'S';
}

int getAnoLancamentoSerie(void *dado){
    tSerie* serie = (tSerie*) dado;
    return serie->anoLancamento;
}

char* getCodConteudoSerie(void *dado){
     tSerie* serie = (tSerie*) dado;
    return serie->id;
}

char* getTituloSerie(void *dado){
    tSerie* serie = (tSerie*) dado;
    return serie->titulo;
}

int getDuracaoSerie(void *dado){
       tSerie* serie = (tSerie*) dado;
    // A "duração" de uma série para o sistema é a duração total
    return serie->duracaoPorEpisodio * serie->numEpisodios;
}

float getNotaMediaSerie(void *dado){
      tSerie* serie = (tSerie*) dado;
    return serie->notaMedia;
}

TipoAssinatura getRestricaoAssinaturaSerie(void *dado){
      tSerie* serie = (tSerie*) dado;
    return serie->restricaoAssinatura;
}

TipoUsuario getRestricaoIdadeSerie(void *dado){
    tSerie* serie = (tSerie*) dado;
    return serie->restricaoIdade;
}
