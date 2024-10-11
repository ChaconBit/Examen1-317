#include <stdio.h>

void calcular_pi_iterativo(int *num_terminos, double *pi) {
    double pi_local = 0.0;
    for (int n = 0; n < *num_terminos; n++) {
        int signo = (n % 2 == 0) ? 1 : -1;  // Determina el signo
        int denominador = 2 * n + 1;        // Calcula el denominador
        pi_local += signo * (1.0 / denominador);  // Suma o resta el término
    }
    *pi = 4 * pi_local;  // Multiplicamos por 4 para obtener el valor de pi
}

int main() {
    int num_terminos;
    double pi;

    printf("Ingrese el numero de terminos: ");
    scanf("%d", &num_terminos);

    calcular_pi_iterativo(&num_terminos, &pi);

    printf("Valor aproximado de pi (iterativo): %lf\n", pi);

    return 0;
}
