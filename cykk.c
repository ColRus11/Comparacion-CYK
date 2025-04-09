#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX 100
#define NUM_NO_TERMINALES 4  // S, A, B, C

char nombres_no_terminales[] = {'S', 'A', 'B', 'C'};

typedef struct {
    int izquierda;
    int derecha1;
    int derecha2;
} ReglaBinaria;

typedef struct {
    int izquierda;
    char terminal;
} ReglaTerminal;

ReglaBinaria reglas_binarias[] = {
    {0, 1, 2}, // S → AB
    {0, 2, 3}, // S → BC
    {1, 2, 1}, // A → BA
    {2, 3, 3}, // B → CC
    {3, 0, 1}  // C → AB
};

ReglaTerminal reglas_terminales[] = {
    {1, 'a'}, // A → a
    {2, 'b'}, // B → b
    {3, 'a'}  // C → a
};

int num_reglas_binarias = sizeof(reglas_binarias) / sizeof(ReglaBinaria);
int num_reglas_terminales = sizeof(reglas_terminales) / sizeof(ReglaTerminal);

bool cyk(const char* cadena, double* tiempo, char* resultado_str) {
    int n = strlen(cadena);
    bool tabla[MAX][MAX][NUM_NO_TERMINALES] = {false};

    clock_t inicio = clock();

    for (int i = 0; i < n; i++) {
        for (int r = 0; r < num_reglas_terminales; r++) {
            if (reglas_terminales[r].terminal == cadena[i]) {
                tabla[i][1][reglas_terminales[r].izquierda] = true;
            }
        }
    }

    for (int longitud = 2; longitud <= n; longitud++) {
        for (int inicio = 0; inicio <= n - longitud; inicio++) {
            for (int particion = 1; particion < longitud; particion++) {
                for (int r = 0; r < num_reglas_binarias; r++) {
                    ReglaBinaria regla = reglas_binarias[r];
                    if (tabla[inicio][particion][regla.derecha1] &&
                        tabla[inicio + particion][longitud - particion][regla.derecha2]) {
                        tabla[inicio][longitud][regla.izquierda] = true;
                    }
                }
            }
        }
    }

    clock_t fin = clock();
    *tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    bool aceptada = tabla[0][n][0];
    strcpy(resultado_str, aceptada ? "Aceptada" : "Rechazada");
    return aceptada;
}

int main() {
    const char* entradas[] = {
        "baaba", "aab", "baba", "ababa", "ababab", "aaaaabbbbb", "aabbaabbaabbaabb", "abababababababab", "aaaaaaaabbbbbbbb", "baabaabaaabbaabb"
    };
    int total = sizeof(entradas) / sizeof(entradas[0]);

    FILE* archivo = fopen("resultados-c.txt", "w");
    if (!archivo) {
        perror("No se pudo abrir el archivo de salida");
        return 1;
    }

    fprintf(archivo, "%-12s %-12s %s\n", "Cadena", "Resultado", "Tiempo");

    for (int i = 0; i < total; i++) {
        const char* cadena = entradas[i];
        double tiempo;
        char resultado[16];
        cyk(cadena, &tiempo, resultado);
        fprintf(archivo, "%-12s %-12s %.6f\n", cadena, resultado, tiempo);
        printf("Cadena: %-12s Resultado: %-10s Tiempo: %.6f s\n", cadena, resultado, tiempo);
    }

    fclose(archivo);
    printf("\nResultados guardados en 'resultados-c.txt'\n");
    return 0;
}

