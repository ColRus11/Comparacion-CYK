Comparación de Algoritmos CYK en C puro vs Bison

Este proyecto tiene como objetivo comparar el rendimiento del algoritmo CYK (Cocke-Younger-Kasami) implementado en dos versiones diferentes:

- Versión en C puro 
- Versión utilizando Flex & Bison

Estructura del proyecto

Comparacion-CYK/
- bison/ → Código de Flex & Bison
  - parser.y 
  - resultados.txt (resultados de Bison)

- cyk-c/ → Código de C puro
  - cyk.c 
  - resultados-c.txt (resultados de C puro)

- graficar.py → Script para graficar los resultados
- README.md → Este archivo

Gramática utilizada

La gramática es binaria y está en Forma Normal de Chomsky:

S → AB | BC
A → BA | a
B → CC | b
C → AB | a

Cadenas de prueba

Se evaluaron múltiples cadenas como:

- baaba
- aab
- baba
- ababa
- ababab
- aaaaabbbbb
- aabbaabbaabbaabb
- abababababababab
- aaaaaaaabbbbbbbb
- baabaabaaabbaabb

Cada implementación evalúa si la cadena es aceptada o rechazada, y mide el tiempo de ejecución.

Para compilar y ejecutar:

- Para C:
gcc -o cykc cyk.c -o cyk
./cykc

- Para Bison:

bison -d parser.y
gcc -o cykb parser.tab.c
./cykb

Gráfica de comparación

El archivo graficar.py genera una gráfica comparando los tiempos de ejecución de ambas versiones.

Cómo ejecutar graficar.py:

python3 graficar.py


Requisitos:

Para poder graficar:

sudo apt install python3-matplotlib

Autor:

Sebastián Díaz – GitHub: @ColRus11
