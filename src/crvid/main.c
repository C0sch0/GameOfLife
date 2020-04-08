#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv)
{
	if(argc != 3) {
		printf("Modo de uso: %s <input.txt> <linea_n>\n", argv[0]);
		printf("\t input.txt : Nombre de archivo con definicion del problema.\n");
		printf("\t linea_n : lınea del archivo de entrada donde empezar a leer\n");
		return 1;
	}

	FILE* input_file = fopen(argv[1], "r");

	if (!input_file)
		{
			printf("¡El archivo %s no existe!\n", argv[1]);
			return 2;
		}

	int process_type;
	fscanf(input_file, "%i", &process_type);

	if(process_type == 0) {
		printf("I'm a generator");
	}
	if(process_type == 1) {
		printf("I'm a simulation");
		int iters; int board; int A; int B; int C; int D;
		fscanf(input_file, "%d %d %d %d %d %d \n", &iters, &A, &B, &C, &D, &board);

		printf(" iters: %d A: %d B: %d C: %d D: %d board: %d \n", iters, A, B, C, D, board);

		char As[10];
		char Bs[10];
		char Cs[10];
		char Ds[10];
		char boards[10];
		char iterss[10];

		sprintf(As, "%i", A);
		sprintf(Bs, "%i", B);
		sprintf(Cs, "%i", C);
		sprintf(Ds, "%i", D);
		sprintf(boards, "%i", board);
		sprintf(iterss, "%i", iters);

		char *const args[255] = {As, Bs, Cs, Ds, boards, iterss};
		execve("utils", args, NULL);
		printf("%s\n", strerror(errno));
	}

	fclose(input_file);

}

int leer_tablero(int linea_a_leer)
{
	FILE* tablero_inicial = fopen("tablero.txt", "r");
	int live_cells;
	fscanf(tablero_inicial, "%i", &live_cells);
	return 1;
}
