#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cadastro.h"
#include "verificadores.h"
#include "utilidades.h"
#include "data.h"

Cliente clientes[50];
int clientesCadastrados = 0;

const Cliente cliente0 = {
    .cpf = "53394608863",
    .telefone = "018996115391",
    .nome = "Gustavo Malaquias",
    .numeroCartao = "12345",
    .dataNascimento = {8, 4, 2008},
    .chavePix = "gustavo.malaquias@outlook.com.br"};

const Cliente cliente1 = {
    .cpf = "46164241871",
    .telefone = "043999204645",
    .nome = "Gabriel Buk",
    .numeroCartao = "12345",
    .dataNascimento = {24, 9, 2007},
    .chavePix = "gabrielnitobuk@gmail.com"};

const Cliente cliente2 = {
    .cpf = "52998224725",
    .telefone = "019998887777",
    .nome = "Lucas Ferreira",
    .numeroCartao = "4539578763621486",
    .dataNascimento = {15, 6, 1999},
    .chavePix = "lucas.ferreira@email.com"};

void inicializarClientes()
{
    clientes[0] = cliente0;
    clientes[1] = cliente1;
    clientes[2] = cliente2;

    clientesCadastrados = 3;
}

void mostrarInformacoesCliente(Cliente cliente)
{
    printf("CPF: %s\n", cliente.cpf);
    printf("Nome: %s\n", cliente.nome);
    printf("Telefone: %s\n", cliente.telefone);
    printf("Data de Nascimento: ");
    printarDataFormatada(cliente.dataNascimento);
    printf("\n");
    printf("Numero do cartao: %s\n", cliente.numeroCartao);
    printf("Chave pix: %s\n", cliente.chavePix);
}

Cliente buscarClientePorCPF(char cpf[])
{
    for (int i = 0; i < clientesCadastrados; i++)
    {
        Cliente atual = clientes[i];
        if (strcmp(atual.cpf, cpf) == 0)
            return atual;
    }

    Cliente vazio = {0};
    return vazio;
}

Cliente buscarClientePorNome(char nome[])
{
    for (int i = 0; i < clientesCadastrados; i++)
    {
        Cliente atual = clientes[i];
        if (strcmp(atual.nome, nome) == 0)
            return atual;
    }

    Cliente vazio = {0};
    return vazio;
}

Cliente buscarClientePorTelefone(char telefone[])
{
    for (int i = 0; i < clientesCadastrados; i++)
    {
        Cliente atual = clientes[i];
        if (strcmp(atual.telefone, telefone) == 0)
            return atual;
    }

    Cliente vazio = {0};
    return vazio;
}

void cadastrarNovoCliente()
{
    limparConsole();
    Cliente novoCliente;

    while (1)
    {
        printf("Digite o CPF: ");
        scanf(" %s", novoCliente.cpf);

        int cpfValido = validarCPF(novoCliente.cpf);

        if (cpfValido == 0)
        {
            printf("CPF Invalido, tente novamente.\n");
        }
        else
        {
            break;
        }
    }

    printf("Digite o nome: ");

    getchar();
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    novoCliente.nome[strlen(novoCliente.nome) - 1] = '\0';

    while (1)
    {
        printf("Digite o telefone: ");

        scanf(" %s", novoCliente.telefone);

        int telefoneValido = validarTelefone(novoCliente.telefone);

        if (telefoneValido == 1)
        {
            break;
        }
        else
        {
            printf("Numero invalido, tente novamente.\n");
        }
    }

    while (1)
    {
        printf("Digite a data de nascimento: ");

        scanf("%d/%d/%d", &novoCliente.dataNascimento.dia, &novoCliente.dataNascimento.mes, &novoCliente.dataNascimento.ano);

        int dataValida = validarData(novoCliente.dataNascimento);

        if (dataValida == 1)
        {
            break;
        }
        else
        {
            printf("Data de nascimento invalida, tente novamente.\n");
        }
    }

    while (1)
    {
        printf("Digite seu numero de cartao: ");

        scanf(" %s", novoCliente.numeroCartao);

        int cartaoValido = validarCartao(novoCliente.numeroCartao);

        if (cartaoValido == 1)
        {
            break;
        }
        else
        {
            printf("Numero do cartao invalido, tente novamente.\n");
        }
    }

    while (1)
    {
        printf("Digite a chave pix: ");

        scanf(" %s", novoCliente.chavePix);

        int pixValido = validarChavePix(novoCliente.chavePix);

        if (pixValido == 1)
        {
            break;
        }
        else
        {
            printf("Chave pix invalida, tente novamente.\n");
        }
    }

    clientes[clientesCadastrados] = novoCliente;
    clientesCadastrados++;

    limparConsole();

    printf("Novo cliente cadastrado! Resumo da operacao: \n");
    mostrarInformacoesCliente(novoCliente);
};

void iniciarBuscaCliente()
{
    limparConsole();

    while (1)
    {
        int escolha;
        printf("1 - Busca por CPF \n 2 - Busca por nome \n 3 - Busca por telefone \n\n");
        printf("Selecione uma opcao: ");
        scanf(" %d", &escolha);

        if (escolha == 1)
        {
            while (1)
            {
                char cpf[20];
                printf("Digite o cpf: ");
                scanf(" %s", cpf);

                Cliente clienteEncontrado = buscarClientePorCPF(cpf);

                if (clienteEncontrado.cpf[0] == '\0')
                {
                    printf("Cliente nao encontrado! Tente novamente.\n");
                }
                else
                {
                    limparConsole();
                    mostrarInformacoesCliente(clienteEncontrado);
                    break;
                }
            }

            break;
        }
        else if (escolha == 2)
        {
            while (1)
            {
                char nome[50];
                printf("Digite o nome: ");

                getchar();
                fgets(nome, sizeof(nome), stdin);
                nome[strlen(nome) - 1] = '\0';

                Cliente clienteEncontrado = buscarClientePorNome(nome);

                if (clienteEncontrado.nome[0] == '\0')
                {
                    printf("Cliente nao encontrado! Tente novamente.\n");
                }
                else
                {
                    limparConsole();
                    mostrarInformacoesCliente(clienteEncontrado);
                    break;
                }
            }

            break;
        }
        else if (escolha == 3)
        {
            while (1)
            {
                char telefone[15];
                printf("Digite o telefone: ");
                scanf(" %s", telefone);

                Cliente clienteEncontrado = buscarClientePorTelefone(telefone);

                if (clienteEncontrado.telefone[0] == '\0')
                {
                    printf("Cliente nao encontrado! Tente novamente.\n");
                }
                else
                {
                    limparConsole();
                    mostrarInformacoesCliente(clienteEncontrado);
                    break;
                }
            }

            break;
        }
        else
        {
            printf("Escolha invalida!");
        }
    }
}

void visualizarTodosClientes()
{
    limparConsole();
    for (int i = 0; i < clientesCadastrados; i++)
    {
        printf("\033[36mInformacoes do cliente #%d:\033[0m\n", i + 1);
        mostrarInformacoesCliente(clientes[i]);
        printf("\n\n");
    }
}
