#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conteudo.h"
#include "util.h"
#include "avaliacao.h"

struct Conteudo {
    void* dado;

 // Ponteiros de função ("callbacks") para as operações específicas
     func_ptr_codConteudo getCod;
    func_ptr_titulo getTitulo;
    func_ptr_anoLancamento getAno;
    func_ptr_notaMedia getNota;
    func_ptr_duracao getDuracao;
    func_ptr_printaConteudo printa;
    func_ptr_liberaConteudo libera;
    func_ptr_restricaoConteudo getRestricaoAssinatura;
    func_ptr_restricaoIdade getRestricaoIdade;
    func_ptr_tipoConteudo getTipo;

    tAvaliacao** avaliacoes;
    int qtdAvaliacoes;
    int capacidadeAvaliacoes;
};




/// @brief Função que cria uma variável do tipo conteúdo. Olhar os tipos dos callbacks acima
/// @param dado Um ponteiro para um objeto genérico (Filme, Série ou Jogo)
/// @param anoLancamento Um callback para a função que retorna o ano de lançamento do conteúdo
/// @param codConteudo Um callback para a função que retorna o codigo do conteúdo
/// @param notaMedia Um callback para a função que retorna a nota media do conteúdo
/// @param titulo Um callback para a função que retorna o titulo do conteúdo
/// @param duracao Um callback para a função que retorna a duracao do conteúdo
/// @param printaConteudo Um callback para a função que imprime o conteúdo
/// @param restricaoConteudo Um callback para a função que retorna restricao do conteudo (Assinatura)
/// @param tipoConteudo Um callback para a função que retorna o tipo do conteudo 
/// @param restricaoIdade Um callback para a função que retorna restricao de idade do conteudo 
/// @param liberaConteudo Um callback para a função que libera o conteúdo
/// @return Uma variável do tipo tConteudo* que armazena os parâmetros listados
tConteudo *criaConteudo(void *dado,
                        func_ptr_anoLancamento anoLancamento,
                        func_ptr_codConteudo codConteudo,
                        func_ptr_notaMedia notaMedia,
                        func_ptr_titulo titulo,
                        func_ptr_duracao duracao,
                        func_ptr_printaConteudo printaConteudo,
                        func_ptr_restricaoConteudo restricaoConteudo,
                        func_ptr_tipoConteudo tipoConteudo,
                        func_ptr_restricaoIdade restricaoIdade,
                        func_ptr_liberaConteudo liberaConteudo
                    ){
                           tConteudo* c = (tConteudo*) malloc(sizeof(tConteudo));
    if (c == NULL) {
        printf("Erro na alocacao de memoria para o conteudo!\n");
        exit(1);
    }

    c->dado = dado;

    c->getAno = anoLancamento;
    c->getCod = codConteudo;
    c->getNota = notaMedia;
    c->getTitulo = titulo;
    c->getDuracao = duracao;
    c->printa = printaConteudo;
    c->getRestricaoAssinatura = restricaoConteudo;
    c->getTipo = tipoConteudo;
    c->getRestricaoIdade = restricaoIdade;
    c->libera = liberaConteudo;

    c->qtdAvaliacoes = 0;
    c->capacidadeAvaliacoes = 5; // Capacidade inicial de 5 avaliações
    c->avaliacoes = (tAvaliacao**) malloc(c->capacidadeAvaliacoes * sizeof(tAvaliacao*));
    if (c->avaliacoes == NULL) {
        printf("Erro na alocacao de memoria para as avaliacoes!\n");
        exit(1);
    }
    
    return c;
                    }


/// @brief Retorna o tipo da assinatura necessária para assistir um conteúdo (olhar util.h/.c)
/// @param conteudo - Um ponteiro para um conteúdo
/// @return o tipo da assinatura necessária para assistir um conteúdo
TipoAssinatura getRestricaoConteudo(tConteudo *conteudo){
     return conteudo->getRestricaoAssinatura(conteudo->dado);
}

/// @brief Imprime as informações de um conteúdo de acordo com o especificado (especificação/Casos)
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
void printaConteudo(tConteudo *conteudo){
    conteudo->printa(conteudo->dado);
}

/// @brief Retorna o tipo do conteúdo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return o tipo do conteúdo
char getTipoConteudo(tConteudo *conteudo){
     return conteudo->getTipo();
}

/// @brief Retorna a duração do conteudo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return A duração do conteudo
int getDuracaoConteudo(tConteudo *conteudo){
      return conteudo->getDuracao(conteudo->dado);
}

/// @brief Retorna o codigo unico do conteudo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return o codigo unico do conteudo
char *getCodConteudo(tConteudo *conteudo){
     return conteudo->getCod(conteudo->dado);
}

/// @brief Retorna a restrição de idade do conteudo (olhar util.c/.h)
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return a restrição de idade do conteudo
TipoUsuario getRestricaoIdade(tConteudo *conteudo){
     return conteudo->getRestricaoIdade(conteudo->dado);
}

/// @brief Insere uma avaliação a em um conteúdo c
/// @param c um ponteiro para uma variável do tipo conteúdo
/// @param a um ponteiro para uma avaliação
void inserirAvaliacaoConteudo(tConteudo *c, tAvaliacao *a){
    if (c->qtdAvaliacoes == c->capacidadeAvaliacoes) 
    {
        // Dobra a capacidade
        c->capacidadeAvaliacoes *= 2;
        c->avaliacoes = (tAvaliacao**) realloc(c->avaliacoes, c->capacidadeAvaliacoes * sizeof(tAvaliacao*));
        if (c->avaliacoes == NULL) 
        {
            printf("Erro na realocacao de memoria para as avaliacoes!\n");
            exit(1);
        }
    }
    c->avaliacoes[c->qtdAvaliacoes] = a;
    c->qtdAvaliacoes++;
}

/// @brief Função que imprime o conteúdo com a nota dada pelo usuário de cpf
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @param cpf O cpf da pessoa que deu a nota
void printaConteudoComNota(tConteudo *conteudo, char* cpf){
     tAvaliacao* avaliacao = buscaNotaAvaliacao(conteudo, cpf);
    int nota = getNotaAvaliacao(avaliacao);
    printf("CONTEUDO %s AVALIADO COM NOTA %d!\n", getTituloConteudo(conteudo), nota);
}

/// @brief Função que retorna a avaliação de um conteúdo dado pelo usuário de cpf
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @param cpf o cpf da pessoa que fez a avaliação
/// @return A avaliação que a pessoa deu ao conteúdo, se ela existir
tAvaliacao* buscaNotaAvaliacao(tConteudo *conteudo, char* cpf){
    for (int i = 0; i < conteudo->qtdAvaliacoes; i++) {
        if (strcmp(getCpfAvaliacao(conteudo->avaliacoes[i]), cpf) == 0) {
            return conteudo->avaliacoes[i];
        }
    }
    return NULL; 
}

/// @brief Retorna a quantidade de avaliações de um conteúdo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return A quantidade de avaliações de um conteúdo
int getQtdAvaliacoes(tConteudo *conteudo){
    return conteudo->qtdAvaliacoes;
}

/// @brief Retorna a avaliação da posição "pos" do vetor de avaliações de um conteúdo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @param pos A posição da avaliação no conteúdo
/// @return Um ponteiro para uma variável da avaliação, se existir.
tAvaliacao* getAvaliacaoPosicao(tConteudo *conteudo, int pos){
      if (pos < 0 || pos >= conteudo->qtdAvaliacoes) {
        return NULL; // Posição inválida
    }
    return conteudo->avaliacoes[pos];
}

/// @brief Retorna o título do conteúdo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return  o título do conteúdo
char* getTituloConteudo(tConteudo *conteudo){
        return conteudo->getTitulo(conteudo->dado);
}

/// @brief Retorna a nota media do conteúdo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return a nota media do conteúdo
float getNotaMediaConteudo(tConteudo *conteudo){
    return conteudo->getNota(conteudo->dado);
}

/// @brief Função que libera a memória alocada para um conteúdo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
void liberaConteudo(tConteudo *conteudo){
      if (conteudo == NULL) return;
    // 1. Libera o dado específico (filme/serie/jogo)
    conteudo->libera(conteudo->dado);
    // 2. Libera cada uma das avaliações
    for (int i = 0; i < conteudo->qtdAvaliacoes; i++) {
        liberaAvaliacao(conteudo->avaliacoes[i]);
    }
    // 3. Libera o array de ponteiros de avaliações
    free(conteudo->avaliacoes);
    // 4. Libera a struct do conteúdo genérico
    free(conteudo);
}

/// @brief Retorna o ponteiro genérico para o conteúdo (variável filme/jogo/serie)
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return o ponteiro genérico para o conteúdo armazenado pelo tad genérico
void* getDadoConteudo(tConteudo *conteudo){
    return conteudo->dado;
}

// Adicionar em conteudo.c
void imprimeConteudoEmLista(tConteudo* conteudo, int num) {
    char tipoStr[10];
    char tipo = getTipoConteudo(conteudo);
    if (tipo == 'F') strcpy(tipoStr, "FILME");
    else if (tipo == 'S') strcpy(tipoStr, "SERIE");
    else strcpy(tipoStr, "JOGO");

    int duracao = getDuracaoConteudo(conteudo);
    int horas = duracao / 60;
    int minutos = duracao % 60;

    // Para filmes e séries, precisamos do idioma. Para jogos, é "N/A".
    char idiomaStr[30] = "N/A";
    if (tipo == 'F' || tipo == 'S') {
        // Precisaríamos de uma função getIdioma... vamos simplificar por enquanto
        // Supondo que exista uma função getIdioma no tFilme/tSerie que retorna "DL", "L", etc.
        // const char* idioma = getIdioma(getDadoConteudo(conteudo));
        // strcpy(idiomaStr, descricaoIdioma(idioma));
    }
    
    // Formato final da Funcionalidade 4:
    // NUMERO-TIPO #ID; NOME; HH:MM; IDIOMA/N/A; ANO
    printf("%d-%s %s; %s; %02d:%02d; %s; %d\n",
        num,
        tipoStr,
        getCodConteudo(conteudo),
        getTituloConteudo(conteudo),
        horas, minutos,
        idiomaStr, // Usando a string N/A por enquanto para simplificar
        getAnoLancamento(conteudo) // Precisaria de um getAnoLancamento genérico
    );
}