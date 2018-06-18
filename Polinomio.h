#ifndef POLINOMIO_H
#define POLINOMIO_H
/**
 * Definições e protótiopos de funções para o TAD polinômio.
 * Não modfique esse arquivo !
 */

typedef struct polinomio Polinomio;

/**
 * Cria um polinômio a partir de um vetor de coeficientes
 * P(x) = c[0]*x^n-1 + ... + c[n-1]
 * @param coef: Um ponteiro para o vetor de coeficientes:
 * @param n : O númer de termos do polinômio.
 */
Polinomio* poli_cria(float *coef, int n);

/**
 * Libera o espaço utilizado pelo polinỗmio.
 * @param p: Um ponteiro para um polinômio.
 */
void poli_free(Polinomio* p);

/**
 * Retorna a soma de dois polinômios
 * R(x) = P(x) + Q(x);
 */
Polinomio* poli_add(Polinomio p, Polinomio r);

/**
 * * Retorna a subtração de dois polinômios
 * R(x) = P(x) + Q(x);
 */
Polinomio* poli_sub(Polinomio p, Polinomio r);

/**
 * Retorna a multiplicaçãp de dois polinômios
 * R(x) = P(x) * Q(x);
 */
Polinomio* poli_mult(Polinomio p, Polinomio r);

/**
 * Retorna a divisão de dois polinômios
 * R(x) = P(x) + Q(x);
 */
Polinomio* poli_div(Polinomio p, Polinomio r);

/**
 * Avalia um polinômio para um dado valor de x.
 * @param p: Um ponteiro para o polinômio a ser avaliado.
 * @param x: O valor de x para o qual se deseja avaliar o polinômio.
 * @return : O valor de p(x);
 */
float poli_eval(Polinomio* p, float x);

/**
 * Imprime o polinômio na tela.
 * @param p: Um ponteiro para um polinômio.
 */
void poli_print(Polinomio* p);

/**
 * Imprime uma tabela de valores de x e p(x), para x entre i e f.
 * @param p: Um ponteiro para um polinômio.
 * @param i: o valor inicial de x.
 * @param f: o valor final de x.
 * @param passo: o tamanho do incremento de x.
 */
void poli_table(Polinomio* p, float i, float f, float passo);

#endif
