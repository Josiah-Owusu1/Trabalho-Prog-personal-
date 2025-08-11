#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avaliacao.h"

struct Avaliacao{
   char cpf[15];
   int nota; 
};


/// @brief Função que cria um objeto do tipo tAvaliação*
/// @param cpf - CPF da pessoa que fez a avaliação
/// @param nota - A nota que a pessoa deu
/// @return O objeto avaliação criado
tAvaliacao* criaAvaliacao(char* cpf, int nota)
{
     tAvaliacao* avaliacao = (tAvaliacao*) malloc(sizeof(tAvaliacao));
    if (avaliacao == NULL) 
    {
        printf("Erro na alocacao de memoria para a avaliacao!\n");
        exit(1);
}
    strcpy(avaliacao->cpf,cpf);
    avaliacao->nota = nota;
    return avaliacao;
}

/// @brief Retorna a nota de uma avaliação
/// @param a 
/// @return A nota de uma avaliação
int getNotaAvaliacao(tAvaliacao *a){
    return a->nota;
}


/// @brief Retorna o CPF de quem fez aquela avaliação
/// @param a 
/// @return O CPF do responsável pela avaliação
char* getCpfAvaliacao(tAvaliacao *a){
    return a->cpf;
}

/// @brief Função que libera a memória alocada para uma avaliação
/// @param avaliacao um ponteiro para uma variável do tipo tAvaliacao
void liberaAvaliacao(tAvaliacao *avaliacao){
      if (avaliacao != NULL) {
        free(avaliacao);
    }
}

