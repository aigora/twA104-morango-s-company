#include<stdio.h>
#include<stdlib.h>
int main() {
	int i, n;
	FILE *recibo;
	int precio = 5;
	errno_t err1;
	char* p;
	n = 12;
	p = (char *)malloc(n+1 * sizeof(char));
	fgets(p, n + 1, stdin);
	err1 = fopen_s(&recibo, "recibo.txt", "a+");
	if (err1 == 0)
		printf("funciona");
	else
		printf("no funciona");

	fprintf(recibo, "Recibo de su pedido:\n");
	fprintf(recibo, "%s: %d€\n", p, precio);
	fclose(recibo);
}

