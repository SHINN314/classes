#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
  int size, n, i;
  if (argc < 2)
    return 1;
  size = atoi(argv[1]);
  for (i = 0; i < size; i++)
    printf("\n");
  return 0;
}