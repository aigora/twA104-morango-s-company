#include<stdio.h>
#include<stdlib.h>
struct recibo {
	int precio;
	char* p;
};
int main() {
	int n;
	FILE *recibo;
	struct recibo cliente;
	cliente.precio = 5;
	errno_t err1;
	n = 12;
	cliente.p = (char *)malloc(n+1 * sizeof(char));
	fgets(cliente.p, n + 1, stdin);
	err1 = fopen_s(&recibo, "recibo.txt", "a+");
	if (err1 == 0)
		printf("funciona");
	else
		printf("no funciona");

	fprintf(recibo, "Recibo de su pedido:\n");
	fprintf(recibo, "%s: %d€\n", cliente.p, cliente.precio);
	fclose(recibo);
}

