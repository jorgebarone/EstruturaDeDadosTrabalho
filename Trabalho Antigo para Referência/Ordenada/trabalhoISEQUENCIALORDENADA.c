#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// CONSTANTES
#ifndef NUM_MAX_ALUNOS
#define NUM_MAX_ALUNOS 100
#endif

typedef struct
{
  int   matricula;  // chave de pesquisa (unica)
  char  nome[30];
  int idade;
}
Aluno;

typedef struct
{
  Aluno aluno[NUM_MAX_ALUNOS];
  int   nAlunos;
}
Turma; // LISTA SEQUENCIAL

//-------------------------------------------------------------
// INSERIR UM NOVO ALUNO
//-------------------------------------------------------------

int inserir(Turma *pTurma, const Aluno *pNovoAluno)
{
  int i;

  // 1. Verificar se existe espaço para inserção de um novo item
  
  if (pTurma->nAlunos == NUM_MAX_ALUNOS)
  {
    return 1;  // ERRO 1: Lista Cheia
  }
  
 
  // 2. Deslocar 1 posicao a direita todos os itens com
  //    chave maior que a chave do item a ser inserido
  
  i = pTurma->nAlunos - 1;
  while (i >= 0 && pTurma->aluno[i].matricula > pNovoAluno->matricula)
  {
    pTurma->aluno[i+1] = pTurma->aluno[i];
    i--;
  }
  
  // 3. Armazenar o novo item na posicao i+1
  
  pTurma->aluno[i+1] = *pNovoAluno;
  
  // 4. Incrementar a quantidade de itens

  pTurma->nAlunos++;
  
  // 5. Retornar indicando inclusao bem-sucedida
  
  return 0;

}

//-------------------------------------------------------------
// RECUPERAR DADOS DE UM ALUNO
//-------------------------------------------------------------

Aluno *recuperar(const Turma *pTurma, const int matricula)
{
  int i,m,f;  // inicio, meio, fim
  
  i = 0;
  f = pTurma->nAlunos-1;
  while (i<=f)
  {
    m = (i+f)/2;
    if (pTurma->aluno[m].matricula == matricula)
    {
      return (Aluno *) &(pTurma->aluno[m]);
    }
    if (pTurma->aluno[m].matricula > matricula) f = m-1;
                                           else i = m+1;
  }
  return (Aluno *)NULL;
}

//-------------------------------------------------------------
// REMOVER ALUNO
//-------------------------------------------------------------

int excluir(Turma *pTurma, const int matricula)
{
  int i;
  
  // 1. Localizar o item correspondente à chave fornecida
  
  for (i=0; i<pTurma->nAlunos; i++)
  {
    if (pTurma->aluno[i].matricula == matricula) break;
  }
  if (i==pTurma->nAlunos) return 1; // Aluno nao encontrado

  // 2. Deslocar todos os itens posteriores 1 posição a frente.
  
  while(i < pTurma->nAlunos-1)
  {
    pTurma->aluno[i] = pTurma->aluno[i+1];
    i++;
  }

  // 3. Decrementar a quantidade de alunos

  pTurma->nAlunos--;


  // 4. Retornar indicando exclusao bem sucedida
  
  return 0;
  
}


//-------------------------------------------------------------
// LISTAR TODOS ALUNOS
//-------------------------------------------------------------

void listar(const Turma *pTurma)
{
  int i;
  
  printf("%4s  %-20s  %4s\n\n","MATR","IDADE","NOME");
  for (i=0; i<pTurma->nAlunos; i++)
  {
    printf("%4d  %-20d  %s\n",
           pTurma->aluno[i].matricula,
           pTurma->aluno[i].idade,
           pTurma->aluno[i].nome);
  }
}

//-------------------------------------------------------------
// PROGRAMA PRINCIPAL
//-------------------------------------------------------------


int main()
{
  FILE *fInsert;
  FILE *fBusca;
  FILE *fRemove;
  fInsert = fopen("inseresequenciaord.csv", "a");
  fBusca = fopen("buscasequenciaord.csv", "a");
  fRemove = fopen("removesequenciaord.csv", "a");
  clock_t timeINC, timeBUSC, timeREM;
  Aluno meuAluno;
  Turma minhaTurma;
  int resultado,opcao,m, i,j;
  Aluno *pAluno;

  // Iniciar com a lista vazia
  
  minhaTurma.nAlunos = 0;
  

// INCLUIR ALUNO
	timeINC = clock();
	for (i=1;i<=NUM_MAX_ALUNOS;i++)
	    {
	      scanf("%d",&(meuAluno.matricula));
	      scanf("%d",&(meuAluno.idade));
	      scanf("%s",meuAluno.nome);
	      resultado = inserir(&minhaTurma,&meuAluno);
	    }
	    
	 timeINC = clock() - timeINC;
	 fprintf(fInsert, "%6d,%f\n",
	  NUM_MAX_ALUNOS, (((float)timeINC)/(CLOCKS_PER_SEC/1000)));

// BUSCAR ALUNO VIA MATRICULA
	timeBUSC = clock();
	for (i=1;i<=NUM_MAX_ALUNOS;i++) {
      m = rand()%NUM_MAX_ALUNOS;
      pAluno = recuperar(&minhaTurma,m);
      }
     timeBUSC = clock() - timeBUSC;
	 fprintf(fBusca, "%6d,%f\n",
	  NUM_MAX_ALUNOS, (((float)timeBUSC)/(CLOCKS_PER_SEC/1000)));

// EXCLUIR ALUNO
	timeREM = clock();
	for (i=1;i<=NUM_MAX_ALUNOS;i++) {
      m = rand()%NUM_MAX_ALUNOS;
      resultado = excluir(&minhaTurma,m);
      }
     timeREM = clock() - timeREM;
	 fprintf(fRemove, "%6d,%f\n",
	  NUM_MAX_ALUNOS, (((float)timeREM)/(CLOCKS_PER_SEC/1000)));

fclose(fInsert);
fclose(fBusca);
fclose(fRemove);
}
