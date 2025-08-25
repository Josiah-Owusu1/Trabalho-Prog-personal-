#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jogo.h"
#include "util.h"

// Forward declaration para o TAD opaco
struct Jogo {
    char id[10];
    char titulo[101];
    TipoAssinatura restricaoAssinatura;
    TipoUsuario restricaoIdade;
    int anoLancamento;
    int duracaoEstimada; // Duração em minutos para completar
    char categoria[16];  // Categoria com até 15 caracteres + '\0'
    char desenvolvedora[21]; // Desenvolvedora com até 20 caracteres + '\0'
    float notaMedia;
};

/// @brief Cria uma variável do tipo tJogo a partir de uma linha de dados.
/// @param linhaJogo A string lida do teclado com as informações de um jogo (sem o 'J').
/// @return Um ponteiro para o objeto tJogo* criado.
tJogo* criaJogo(char *linhaJogo){
    tJogo* jogo = (tJogo*) malloc(sizeof(tJogo));
    if (jogo == NULL) {
        printf("Erro na alocacao de memoria para o jogo!\n");
        exit(1);
}
}

/// @brief Libera a memória alocada dinamicamente para um jogo.
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tJogo* e liberado.
void liberaJogo(void *dado){
     tJogo* jogo = (tJogo*) dado;
    if (jogo != NULL) {
        free(jogo);
    }
}

/// @brief Imprime as informações de um jogo no formato especificado.
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tJogo*.
void printaJogo(void *dado){
     tJogo* jogo = (tJogo*) dado;

    int horas = 0, minutos = 0;
    converteMinutos(jogo->duracaoEstimada, &horas, &minutos);
    
    // NOVO FORMATO (Funcionalidade 4): TIPO #ID; NOME; HH:MM; IDIOMA (N/A); ANO
    printf("JOGO %s; %s; %02d:%02d; N/A; %d\n",
        jogo->id, 
        jogo->titulo, 
        horas, 
        minutos,
        jogo->anoLancamento);
}


// --- Funções "get" para os callbacks do TAD Conteudo ---

char getTipoJogo(){
     return 'J';
}

int getAnoLancamentoJogo(void *dado){
    tJogo* jogo = (tJogo*) dado;
    return jogo->anoLancamento;
}

char* getCodConteudoJogo(void *dado){
      tJogo* jogo = (tJogo*) dado;
    return jogo->id;
}

char* getTituloJogo(void *dado){
      tJogo* jogo = (tJogo*) dado;
    return jogo->titulo;
}

int getDuracaoJogo(void *dado){
    tJogo* jogo = (tJogo*) dado;
    return jogo->duracaoEstimada;
}

float getNotaMediaJogo(void *dado){
      tJogo* jogo = (tJogo*) dado;
    return jogo->notaMedia;
}

TipoAssinatura getRestricaoAssinaturaJogo(void *dado){
     tJogo* jogo = (tJogo*) dado;
    return jogo->restricaoAssinatura;
}

TipoUsuario getRestricaoIdadeJogo(void *dado){
     tJogo* jogo = (tJogo*) dado;
    return jogo->restricaoIdade;
}

