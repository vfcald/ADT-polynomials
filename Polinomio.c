#include"Polinomio.h"
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

struct polinomio {
    float* arr;
    int n;
};

/**
 * Cria um polinômio a partir de um vetor de coeficientes
 * P(x) = c[0]*x^n-1 + ... + c[n-1]
 * @param coef: Um ponteiro para o vetor de coeficientes:
 * @param n : O número de termos do polinômio.
 */
struct polinomio* poli_cria(float *coef, int n){
    struct polinomio* p = (struct polinomio*)malloc(sizeof(struct polinomio));
    p->arr = (float*)malloc(n*sizeof(float));
    p->n = n;
    int i;
    for(i = 0; i < n; i++){
        p->arr[n-i-1] = coef[i];
    }
    return p;
}
//--------------------------------------------------------------------------//
/**
 * Libera o espaço utilizado pelo polinỗmio.
 * @param p: Um ponteiro para um polinômio.
 */
void poli_free(struct polinomio *p){
    if(p != NULL){
        free(p->arr);
        free(p);
    }
}
//--------------------------------------------------------------------------//
/**
 * Retorna a soma de dois polinômios
 * R(x) = P(x) + Q(x);
 */
struct polinomio* poli_add(struct polinomio p, struct polinomio r){

   int cont1=0;
   int cont2=0;
   int x;
   int y;
   int j;
   cont1=p.n; //vai receber o tamanho do polinomio1
   cont2=r.n; //vai receber o tamanho do polinomio2

if(cont1>cont2){

   x=cont1;
   y=cont2;

}else{

   x=cont2;
   y=cont1;

}
    float *vetorDaSOMA; //cria um vetor do tamanho do maior polinomio
    vetorDaSOMA = (float*)malloc(x * sizeof(float));
    int q = x;

for(j=0; j<q; j++){

    if(x==y){ /*caso os polinomios tenham tamanho iguais, a soma vai ser
               diretamente posicao por posicao.*/

      vetorDaSOMA[j] = (float) p.arr[x] + r.arr[y];
      x--;
      y--;

    }else if(x>y){//nesse caso estou sempre colocando o polinomio x como maior.

    if(p.n > r.n){
      vetorDaSOMA[x] = p.arr[x]; /*caso o vetor x seja maior que o y, os
      valores do maior vetor vao simplesmente descer ate que os 2 vetores passam a
      ser do mesmo tamanho*/
    }else{
        vetorDaSOMA[x] = r.arr[x];
    }
      x--;
      }
}

    struct polinomio *retorno = (struct polinomio*) poli_cria(vetorDaSOMA, q);

    return retorno;

 }

//--------------------------------------------------------------------------//
/**
 * * Retorna a subtração de dois polinômios
 * R(x) = P(x) - Q(x);
 */
struct polinomio* poli_sub(struct polinomio p, struct polinomio r){

   int cont1=0;
   int cont2=0;
   int x;
   int y;
   int j;
   cont1=p.n; //vai receber o tamanho do polinomio1
   cont2=r.n;//vai receber o tamanho do polinomio2

    if(cont1>cont2){

   x=cont1;
   y=cont2;

     }else{

   x=cont2;
   y=cont1;

   }
   float *vetorDaSUBTRACAO; //cria um vetor do tamanho do maior polinomio
   vetorDaSUBTRACAO = (float*)malloc(x * sizeof(float));
  int q = x;

   for(j=0; j<q; j++){

     if(x==y){ /*caso os polinomios tenham tamanho iguais, a subtracao vai
                ser diretamente posicao por posicao.*/

      vetorDaSUBTRACAO[j] = p.arr[x] - r.arr[y];
      x--;
      y--;

    }else if(x>y){//nesse caso estou sempre colocando o polinomio x como maior.

    if(p.n > r.n){
   vetorDaSUBTRACAO[j] = p.arr[x]; /*caso o vetor x seja maior que o y, os
   valores do maior vetor vao simplesmente descer ate que os 2 vetores passam a
   ser do mesmo tamanho*/
    }else{
        vetorDaSUBTRACAO[j] = r.arr[x];
    }
   x--;
   }
}

struct polinomio* retorno = (struct polinomio*) poli_cria(vetorDaSUBTRACAO, q);

 return retorno;

}
//--------------------------------------------------------------------------//
/**
 * Retorna a multiplicaçãp de dois polinômios
 * R(x) = P(x) * Q(x);
 */
struct polinomio* poli_mult(struct polinomio p, struct polinomio r){

   int i, j, q;
   q = p.n + r.n - 2;
   float* auxiliar = (float*) malloc((q+1) * sizeof(float));
   for(i=0; i<q+1; ++i){
    auxiliar[i] = 0.0;
   }
   struct polinomio* retorno = (struct polinomio*) poli_cria(auxiliar, (q+1));
   free(auxiliar);
   for(i=0; i<p.n; ++i)
   {
       int grau = 0;
       auxiliar = (float*) malloc((q+1) * sizeof(float));
       for(j=0; j<r.n; ++j)
       {
           auxiliar[grau] = p.arr[i] * r.arr[j];
           grau++;
       }
       while(grau<=q){
        auxiliar[grau] = 0.0;
        grau++;
       }
       struct polinomio* auxiliar2 = (struct polinomio*) poli_cria(auxiliar, q+1);
       struct polinomio* auxiliar3 = (struct polinomio*) poli_add(*retorno, *auxiliar2);
       poli_free(retorno);
       retorno = auxiliar3;
       poli_free(auxiliar2);
       free(auxiliar);
       q--;
   }

   return retorno;


}
//--------------------------------------------------------------------------//
/**
 * Retorna a divisão de dois polinômios
 * R(x) = P(x) / Q(x);
 */
struct polinomio* poli_div(struct polinomio p, struct polinomio r){
   int i, j, q;
   struct polinomio* resto;
   struct polinomio* retorno;
   if(p.n > r.n){
    q = p.n - r.n;
    resto = (struct polinomio*) poli_cria(p.arr, p.n);

    float* auxiliar = (float*) malloc((q+1) * sizeof(float));
    for(i=0; i<q+1; ++i){
        auxiliar[i] = 0.0;
    }
    retorno = (struct polinomio*) poli_cria(auxiliar, (q+1));
    free(auxiliar);

    while(q >= 0){
        auxiliar = (float*) malloc((q + 1) * sizeof(float));
        auxiliar[0] = (p.arr[0] / r.arr[0]);
        for(i=1; i<(q+1); ++i)
        {
            auxiliar[i] = 0.0;
        }
        struct polinomio* auxiliar2 = (struct polinomio*) poli_cria(auxiliar, (q+1));
        struct polinomio* auxiliar3 = (struct polinomio*) poli_add(*retorno, *auxiliar2);
        poli_free(retorno);
        retorno = auxiliar3;
        poli_free(auxiliar2);
        auxiliar[0] = - auxiliar[0];
        struct polinomio* auxiliar4 = (struct polinomio*) poli_mult(auxiliar, (q+1));;
        poli_free(resto);
        resto = auxiliar4;
        q = resto->n - r.n;
    }

   }else{
    q = r.n - p.n;
    resto = (struct polinomio*) poli_cria(r.arr, r.n);

    float* auxiliar = (float*) malloc((q+1) * sizeof(float));
    for(i=0; i<q+1; ++i){
        auxiliar[i] = 0.0;
    }
    retorno = (struct polinomio*) poli_cria(auxiliar, (q+1));
    free(auxiliar);

    while(q >= 0){
        auxiliar = (float*) malloc((q + 1) * sizeof(float));
        auxiliar[0] = (p.arr[0] / r.arr[0]);
        for(i=1; i<(q+1); ++i)
        {
            auxiliar[i] = 0.0;
        }
        struct polinomio* auxiliar2 = (struct polinomio*) poli_cria(auxiliar, (q+1));
        struct polinomio* auxiliar3 = (struct polinomio*) poli_add(*retorno, *auxiliar2);
        poli_free(retorno);
        retorno = auxiliar3;
        poli_free(auxiliar2);
        auxiliar[0] = - auxiliar[0];
        struct polinomio* auxiliar4 = (struct polinomio*) poli_mult(auxiliar, (q+1));;
        poli_free(resto);
        resto = auxiliar4;
        q = resto->n - p.n;
    }
   }


   return retorno;
}
//--------------------------------------------------------------------------//
/**
 * Avalia um polinômio para um dado valor de x.
 * @param p: Um ponteiro para o polinômio a ser avaliado.
 * @param x: O valor de x para o qual se deseja avaliar o polinômio.
 * @return : O valor de p(x);
 */
float poli_eval(struct polinomio *p, float x){
    int i;
    float result = 0.0;
    for(i=0; i<p->n; ++i){
        result += p->arr[i] * pow(x, (p->n-i-1));
    }
    return result;
}
//--------------------------------------------------------------------------//
/**
 * Imprime o polinômio na tela.
 * @param p: Um ponteiro para um polinômio.
 */
void poli_print(struct polinomio *p){

  int i;

  printf("\nPolinomio = ");
  for(i=0; i < p->n; i++){
        printf("(%.2fx^%d) + ", p->arr[i], i);
  }
  printf("\n");
}
//--------------------------------------------------------------------------//
/**
 * Imprime uma tabela de valores de x e p(x), para x entre i e f.
 * @param p: Um ponteiro para um polinômio.
 * @param i: o valor inicial de x.
 * @param f: o valor final de x.
 * @param passo: o tamanho do incremento de x.
 */
void poli_table(struct polinomio *p, float i, float f, float passo){
    printf("\n x ; p(x)\n");
    float j;
    for(j=i; j<=f; j+=passo){
        printf(" %.2f ; %.2f\n", j, poli_eval(p, j));
    }
}
