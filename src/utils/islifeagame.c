#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>


int main(int argc, char *argv[])
{
  int A_; int B_; int C_; int D_; int _board; int _iters;
  A_ = atoi(argv[0]);
  B_ = atoi(argv[1]);
  C_ = atoi(argv[2]);
  D_ = atoi(argv[3]);
  _board = atoi(argv[4]);
  _iters = atoi(argv[5]);
  printf(" _iters: %d _A: %d _B: %d _C: %d _D: %d _board: %d \n", _iters, A_, B_, C_, D_, _board);

  return 0;
}
