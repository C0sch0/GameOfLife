#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

int processes;
char path[255];

void alarm_handler(int signum)
{
    printf ("Times is up\n");

}

char nameoffile[255];
int main(int argc, char** argv)
{
	if(argc != 3) {
		printf("Debes ingresar: %s <input.txt> <linea_n>\n", argv[0]);
		printf("\t input.txt : Nombre de archivo con definicion del problema.\n");
		printf("\t linea_n : lınea del archivo de entrada donde empezar a leer\n");
		return 1;
	}
  strcpy(path, argv[1]);
  //printf("PATH: %s\n", path);
  int linea_a_leer = atoi(argv[2]);
  sprintf(nameoffile, "%s.csv", argv[2]);
  int aux = 0;
  char linea[256];
  FILE* input_file = fopen(path, "r");
	//printf("path%s\n", path);
  //printf("linea %d\n", linea_a_leer);

	if (!input_file)
		{printf("¡El archivo %s no existe!\n", path);
			return 2;}

	while (fgets(linea, sizeof(linea), input_file)) {
					if(aux == linea_a_leer)
					{break;}
					aux++;
	}

	char* _token;
	char* linea_electa = linea;
	char var[2] = " ";
	_token = strtok(linea_electa, var);
	int process_type = atoi(_token);
	//printf("type: %d\n", process_type);
  int n_subprocesos = 0;


	if(process_type == 0) {
		int tiempo = atoi(strtok(NULL, var));
		n_subprocesos = atoi(strtok(NULL, var));
		//printf("I'm a generator \n");
		//printf("time: %d subprocc: %d\n", tiempo, n_subprocesos);

    signal (SIGALRM, alarm_handler);
    alarm(tiempo);

		pid_t pid;
		for (int n = 0; n < n_subprocesos; n++){
			pid = fork();
			if (pid < 0) {
				fprintf(stderr, "Fork Failed");
				return 1;
			}

			else if (pid == 0) {
				char linea_subprocess[255];
        strcpy(linea_subprocess,strtok(NULL, var));
        printf("linea: %s\n", linea_subprocess);
				execlp("./crvid", "./crvid", path, linea_subprocess, NULL);
        printf("%s\n", strerror(errno));
				}
      else if (pid > 0) {
        printf("I'm the parent %d \n", pid);

        }
      }
		}

	else if(process_type == 1) {

		printf("I'm a simulation");
		int iters = atoi(strtok(NULL, var));
		int A= atoi(strtok(NULL, var));
		int B= atoi(strtok(NULL, var));
		int C= atoi(strtok(NULL, var));
		int D= atoi(strtok(NULL, var));
		int board= atoi(strtok(NULL, var));
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

		char *const args[255] = {iterss, As, Bs, Cs, Ds, boards, nameoffile};
		execve("utils", args, NULL);
	}

  //parent process
  for (int child = 0; child < n_subprocesos; child++)
  {
    wait(NULL);
  }

	fclose(input_file);

}
