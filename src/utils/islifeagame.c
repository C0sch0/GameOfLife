#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

// variables globales
int tsim;
int cells;
char name[255];
char aux[255];
FILE* output_file;
FILE* aux_txt;
int D;
int** board;
int **next;
int **prev1;
int **prev2;
int **prev3;
int **prev4;
int del;


void handler(int n)
{

}


int main(int argc, char *argv[])
{
  int A_; int B_; int C_; int D_; int _board; int _iters;
  A_ = atoi(argv[0]);
  B_ = atoi(argv[1]);
  C_ = atoi(argv[2]);
  D_ = atoi(argv[3]);
  _board = atoi(argv[4]);
  _iters = atoi(argv[5]);
  //printf(" _iters: %d _A: %d _B: %d _C: %d _D: %d _board: %d \n", _iters, A_, B_, C_, D_, _board);


  // CONTROL + C:
  struct sigaction sign;
  sign.sa_handler = handler;
  sigaction(SIGINT, &sign, NULL);


  board = malloc(sizeof(int*)*D);
  for (int j = 0; j < D; j++)
  {
    board[j] = malloc(sizeof(int)*D);
  }


  return 0;
}
