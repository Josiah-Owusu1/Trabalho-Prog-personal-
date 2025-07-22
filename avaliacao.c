#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avaliacao.h"

#define TAMANHO_CPF 15

struct Avaliacao
{
    char cpf[TAMANHO_CPF];
    int nota;
};


/// @brief Função que cria um objeto do tipo tAvaliação*
/// @param cpf - CPF da pessoa que fez a avaliação
/// @param nota - A nota que a pessoa deu
/// @return O objeto avaliação criado
tAvaliacao* criaAvaliacao(char* cpf, int nota)
{
      if(cpf == NULL || nota < 1 || nota > 5) 
    {
        return NULL;
    }
    
    tAvaliacao *a = (tAvaliacao*) malloc(sizeof(tAvaliacao));
        if(a == NULL) 
        {
            return NULL;
        }

    a->nota =nota;
    strncpy(a->cpf, cpf, TAMANHO_CPF -1);
    a->cpf[TAMANHO_CPF -1] = '\0';

    return a;
}



/// @brief Retorna a nota de uma avaliação
/// @param a 
/// @return A nota de uma avaliação
int getNotaAvaliacao(tAvaliacao *a){
    if (a != NULL){
        return a-> nota;
    }
    return -1;
}


/// @brief Retorna o CPF de quem fez aquela avaliação
/// @param a 
/// @return O CPF do responsável pela avaliação
char* getCpfAvaliacao(tAvaliacao *a)
{
    if(a != NULL){
        return a->cpf;
    }
    return NULL;
}

/// @brief Função que libera a memória alocada para uma avaliação
/// @param avaliacao um ponteiro para uma variável do tipo tAvaliacao
void liberaAvaliacao(tAvaliacao *avaliacao)
{
    if(avaliacao != NULL){
        free(avaliacao);
    }
}
