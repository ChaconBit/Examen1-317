#include <stdio.h>

int suma(int a, int b) {
    return a + b;
}

int resta(int a, int b) {
    return a - b;
}

int multiplicacion(int a, int b) {
    return a * b;
}

float division(int a, int b) {
    if (b != 0) {
        return (float)a / b;
    } else {
        printf("No se puede hacer la división por cero\n");
        return 0;
    }
}

int main() {
    int a = 8; 
    int b = 4;  
    int c;
    float d;
    printf("los numeros son:\n a = %d \n b = %d\n\n",a,b);
    c = suma(a, b);
    printf("La suma es: %d\n",c);
    c = resta(a, b);
    printf("La resta es: %d\n", c);
    c = multiplicacion(a, b);
    printf("La multiplicacion es: %d\n",c);
    d = division(a, b);
    printf("La division es: %.2f\n", d); 
}
