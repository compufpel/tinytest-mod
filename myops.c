/** Soma todos os elementos de um vetor de inteiros
 *  @param a vetor a ser somado
 *  @param tam comprimento do vetor
 *  @return soma dos elementos
 */
int soma_todos(int a[], int size){
  int soma = 0;
  int i;

  for(i=0; i<size; i++)
    soma = soma + a[i];
    
  return soma;
}
