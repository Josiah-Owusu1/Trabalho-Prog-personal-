#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sistema.h"
#include "usuario.h"
#include "distribuidor.h"
#include "conteudo.h"

// O TAD principal que armazena todos os dados do sistema
 struct Sistema{
    tUsuario** usuarios;
    int qtdUsuarios;
    int capacidadeUsuarios;

    tDistribuidor** distribuidores;
    int qtdDistribuidores;
    int capacidadeDistribuidores;
    
    tConteudo** conteudos;
    int qtdConteudos;
    int capacidadeConteudos;
 };

/// @brief Cria e inicializa o sistema.
/// @return Um ponteiro para o sistema criado.
tSistema* criaSistema(){
     tSistema* sistema = (tSistema*) malloc(sizeof(tSistema));
    if (sistema == NULL) {
        printf("Erro na alocacao de memoria para o sistema!\n");
        exit(1);
    }
    sistema->qtdUsuarios = 0;
    sistema->capacidadeUsuarios = 20;
    sistema->usuarios = (tUsuario**) malloc(sistema->capacidadeUsuarios * sizeof(tUsuario*));

    // Inicializa a lista de distribuidores
    sistema->qtdDistribuidores = 0;
    sistema->capacidadeDistribuidores = 10;
    sistema->distribuidores = (tDistribuidor**) malloc(sistema->capacidadeDistribuidores * sizeof(tDistribuidor*));

    // Inicializa a lista de conteúdos (catálogo geral)
    sistema->qtdConteudos = 0;
    sistema->capacidadeConteudos = 50;
    sistema->conteudos = (tConteudo**) malloc(sistema->capacidadeConteudos * sizeof(tConteudo*));
    
    return sistema;
}

/// @brief Libera toda a memória alocada pelo sistema, incluindo todos os
/// usuários, distribuidores e conteúdos.
/// @param sistema O sistema a ser liberado.
void liberaSistema(tSistema* sistema){
    if(sistema == NULL) return;

    for (int i = 0; i < sistema->qtdUsuarios; i++) {
        liberaUsuario(sistema->usuarios[i]);
    }
    free(sistema->usuarios);

    // Libera cada distribuidor
    for (int i = 0; i < sistema->qtdDistribuidores; i++) {
        liberaDistribuidor(sistema->distribuidores[i]);
    }
    free(sistema->distribuidores);

    // Libera cada conteúdo do catálogo
    for (int i = 0; i < sistema->qtdConteudos; i++) {
        liberaConteudo(sistema->conteudos[i]);
    }
    free(sistema->conteudos);

    // Libera a struct do sistema
    free(sistema);
}


// --- Funções de Gerenciamento de USUÁRIOS ---

/// @brief Adiciona um usuário à lista de usuários do sistema.
/// @param sistema O sistema.
/// @param usuario O usuário a ser adicionado.
void adicionaUsuarioSistema(tSistema* sistema, tUsuario* usuario){
      if (sistema->qtdUsuarios == sistema->capacidadeUsuarios) {
        sistema->capacidadeUsuarios *= 2;
        sistema->usuarios = (tUsuario**) realloc(sistema->usuarios, sistema->capacidadeUsuarios * sizeof(tUsuario*));
    }
    sistema->usuarios[sistema->qtdUsuarios] = usuario;
    sistema->qtdUsuarios++;
}

/// @brief Busca um usuário no sistema pelo seu CPF.
/// @param sistema O sistema.
/// @param cpf O CPF a ser buscado.
/// @return Um ponteiro para o tUsuario se encontrado, caso contrário NULL.
tUsuario* buscaUsuarioSistema(tSistema* sistema, const char* cpf){
    for (int i = 0; i < sistema->qtdUsuarios; i++) {
        if (strcmp(getCpfUsuario(sistema->usuarios[i]), cpf) == 0) {
            return sistema->usuarios[i];
        }
    }
    return NULL;
}


// --- Funções de Gerenciamento de DISTRIBUIDORES ---

/// @brief Adiciona um distribuidor à lista de distribuidores do sistema.
/// @param sistema O sistema.
/// @param distribuidor O distribuidor a ser adicionado.
void adicionaDistribuidorSistema(tSistema* sistema, tDistribuidor* distribuidor){
    if (sistema->qtdDistribuidores == sistema->capacidadeDistribuidores) {
        sistema->capacidadeDistribuidores *= 2;
        sistema->distribuidores = (tDistribuidor**) realloc(sistema->distribuidores, sistema->capacidadeDistribuidores * sizeof(tDistribuidor*));
    }
    sistema->distribuidores[sistema->qtdDistribuidores] = distribuidor;
    sistema->qtdDistribuidores++;
}

/// @brief Busca um distribuidor no sistema pelo seu CNPJ.
/// @param sistema O sistema.
/// @param cnpj O CNPJ a ser buscado.
/// @return Um ponteiro para o tDistribuidor se encontrado, caso contrário NULL.
tDistribuidor* buscaDistribuidorSistema(tSistema* sistema, const char* cnpj){
     for (int i = 0; i < sistema->qtdDistribuidores; i++) {
        if (strcmp(getCnpjDistribuidor(sistema->distribuidores[i]), cnpj) == 0) {
            return sistema->distribuidores[i];
        }
    }
    return NULL;
}


// --- Funções de Gerenciamento de CONTEÚDOS ---

/// @brief Adiciona um conteúdo ao catálogo geral do sistema.
/// @param sistema O sistema.
/// @param conteudo O conteúdo a ser adicionado.
void adicionaConteudoSistema(tSistema* sistema, tConteudo* conteudo){
    if (sistema->qtdConteudos == sistema->capacidadeConteudos) {
        sistema->capacidadeConteudos *= 2;
        sistema->conteudos = (tConteudo**) realloc(sistema->conteudos, sistema->capacidadeConteudos * sizeof(tConteudo*));
    }
    sistema->conteudos[sistema->qtdConteudos] = conteudo;
    sistema->qtdConteudos++;
}

/// @brief Busca um conteúdo no sistema pelo seu ID único.
/// @param sistema O sistema.
/// @param id O ID do conteúdo a ser buscado.
/// @return Um ponteiro para o tConteudo se encontrado, caso contrário NULL.
tConteudo* buscaConteudoSistema(tSistema* sistema, const char* id){
      for (int i = 0; i < sistema->qtdConteudos; i++) {
        // O ID vem com '#' no início, precisamos pular esse caractere na comparação
        if (strcmp(getCodConteudo(sistema->conteudos[i]) + 1, id + 1) == 0) {
            return sistema->conteudos[i];
        }
    }
    return NULL;
}

int getTotalConteudos(tSistema* sistema) {
    return sistema->qtdConteudos;
}
tConteudo* getConteudoPeloIndice(tSistema* sistema, int indice) {
    if (indice < 0 || indice >= sistema->qtdConteudos) return NULL;
    return sistema->conteudos[indice];
}

