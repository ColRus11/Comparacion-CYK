import matplotlib.pyplot as plt

def leer_resultados_alineados(nombre_archivo):
    cadenas = []
    tiempos = []
    with open(nombre_archivo, 'r') as f:
        next(f)  # Saltar la cabecera
        for linea in f:
            partes = linea.strip().split()
            if len(partes) >= 3:
                cadena = partes[0]
                tiempo = float(partes[2])
                cadenas.append(cadena)
                tiempos.append(tiempo)
    return cadenas, tiempos

# Leer los archivos
cadenas_bison, tiempos_bison = leer_resultados_alineados('resultados.txt')
cadenas_c, tiempos_c = leer_resultados_alineados('resultados-c.txt')

# Verificar coincidencias
if cadenas_bison != cadenas_c:
    print("Las cadenas no coinciden entre los archivos. Comparación puede no ser precisa.")

# Graficar
plt.figure(figsize=(12, 6))
plt.plot(cadenas_bison, tiempos_bison, marker='o', label='Bison')
plt.plot(cadenas_c, tiempos_c, marker='s', label='C puro')

plt.title("Comparación de tiempos CYK (Bison vs C)")
plt.xlabel("Cadena de entrada")
plt.ylabel("Tiempo (segundos)")
plt.xticks(rotation=45)
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

