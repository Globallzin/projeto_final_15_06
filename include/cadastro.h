#pragma once

#include "verificadores.h"
#include "data.h"

typedef struct
{
    char cpf[20];
    char nome[50];
    char telefone[15];
    Data dataNascimento;
    char numeroCartao[20];
    char chavePix[50];
} Cliente;

void inicializarClientes(void);
void cadastrarNovoCliente(void);
void visualizarTodosClientes(void);
void mostrarInformacoesCliente(Cliente cliente);
Cliente buscarClientePorCPF(char cpf[]);
void iniciarBuscaCliente(void);