#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

#include "funcoesAuxiliares.h"
#include "funcoesUCS.h"
#include "constantes.h"
#include "menus.h"
#include "funcoesAulas.h"
#include "Estruturas.h"
#include "funcoesAlunos.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    char op1,op2,op3,op4,op5,op6,op7;

    int quantAulasAgendadas=0,quantAulasRealizadas=0,quantAulasGravadas=0;
    int quantAlunosPresentes=0,quantAcessosGravacao=0;

    tipoUC vetorUCS[MAXUCS];
    tipoAluno vetorAlunos[MAXALUNOS];
    tipoAula *vetorAulas = NULL;

    tipoUC *vetorUCS2 = NULL;

    int quantAulas = 0;
    int quantAlunos = 0;
    int quantUCs = 0;

    float mediaPresencas,percentagemAulasGravadas;
    int aulasGravadas=0,UCSdiurno=0,quantAulasPL=0;

    do
    {
        op1 = menuPRINCIPAL(quantUCs,quantAulasAgendadas,quantAulasRealizadas,quantAulasGravadas);

        switch(op1)
        {
        case 'A':
            do
            {
                op2 = menuUCS();

                switch(op2)
                {
                case 'A':
                    quantUCs = acrescentaUC(vetorUCS,quantUCs,&UCSdiurno);

                    break;
                case 'B':
                    editarUC(vetorUCS,quantUCs);
                    break;
                case 'C':
                    do
                    {
                        op7 = menuListarUCS();
                        switch(op7)
                        {

                        case 'A':
                            listarUCS (vetorUCS,quantUCs);
                            break;
                        case 'B':
                            listarUCSDiurnas (vetorUCS,quantUCs,&UCSdiurno);
                            break;

                            break;
                        case 'S':
                            break;
                        }
                    }
                    while (op2 != 'S');


                    break;
                case 'S':
                    break;
                }
            }
            while (op2 != 'S');
            break;

        case 'B':
            do
            {
                op3 = menuAulas();

                switch(op3)
                {
                case 'A':
                    vetorAulas = AgendarAula(&quantAulasPL,vetorAulas,&quantAulas,vetorUCS,quantUCs,&quantAulasAgendadas,&aulasGravadas,&percentagemAulasGravadas);
                    break;
                case 'B':
                    listarAulas (vetorAulas,quantUCs,quantAulas);
                    break;
                case 'C':
                    MostrarAulaSolicitada(vetorAulas,&quantAulas,quantUCs);
                    break;

                case 'D':
                    do
                    {
                        op4 = menuAlterarAula();

                        switch(op4)
                        {
                        case 'A':
                            eliminarAula (vetorAulas,&quantAulas,vetorUCS);
                            break;

                        case 'B':
                            AlterarAgendamento(vetorAulas,&quantAulas,quantUCs);
                            break;

                        case 'S':
                            break;
                        }
                    }
                    while (op4 != 'S');

                    break;
                case 'E':
                    IniciarAula(vetorAulas,&quantAulas,quantUCs);
                    break;

                case 'F':
                    FinalizarAula(vetorAulas,&quantAulas,quantUCs,&quantAulasAgendadas,&quantAulasRealizadas);
                    break;

                case 'G': MostrarAulasGravadasdeUCsolicitada(vetorAulas,&quantAulas,quantUCs,vetorUCS);
                    break;

                case 'H': FinalizarTodasAsAulasTipoPL(vetorAulas,&quantAulas,quantUCs,vetorUCS,&quantAulasPL,&quantAulasAgendadas,&quantAulasRealizadas);
                    break;
                }
            }
            while (op3 != 'S');
            break;

        case 'C':
            do
            {
                op5 = menuAlunos();

                switch(op5)
                {
                case 'A':
                    adicionarAluno(vetorAlunos,&quantAlunos);
                    break;
                case 'B':
                    listarAlunosAula(vetorAulas,&quantAulas,vetorAlunos,&quantAlunos);
                    break;
                case 'C':
                    RegistarAcesso(vetorAulas,&quantAulas,vetorAlunos,&quantAlunosPresentes,&quantAcessosGravacao,&quantAlunos,vetorUCS,&mediaPresencas);
                    break;
                }
            }
            while (op5 != 'S');
            break;
        case 'D':
            RankingUCS(vetorUCS,quantUCs);
            break;

        case 'E':
            listarAulas (vetorAulas,quantUCs,quantAulas);
            break;

        case 'F':
            op6 = menuFicheiros();

            switch(op6)
            {
            case 'A':
                gravaFicheiroBinarioAulas (vetorAulas,quantAulas);
                gravaFicheiroBinarioUCS (vetorUCS,quantUCs);
                break;

            case 'B':
                leFicheiroBinarioAulas (vetorAulas,&quantAulas);
                leFicheiroBinarioUCS (vetorUCS,&quantUCs);
                break;
            }

        case 'S':
            break;
        }
    }
    while (op1 != 'S');

    return 0;
}

