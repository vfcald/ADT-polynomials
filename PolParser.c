#include<stdlib.h>
#include<stdio.h>
#include"PolParser.h"

struct pstream {
   char *v;
   int size;
   int pos;
   int bb;
};

struct polterm {
   int exp;
   float coef;
};

struct termNode{
     PolTerm t;
     struct termNode* next;
};

struct termList{
     int size;
     struct termNode * head;
};


PStream mkStream(char* v, int n){
    PStream p = (PStream)malloc(sizeof(struct pstream));
    p->v = v;
    p->size = n;
    p->pos = 0;
    p->bb = 0;
    return p;
}

void free_PStream(PStream p){
    if(p != NULL){
        free(p->v);
        free(p);
    }
}

void reset_PStream(PStream p){
    if(p != NULL){
        p->bb = 0;
        p->pos = 0;
    }
}

void buffer_update_PStream(PStream p, int size){
    if(p != NULL){
        p->size = size;
        p->bb = 0;
        p->pos = 0;
    }
}

char next_PStream(PStream p){
    if(p->pos > p->size){
         printf("Error: attempt to read beyond the end of the stream");
         exit(1);
    }
    char c = p->v[p->pos];
    p->pos++;
    return c;
}


void skip_PStream(PStream p){
    if(p->pos > p->size){
         printf("Error: attempt to read beyond the end of the stream");
         exit(1);
    }
    p->pos++;
    p->bb++;
}

char look_PStream(PStream p){
     if(p->pos > p->size){
         printf("Error: attempt to read beyond the end of the stream");
         exit(1);
     }
     return p->v[p->pos];
}

char* get_PStream(PStream s){
    if(s->bb == s->pos){ return NULL;}
    int i,n;
    n = s->pos - s->bb +1;
    char* buff = (char*)malloc((n+1)*sizeof(char));
    for(i = 0; i<n; i++){ buff[i] = s->v[s->bb+i];}
    buff[n] = '\0';
    s->bb = s->pos;
    return buff;
}

PolTerm mkPolTerm(int e, float c){
    PolTerm t = (PolTerm)malloc(sizeof(struct polterm));
    return t;
}
void print_pterm(PolTerm t){
    printf("%fx^%d",t->coef,t->exp);
}


struct termList* mkList(){
    struct termList* l = (struct termList*)malloc(sizeof(struct termList));
    l->size = 0;
    l->head = NULL;
    return l;
}

void add(struct termList* t, PolTerm p){
    struct termNode* data = (struct termNode*)malloc(sizeof(struct termNode*));
    struct termNode* n = t->head;
    data->next = NULL;
    data->t = p;
    if(n == NULL){
        t->head = data;
    }else if(data->t->exp > n->t->exp) {
        data->next = n;
        t->head = data;
    }else if(data->t->exp == n->t->exp) {
        n->t->coef = n->t->coef + data->t->coef;
        free(p);
        free(data);
    }else if(data->t->exp < n->t->exp) {
        while((n->next != NULL) && (data->t->exp < n->next->t->exp)){n = n->next;}
        if(n->next != NULL){
           if(n->next->t->exp == data->t->exp){
               n->next->t->coef = n->next->t->coef + data->t->coef;
               free(p);
               free(data);
               return ;
           }
        }
        data->next = n->next;
        n->next = data;
    }
    t->size = t->size+1;
}

void print_list(struct termList* t){
    struct termNode* n;
    if(t != NULL){
        n = t->head;
        while(n != NULL){
            printf("(%f,%d) -> ",n->t->coef,n->t->exp);
            n = n->next;
        }
        printf("NULL");
    }
}

float* toArray(struct termList* t){
    if(t == NULL){ return NULL;}
    if(t->size == 0){
        return (float*)calloc(1,sizeof(float));
    }
    int numt = t->head->t->exp+1;
    float* arr = (float*)malloc(numt*sizeof(float));
    struct termNode * n = t->head;
    int i = 0;
    while(n != NULL){
        if(numt-1-i == n->t->exp){
            arr[i] = n->t->coef;
            n = n->next;
        }else{
            arr[i] = 0;
        }
        i = i +1;
    }
    return arr;
}

void free_node(struct termNode* t){
     if(t != NULL){
         free_node(t->next);
         free(t->t);
         free(t);
     }
}

void free_list(struct termList* l){
    if(l != NULL){
       free_node(l->head);
       free(l);
    }
}

//****************************************************************************
//***                  FUNÇÔES PARA o PARSER                               ***
//****************************************************************************


int pfloat(PStream s, float *f){
    if( !( (look_PStream(s) >= '0') && (look_PStream(s) <= '9')) ){ return 0;}
    while((look_PStream(s) >= '0') && (look_PStream(s) <= '9')){ next_PStream(s); }
    if(look_PStream(s) == '.'){
        next_PStream(s);
        while((look_PStream(s) >= '0') && (look_PStream(s) <= '9')){ next_PStream(s); }
    }
    char* n = get_PStream(s);
    *f = atof(n);
    free(n);
    return 1;
}

int pint(PStream s, int *i){
    if( !( (look_PStream(s) >= '0') && (look_PStream(s) <= '9')) ){ return 0;}
    while((look_PStream(s) >= '0') && (look_PStream(s) <= '9')){ next_PStream(s); }
    char* n = get_PStream(s);
    *i = atoi(n);
    free(n);
    return 1;
}


int pvar(PStream s){
    if( look_PStream(s) == 'x' ){
        skip_PStream(s);
        return 1;
    }
    return 0;
}

int pname(PStream s, char * c){
    if( (look_PStream(s) >= 'A') && (look_PStream(s) <= 'Z') ){
        next_PStream(s);
        c = get_PStream(s);
        return 1;
    }
    return 0;
}

int skip_char(PStream s, char c){
    if( (look_PStream(s) == c) ){
        skip_PStream(s);
        return 1;
    }
    return 0;
}

int whites(PStream s){
    while(look_PStream(s) == ' '){ skip_PStream(s);}
    return 1;
}


int term(PStream s, PolTerm t){
    float c;
    int e;
    if(pfloat(s,&c) > 0){
         t->coef = c;
         if(pvar(s) > 0){
             if(skip_char(s,'^') > 0){
                  if(pint(s,&e) > 0){
                      t->exp = e;
                      return 1;
                  }
                  else{ return 0;}
             }
             t->exp = 1;
        }else{
            t->exp = 0;
        }
        return 1;
    }
    return 0;
}

float* polParser(PStream s, int* n){
    int signal = 1;
    PolTerm t = mkPolTerm(0,0);
    struct termList *l = mkList();
    whites(s);
    while(term(s,t) > 0){
        t->coef = signal*t->coef;
        add(l,t);
        whites(s);
        if(skip_char(s,'+') > 0){
            signal = 1;
        }else if(skip_char(s,'-') > 0){
            signal = -1;
        }else { break; }
        whites(s);
        t = mkPolTerm(0,0);
    }
    if(l->size == 0){
        free_list(l);
        *n = 0;
        return NULL;
    }else{
        float * arr = toArray(l);
        *n = l->head->t->exp+1;
        free_list(l);
        return arr;
    }
}
