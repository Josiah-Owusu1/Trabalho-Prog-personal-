#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "distribuidor.h"
#include "conteudo.h"

// Forward declaration para o TAD opaco
struct Distribuidor {
    char nomeCompleto[101];
    char cnpj[19];
    char telefone[15];
    char endereco[151];
    char nomeUsuario[16];
    char senha[21];

tConteudo** conteudosOfertados;
    int numProdutosOfertados; // Também é a quantidade de conteúdos na lista
    int capacidadeConteudos;
};

/// @brief Cria um objeto do tipo tDistribuidor*.
/// @param linhaDados A string com os dados do distribuidor a serem cadastrados.
/// @return Um ponteiro para o objeto tDistribuidor* criado.
tDistribuidor* criaDistribuidor(char* linhaDados){
     tDistribuidor* distribuidor = (tDistribuidor*) malloc(sizeof(tDistribuidor));
    if (distribuidor == NULL) {
        printf("Erro na alocacao de memoria para o distribuidor!\n");
        exit(1);
    }

     sscanf(linhaDados, "%[^;];%[^;];%[^;];%[^;];%[^;];%s",
        distribuidor->nomeCompleto, distribuidor->cnpj, distribuidor->telefone,
        distribuidor->endereco, distribuidor->nomeUsuario, distribuidor->senha);

    // Inicializa a lista de conteúdos
    distribuidor->numProdutosOfertados = 0; 
    distribuidor->capacidadeConteudos = 10; // Capacidade inicial
    distribuidor->conteudosOfertados = (tConteudo**) malloc(distribuidor->capacidadeConteudos * sizeof(tConteudo*));
    if (distribuidor->conteudosOfertados == NULL) {
        printf("Erro na alocacao de memoria para a lista de conteudos do distribuidor!\n");
        exit(1);
    }
    
    return distribuidor;
}

/// @brief Libera a memória alocada para um distribuidor.
/// @param distribuidor O distribuidor a ser liberado.
void liberaDistribuidor(tDistribuidor* distribuidor){
    if (distribuidor == NULL) return;

    free(distribuidor->conteudosOfertados);
    
    // Libera a struct do distribuidor
    free(distribuidor);

}

/// @brief Retorna o CNPJ de um distribuidor.
/// @param distribuidor Um ponteiro para o distribuidor.
/// @return Uma string contendo o CNPJ do distribuidor.
char* getCnpjDistribuidor(tDistribuidor* distribuidor){
    return distribuidor->cnpj;
}

/// @brief Adiciona um conteúdo à lista de conteúdos ofertados pelo distribuidor.
/// @param distribuidor O distribuidor que vai ofertar o conteúdo.
/// @param conteudo O conteúdo a ser adicionado.
void adicionaConteudoDistribuidor(tDistribuidor* distribuidor, tConteudo* conteudo){
    if (distribuidor->numProdutosOfertados == distribuidor->capacidadeConteudos) {
        distribuidor->capacidadeConteudos *= 2;
        distribuidor->conteudosOfertados = (tConteudo**) realloc(distribuidor->conteudosOfertados,distribuidor->capacidadeConteudos * sizeof(tConteudo*));
    }
    
    distribuidor->conteudosOfertados[distribuidor->numProdutosOfertados] = conteudo;
    distribuidor->numProdutosOfertados++;
}

