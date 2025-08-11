#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filme.h"
#include "util.h"

struct Filme {
    char id[10];               
    char titulo[101];           
    TipoAssinatura restricaoAssinatura; 
    TipoUsuario restricaoIdade; 
    int anoLancamento;         
    int duracao;               
    char idioma[4];             
    float notaMedia;          
    char produtora[101];         
};

/// @brief Cria uma variável do tipo tFilme
/// @param linhaFilme - A string lida do teclado com as informações de um filme (sem o F)
/// @return O objeto criado
tFilme* criaFilme(char *linhaFilme){
    tFilme* filme = (tFilme*) malloc(sizeof(tFilme));
    if (filme == NULL) {
        printf("Erro na alocacao de memoria para o filme!\n");
        exit(1);
    }

    
    int restrAssinaturaInt, restrIdadeInt;

    sscanf(linhaFilme, "%[^;];%[^;];%d;%d;%d;%d;%s",
           filme->id,
           filme->titulo,
           &restrAssinaturaInt,
           &restrIdadeInt,
           &filme->anoLancamento,
           &filme->duracao,
           filme->idioma);
    
    filme->restricaoAssinatura = (TipoAssinatura)restrAssinaturaInt;
    filme->restricaoIdade = (TipoUsuario)restrIdadeInt;

    // A nota média inicial é 0, pois ainda não foi avaliado
    filme->notaMedia = 0.0;
    
    // A produtora não é fornecida no cadastro do conteúdo, mas é impressa.
    // Vamos definir um valor padrão por enquanto. Isso pode ser ajustado depois.
    strcpy(filme->produtora, "PRODUTORA INDEFINIDA");

    return filme;
}

/// @brief Retorna o ano de lançamento de um filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return O ano de lançamento do filme
int getAnoLancamentoFilme(void *dado){
     tFilme* filme = (tFilme*) dado;
    return filme->anoLancamento;
}

/// @brief Retorna o codigo (id único) de um filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return O codigo (id único) do filme
char* getCodConteudoFilme(void *dado){
     tFilme* filme = (tFilme*) dado;
    return filme->id;
}


/// @brief Retorna o título de um filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return O título do filme
char* getTituloFilme(void *dado){
    tFilme* filme = (tFilme*) dado;
    return filme->titulo;
}

/// @brief Retorna a duração de um filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return A duração do filme
int getDuracaoFilme(void *dado){
    tFilme* filme = (tFilme*) dado;
    return filme->duracao;
}

/// @brief Retorna a nota média de um filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return A nota média do filme
float getNotaMediaFilme(void *dado){
    tFilme* filme = (tFilme*) dado;
    return filme->notaMedia;
}

/// @brief Função que imprime as informações de um filme conforme especificação do trabalho
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
void printaFilme(void *dado){
     tFilme* filme = (tFilme*) dado;
    
    int horas = 0, minutos = 0;
    converteMinutos(filme->duracao, &horas, &minutos);
    const char* descIdioma = descricaoIdioma(filme->idioma);

    // Formato da impressão: #; TIPO; ID; NOME; DURACAO; DISP. IDIOMA; ANO; PRODUTORA
    // Exemplo: 1-FILME #123456789; O SENHOR DOS ANEIS: A SOCIEDADE DO ANEL; 2:58; DUBLADO/LEGENDADO; 2001; WINGNUT FILMS
    // O número "1-" no início será controlado por quem chama a função (laço de repetição).
    printf("FILME %s; %s; %d:%02d; %s; %d; %s\n",
        filme->id, filme->titulo, horas, minutos, descIdioma, filme->anoLancamento, filme->produtora);
}


/// @brief Retorna o tipo de assinatura de um filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return O tipo da assinatura do filme (olhar util.h/.c)
TipoAssinatura getRestricaoAssinaturaFilme(void *dado){
     tFilme* filme = (tFilme*) dado;
    return filme->restricaoAssinatura;
}

/// @brief Retorna o tipo de um filme
/// @return o caractere usado para representar um filme: 'F'
char getTipoFilme(){
     return 'F';
}

/// @brief Retorna o tipo do usuario que pode assistir ao filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return O tipo do usuario que pode assistir ao filme (olhar util.h/.c)
TipoUsuario getRestricaoIdadeFilme(void *dado){
tFilme* filme = (tFilme*) dado;
    return filme->restricaoIdade;
}

/// @brief Função que libera a memória alocada dinamicamente para armazenar um filmea
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme* e posteriormente liberado
void liberaFilme(void *dado){
        tFilme* filme = (tFilme*) dado;
    if (filme != NULL) {
        free(filme);
    }
}
