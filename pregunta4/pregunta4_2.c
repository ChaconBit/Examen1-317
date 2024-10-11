#include <stdio.h>

double calcular_pi_recursivo(int *num_terminos, int n, double pi_local) {
    if (n == *num_terminos) {
        return pi_local;  // Condición de parada
    }

    int signo = (n % 2 == 0) ? 1 : -1;  // Determina el signo
    int denominador = 2 * n + 1;        // Calcula el denominador
    pi_local += signo * (1.0 / denominador);  // Suma o resta el término

    return calcular_pi_recursivo(num_terminos, n + 1, pi_local);  // Llamada recursiva
}

int main() {
    int num_terminos;
    double pi;

    printf("Ingrese el numero de terminos: ");
    scanf("%d", &num_terminos);

    pi = 4 * calcular_pi_recursivo(&num_terminos, 0, 0.0);  // Llama a la función recursiva

    printf("Valor aproximado de pi (recursivo): %lf\n", pi);

    return 0;
}
