#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void printboard(int D, int **board)
{
  printf("Proceso: \n");

  for (int i = 0; i < D; i++)
  {
    for (int j = 0; j < D; j++)
    {
      if (board[i][j] == 0)
      {
        printf("\u25A1 ");
      }
      else
      {
        printf("\u25A0 ");
      }
    }
    printf("\n");
  }
  printf("-------------------------------------\n");
}

int countcells(int D, int **board)
{
  int sum = 0;
  for (int i = 0; i < D; i ++)
  {
    for (int j = 0; j < D; j++)
    {
      if (board[i][j] == 1)
      {
        sum ++;
      }
    }
  }
  return sum;
}

int countneighbors(int D, int **board, int x, int y)
{
  int sum = 0;
  if (x != 0) {if (board[y][x-1] == 1){sum++;}}
  if (y != 0) {if (board[y-1][x] == 1){sum++;}}
  if (y+1 != D){if (board[y+1][x] == 1){sum++;}}
  if (x+1 != D){if (board[y][x+1] == 1){sum++;}}

  return sum;
}


// variables globales
int tsim;
int cells;
char name[255];
char aux[255];
FILE* output_file;
FILE* aux_txt;
int** board;
int **next;
int del;


void handler(int n)
{

}


int main(int argc, char *argv[])
{
  // Recibimos los parametros iniciales
  int A_; int B_; int C_; int D_; int _board; int _iters;
  A_ = atoi(argv[0]);
  B_ = atoi(argv[1]);
  C_ = atoi(argv[2]);
  D_ = atoi(argv[3]);
  _board = atoi(argv[4]);
  _iters = atoi(argv[5]);
  printf(" GOF: _iters: %d _A: %d _B: %d _C: %d _D: %d _board: %d \n", _iters, A_, B_, C_, D_, _board);


  // handler para recibir la senal de CONTROL + C
  struct sigaction sign;
  sign.sa_handler = handler;
  sigaction(SIGINT, &sign, NULL);

  // Inicializamos un tablero con el tamano recibido
  board = malloc(sizeof(int*)*D_);
  for (int j = 0; j < D_; j++){board[j] = malloc(sizeof(int)*D_);}

  // Llenamos de 0s
  for (int i = 0; i < D_; i++){for (int j = 0; j < D_; j++){board[i][j] = 0;}}

  // Inicializamos celulas vivas, leyendo del tablero
  // Abrir archivo, sacar la linea pedida
  FILE* tableros_ = fopen("tableros.txt", "r");

  if (!tableros_){printf("No pille los tableros!\n");return 2;}

    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), tableros_)) {
            printf("%d %d\n", count, _board);
            if(count == _board)
            {
                break;
            }
            count++;
          }

  // Cerrar archivo, parsear linea, llenar tablero
  fclose(tableros_);
  printf("linea es %s", line);


  char* token;
  char* rest = line;
  const char s[2] = " ";
  /* Cuantas celulas vivas hay ???? */
  token = strtok(rest, s);
  int total_living_cells = atoi(token);
  printf("total: %d\n", total_living_cells);


  // popular el tablero
  int counter = 0;
  while (counter < total_living_cells) {
    char* X  = strtok(NULL, s);
    char* Y  = strtok(NULL, s);
    int Xi = atoi(X);
    int Yi = atoi(Y);
    printf("X: %s Y: %s\n", X, Y);
    board[Yi][Xi] = 1;
    counter++;
    }

    // Creamos lo que sera la siguiente matriz
    next = malloc(sizeof(int*)*D_);
    for (int j = 0; j < D_; j++){next[j] = malloc(sizeof(int)*D_);}


  // Iniciar Game of Life

  int iteracion_inicial;
  iteracion_inicial = 0;

  int neighbors;
  int state;

  while(iteracion_inicial < _iters)
  {
    iteracion_inicial ++;
    // Habran muerto todos ?
    if (countcells(D_, board) == 0)
    {
      printf("%s NOCELLS. Tiempo de simulación: %d. \n", name, iteracion_inicial - 1);
      fprintf(output_file, "%s,%d,%d,NOCELLS\n", name, iteracion_inicial - 1, 0);
      break;
    }

    ///// imprimir tablero ----------------------------

    printf("Proceso: \n");
    for (int i = 0; i < D_; i++)
    {for (int j = 0; j < D_; j++){
        if (board[i][j] == 0)
        {printf("\u25A1 ");}
        else
        {printf("\u25A0 ");}
      }printf("\n");}printf("-------------------------------------\n");
      ///// imprimir tablero ----------------------------


    // count neighbors
    for (int x = 0; x < D_; x++)
    {
      for (int y = 0; y < D_; y++)
      {
        neighbors = countneighbors(D_, board, x, y);
        state = board[y][x];
        if (state == 0 && neighbors == A_)
        {
          next[y][x] = 1;
        }
        else if (state == 1 && (neighbors < B_ || neighbors > C_))
        {next[y][x] = 0;}
        else
        {next[y][x] = state;}
      }
    }
    printf("%s\n", strerror(errno));




    // Antes de cerrar este ciclo, reemplazo board -> next
    for (int i = 0; i < D_; i++)
    {
      for (int j = 0; j < D_; j++)
      {
        board[i][j] = next[i][j];
      }
    }


  }
  if (iteracion_inicial == _iters)
    {
      //printf("Entro al iff\n");
      int count = countcells(D_, board);
      //printf("%s - celulas %d\n", name, count);
      printf("%s Término por alcanzar tiempo máximo. Tiempo de simulación: %d. %d células\n", name, tsim, count);
      fprintf(output_file, "%s,%d,%d,NOTIME\n", name, tsim, count);
    }



    fclose(output_file);
    return 0;
}
