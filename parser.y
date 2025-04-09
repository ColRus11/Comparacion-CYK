%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%start S
%token A B

%%

S : AB
  | AB S
  ;

AB : A B ;

%%

void yyerror(const char *s) {
    // No mostrar errores por reglas no coincidentes
}


