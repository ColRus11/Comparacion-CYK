%{
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Estructuras CYK
typedef struct {
    int left;
    int right1;
    int right2;
} ReglaBinaria;

typedef struct {
    int left;
    char terminal;
} ReglaTerminal;

ReglaBinaria reglas_binarias[] = {
    {0, 1, 2},
    {0, 2, 3},
    {1, 2, 1},
    {2, 3, 3},
    {3, 0, 1}
};

ReglaTerminal reglas_terminales[] = {
    {1, 'a'},
    {2, 'b'},
    {3, 'a'}
};

#define MAX_LEN 100
#define MAX_VAR 10
int cyk[MAX_LEN][MAX_LEN][MAX_VAR];

void analizar_cadena(const char *cadena, FILE *archivo);
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
int yylex() { return 0; }
%}

%%

input: /* vacío */ { /* no hace nada */ };

%%

int main() {
    const char *cadenas[] = {
        "baaba", "aab", "baba", "ababa", "ababab", "aaaaabbbbb", "aabbaabbaabbaabb", "abababababababab", "aaaaaaaabbbbbbbb", "baabaabaaabbaabb"
    };
    int cantidad = sizeof(cadenas) / sizeof(cadenas[0]);

    FILE *archivo = fopen("resultados.txt", "w");
    if (!archivo) {
        perror("No se pudo abrir resultados.txt");
        return 1;
    }

    fprintf(archivo, "%-12s %-12s %s\n", "Cadena", "Resultado", "Tiempo");

    for (int i = 0; i < cantidad; i++) {
        analizar_cadena(cadenas[i], archivo);
    }

    fclose(archivo);
    printf("\nResultados guardados en 'resultados.txt'\n");

    return 0;
}

void analizar_cadena(const char *cadena, FILE *archivo) {
    int longitud = strlen(cadena);
    memset(cyk, 0, sizeof(cyk));

    clock_t inicio = clock();

    for (int i = 0; i < longitud; i++) {
        for (int r = 0; r < sizeof(reglas_terminales)/sizeof(ReglaTerminal); r++) {
            if (cadena[i] == reglas_terminales[r].terminal)
                cyk[i][i][reglas_terminales[r].left] = 1;
        }
    }

    for (int l = 2; l <= longitud; l++) {
        for (int i = 0; i <= longitud - l; i++) {
            int j = i + l - 1;
            for (int k = i; k < j; k++) {
                for (int r = 0; r < sizeof(reglas_binarias)/sizeof(ReglaBinaria); r++) {
                    int A = reglas_binarias[r].left;
                    int B = reglas_binarias[r].right1;
                    int C = reglas_binarias[r].right2;
                    if (cyk[i][k][B] && cyk[k+1][j][C])
                        cyk[i][j][A] = 1;
                }
            }
        }
    }

    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    const char *resultado = cyk[0][longitud - 1][0] ? "Aceptada" : "Rechazada";

    printf("Cadena: %-15s → %s\tTiempo: %.6f s\n", cadena, resultado, tiempo);

    if (archivo) {
        fprintf(archivo, "%-12s %-12s %.6f\n", cadena, resultado, tiempo);
    }
}

