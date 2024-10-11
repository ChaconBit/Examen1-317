#include <stdio.h>
#include <mpi.h>

#define FILAS 5  // Número de filas de X
#define COLUMNAS 3  // Número de columnas de X (y filas de Y)
#define COL_RES 4  // Número de columnas de Y

int main(int argc, char **argv) {
    int proceso_id, num_procesos;
    int X[FILAS][COLUMNAS], Y[COLUMNAS][COL_RES], Z[FILAS][COL_RES]; // Matrices X, Y y el resultado Z
    int filaX[COLUMNAS], filaResultado[COL_RES];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procesos);

    if (proceso_id == 0) {
        // Inicializar la matriz X
        printf("Matriz X (%d x %d):\n", FILAS, COLUMNAS);
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                X[i][j] = i + j;  // Ejemplo de valores iniciales
                printf("%d ", X[i][j]);
            }
            printf("\n");
        }

        // Inicializar la matriz Y
        printf("Matriz Y (%d x %d):\n", COLUMNAS, COL_RES);
        for (int i = 0; i < COLUMNAS; i++) {
            for (int j = 0; j < COL_RES; j++) {
                Y[i][j] = i + j;  // Ejemplo de valores iniciales
                printf("%d ", Y[i][j]);
            }
            printf("\n");
        }
    }

    // Difundir la matriz Y a todos los procesos
    MPI_Bcast(&Y, COLUMNAS * COL_RES, MPI_INT, 0, MPI_COMM_WORLD);

    // Enviar filas de la matriz X a cada proceso
    if (proceso_id == 0) {
        for (int i = 1; i < num_procesos; i++) {
            if (i - 1 < FILAS) {
                MPI_Send(X[i - 1], COLUMNAS, MPI_INT, i, 0, MPI_COMM_WORLD); // Enviar fila de X
            }
        }
        // Calcular la primera fila para el proceso 0
        for (int j = 0; j < COL_RES; j++) {
            filaResultado[j] = 0;
            for (int k = 0; k < COLUMNAS; k++) {
                filaResultado[j] += X[0][k] * Y[k][j];
            }
        }
        for (int j = 0; j < COL_RES; j++) {
            Z[0][j] = filaResultado[j];
        }
    } else {
        // Recibir fila de la matriz X
        if (proceso_id - 1 < FILAS) {
            MPI_Recv(filaX, COLUMNAS, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // Multiplicar la fila recibida de X por la matriz Y
            for (int j = 0; j < COL_RES; j++) {
                filaResultado[j] = 0;
                for (int k = 0; k < COLUMNAS; k++) {
                    filaResultado[j] += filaX[k] * Y[k][j];
                }
            }
            // Enviar el resultado al proceso 0
            MPI_Send(filaResultado, COL_RES, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    // Ensamblar las filas en la matriz Z en el proceso 0
    if (proceso_id == 0) {
        for (int i = 1; i < num_procesos; i++) {
            if (i - 1 < FILAS) {
                MPI_Recv(Z[i], COL_RES, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

        // Imprimir la matriz resultante Z
        printf("Matriz resultante Z (%d x %d):\n", FILAS, COL_RES);
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COL_RES; j++) {
                printf("%d ", Z[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}