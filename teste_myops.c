#include "tinytest.h"
#include "tinytest_macros.h"

#include "myops.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * Todas as funções de teste devem ter como entrada um ponteiro para void.
 *
 * Um ponteiro para void é a forma como C define um ponteiro para um tipo
 * não determinado. Esse tipo deve ser determinado mais tarde com um "cast".
 *
 * Isto é bastante util na hora de definir um ponteiro para uma função que
 * nao se sabe ainda que tipo de parametro receberá.
 *
 * Outras bibliotecas, como POSIX Threads (pthreads), também usam este
 * artifício.
 *
 * Para o teste de progressao aritmetica, definimos a struct abaixo para
 * passar parâmetros.
 */

struct progressao{
  int r; // razão
  int n; // início
  int tam; // número de elementos
};

 /*
 * No exemplo abaixo, definimos uma função que soma n numeros de uma progressao
 * aritmetica de razão r e primeiro termo n.
 */

 void teste_progressao_aritmetica(void * dados){
   struct progressao *ptr = (struct progressao *) dados; // transforma o ponteiro para void
   int tam = ptr->tam ;
   int i = ptr->n;
   int r = ptr->r;
   int *v = NULL; // vetor para o teste
   int soma = 0; // valor para verificar se a soma está sendo feito corretamente

   /* bom testar se o teste faz sentido, n deve ser positivo */
   tt_int_op(tam, > , 0);

   /**
    * aloca o vetor. Sempre testar por NULL!
    * calloc zera os elementos, malloc não
    */
   v = (int *) calloc(sizeof(int), tam);
   tt_assert(v); // se NULL, vai para end:

   for ( ; i<tam; i++){ // i já foi inicializado
     soma = soma + r * i;
     v[i] = i * r;
   }
  /* agora faz o teste */
  tt_int_op(soma_todos(v, tam), == , soma);

  /* tinytest espera que haja essa tag para o caso de algo dar errado */
  end:
    free(v); // se v for NULL, nada acontece de qualquer forma

 }

/**
 *  Função para inicializar a struct do teste.
 *  Sempre recebe uma struct testcase_t * e retorna void *.
 */
void *
setup_progressao(const struct testcase_t *testcase)
{
  struct progressao * meuteste = (struct progressao *)
    calloc(sizeof(struct progressao),1);

  if (!meuteste)
    return NULL;

  meuteste->r = 10;
  meuteste->n = 0;
  meuteste->tam = 10;

  return (void *) meuteste;
}
/**
 * No fim, essa função é chamada para fazer a limpeza
 */
 int
 clean_progressao(const struct testcase_t *testcase, void *ptr)
 {
 	struct progressao * meuteste  = (struct progressao *) ptr;

 	if (meuteste) {
 		free(meuteste);
 		return 1;
 	}
 	return 0;
 }


/* Finally, declare a testcase_setup_t with these functions. */
struct testcase_setup_t meuteste_setup = {
	setup_progressao, clean_progressao
};

/**
 * Agora define-se um conjunto de testes.
 */
 struct testcase_t meus_testes[] = {
   /* nome do teste, funcao a executar, flags, ponteiro para função
    *   de setup de parâmetros
    */
 	{ "teste1", teste_progressao_aritmetica, 0, &meuteste_setup},
 	/*  Sempre termine com END_OF_TESTCASES. */
 	END_OF_TESTCASES
 };

 /* Finalmente, faz um grupo de testes. Obrigatório também. */
 struct testgroup_t grupos[] = {

 	/* Cada grupo tem um 'prefixo' e um vetor de testes. */
 	{ "myops/", meus_testes },

 	END_OF_GROUPS
 };


int main(int argc, const char ** argv){
  /* manda o tinytest executar tudo agora */
  return tinytest_main(argc, argv, grupos);
}
