#include "stdio.h"
int suma(int *a, int *b)
{
  return *a + *b;
}
int resta(int *a, int *b)
{
  return *a - *b;
}
int multi(int *a, int *b)
{
  return *a * *b;
}
int div(int *a, int *b)
{
    return *a / *b;
}
void main ()
{
  int a,b;
  printf("Introduce un numero a:");
  scanf("%d", &a);
  printf("Introduce un numero b:");
  scanf("%d", &b);
  printf("La suma es: %d \n",suma(&a,&b));
  printf("La resta es: %d \n",resta(&a,&b));
  printf("La multiplicacion es: %d \n",multi(&a,&b));
  if (b != 0)
    printf("La division es: %d \n",div(&a,&b));
  else
    printf("No existe division entre cero \n");
}
