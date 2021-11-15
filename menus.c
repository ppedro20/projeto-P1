#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "funcoesAuxiliares.h"
#include "funcoesUCS.h"
#include "constantes.h"
#include "menus.h"
#include "funcoesAulas.h"
#include "Estruturas.h"
#include "funcoesAlunos.h"

char menuPRINCIPAL(int quantUCS,int quantAulasAgendadas,int quantAulasRealizadas,int quantAulasGravadas)
{
    char op;
    do
    {
        printf("------------------------------------------------------------------------------------------------------------------------");
        printf("\n\t\t\t\t\t\tMENU PRINCIPAL\n");
        printf("\n\t\t\t\t\t\tQuantidade de UCS: %d\n", quantUCS);
        printf("\nQuantidade de Aulas Agendadas: %d\tQuantidade de Aulas Realizadas: %d\tQuantidade de Aulas Gravadas: %d\n",quantAulasAgendadas,quantAulasRealizadas,quantAulasGravadas);
        printf("\n------------------------------------------------------------------------------------------------------------------------");
        printf("\n\tA - UCS");
        printf("\n\tB - Aulas");
        printf("\n\tC - Alunos");
        printf("\n\tD - Ranking das UCs");
        printf("\n\tE - Dados estatisticos");
        printf("\n\tF - Ficheiros");
        printf("\n\n\tS - Sair");
        printf("\n\t\tOpção:");

        scanf(" %c", &op);
        limpaBufferStdin();

        op = toupper (op);

        if (strchr("ABCDEFS", op) == NULL)
        {
            printf("\n\nERRO: opção invalida\n\n");
        }
    }
    while (strchr("ABCDEFGS", op) == NULL);

    return op;
}

char menuListarUCS(void)
{
    char op;
    do
    {
        printf("\n-------------------------------");
        printf("\n\tMenu Listar");
        printf("\n-------------------------------");
        printf("\n\tA - Listar todas as UCS");
        printf("\n\tB - Listar so as ucs de regime diurno");

        printf("\n\n\tS - Sair");
        printf("\n\t\tOpcao:");

        scanf(" %c", &op);
        limpaBufferStdin();

        op = toupper (op);

        if (strchr("ABS", op) == NULL)
        {
            printf("\n\nERRO: opcao invalida\n\n");
        }
    }
    while (strchr("ABS", op) == NULL);

    return op;
}

char menuFicheiros(void)
{
    char op;
    do
    {
        printf("\n-------------------------------");
        printf("\n\tMenu Ficheiros");
        printf("\n-------------------------------");
        printf("\n\tA - Guardar dados no ficheiro");
        printf("\n\tB - Ler dados do ficheiro");

        printf("\n\n\tS - Sair");
        printf("\n\t\tOpcao:");

        scanf(" %c", &op);
        limpaBufferStdin();

        op = toupper (op);

        if (strchr("ABS", op) == NULL)
        {
            printf("\n\nERRO: opcao invalida\n\n");
        }
    }
    while (strchr("ABS", op) == NULL);

    return op;
}


char menuAlunos(void)
{
    char op;
    do
    {
        printf("\n-------------------------------");
        printf("\n\tMenu Alunos");
        printf("\n-------------------------------");
        printf("\n\tA - Adicionar Aluno");
        printf("\n\tB - Listar Alunos de uma aula");
        printf("\n\tC - Registar acesso do aluno uma aula");
        printf("\n\tS - Sair");
        printf("\n\t\tOpcao:");

        scanf(" %c", &op);
        limpaBufferStdin();

        op = toupper (op);

        if (strchr("ABCS", op) == NULL)
        {
            printf("\n\nERRO: opcao invalida\n\n");
        }
    }
    while (strchr("ABCS", op) == NULL);

    return op;
}

char menuAulas(void)
{
    char op;
    do
    {
        printf("\n-------------------------------");
        printf("\n\tMenu Aulas");
        printf("\n-------------------------------");
        printf("\n\tA - Agendar Aula");
        printf("\n\tB - Listar todas as Aulas");
        printf("\n\tC - Listar uma aula");
        printf("\n\tD - Alterar Aula agendada");
        printf("\n\tE - Iniciar Aula agendada");
        printf("\n\tF - Finalizar Aula agendada");
        printf("\n\tG - Mostrar aulas gravadas de uma uc");
        printf("\n\tH - Finalizar todas as Aulas do tipo PL");
        printf("\n\tS - Sair");
        printf("\n\t\tOpção:");

        scanf(" %c", &op);
        limpaBufferStdin();

        op = toupper (op);

        if (strchr("ABCDEFGHS", op) == NULL)
        {
            printf("\n\nERRO: Opção invalida\n\n");
        }
    }
    while (strchr("ABCDEFGHS", op) == NULL);

    return op;
}
char menuAlterarAula(void)
{
    char op;
    do
    {
        printf("\n-------------------------------");
        printf("\n\tAlterar Aula agendada");
        printf("\n-------------------------------");
        printf("\n\tA - Eliminar");
        printf("\n\tB - Alterar Agendamento");
        printf("\n\tS - Sair");
        printf("\n\t\tOpção:");

        scanf(" %c", &op);
        limpaBufferStdin();

        op = toupper (op);

        if (strchr("ABS", op) == NULL)
        {
            printf("\n\nERRO: Opção invalida\n\n");
        }
    }
    while (strchr("ABS", op) == NULL);

    return op;
}

char menuUCS(void)
{
    char op;
    do
    {
        printf("\n-------------------------------");
        printf("\n\tMenu UCS");
        printf("\n-------------------------------");
        printf("\n\tA - Inserir UC");
        printf("\n\tB - Editar UC");
        printf("\n\tC - Listar UCS");
        printf("\n\tS - Sair");
        printf("\n\t\tOpção:");

        scanf(" %c", &op);
        limpaBufferStdin();

        op = toupper (op);

        if (strchr("ABCS", op) == NULL)
        {
            printf("\n\nERRO: Opção invalida\n\n");
        }
    }
    while (strchr("ABCS", op) == NULL);

    return op;
}

char menuEditarUC(void)
{
    char op;

    do
    {
        printf("\n-------------------------------");
        printf("\nO que deseja editar?");
        printf("\n-------------------------------");
        printf("\n\tA - Código");
        printf("\n\tB - Nome");
        printf("\n\tC - Tipo UC");
        printf("\n\tD - Semestre");
        printf("\n\tE - Regime");
        printf("\n\tF - quantidade de Aulas T");
        printf("\n\tG - quantidade de Aulas TP");
        printf("\n\tH - quantidade de Aulas PL");
        printf("\n\tI - Duração Aula");
        printf("\n\tS - Sair");
        printf("\n\t\tOpção:");

        scanf(" %c", &op);
        limpaBufferStdin();

        op = toupper (op);

        if (strchr("ABCDEFGHIS", op) == NULL)
        {
            printf("\n\nERRO: Opção invalida\n\n");
        }
    }
    while (strchr("ABCDEFGHIS", op) == NULL);

    return op;
}

char menuAlterarAgendamentoAulas(void)
{
    char op;

    do
    {
        printf("\n-------------------------------");
        printf("\nO que deseja alterar?");
        printf("\n-------------------------------");
        printf("\n\tA - Data");
        printf("\n\tB - Hora");
        printf("\n\tC - Ambos");
        printf("\n\tS - Sair");
        printf("\n\t\tOpcao:");

        scanf(" %c", &op);
        limpaBufferStdin();

        op = toupper (op);

        if (strchr("ABCS", op) == NULL)
        {
            printf("\n\nERRO: Opção invalida\n\n");
        }
    }
    while (strchr("ABCS", op) == NULL);

    return op;
}
