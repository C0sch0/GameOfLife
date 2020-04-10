#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void printboard(int D, int **board)
{
  printf("Proceso: \n");

  for (int i = 0; i < D; i++)
  {for (int j = 0; j < D; j++)
    {if (board[i][j] == 0)
      {printf("\u25A1 ");}
      else
      {printf("\u25A0 ");}
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
  if (y - 1 >= 0) {
    if (x-1>=0) {
      if (board[y-1][x-1] == 1) {sum++;}
    }
    if (x+1<D) {
      if (board[y-1][x+1] == 1) {sum++;}
    }
    if (board[y-1][x] == 1) {sum++;}
  }
  if (y + 1 < D) {
    if (x-1 >= 0) {
      if (board[y+1][x-1] == 1) {sum++;}
    }
    if (x+1 < D) {
      if (board[y+1][x+1] == 1) {sum++;}
    }
    if (board[y+1][x] == 1) {sum++;}
    }
  if (x - 1 >= 0) {
    if (board[y][x-1] == 1) {sum++;}
  }
  if (x + 1 > 0) {
    if (board[y][x+1] == 1) {sum++;}
  }
  return sum;
}

// globals
int** board;
int **next;
int D_;
FILE *output_file;
int iteracion_inicial;
char name[255];

void handler(int n)
{
  int cells = countcells(D_, board);
  // archivos
  output_file = fopen("output.csv", "a");
  printf("%s terminado por Señal. Tiempo de simulación: %d. %d células\n", name, iteracion_inicial - 1, cells);
  //printboard(D, board, name);
  fprintf(output_file, "%d, %d, SIGNAL\n", iteracion_inicial - 1, cells);
  fclose(output_file);

  for (int j = 0; j < D_; j++)
  {
    free(board[j]);
    free(next[j]);
  }
  free(board);
  free(next);
  raise(SIGTERM);
}


int main(int argc, char *argv[])
{
  output_file = fopen("output.csv", "a");
  // Recibimos los parametros iniciales
  int A_; int B_; int C_; int _board; int _iters;
  _iters = atoi(argv[0]);
  A_ = atoi(argv[1]);
  B_ = atoi(argv[2]);
  C_ = atoi(argv[3]);
  D_ = atoi(argv[4]);
  _board = atoi(argv[5]);
  //printf("init G.O.L.: _iters: %d _A: %d _B: %d _C: %d _D: %d _board: %d \n", _iters, A_, B_, C_, D_, _board);



  // ctrl + c:
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
          if(count == _board)
          {break;}
          count++;
        }

  // Cerrar archivo, parsear linea, llenar tablero
  fclose(tableros_);
  //printf("Tablero electo:%s", line);


  char* token;
  char* rest = line;
  const char s[2] = " ";
  /* Cuantas celulas vivas hay ???? */
  token = strtok(rest, s);
  int total_living_cells = atoi(token);
  //printf("total vivas: %d\n", total_living_cells);


  // popular el tablero
  int counter = 0;
  while (counter < total_living_cells) {
    char* X  = strtok(NULL, s);
    char* Y  = strtok(NULL, s);
    int Xi = atoi(X);
    int Yi = atoi(Y);
    //printf("X: %s Y: %s\n", X, Y);
    board[Yi][Xi] = 1;
    counter++;
    }

    // Creamos lo que sera la siguiente matriz
    next = malloc(sizeof(int*)*D_);
    for (int j = 0; j < D_; j++){next[j] = malloc(sizeof(int)*D_);}


  // Iniciar Game of Life
  iteracion_inicial = 0;
  int neighbors = 0;
  int state = 0;

  while(iteracion_inicial < _iters)
  {
    iteracion_inicial ++;
    if (countcells(D_, board) == 0)
    {
      printf("cantidad celulas: 0, iteraciones %d, razon termino: NOCELLS.\n", iteracion_inicial - 1);
      fprintf(output_file, "0, %d, NOCELLS\n", iteracion_inicial - 1);
      break;
    }


    /*
    ///// imprimir tablero ----------------------------
    printf("Proceso: \n");
    for (int i = 0; i < D_; i++)
    {for (int j =
      0; j < D_; j++){
        if (board[i][j] == 0)
        {printf("\u25A1 ");}
        else
        {printf("\u25A0 ");}
      }printf("\n");}printf("-------------------------------------\n");
      ///// imprimir tablero ----------------------------
      */

    // Chequear condiciones segun numero de vecinos para cada pos de matriz
    // Ir guardando esta informacion de cambio en una matriz aux
    // Reemplazar original por aux, limpiar aux, y seguir
    for (int x = 0; x < D_; x++)
    {
      for (int y = 0; y < D_; y++)
      {
        neighbors = countneighbors(D_, board, x, y);
        state = board[y][x];
        if (state == 0)
        {
          if (neighbors == A_) {
            //printf("nazco! vecinos :%d x:%d y:%d   %d\n", neighbors, x, y, iteracion_inicial );
            next[y][x] = 1;
          }
          else{
          //  printf("sobrevivo! vecinos :%d x:%d y:%d\n", neighbors, x, y );
            next[y][x] = state;
          }
        }
        else if (state == 1)
        {
          if (neighbors < B_ || neighbors > C_) {
            //printf("muero! tengo vecinos :%d x:%d y:%d\n", neighbors, x, y);
            next[y][x] = 0;
          }
          else{
          //  printf("sobrevivo! vecinos :%d x:%d y:%d\n", neighbors, x, y );
            next[y][x] = state;
          }
        }
      }
    }

    // Antes de cerrar este ciclo, reemplazo board -> next
    for (int i = 0; i < D_; i++)
    {
      for (int j = 0; j < D_; j++)
      {
        board[i][j] = next[i][j];
      }
    }

    for (int i = 0; i < D_; i++)
    {
      for (int j = 0; j < D_; j++)
      {
        next[i][j] = 0;
      }
    }

  }


  if (iteracion_inicial == _iters)
    {
      int count = countcells(D_, board);
      printf("NOTIME. Tiempo de simulación: %d. %d células\n", iteracion_inicial, count);
      fprintf(output_file, "%d, %d, NOTIME\n", count, iteracion_inicial);
      iteracion_inicial++;
    }

    //printf("%s\n", strerror(errno));

    fclose(output_file);
    return 0;
}
