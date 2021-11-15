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

void guardarDadosALUNOSLogBinario (tipoAluno Aluno, int operacao)
{
    FILE *ficheiro;

    ficheiro = fopen("LogDadosReservasBINARIO.txt", "ab");

    if  (ficheiro == NULL)
    {
        printf("\n\nERRO: falha na abertura do ficheiro\n\n");
    }
    else
    {
        if (operacao == OPERACAO_Adicionar)
        {
            fprintf(ficheiro, "\n-- Aluno Adicionado --");
        }

        fprintf(ficheiro, "\nNumero Aluno: %d\n", Aluno.numEstudante);

        fclose(ficheiro);
    }
}

void guardarDadosALUNOSLogTexto (tipoAluno Aluno, int operacao)
{
    FILE *ficheiro;

    ficheiro = fopen("LogDadosReservasTEXTO.txt", "a");

    if  (ficheiro == NULL)
    {
        printf("\n\nERRO: falha na abertura do ficheiro\n\n");
    }
    else
    {
        if (operacao == OPERACAO_Adicionar)
        {
            fprintf(ficheiro, "\n-- Aluno Adicionado --");
        }

        fprintf(ficheiro, "\nNumero Aluno: %d\n", Aluno.numEstudante);

        fclose(ficheiro);
    }
}

void listarAlunosAula(tipoAula vetorAulas[], int *quantAulas,tipoAluno vetorAlunos[],int *quantAlunos)
{
    int controlo, i;
    char designacaoAula[MAXSTRING];

    if (*quantAulas == 0)
    {
        printf("\n\nATENCAO: nao existem aulas \n\n");
    }
    else
    {
        lerString("\nDesignação da aula a mostrar as presenças: ",designacaoAula, MAXSTRING);
        controlo  = procuraAula(vetorAulas,*quantAulas,designacaoAula);

        if (controlo == -1)
        {
            printf("\n\nERRO: Aula nao encontrada\n\n");
        }
        else
        {
            for (i=0; i < *quantAlunos; i++)
            {
                printf("\n%d - %d\n",i+1,vetorAlunos[i].numEstudante);
            }
        }
    }
}

tipoAula *RegistarAcesso(tipoAula vetorAulas[], int *quantAulas,tipoAluno vetorAlunos[],int *quantAlunosPresentes,int *quantAcessosGravacao,int *quantAlunos,tipoUC vetorUCs[],float *mediaPresencas)
{
    int controlo,numEstudante,TipoAcesso,pos,codigoUC;
    char designacaoAula[MAXSTRING];

    tipoAula *pAux=NULL;

    if (quantAulas == 0)
    {
        printf("\nERRO: não existem aulas agendadas\n\n");
    }
    else
    {
        lerString("\nDesignação da aula a marcar presenças: ",designacaoAula, MAXSTRING);
        controlo  = procuraAula(vetorAulas,*quantAulas,designacaoAula);

        if (controlo  == -1)
        {
            printf("\n\nERRO: aula nao encontrada\n\n");
        }
        else
        {
            if((strcmp(vetorAulas[controlo].estadoAula,"Agendada")==0)||(strcmp(vetorAulas[controlo].estadoAula,"Decorrer")==0))
            {
                printf("\nERRO: Aula não finalizada\n");
            }
            else
            {
                numEstudante = lerInteiro("\nInsira o numero do estudante:",MIN_NRALUNO,MAX_NRALUNO);
                pos = procuraAluno(vetorAlunos,*quantAlunos,numEstudante);

                codigoUC = vetorAulas[controlo].codigoUC;

                if(pos == -1)
                {
                    printf("\n\nERRO: Numero de aluno nao identificado\n\n");
                }
                else
                {
                    TipoAcesso = lerInteiro("\nTipo de Acesso:\n1-Online\t2-Offline\t3-Nao Assistiu\nInsira: ",1,3);

                    switch(TipoAcesso)
                    {
                    case 1:
                        strcpy(vetorAulas[*quantAulas].AcessoAluno.tipoAcesso,"Online");
                        (*quantAlunosPresentes)++;
                        (vetorUCs[codigoUC].quantAcessos)++;
                        break;

                    case 2:
                        strcpy(vetorAulas[*quantAulas].AcessoAluno.tipoAcesso,"Offline");
                        (*quantAcessosGravacao)++;
                        (vetorUCs[codigoUC].quantAcessos)++;
                        break;

                    case 3:
                        strcpy(vetorAulas[*quantAulas].AcessoAluno.tipoAcesso,"");
                        break;
                    }
                    guardarDadosALUNOSLogTexto(vetorAlunos[*quantAlunos],OPERACAO_Adicionar);
                    guardarDadosALUNOSLogBinario(vetorAlunos[*quantAlunos],OPERACAO_Adicionar);

                    (*mediaPresencas) = (float)(*quantAlunosPresentes) / (*quantAulas);
                }
            }
        }
    }
    return vetorAulas;
}

void adicionarAluno (tipoAluno vetorAlunos[], int *quantAlunos)
{
    int posicao;

    if (*quantAlunos == MAXALUNOS)
    {
        printf("\n\nATENÇÃO: Limite de vagas no curso atingido\n\n");
    }
    else
    {
        vetorAlunos[*quantAlunos] = DadosAlunos();
        posicao = procuraAluno(vetorAlunos, *quantAlunos, vetorAlunos[*quantAlunos].numEstudante);

        if (posicao != -1)
        {
            printf("\n\nERRO: já existe um aluno com o número indicado\n\n");
        }
        else
        {
            (*quantAlunos)++;
        }
    }
}

int procuraAluno (tipoAluno vetorAlunos[], int quantAlunos, int numEstudante)
{
    int i, posicao=-1;

    for (i=0; i < quantAlunos; i++)
    {
        if (numEstudante == vetorAlunos[i].numEstudante)
        {
            posicao = i;
            i = quantAlunos;
        }
    }

    return posicao;
}

tipoAluno DadosAlunos(void)
{

    tipoAluno aluno;

    printf("\n------- Dados Aluno --------\n");
    aluno.numEstudante = lerInteiro("Número do Aluno: ", MINAlUNOS, MAXALUNOS);

    return aluno;
}

int lerQuantidadeAlunos(void)
{
    int quantAlunos;

    quantAlunos = lerInteiro("\nIndique a quantidade de alunos no curso: ",MINAlUNOS, MAXALUNOS);

    return quantAlunos;
}




