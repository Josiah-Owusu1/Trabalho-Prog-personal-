#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "conteudo.h"
#include "usuario.h"
#include "sistema.h"

// declaracao para o TAD opaco
struct Usuario {
   char nomeCompleto[101];
    char cpf[15]; // Identificador único
    char telefone[15];
    char endereco[151];
    char nomeUsuario[16];
    char senha[21];
 
    char dataNascimento[11];
    char email[51];
    int numConteudosConsumidos;
    int numAvaliacoesRealizadas;
    int totalMinutosConsumidos;
    TipoUsuario tipo; // Flag para 18+ (ADULTO) ou infantil (INFANTIL)

     tConteudo** listaReproducao;
    int qtdConteudoReproducao;
    int capacidadeReproducao;

    tConteudo** listaConsumidos;
    int qtdConteudoConsumido;
    int capacidadeConsumido;

    char cartaoCredito[13];// Para ADULTO
    TipoAssinatura assinatura;// Para ADULTO
    char cpfResponsavel[15];// Para INFANTIL
};

/// @brief Cria um objeto do tipo tUsuario*.
/// @param tipo O tipo de usuário a ser criado (ADULTO ou INFANTIL).
/// @param linhaDados A string com os dados do usuário a serem cadastrados.
/// @return Um ponteiro para o objeto tUsuario* criado.
tUsuario* criaUsuario(TipoUsuario tipo, const char* subtipoAtor, char* linhaDados){
       tUsuario* usuario = (tUsuario*) malloc(sizeof(tUsuario));
    if (usuario == NULL) {
        printf("Erro na alocacao de memoria para o usuario!\n");
        exit(1);
    }
    usuario->tipo = tipo;
    usuario->numConteudosConsumidos = 0;
    usuario->numAvaliacoesRealizadas = 0;
    usuario->totalMinutosConsumidos = 0;
    
    // Inicializa as listas dinâmicas
    usuario->capacidadeReproducao = 10;
    usuario->qtdConteudoReproducao = 0;
    usuario->listaReproducao = (tConteudo**) malloc(usuario->capacidadeReproducao * sizeof(tConteudo*));

    usuario->capacidadeConsumido = 10;
    usuario->qtdConteudoConsumido = 0;
    usuario->listaConsumidos = (tConteudo**) malloc(usuario->capacidadeConsumido * sizeof(tConteudo*));

     if (tipo == ADULTO) {
        // Formato ADULTO: NOME;CPF;TELEFONE;ENDERECO;LOGIN;SENHA;NASC;EMAIL;CARTAO 
        sscanf(linhaDados, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s",
            usuario->nomeCompleto, usuario->cpf, usuario->telefone, usuario->endereco,
            usuario->nomeUsuario, usuario->senha, usuario->dataNascimento,
            usuario->email, usuario->cartaoCredito);
        strcpy(usuario->cpfResponsavel, ""); // Garante que o campo do responsável esteja vazio
            usuario->assinatura = (strcmp(subtipoAtor, "PREMIUM")== 0) ? PREMIUM : PADRAO;
    } else { // INFANTIL
        // Formato INFANTIL: NOME;CPF;TELEFONE;ENDERECO;LOGIN;SENHA;NASC;EMAIL;CPF_RESP 
        sscanf(linhaDados, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s",
            usuario->nomeCompleto, usuario->cpf, usuario->telefone, usuario->endereco,
            usuario->nomeUsuario, usuario->senha, usuario->dataNascimento,
            usuario->email, usuario->cpfResponsavel);
        strcpy(usuario->cartaoCredito, ""); // Garante que o campo de cartão esteja vazio
    }

    return usuario;
}

/// @brief Libera toda a memória alocada para um usuário e suas listas.
/// @param usuario Um ponteiro para o usuário a ser liberado.
void liberaUsuario(tUsuario* usuario){
     if (usuario == NULL) return;

    free(usuario->listaReproducao);
    free(usuario->listaConsumidos);

    free(usuario);
}


/// @brief Retorna o CPF de um usuário.
/// @param usuario Um ponteiro para o usuário.
/// @return Uma string contendo o CPF do usuário.
char* getCpfUsuario(tUsuario* usuario){
    return usuario->cpf;
}

/// @brief Verifica se a senha fornecida corresponde à senha do usuário.
/// @param usuario O usuário a ser verificado.
/// @param senha A senha a ser comparada.
/// @return 1 se a senha for correta, 0 caso contrário.
int verificaSenhaUsuario(tUsuario* usuario, const char* senha){
    if (strcmp(usuario->senha, senha) == 0) {
        return 1; // Senha correta
    }
    return 0; // Senha incorreta
}

/// @brief Adiciona um conteúdo à lista de reprodução do usuário.
/// @param usuario O usuário que receberá o conteúdo.
/// @param conteudo O conteúdo a ser adicionado.
void adicionaConteudoListaReproducao(tUsuario* usuario, tConteudo* conteudo){
   if (usuario->qtdConteudoReproducao == usuario->capacidadeReproducao) {
        usuario->capacidadeReproducao *= 2;
        
        tConteudo** temp = realloc(usuario->listaReproducao, usuario->capacidadeReproducao * sizeof(tConteudo*));
        if (temp == NULL) {
            printf("Erro na realocacao de memoria!\n");
            // Aqui poderíamos tentar liberar a memória antes de sair
            exit(1);
        }
        usuario->listaReproducao = temp; // Apenas atribui de volta se o realloc foi bem-sucedido
    }
    usuario->listaReproducao[usuario->qtdConteudoReproducao] = conteudo;
    usuario->qtdConteudoReproducao++;
}

/// @brief Imprime a lista de reprodução de um usuário.
/// @param usuario O usuário cuja lista será impressa.
void imprimeListaReproducaoUsuario(tUsuario* usuario){
    if (usuario->qtdConteudoReproducao == 0) {
        printf("LISTA DE REPRODUCAO VAZIA!\n");
        printf("(TOTAL 0:00 horas)\n"); 
        return;
    }

    printf("LISTA DE REPRODUCAO:\n");
    int totalMinutos = 0;
    for (int i = 0; i < usuario->qtdConteudoReproducao; i++) {
        tConteudo* c = usuario->listaReproducao[i];
        printf("%d-", i + 1); // Numeração da lista
        printaConteudo(c); // O TAD Conteudo sabe como se imprimir
        totalMinutos += getDuracaoConteudo(c);
    }
    
    int horas, minutos;
    converteMinutos(totalMinutos, &horas, &minutos);
    printf("(TOTAL %d:%02d horas)\n", horas, minutos);
}

/// @brief Busca um conteúdo na lista de reprodução do usuário pelo seu ID.
/// @param usuario O usuário.
/// @param idConteudo O ID do conteúdo a ser buscado.
/// @return Um ponteiro para o tConteudo se encontrado, caso contrário NULL.
tConteudo* buscaConteudoListaReproducao(tUsuario* usuario, const char* idConteudo){
     for (int i = 0; i < usuario->qtdConteudoReproducao; i++) {
        // Compara o ID do conteúdo na lista com o ID buscado
        if (strcmp(getCodConteudo(usuario->listaReproducao[i]), idConteudo) == 0) {
            return usuario->listaReproducao[i];
        }
    }
    return NULL;
}

/// @brief Remove um conteúdo da lista de reprodução do usuário.
/// @param usuario O usuário.
/// @param idConteudo O ID do conteúdo a ser removido.
void removeConteudoListaReproducao(tUsuario* usuario, const char* idConteudo){
  int i, achou = -1;
    for (i = 0; i < usuario->qtdConteudoReproducao; i++) {
        if (strcmp(getCodConteudo(usuario->listaReproducao[i]), idConteudo) == 0) {
            achou = i;
            break;
        }
    }

    if (achou != -1) {
        // Move todos os elementos após o item removido uma posição para a esquerda
        for (i = achou; i < usuario->qtdConteudoReproducao - 1; i++) {
            usuario->listaReproducao[i] = usuario->listaReproducao[i + 1];
        }
        usuario->qtdConteudoReproducao--;
    }
}


/// @brief Retorna o tipo do usuário (ADULTO ou INFANTIL).
/// @param usuario O usuário.
/// @return O enum TipoUsuario correspondente.
TipoUsuario getTipoUsuario(tUsuario* usuario){
    return usuario->tipo;
}

/// @brief Retorna o tipo de assinatura de um usuário adulto.
//         Para um usuário infantil, retorna a assinatura do seu responsável.
/// @param usuario O usuário (pode ser infantil).
/// @param sistema O sistema principal, para buscar o responsável se necessário.
/// @return O enum TipoAssinatura correspondente.
TipoAssinatura getAssinaturaUsuario(tUsuario* usuario, tSistema* sistema){
     if (usuario->tipo == ADULTO) {
        return usuario->assinatura;
    } else { // Se for infantil, busca a assinatura do responsável
        tUsuario* responsavel = buscaUsuarioSistema(sistema, usuario->cpfResponsavel);
        if (responsavel) {
            return responsavel->assinatura;
        }
        return PADRAO; // Caso não encontre o responsável, retorna padrão
    }
}

/// @brief "Consome" o primeiro item da lista de reprodução do usuário.
//         Isso envolve mover o conteúdo para a lista de "consumidos" e
//         atualizar as estatísticas do usuário.
/// @param usuario O usuário.
/// @return Um ponteiro para o conteúdo que foi consumido.
tConteudo* consomePrimeiroDaLista(tUsuario* usuario){
    if (usuario->qtdConteudoReproducao == 0) {
        return NULL;
    }

    tConteudo* consumido = usuario->listaReproducao[0];
    
    // Remove da lista de reprodução
    removeConteudoListaReproducao(usuario, getCodConteudo(consumido));

    // Adiciona na lista de consumidos
    adicionaConteudoListaConsumidos(usuario, consumido);
    
    // Atualiza estatísticas
    usuario->numConteudosConsumidos++;
    usuario->totalMinutosConsumidos += getDuracaoConteudo(consumido);
    
    return consumido;
}

char* getNomeCompleto(tUsuario* usuario) { return usuario->nomeCompleto; }
char* getTelefone(tUsuario* usuario) { return usuario->telefone; }
char* getEndereco(tUsuario* usuario) { return usuario->endereco; }
char* getLogin(tUsuario* usuario) { return usuario->nomeUsuario; }
char* getSenha(tUsuario* usuario) { return usuario->senha; }
char* getEmail(tUsuario* usuario) { return usuario->email; }
char* getDataNascimento(tUsuario* usuario) { return usuario->dataNascimento; }
int getNumConsumidos(tUsuario* usuario) { return usuario->qtdConteudoConsumido; }
int getTotalMinutosConsumidos(tUsuario* usuario) { return usuario->totalMinutosConsumidos; }
int getNumAvaliacoes(tUsuario* usuario) { return usuario->numAvaliacoesRealizadas; }
char* getCartao(tUsuario* usuario) { return usuario->cartaoCredito; }
char* getCpfResponsavel(tUsuario* usuario) { return usuario->cpfResponsavel; }
tConteudo* getConteudoConsumidoPeloIndice(tUsuario* usuario, int indice) {
    if (indice < 0 || indice >= usuario->qtdConteudoConsumido) return NULL;
    return usuario->listaConsumidos[indice];
}