#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/array.c"


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

	int iter, height, width, living_init;
	fscanf(input_file, "%i %i %i %i", &iter, &height, &width, &living_init);

}

int leer_tablero(int linea_a_leer)
{
	FILE* tablero_inicial = fopen("tablero.txt", "r");
	int live_cells;
	fscanf(tablero_inicial, "%i", &live_cells);
	return 1;
}
