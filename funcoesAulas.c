#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "funcoesAuxiliares.h"
#include "funcoesUCS.h"
#include "constantes.h"
#include "menus.h"
#include "Estruturas.h"
#include "funcoesAlunos.h"

void FinalizarTodasAsAulasTipoPL(tipoAula vetorAulas[], int *quantAulas,int quantUCs,tipoUC vetorUCS[],int *quantAulasPL,int *quantAulasAgendadas,int *quantAulasRealizadas)
{
    int codigoUC,i;
    float mediaAulasPLporUC;

    if (quantUCs == 0)
    {
        printf("\n\nERRO: não existem ucs\n\n");
    }
    else
    {
        if(*quantAulas == 0)
        {

            printf("\n\nERRO: não existem aulas\n\n");
        }
        else
        {
            mediaAulasPLporUC = (float)*quantAulasPL/quantUCs;


            for(i=0; i<*quantAulas; i++)
            {
                if(strcmp(vetorAulas[i].tipoAula,"PL")==0)
                {
                    strcpy(vetorAulas[i].estadoAula,"Finalizada");
                        (*quantAulasAgendadas)--;
                        (*quantAulasRealizadas)++;
                }
                printf("\n%d.Codigo UC: %d\n",i+1,vetorAulas[i].codigoUC);
                printf("\nQuantidade média de aulas PL por UC: %f",mediaAulasPLporUC);

            }
        }
    }
}

void MostrarAulasGravadasdeUCsolicitada(tipoAula vetorAulas[], int *quantAulas,int quantUCs,tipoUC vetorUCS[])
{
    int controlo,pos=-1,codigoUC,i;

    if (quantUCs == 0)
    {
        printf("\n\nERRO: não existem ucs\n\n");
    }
    else
    {
        do
        {
            codigoUC = lerInteiroSlim("\nIntroduza o código da UC que deseja alterar: ");
            pos = procuraUC(vetorUCS, quantUCs, codigoUC);

            if(pos != -1)
            {
                if(*quantAulas == 0)
                {
                    printf("\n\nERRO: não existem aulas agendadas\n\n");
                }
                else
                {
                    printf("\nCodigo da UC: %d\n",codigoUC);
                    for(i=0; i<*quantAulas; i++)
                    {
                        if(strcmp(vetorAulas[i].opGravacao,"Sim")==0)
                        {
                            printf("\n%d. %s\n",i+1,vetorAulas[i].designacao);

                            (vetorUCS->numAulasGravadas)++;
                        }
                    }
                    printf("\nAulas gravadas: %d\n",vetorUCS->numAulasGravadas);
                }
            }
            else
            {
                printf("\n\nERRO: não existe nenhuma UC com esse código!");
            }
        }
        while (pos == -1);
    }
}

void leFicheiroBinarioAulas (tipoAula vetorAulas[], int *quantAulas)
{
    FILE *ficheiro;
    int controlo;

    ficheiro = fopen("dadosAulas.bin", "rb");

    if (ficheiro == NULL)
    {
        printf("\n\nERRO: falha na abertura do ficheiro\n\n");
    }
    else
    {
        controlo = fread(quantAulas, sizeof(int), 1, ficheiro);
        if (controlo != 1)
        {
            printf("\n\nERRO: falha na leitura dos dados\n\n");
        }
        else
        {
            controlo = fread(vetorAulas, sizeof(tipoAula), *quantAulas, ficheiro);
            if (controlo != *quantAulas)
            {
                printf("\n\nERRO: falha na leitura dos dados dos alunos\n\n");
                *quantAulas = 0;
            }
            else
            {
                printf("\n\nLeitura dos dados realizada com sucesso\n\n");
            }
        }
        fclose(ficheiro);
    }
}

void gravaFicheiroBinarioAulas (tipoAula vetorAulas[], int quantAulas)
{
    FILE *ficheiro;
    int controlo;

    ficheiro = fopen("dadosAulas.bin", "wb");

    if (ficheiro == NULL)
    {
        printf("\nERRO: falha na abertura/criacao do ficheiro\n\n");
    }
    else
    {
        controlo = fwrite(&quantAulas, sizeof(int), 1, ficheiro);
        if (controlo != 1)
        {
            printf("\nERRO: falha na escrita dos dados\n\n");
        }
        else
        {
            controlo = fwrite(vetorAulas, sizeof(tipoAula), quantAulas, ficheiro);
            if (controlo != quantAulas)
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

void MostrarAulaSolicitada(tipoAula vetorAulas[], int *quantAulas,int quantUCs)
{
    int controlo;
    char designacaoAula[MAXSTRING];

    if (quantUCs == 0)
    {
        printf("\n\nERRO: não existem ucs\n\n");
    }
    else
    {
        if(*quantAulas == 0)
        {
            printf("\n\nERRO: não existem aulas agendadas\n\n");
        }
        else
        {
            lerString("\nDesignação da aula a mostrar: ",designacaoAula, MAXSTRING);
            controlo  = procuraAula(vetorAulas, *quantAulas,designacaoAula);

            do
            {
                if (controlo != -1)
                {
                    escreverDadosAula (vetorAulas[controlo]);
                }
                else
                {
                    printf("\n\nERRO: não existe nenhuma aula com essa designação!\n\n");
                    break;
                }
            }
            while (controlo == -1);
        }
    }
}

void FinalizarAula(tipoAula vetorAulas[], int *quantAulas,int quantUCs,int *quantAulasAgendadas,int *quantAulasRealizadas)
{
    int controlo;
    char designacaoAula[MAXSTRING];

    if (quantUCs == 0)
    {
        printf("\n\nERRO: não existem ucs \n\n");
    }
    else
    {
        if(*quantAulas == 0)
        {
            printf("\n\nERRO: não existem aulas agendadas\n\n");
        }
        else
        {
            lerString("\nDesignação da aula a finalizar: ",designacaoAula, MAXSTRING);
            controlo  = procuraAula(vetorAulas, *quantAulas,designacaoAula);

            do
            {
                if(strcmp(vetorAulas[controlo].estadoAula,"Agendada")==0)
                {
                    printf("\nERRO: Aula por iniciar\n");
                }
                else
                {
                    if (controlo != -1)
                    {
                        strcpy(vetorAulas[controlo].estadoAula,"Finalizada");
                        printf("\nAula finalizada com sucesso\n");

                        (*quantAulasAgendadas)--;
                        (*quantAulasRealizadas)++;

                    }
                    else
                    {
                        printf("\n\nERRO: não existe nenhuma aula com essa designação!");
                    }
                }
            }
            while (controlo == -1);
        }
    }
}

void IniciarAula(tipoAula vetorAulas[], int *quantAulas,int quantUCs)
{
    int controlo;
    char designacaoAula[MAXSTRING];

    if (quantUCs == 0)
    {
        printf("\n\nERRO: não existem ucs \n\n");
    }
    else
    {
        if(quantAulas == 0)
        {
            printf("\n\nERRO: não existem aulas agendadas\n\n");
        }
        else
        {
            lerString("\nDesignação da aula a iniciar: ",designacaoAula, MAXSTRING);
            controlo  = procuraAula(vetorAulas, *quantAulas,designacaoAula);
            do
            {
                if(strcmp(vetorAulas[controlo].estadoAula,"Finalizada")==0)
                {
                    printf("\nERRO: Aula já foi finalizada\n");
                }
                else
                {
                    if (controlo != -1)
                    {
                        strcpy(vetorAulas[controlo].estadoAula,"Decorrer");
                        printf("\nAula iniciada com sucesso\n");
                    }
                    else
                    {
                        printf("\n\nERRO: não existe nenhuma aula com essa designação!");
                    }
                }
            }
            while (controlo == -1);
        }
    }
}

void AlterarAgendamento(tipoAula vetorAulas[], int *quantAulas,int quantUCs)
{
    int controlo;
    char designacaoAula[MAXSTRING],op;

    if (quantUCs == 0)
    {
        printf("\n\nERRO: não existem ucs \n\n");
    }
    else
    {
        if(quantAulas == 0)
        {
            printf("\n\nERRO: não existem aulas agendadas\n\n");
        }
        else
        {
            do
            {
                lerString("\nDesignação da aula a iniciar: ",designacaoAula, MAXSTRING);
                controlo  = procuraAula(vetorAulas,*quantAulas,designacaoAula);

                if (controlo != -1)
                {
                    op = menuAlterarAgendamentoAulas();

                    switch(op)
                    {
                    case 'A':
                        vetorAulas[*quantAulas].Data = lerData("\nInsira a data: ");
                        break;
                    case 'B':
                        vetorAulas[*quantAulas].HoraInicio = lerHora("\nInsira as horas de inicio: ");
                        break;
                    case 'C':
                        vetorAulas[*quantAulas].Data = lerData("\nInsira a data: ");
                        vetorAulas[*quantAulas].HoraInicio = lerHora("\nInsira as horas de inicio: ");

                        break;
                    case 'S':
                        break;
                    default:
                        printf("\nERRO: Opção invalida!\n");
                        break;
                    }
                }
                else
                {
                    printf("\n\nERRO: não existe nenhuma aula com essa designação");
                }
            }
            while (controlo == -1 && op != 'S');
        }
    }
}

int procuraAula (tipoAula vetorAulas[], int quantAulas, char designacaoAula[])
{
    int i, posicao=-1;

    for (i=0; i < quantAulas; i++)
    {
        if (strcmp (vetorAulas[i].designacao,designacaoAula) == 0)
        {
            posicao = i;
            i = quantAulas;
        }
    }
    return posicao;
}

tipoAula* eliminarAula (tipoAula vetorAulas[], int *quantAulas, tipoUC vetorUCS[])
{
    int controlo,i;
    char designacaoAula[MAXSTRING];
    tipoAula *pAux=NULL;

    if (quantAulas == 0)
    {
        printf("\nERRO: não existem aulas agendadas\n\n");
    }
    else
    {
        lerString("\nDesignação da aula a eliminar: ",designacaoAula, MAXSTRING);
        controlo  = procuraAula(vetorAulas, *quantAulas,designacaoAula);

        if (controlo  == -1)
        {
            printf("\n\nERRO: a aula indicada ja foi eliminada ou nao existe nenhuma aula com essa designacao\n\n");
        }
        else
        {
            vetorUCS[controlo].totalAulas--;

            for (i=controlo ; i < *quantAulas-1; i++)
            {
                vetorAulas[i] = vetorAulas[i+1];
            }
            (*quantAulas)--;
            pAux = realloc(vetorAulas, (*quantAulas) * sizeof(tipoAula));
            if (pAux == NULL && *quantAulas>0)
            {
                printf("\nERRO: falha na alocação de memória, mas a eliminação foi realizada\n");
            }
            else
            {
                vetorAulas = pAux;
                printf("\n\nEliminação da aula efectuada com sucesso\n\n");
            }
        }
    }
    return vetorAulas;
}

void listarAulas (tipoAula *vetorAulas, int quantUCs,int quantAulas)
{
    int i;

    if (quantUCs == 0)
    {
        printf("\nERRO: Não existem ucs!\n");
    }
    else
    {
        if(quantAulas == 0)
        {
            printf("\nERRO: Não existem aulas agendadas!\n");
        }
        else
        {
            for(i=0; i<quantAulas; i++)
            {
                printf("\n%d.",i+1);
                escreverDadosAula (vetorAulas[i]);
            }
        }
    }
}

void escreverDadosAula (tipoAula aula)
{

    printf("\nCódigo UC:%d", aula.codigoUC);

    printf("\nDesignação:%s\tNome do Docente:%s\n",aula.designacao,aula.nomeDocente);

    printf("\nTipo Aula:%s\tData:",aula.tipoAula);
    escreverData(aula.Data);

    printf("\t\tHora Inicio:");
    escreverHora(aula.HoraInicio);

    printf("\tHora Fim:");
    escreverHora(aula.HoraFim);

    printf("\tEstado Atual:%s\tGravado:%s",aula.estadoAula,aula.opGravacao);

    printf("\tQuantidade de Alunos Presentes:%d\n",aula.quantAlunosPresentes);

    printf("\tQuantidade de acessos a gravacao: %d\n",aula.quantAcessosGravacao);

}

tipoAula* AgendarAula(int *quantAulasPL,tipoAula *vetorAulas,int *quantAulas,tipoUC vetorUCS[],int quantUCs,int *quantAulasAgendadas,int *aulasGravadas,float *percentagemAulasGravadas)
{
    int codigoUC,controlo,mintotal;
    int opTipoAula,opOpGravacao;
    int falha;

    tipoAula *pAux = NULL;

    if(quantUCs == 0)
    {
        printf("\n\nERRO: não existem UCs criadas\n\n");
    }
    else
    {
        printf("\n------- Nova Aula--------\n");
        codigoUC = lerInteiroSlim("Insira o código da uc que deseja adicionar a aula: ");

        controlo = procuraUC(vetorUCS,quantUCs,codigoUC);

        if (controlo == -1)
        {
            printf("\n\nERRO: Não existe nenhuma uc com esse código!\n\n");
        }
        else
        {
            pAux = realloc(vetorAulas, (*quantAulas+1) * sizeof(tipoAula));
            if(pAux == NULL)
            {
                printf("\n\nERRO: falha na alocação de memória\n\n");
            }
            else
            {
                vetorAulas = pAux;

                if (*quantAulas == 0)
                {
                    vetorAulas[0].posicao = 1;
                }
                else
                {
                    vetorAulas[*quantAulas].posicao = vetorAulas[*quantAulas-1].posicao+1;
                }
                vetorAulas[*quantAulas].codigoUC = vetorUCS[controlo].codigo ;

                lerString("\nDesignação da aula: ", vetorAulas[*quantAulas].designacao, MAXSTRING);


                do
                {
                    opTipoAula = lerInteiro("\nTipo de Aula:\n1-T\t2-TP\t3-PL\nInsira: ",1,3);

                    switch(opTipoAula)
                    {
                    case TIPO_T:
                        strcpy(vetorAulas[*quantAulas].tipoAula,"T");
                        (vetorUCS->quantAulasT)--;
                        if((vetorUCS->quantAulasT)<0)
                        {
                            printf("\nERRO: limite atingido numero de aulas agendadas deste tipo\n");
                            falha = -1;
                        }
                        else
                        {
                            printf("\nNOTA: %d aulas do tipo T por agendar\n",vetorUCS->quantAulasT);
                            falha = 1;
                        }
                        break;

                    case TIPO_TP:
                        strcpy(vetorAulas[*quantAulas].tipoAula,"TP");
                        (vetorUCS->quantAulasTP)--;
                        if((vetorUCS->quantAulasTP)<0)
                        {
                            printf("\nERRO: limite atingido numero de aulas agendadas deste tipo\n");
                            falha = -1;
                        }
                        else
                        {
                            printf("\nNOTA: %d aulas do tipo TP por agendar\n",vetorUCS->quantAulasTP);
                            falha = 1;
                        }
                        break;

                    case TIPO_PL:
                        strcpy(vetorAulas[*quantAulas].tipoAula,"PL");
                        (vetorUCS->quantAulasPL)--;
                        (*quantAulasPL)++;
                        if((vetorUCS->quantAulasPL)<0)
                        {
                            printf("\nERRO: limite atingido numero de aulas agendadas deste tipo\n");
                            falha = -1;
                        }
                        else
                        {
                            printf("\nNOTA:: %d aulas do tipo PL por agendar\n",vetorUCS->quantAulasPL);
                            falha = 1;
                        }
                        vetorUCS->totalAulas = vetorUCS->quantAulasPL + vetorUCS->quantAulasTP + vetorUCS->quantAulasT;
                        break;
                    }
                }
                while(falha == -1);

                lerString("\nNome do Docente: ", vetorAulas[*quantAulas].nomeDocente, MAXSTRING);

                vetorAulas[*quantAulas].Data = lerData("\nInsira a data: ");


                if(strcmp(vetorUCS[controlo].regime,"Diurno")==0)
                {

                    vetorAulas[*quantAulas].HoraInicio = lerHoracLIM("\nInsira as horas previstas de inicio:",MIN_HORA_DIURNO,MAX_HORA_DIURNO);

                }
                else
                {

                    vetorAulas[*quantAulas].HoraInicio = lerHoracLIM("\nInsira as horas previstas de inicio:",MIN_HORA_PL,MAX_HORA_PL);

                }

                vetorAulas[*quantAulas].HoraFim.hour = vetorAulas[*quantAulas].HoraInicio.hour + vetorUCS->duracaoAula.hour;

                vetorAulas[*quantAulas].HoraFim.minuto = vetorAulas[*quantAulas].HoraInicio.minuto + vetorUCS->duracaoAula.minuto;

                mintotal = vetorAulas[*quantAulas].HoraFim.hour * 60 + vetorAulas[*quantAulas].HoraFim.minuto;

                vetorAulas[*quantAulas].HoraFim.hour = mintotal/60;

                vetorAulas[*quantAulas].HoraFim.minuto = mintotal%60;

                strcpy(vetorAulas[*quantAulas].estadoAula,"Agendada");

                opOpGravacao = lerInteiro("\nDeseja gravar:\n0-Sim\t1-Não\nInsira: ",OP_GRAVACAO_SIM,OP_GRAVACAO_NAO);

                switch(opOpGravacao)
                {
                case OP_GRAVACAO_SIM:
                    strcpy(vetorAulas[*quantAulas].opGravacao,"Sim");
                    (*aulasGravadas)++;
                    break;

                case OP_GRAVACAO_NAO:
                    strcpy(vetorAulas[*quantAulas].opGravacao,"Não");
                    break;
                }

                vetorAulas[*quantAulas].quantAcessosGravacao = 0;

                vetorAulas[*quantAulas].quantAlunosPresentes = 0;

                (*quantAulas)++;
                (*quantAulasAgendadas)++;

                (*percentagemAulasGravadas) = (float)(*aulasGravadas)/(*quantAulas)*100;
            }
        }
    }
    return vetorAulas;
}

