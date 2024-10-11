#include <stdio.h>
#include <mpi.h>

#define TAM 7 // Tamaño del vector

int main(int argc, char **argv) {
    int rank, size;
    // Inicializamos los vectores con nuevos valores
    int vec1[TAM] = {10, 3, 5, 7, 12, 1, 6}; 
    int vec2[TAM] = {2, 8, 4, 3, 9, 5, 11}; 
    int resultado[TAM];
    int impares[TAM / 2], pares[TAM / 2]; // Arreglos temporales para pares e impares

    // Inicio de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Enviar posiciones impares a procesador 1
        MPI_Send(vec1, TAM, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(vec2, TAM, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // Enviar posiciones pares a procesador 2
        MPI_Send(vec1, TAM, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Send(vec2, TAM, MPI_INT, 2, 0, MPI_COMM_WORLD);

        // Recibir resultado de posiciones impares desde procesador 1
        MPI_Recv(impares, TAM / 2, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Recibir resultado de posiciones pares desde procesador 2
        MPI_Recv(pares, TAM / 2, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Combinar los resultados de pares e impares
        for (int i = 0; i < TAM; i++) {
            if (i % 2 == 0) {
                resultado[i] = pares[i / 2]; // Pares
            } else {
                resultado[i] = impares[i / 2]; // Impares
            }
        }

        // Imprimir el vector resultado
        printf("Vector resultado de la suma: [");
        for (int i = 0; i < TAM; i++) {
            printf("%d ", resultado[i]);
        }
        printf("]\n");
    }

    if (rank == 1) {
        // Recibir los vectores desde el procesador 0
        MPI_Recv(vec1, TAM, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vec2, TAM, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Sumar posiciones impares
        for (int i = 1; i < TAM; i += 2) {
            impares[i / 2] = vec1[i] + vec2[i];
        }

        // Enviar resultado de posiciones impares al procesador 0
        MPI_Send(impares, TAM / 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 2) {
        // Recibir los vectores desde el procesador 0
        MPI_Recv(vec1, TAM, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vec2, TAM, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Sumar posiciones pares
        for (int i = 0; i < TAM; i += 2) {
            pares[i / 2] = vec1[i] + vec2[i];
        }

        // Enviar resultado de posiciones pares al procesador 0
        MPI_Send(pares, TAM / 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
