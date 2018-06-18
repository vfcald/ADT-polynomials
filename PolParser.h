#ifndef POL_PARSER_H
#define POL_PARSER_H

typedef struct pstream* PStream;
typedef struct polterm* PolTerm;

PStream mkStream(char* v, int n);
void free_PStream(PStream p);
void reset_PStream(PStream p);
void buffer_update_PStream(PStream p, int size);
char next_PStream(PStream p);
void skip_PStream(PStream p);
char look_PStream(PStream p);
char* get_PStream(PStream s);

PolTerm mkPolTerm(int e, float c);
void print_pterm(PolTerm t);

int pfloat(PStream s, float *f);
int pvar(PStream s);

int term(PStream s, PolTerm t);
float* polParser(PStream s, int* n);


#endif
