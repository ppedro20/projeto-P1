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

void UCSEXTRA (tipoUC vetorUCS[MAXUCS], int quantUCs,tipoUC vetorUCS2)
{
    int i;

    tipoUC *pAux = NULL;

    pAux = realloc(vetorUCS2, (*quanUCs+1) * sizeof(tipoUC));


    if(pAux == NULL)
    {
        printf("\n\nERRO: falha na alocação de memória\n\n");
    }
    else
    {
        vetorUCS2 = pAux;

        if (*quantUCs == 0)
        {
            vetorUCS2[0].codigo = 1;
        }
        else
        {
            vetorUCS2[*quantUCs].codigo = vetorUCS2[*quantUCs-1].codigo+1;

            for(i=0; i < quantUCs; i++)
            {
                if((vetorUCS[i].quantAulasPL != 0)&&(vetorUCS[i].duracaoAula <= 120))
                {

                    vetorUCS2[i] = vetorUCS[i];
                }
            }
        }
    }
}

void listarUCSDiurnas (tipoUC vetorUCS[MAXUCS], int quantUCs,int *UCSdiurno)
{
    int i;
    float pUCSdiurno;

    if (quantUCs == 0)
    {
        printf("\nERRO: Não existem UCs!\n");
    }
    else
    {

        pUCSdiurno = (float)(*UCSdiurno)/quantUCs;

        printf("\nLISTA DE UCS COM REGIME DIURNO:\n");

        printf("\nPercentagem de UCs de regime diurno: %f %%\n",pUCSdiurno);

        for(i=0; i < quantUCs; i++)
        {
            if(strcmp(vetorUCS[i].regime,"Diurno")==0)

                printf("\nCódigo: %d\t\tSemestre: %d\n",vetorUCS[i].codigo,vetorUCS[i].semestre);

        }
    }
}

void DadosEstatisticos (float *mediaPresencas,float *percentagemAulasGravadas)
{

    printf("------------------------------------------------------------------------------------------------------------------------");
    printf("\n\t\t\t\t\t\tDADOS ESTATISTICOS\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    printf("\nQuantidade média de presenças nas aulas: %.2f\n",mediaPresencas);

    printf("\nPercentagem de UCs com aulas gravadas: %.2f\n",percentagemAulasGravadas);

    printf("\nUCs com menor quantidade de aulas: \n");

    printf("\nTipos de aula com maior quantidade de acessos: \n");

    printf("\nAulas realizadas à mais tempo: \n");

}

void RankingUCS(tipoUC vetorUCS[], int quantUCs)
{
    int i, j, troca;
    tipoUC aux;

    troca=1;

    for(i=0; i<quantUCs-1 && troca!=0; i++)
    {
        troca=0;

        for (j= 0; j < quantUCs-i-1; j++)
        {
            if(vetorUCS[j+1].quantAcessos > vetorUCS[j].quantAcessos)
            {
                troca=1;
                aux=vetorUCS[j];
                vetorUCS[j]=vetorUCS[j+1];
                vetorUCS[j+1]=aux;
            }
        }
    }
    listarRankingUCS(vetorUCS,quantUCs);
}

void leFicheiroBinarioUCS (tipoUC vetorUCS[], int *quantUCs)
{
    FILE *ficheiro;
    int controlo;

    ficheiro = fopen("dadosUCS.bin", "rb");

    if (ficheiro == NULL)
    {
        printf("\n\nERRO: falha na abertura do ficheiro\n\n");
    }
    else
    {
        controlo = fread(quantUCs, sizeof(int), 1, ficheiro);
        if (controlo != 1)
        {
            printf("\n\nERRO: falha na leitura dos dados\n\n");
        }
        else
        {
            controlo = fread(vetorUCS, sizeof(tipoUC), *quantUCs, ficheiro);
            if (controlo != *quantUCs)
            {
                printf("\n\nERRO: falha na leitura dos dados dos alunos\n\n");
                *quantUCs = 0;
            }
            else
            {
                printf("\n\nLeitura dos dados realizada com sucesso\n\n");
            }
        }
        fclose(ficheiro);
    }
}

void gravaFicheiroBinarioUCS (tipoUC vetorUCS[], int quantUCs)
{
    FILE *ficheiro;
    int controlo;

    ficheiro = fopen("dadosUCS.bin", "wb");

    if (ficheiro == NULL)
    {
        printf("\nERRO: falha na abertura/criacao do ficheiro\n\n");
    }
    else
    {
        controlo = fwrite(&quantUCs, sizeof(int), 1, ficheiro);
        if (controlo != 1)
        {
            printf("\nERRO: falha na escrita dos dados\n\n");
        }
        else
        {
            controlo = fwrite(vetorUCS, sizeof(tipoUC), quantUCs, ficheiro);
            if (controlo != quantUCs)
            {
                printf("\nERRO: falha na escrita dos dados\n\n");
            }
            else
            {
                printf("\n\nGravacao de dados efetuada com sucesso\n\n");
            }
        }
        fclose(ficheiro);
    }
}

int lerQuantidadeUCs(void)
{
    int quantUCs;

    quantUCs = lerInteiro("\nIndique o numero de ucs: ",0, MAXUCS);

    return quantUCs;
}

tipoUC LerDadosUC(int *UCSdiurno)
{
    int opTipoUC,opRegime;

    tipoUC uc;

    int AulasTotal;

    printf("\n------- Nova UC--------\n");
    uc.totalAulas = 0;
    uc.codigo = lerInteiroSlim("Código da UC: ");
    lerString("\nNome da UC: ", uc.nomeUC, MAXSTRING);
    uc.semestre = lerInteiro("\nSemestre: ",MIN_SEMESTRE,MAX_SEMESTRE);

    opTipoUC = lerInteiro("\nTipo UC:\n0 - Obrigatória\n1 - Opcional\nInsira:",0,1);

    switch(opTipoUC)
    {
    case TIPO_OBRIGATORIA:
        strcpy(uc.tipoUC,"obrigatória");
        break;

    case TIPO_OPCIONAL:
        strcpy(uc.tipoUC,"opcional");
        break;
    }
    opRegime = lerInteiro("\nRegime:\n0 - Diurno\n1 - Pós-Laboral\nInsira:",0,1);

    switch(opRegime)
    {
    case REGIME_DIURNO:
        strcpy(uc.regime,"Diurno");
        (*UCSdiurno)++;
        break;

    case REGIME_POS_LABORAL:
        strcpy(uc.regime,"Pós-Laboral");
        break;
    }
    uc.duracaoAula = lerHora("\nDuração da Aula:");

    do
    {
        uc.quantAulasPL = lerInteiroSlim("\nQuantidade de Aulas PL: ");
        uc.quantAulasT = lerInteiroSlim("\nQuantidade de Aulas T: ");
        uc.quantAulasTP = lerInteiroSlim("\nQuantidade de Aulas TP: ");

        AulasTotal = uc.quantAulasPL + uc.quantAulasT + uc.quantAulasTP;



        if(AulasTotal == 0)
        {
            printf("\nERRO: Numero de aulas igual a 0 !\n");
        }
    }
    while(AulasTotal == 0);

    return uc;
}

int procuraUC (tipoUC vetorUCS[], int quantUCs, int codigoUC)
{
    int i, posicao=-1;

    for (i=0; i < quantUCs; i++)
    {
        if (codigoUC == vetorUCS[i].codigo)
        {
            posicao = i;
            i = quantUCs;
        }
    }

    return posicao;
}

int acrescentaUC(tipoUC vetorUCS[], int quantUCs,int *UCSdiurno)
{
    int posicao;

    if (quantUCs == MAXUCS)
    {
        printf("\n\nERRO: Impossivel inserir nova UC.\n\n");
    }
    else
    {
        vetorUCS[quantUCs] = LerDadosUC(UCSdiurno);
        posicao  = procuraUC(vetorUCS, quantUCs, vetorUCS[quantUCs].codigo);

        if (posicao != -1)
        {
            printf("\n\nERRO: já existe uma UC com esse código\n\n");
        }
        else
        {
            quantUCs++;
        }
    }
    return quantUCs;
}

void editarUC(tipoUC vetorUCS[MAXUCS], int quantUCs)
{
    int codigoUC;
    int opTipoUC,opRegime;
    char op1;
    if (quantUCs == 0)
    {
        printf("\n\nERRO: não existem ucs\n\n");
    }
    else
    {
        int pos = -1;
        do
        {
            codigoUC = lerInteiroSlim("\nIntroduza o código da UC que deseja alterar: ");
            pos = procuraUC(vetorUCS, quantUCs, codigoUC);
            if (pos != -1)
            {
                op1 = menuEditarUC();
                switch (op1)
                {
                case 'A':
                    vetorUCS[pos].codigo = lerInteiroSlim("Código da UC: ");
                    break;
                case 'B':
                    lerString("\nIndique o novo nome: ", vetorUCS[pos].nomeUC, MAXSTRING);
                    break;
                case 'C':
                    opTipoUC = lerInteiro("\nTipo UC:\n0 - Obrigatória\n1 - Opcional\nInsira:",0,1);

                    switch(opTipoUC)
                    {
                    case TIPO_OBRIGATORIA:
                        strcpy(vetorUCS[pos].tipoUC,"obrigatória");
                        break;

                    case TIPO_OPCIONAL:
                        strcpy(vetorUCS[pos].tipoUC,"opcional");
                        break;
                    }
                    break;

                case 'D':
                    vetorUCS[pos].semestre = lerInteiro("\nSemestre: ",MIN_SEMESTRE,MAX_SEMESTRE);
                    break;
                case 'E':
                    opRegime = lerInteiro("\nRegime:\n0 - Diurno\n1 - Pós-Laboral\nInsira:",0,1);

                    switch(opRegime)
                    {
                    case REGIME_DIURNO:
                        strcpy(vetorUCS[pos].regime,"Diurno");
                        break;

                    case REGIME_POS_LABORAL:
                        strcpy(vetorUCS[pos].regime,"Pós-Laboral");
                        break;
                    }
                    break;
                case 'F':
                    vetorUCS[pos].quantAulasT = lerInteiroSlim("\nQuantidade de Aulas T: ");
                    break;
                case 'G':
                    vetorUCS[pos].quantAulasTP = lerInteiroSlim("\nQuantidade de Aulas TP: ");
                    break;
                case 'H':
                    vetorUCS[pos].quantAulasPL = lerInteiroSlim("\nQuantidade de Aulas PL: ");
                    break;
                case 'I':
                    vetorUCS[pos].duracaoAula = lerHora("\nDuracao da Aula (minutos):");
                    break;
                default:
                    printf("ERRO: Opção invalida!");
                    break;
                }
            }
            else
            {
                printf("\n\nERRO: não existe nenhuma UC com esse código!");
            }
        }
        while (pos == -1 && op1 != 'S');
    }

}

void listarRankingUCS (tipoUC vetorUCS[MAXUCS], int quantUCs)
{
    int i;

    if (quantUCs == 0)
    {
        printf("\nERRO: Não existem UCs!\n");
    }
    else
    {
        printf("\n------------RANKING------------\n");
        printf("\nPosicao\tCodigo\tDesignacao\tQuantidade de Acessos\n");
        for(i=0; i < quantUCs; i++)
        {
            printf("\n%d\t%d\t%s\t%d\n",i+1,vetorUCS[i].codigo,vetorUCS[i].nomeUC,vetorUCS[i].quantAcessos);
        }
    }
}

void listarUCS (tipoUC vetorUCS[MAXUCS], int quantUCs)
{
    int i;

    if (quantUCs == 0)
    {
        printf("\nERRO: Não existem UCs!\n");
    }
    else
    {
        printf("LISTA DE UCS:\n");
        for(i=0; i < quantUCs; i++)
        {
            printf("\nCódigo: %d\tDesignação: %s\t\tTipo de UC: %s\t\tSemestre: %d\t\tRegime: %s",vetorUCS[i].codigo,vetorUCS[i].nomeUC,vetorUCS[i].tipoUC,
                   vetorUCS[i].semestre,vetorUCS[i].regime);
            printf("\tQuantidade de aulas:(T: %d\tTP: %d\tPL: %d)\n",vetorUCS[i].quantAulasT,vetorUCS[i].quantAulasTP,vetorUCS[i].quantAulasPL);
        }
    }
}
