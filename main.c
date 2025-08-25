#include <stdio.h>
#include <string.h>

// Incluímos as interfaces de todos os nossos "departamentos"
#include "sistema.h"
#include "cadastro.h"
#include "interacoes.h"
#include "relatorios.h"
#include "busca.h"

int main() {
    // 1. Cria a instância principal do sistema que gerenciará todos os dados
    tSistema* sistema = criaSistema();
    
    char comando[10];

    // 2. Laço principal que lê e processa os comandos
    while (scanf("%s", comando) == 1) {
        // Verifica o comando e chama a função do módulo correspondente

        if (strcmp(comando, "CAT") == 0) {
            realizaCadastroAtor(sistema);
        } else if (strcmp(comando, "CAC") == 0) {
            realizaCadastroConteudo(sistema);
        } else if (strcmp(comando, "ACL") == 0) {
            realizaAdicionarConteudoNaLista(sistema);
        } else if (strcmp(comando, "RCL") == 0) {
            realizaRemoverConteudoDaLista(sistema);
        } else if (strcmp(comando, "CPCLR") == 0) {
            realizaConsumirPrimeiroDaLista(sistema);
        } else if (strcmp(comando, "MLR") == 0) {
            geraRelatorioListaReproducao(sistema);
        } else if (strcmp(comando, "GRU") == 0) {
            geraRelatorioUsuario(sistema);
        } else if (strcmp(comando, "RGC") == 0) {
            geraRelatorioGeralDeConteudo(sistema);
        } else if (strcmp(comando, "GRAC") == 0) {
            geraRelatorioAvaliacoes(sistema);
        } else if (strncmp(comando, "CO", 2) == 0) { // Todos os comandos de busca começam com "CO"
            realizaBusca(sistema, comando);
        } else if (strcmp(comando, "OUT") == 0) {
            break; // Sai do laço
        }
    }

    // 3. Libera toda a memória alocada pelo sistema antes de terminar
    liberaSistema(sistema);
    
    return 0;
}