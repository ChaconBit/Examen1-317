#include <stdio.h>
#include <mpi.h>
#include <string.h>

#define TAM 6  // Tamaño del arreglo de palabras
#define LONG_MAX 120  // Longitud máxima de las palabras

int main(int argc, char **argv) {
    int id_proceso, num_procesos;
    char lista_palabras[TAM][LONG_MAX] = {"Azul", "Tren", "Montaña", "Rio", "Nieve", "Viento"};  // Lista de palabras
    char even_index[(TAM + 1) / 2][LONG_MAX], odd_index[TAM / 2][LONG_MAX];  // Espacios para pares e impares

    // Inicialización de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id_proceso);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procesos);

    if (id_proceso == 0) {
        // Enviar las palabras en posiciones pares al proceso 1
        for (int i = 0; i < TAM; i += 2) {
            MPI_Send(lista_palabras[i], LONG_MAX, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        }

        // Enviar las palabras en posiciones impares al proceso 2
        for (int i = 1; i < TAM; i += 2) {
            MPI_Send(lista_palabras[i], LONG_MAX, MPI_CHAR, 2, 0, MPI_COMM_WORLD);
        }
    }

    if (id_proceso == 1) {
        // Recibir y mostrar las palabras en posiciones pares
        printf("Proceso 1 (posiciones pares):{");
        for (int i = 0; i < (TAM + 1) / 2; i++) {
            MPI_Recv(even_index[i], LONG_MAX, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", even_index[i]);
            if (i < (TAM + 1) / 2 - 1) {
                printf(",");  // Añadir coma entre palabras
            }
        }
        printf("}\n");  // Cerrar con llave al final
    }

    if (id_proceso == 2) {
        // Recibir y mostrar las palabras en posiciones impares
        printf("Proceso 2 (posiciones impares):{");
        for (int i = 0; i < TAM / 2; i++) {
            MPI_Recv(odd_index[i], LONG_MAX, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", odd_index[i]);
            if (i < TAM / 2 - 1) {
                printf(",");  // Añadir coma entre palabras
            }
        }
        printf("}\n");  // Cerrar con llave al final
    }

    MPI_Finalize();
    return 0;
}
