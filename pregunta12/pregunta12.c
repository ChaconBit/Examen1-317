#include <stdio.h>
#include <omp.h>

int main() {
    int cantidad = 12; // Total de términos de la secuencia de Fibonacci
    int secuencia[cantidad]; // Arreglo para guardar la secuencia
    int indice;

    // Inicializar los dos primeros términos de la secuencia
    secuencia[0] = 0;
    secuencia[1] = 1;

    // Usamos OpenMP para calcular el resto de la secuencia de Fibonacci
    #pragma omp parallel shared(secuencia) private(indice)
    {
        // Cada hilo calculará un término de la secuencia
        #pragma omp for
        for (indice = 2; indice < cantidad; indice++) {
            // Cada hilo calcula el siguiente término en la secuencia
            secuencia[indice] = secuencia[indice - 1] + secuencia[indice - 2];
        }
    }

    // Imprimir la secuencia de Fibonacci
    printf("Secuencia de Fibonacci: ");
    for (indice = 0; indice < cantidad; indice++) {
        printf("%d ", secuencia[indice]);
    }
    printf("\n");

    return 0;
}
