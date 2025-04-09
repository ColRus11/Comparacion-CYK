
# Comparación de Algoritmos CYK en C vs Bison

Este proyecto tiene como objetivo comparar el rendimiento del algoritmo CYK (Cocke-Younger-Kasami) implementado en dos versiones diferentes:

- Versión en C puro
- Versión utilizando Flex & Bison

---

## Estructura del Proyecto

Comparacion-CYK/
├── bison/            → Código de Flex & Bison
│   ├── parser.y
│   ├── scanner.l
│   └── resultados-b.txt      ← Resultados de ejecución
│
├── cyk-c/            → Implementación en C puro
│   ├── cyk.c
│   └── resultados-c.txt      ← Resultados de ejecución
│
├── graficar.py       → Script para graficar los resultados
└── README.md         → Este archivo


---

## Gramática utilizada (Forma Normal de Chomsky)

En esta versión, se utiliza una gramática simple que acepta únicamente cadenas con repeticiones del patrón `"ab"`:

S → AB | SB 
A → a 
B → b 

Es decir, acepta cadenas como: `"ab"`, `"abab"`, `"ababab"`, etc.

---

## Cadenas de prueba utilizadas

Se evaluaron las siguientes cadenas:


ab 
abab 
ababab 
abababab 
a 
b 
ba 
aabb 
aba 
abba 
abababababababababab 
abababababababababababababababababab 
abababababababababababababababababababababababab 
aaaaaaaaaaaaaaaaaaaa 
bbbbbbbbbbbbbbbbbbbb 
abababababababababababababababababababababababababababababab 


---

## ¿Qué hace cada implementación?

Cada versión:
- Evalúa si la cadena es aceptada o no por la gramática,
- Mide el **tiempo de ejecución** de forma precisa,
- Imprime los resultados en la **consola** y los guarda en un archivo de texto.

---

## Cómo compilar y ejecutar

### Versión en C puro

gcc -o cykc cykk.c
./cykc


Genera salida en consola y en el archivo resultados-c.txt.

---

### Versión con Flex & Bison

bison -d parser.y
flex scanner.l
gcc -o cykb main.c parser.tab.c lex.yy.c -lfl
./cykb


Genera resultados en resultados-b.txt.

---

## Gráfica de comparación

El archivo graficar.py genera una gráfica comparando los tiempos de ejecución de ambas versiones.

### Ejecutar:

python3 graficar.py

---

## Requisitos

Para generar las gráficas, necesitas instalar matplotlib:

sudo apt install python3-matplotlib


---

## Autor

Sebastián Díaz
GitHub: [@ColRus11]

