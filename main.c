#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 100

// Reglas binarias en FNC
int isRule(char A, char B, char* result) {
    if ((A == 'S' && B == 'B') || (A == 'A' && B == 'B')) {
        *result = 'S';
        return 1;
    }
    return 0;
}

// Reglas unitarias (terminales)
char getNonTerminal(char terminal) {
    if (terminal == 'a') return 'A';
    if (terminal == 'b') return 'B';
    return '?';
}

// Implementación del algoritmo CYK
int cyk(const char* w, int n) {
    char table[MAX_LEN][MAX_LEN][MAX_LEN];
    int count[MAX_LEN][MAX_LEN] = {0};

    // Inicialización
    for (int i = 0; i < n; i++) {
        char nt = getNonTerminal(w[i]);
        if (nt != '?') {
            table[i][0][0] = nt;
            count[i][0] = 1;
        }
    }

    // Llenado de tabla CYK
    for (int l = 2; l <= n; l++) {
        for (int s = 0; s <= n - l; s++) {
            for (int p = 1; p < l; p++) {
                int c1 = count[s][p - 1];
                int c2 = count[s + p][l - p - 1];

                for (int i = 0; i < c1; i++) {
                    for (int j = 0; j < c2; j++) {
                        char result;
                        if (isRule(table[s][p - 1][i], table[s + p][l - p - 1][j], &result)) {
                            // Evita duplicados
                            int exists = 0;
                            for (int k = 0; k < count[s][l - 1]; k++) {
                                if (table[s][l - 1][k] == result) {
                                    exists = 1;
                                    break;
                                }
                            }
                            if (!exists) {
                                table[s][l - 1][count[s][l - 1]++] = result;
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < count[0][n - 1]; i++) {
        if (table[0][n - 1][i] == 'S') return 1;
    }
    return 0;
}

int main() {
    const char* entradas[] = {
        "ab", "abab", "ababab", "abababab", "a", "b", "ba", "aabb", "aba", "abba",
        "abababababababababab", // 20 chars
        "abababababababababababababababababab", // 36 chars
        "abababababababababababababababababababababababab", // 48 chars
        "aaaaaaaaaaaaaaaaaaaa", // 20 a's
        "bbbbbbbbbbbbbbbbbbbb", // 20 b's
        "abababababababababababababababababababababababababababababab" // 60 chars
    };

    int total = sizeof(entradas) / sizeof(entradas[0]);

    FILE* archivo = fopen("resultados-c.txt", "w");
    if (!archivo) {
        perror("No se pudo abrir el archivo de salida");
        return 1;
    }

    fprintf(archivo, "%-12s %-12s %s\n", "Cadena", "Resultado", "Tiempo");
    printf("%-12s %-12s %s\n", "Cadena", "Resultado", "Tiempo");

    for (int i = 0; i < total; i++) {
        const char* cadena = entradas[i];
        int len = strlen(cadena);

        clock_t inicio = clock();
        int aceptada = cyk(cadena, len);
        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        const char* estado = aceptada ? "Aceptada" : "Rechazada";

        fprintf(archivo, "%-12s %-12s %.6f\n", cadena, estado, tiempo);
        printf("Cadena: %-12s Resultado: %-10s Tiempo: %.6f s\n", cadena, estado, tiempo);
    }

    fclose(archivo);
    printf("\nResultados guardados en 'resultados-c.txt'\n");
    return 0;
}

