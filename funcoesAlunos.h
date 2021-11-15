#ifndef FUNCOESALUNOS_H_INCLUDED
#define FUNCOESALUNOS_H_INCLUDED

#include "funcoesAuxiliares.h"
#include "funcoesUCS.h"
#include "constantes.h"
#include "menus.h"
#include "funcoesAulas.h"
#include "Estruturas.h"

void guardarDadosALUNOSLogBinario (tipoAluno Aluno, int operacao);

void guardarDadosALUNOSLogTexto (tipoAluno Aluno, int operacao);

void listarAlunosAula(tipoAula vetorAulas[], int *quantAulas,tipoAluno vetorAlunos[],int *quantAlunos);

tipoAula *RegistarAcesso(tipoAula vetorAulas[], int *quantAulas,tipoAluno vetorAlunos[],int *quantAlunosPresentes,int *quantAcessosGravacao,int *quantAlunos,tipoUC vetorUCs[],float *mediaPresencas);

void adicionarAluno (tipoAluno vetorAlunos[],int *quantAlunos);

int procuraAluno (tipoAluno vetorAlunos[], int quantAlunos, int numEstudante);

tipoAluno DadosAlunos(void);

int lerQuantidadeAlunos(void);

#endif // FUNCOESALUNOS_H_INCLUDED
