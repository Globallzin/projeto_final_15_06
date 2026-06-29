#include <stdio.h>
#include <stdlib.h>
#include "utilidades.h"
#include "cadastro.h"
#include "data.h"

void printarDataFormatada(Data dataNascimento)
{
    printf("%02d/%02d/%04d", dataNascimento.dia, dataNascimento.mes, dataNascimento.ano);
}

void limparConsole(void)
{
    system("cls");
}

int procurarCaractere(char str[], char caractere, int comecandoEm)
{
    for (int i = comecandoEm; str[i] != '\0'; i++)
    {
        if (str[i] == caractere)
            return i;
    }

    return -1;
}

int clamp(int n, int min, int max)
{
    if (n < min)
        return min;
    if (n > max)
        return max;

    return n;
}
