#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv)
{
	if(argc != 3) {
		printf("Debes ingresar: %s <input.txt> <linea_n>\n", argv[0]);
		printf("\t input.txt : Nombre de archivo con definicion del problema.\n");
		printf("\t linea_n : lınea del archivo de entrada donde empezar a leer\n");
		return 1;
	}

	FILE* input_file = fopen(argv[1], "r");

	if (!input_file)
		{printf("¡El archivo %s no existe!\n", argv[1]);
			return 2;}

	int process_type;
	fscanf(input_file, "%i", &process_type);

	if(process_type == 0) {

		int tiempo; int n_subprocesos;
		fscanf(input_file, "%d %d \n", &tiempo, &n_subprocesos);
		
		pid_t pid;
		printf("I'm a generator");
		pid = fork();
		if (pid < 0) {
			fprintf(stderr, "Fork Failed");
			return 1;
			}
		}

	if(process_type == 1) {
		printf("I'm a simulation");
		int iters; int board; int A; int B; int C; int D;
		fscanf(input_file, "%d %d %d %d %d %d \n", &iters, &A, &B, &C, &D, &board);

		//printf(" iters: %d A: %d B: %d C: %d D: %d board: %d \n", iters, A, B, C, D, board);

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

		char *const args[255] = {iterss, As, Bs, Cs, Ds, boards};
		execve("utils", args, NULL);
	}

	fclose(input_file);

}
