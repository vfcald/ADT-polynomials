#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Polinomio.h"
#include"PolParser.h"


#define BUFF_SIZE 512
#define MEM_SIZE 20

void intro(){
   printf("\n                             ------- CALCULADORA DE POLINOMIOS -------               \n");
   printf(" Trabalho Prático de AEDS I     \n");
   printf("Nome: Vinicius Fiedler Caldeira\n" );
   printf("Matrícula: 17.1.8343\n" );
   printf("Curso: Engenharia da Computação\n" );
   printf(" Comandos:    \n");
   printf("   list:             Lista todos os polinômios digitados.  \n");
   printf("   add,sub,mult,div: Soma, subtrai, multiplica e divide respectivamente, os dois últimos\n");
   printf("                     polinômios digitados.\n");
   printf("   eval:             Avalia um polinômio.             \n");
   printf("   dump:             Apaga o último polinômio digitado. \n");
   printf("   quit:             Sai do sistema \n");
   printf("   tabela:           Imprime uma tabela de pontos para um intervalo de valores de x.\n");

}

int main(){
    char * line = (char*)malloc(BUFF_SIZE*sizeof(char));
    char * prompt = " :> ";
    int n, psz, pcounter,j;
    Polinomio* polis = (Polinomio*)calloc(MEM_SIZE,sizeof(Polinomio));
    for(j=0; j< MEM_SIZE; j++){ polis[j] = NULL;}
    PStream ss = mkStream(line,BUFF_SIZE);
    pcounter = 0;
    intro();
    do{
       fputs(prompt,stdout);
       fgets(line, BUFF_SIZE, stdin);
       n = strlen(line);
       line[n-1] = 0;

       if(strcmp(line,"quit")==0){ break;}
       if(strcmp(line,"list")==0){
           for(j = 0; j < pcounter; j++){
               printf("(%d) : ",j);
               poli_print(polis[j]);
               printf("\n");
           }
       }
       else if(strcmp(line,"add")==0){
           if(pcounter < 2){
               printf("Você deve digitar pelo menos dois polinômios antes de usar esta funcionalidade\n");
           }
           if(pcounter < MEM_SIZE){
              Polinomio p = poli_add(polis[pcounter-1],polis[pcounter-2]);
              if(p!=NULL){
                  polis[pcounter] = p;
                  printf("Result = ");
                  poli_print(p);
                  printf("\n");
                  pcounter++;
              }
           }else{
               printf("Memória cheia !, impossível continuar");
           }
       }else if(strcmp(line,"sub")==0){
           if(pcounter < 2){
               printf("Você deve digitar pelo menos dois polinômios antes de usar esta funcionalidade\n");
           }
           if(pcounter < MEM_SIZE){
           Polinomio p = poli_sub(polis[pcounter-1],polis[pcounter-2]);
              if(p!=NULL){
                   polis[pcounter] = p;
                   printf("Result = ");
                   poli_print(p);
                   printf("\n");
                   pcounter++;
              }
           }else{
               printf("Memória cheia !, impossível continuar");
           }
       }else if(strcmp(line,"mult")==0){
           if(pcounter < 2){
               printf("Você deve digitar pelo menos dois polinômios antes de usar esta funcionalidade\n");
           }
           if(pcounter < MEM_SIZE){
              Polinomio p = poli_mult(polis[pcounter-1],polis[pcounter-2]);
              if(p!=NULL){
                  polis[pcounter] = p;
                  printf("Result = ");
                  poli_print(p);
                  printf("\n");
                  pcounter++;
             }
           }else{
               printf("Memória cheia !, impossível continuar");
           }
       }else if(strcmp(line,"eval")==0){
           if(pcounter < 1){
               printf("Você ainda não digitou nenhum polinômio !\n");
           }
           printf(" x = ? ");
           float x = 0, r;
           scanf("%f",&x);
           r = poli_eval(polis[pcounter-1],x);
           printf("p(x) = %f \n",r);
       }else if(strcmp(line,"tabela")==0){
           if(pcounter < 1){
               printf("Você ainda não digitou nenhum polinômio !\n");
           }
           float x0, x1, p;
           printf(" x0 = ? ");
           scanf("%f",&x0);
           printf(" x1 = ? ");
           scanf("%f",&x1);
           printf(" passo = ? ");
           scanf("%f",&p);

           poli_table(polis[pcounter-1],x0,x1,p);
       }else if(strcmp(line,"dump")==0){
           if(pcounter < 1){
               printf("A lista de polinômios está vazia !\n");
           }
           free(polis[pcounter-1]);
           pcounter = pcounter - 1;
       }else{
          if(pcounter < MEM_SIZE){
              buffer_update_PStream(ss,n-1);
              float *pol = polParser(ss,&psz);
              if( pol != NULL){
                  polis[pcounter] = poli_cria(pol,psz);
                  printf("(%d): ",pcounter);
                  poli_print(polis[pcounter]);
                  printf("\n");
                  pcounter ++;
              }else{
                  fputs("Não é um polinômio valido !\n",stdout);
              }
          }
       }   
    }while(1);

    fputs("\n------------------[ Saindo ]------------------\n",stdout);
    fputs("   (i) Desalocando memória ... ",stdout);
    free_PStream(ss);
    for(j = 0; j< pcounter; j++){
        if(polis[j] != NULL){
            free(polis[j]);
        }
    }
    free(polis);
    fputs("[Feito]\n",stdout);
    fputs("   (i) Programa terminado com sucesso. \n",stdout);
    fputs("----------------------------------------------\n",stdout);
    return 0;
}
