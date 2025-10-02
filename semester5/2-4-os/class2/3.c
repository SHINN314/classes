#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
char buf[] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
int
main(int argc, char **argv)
{
  int size, n, i;
  if (argc < 3)
    return 1;
  size = atoi(argv[1]);
  n = atoi(argv[2]);
  if (n > 20)
    return 1;
  for (i = 0; i < size; i += n)
    write(1,buf,n);
  return 0;
}