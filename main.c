/*
# Software feito para aula de algoritmos 1 (C11)
### Professor: Francisco Pereira (Tchesko)

## Autores:
### Gustavo de Andrade Malaquias
### Gabriel Willyan Buk Moreira
*/

#include <stdio.h>
#include <stdlib.h>
#include "cadastro.h"
#include "utilidades.h"
#include "vendas.h"

void mostrarOpcoes()
{
    printf(
        "\n\033[36m Selecione uma opcao: \033[0m\n\n\
        \033[32m(1)\033[0m VISUALIZAR TODOS CLIENTES\n\
        \033[32m(2)\033[0m CADASTRAR NOVO CLIENTE\n\
        \033[32m(3)\033[0m REALIZAR VENDA\n\
        \033[32m(4)\033[0m VISUALIZAR TODAS VENDAS\n\
        \033[32m(5)\033[0m BUSCAR CLIENTE\n\
        \033[32m(6)\033[0m PAGAR PARCELA\n\
        \033[32m(7)\033[0m VISUALIZAR PARCELAS VENCIDAS\n\
        \033[32m(8)\033[0m VISUALIZAR CLIENTES COM DEBITOS PENDENTES\n\
        \033[32m(9)\033[0m VISUALIZAR FATORAMENTO TOTAL\n\
        \033[32m(0)\033[0m SAIR\n\
        ");
}

int main()
{
    inicializarClientes();
    inicializarVendas();
    limparConsole();

    while (1)
    {
        int escolha;
        mostrarOpcoes();

        if (scanf(" %d", &escolha) != 1)
        {
            limparConsole();
            printf("Opcao invalida!\n");
            return 0;
        }

        // esse bloco de ifs poderiam ser substituidos por um array de funções mas iria ser necessário o uso de ponteiros.
        // * ponteiros nao foram permitidos nesse software.
        if (escolha == 1)
            visualizarTodosClientes();
        else if (escolha == 2)
            cadastrarNovoCliente();
        else if (escolha == 3)
            registrarVenda();
        else if (escolha == 4)
            mostrarTodasParcelas();
        else if (escolha == 5)
            iniciarBuscaCliente();
        else if (escolha == 6)
            pagarParcela();
        else if (escolha == 7)
            visualizarParcelasVencidas();
        else if (escolha == 8)
            visualizarClientesComDebitosPendentes();
        else if (escolha == 9)
            visualizarFaturamentoTotal();
        else if (escolha == 0)
            break;
        else
        {
            limparConsole();
            printf("Opcao invalida!\n");
        }
        // limparConsole(); deve ser chamado no fim da funcao, nao aqui
    };

    return 0;
}
