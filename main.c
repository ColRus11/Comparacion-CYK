#include <stdio.h>
#include <time.h>
#include <string.h>  

extern int yyparse();
extern void yyrestart(FILE*);

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

    FILE* archivo = fopen("resultados-b.txt", "w");
    if (!archivo) {
        perror("No se pudo abrir el archivo de salida");
        return 1;
    }

    fprintf(archivo, "%-12s %-12s %s\n", "Cadena", "Resultado", "Tiempo");

    for (int i = 0; i < total; i++) {
        const char* cadena = entradas[i];
        FILE* input = fmemopen((void*)cadena, strlen(cadena), "r");
        yyrestart(input);

        clock_t inicio = clock();
        int resultado = yyparse();
        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        const char* estado = resultado == 0 ? "Aceptada" : "Rechazada";

        fprintf(archivo, "%-12s %-12s %.6f\n", cadena, estado, tiempo);
        printf("Cadena: %-12s Resultado: %-10s Tiempo: %.6f s\n", cadena, estado, tiempo);

        fclose(input);
    }

    fclose(archivo);
    printf("\nResultados guardados en 'resultados-b.txt'\n");
    return 0;
}

