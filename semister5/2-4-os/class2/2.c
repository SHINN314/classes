#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void use_printf() {
  printf("Hello\t");
  sleep(5);
}

void use_write() {
  write(1, "Hello\t", 6);
  sleep(5);
  write(1, "World\n", 7);
}

int main()
{
  printf("Using printf:\n");
  use_printf();
  printf("Using write:\n");
  use_write();
  return 0;
}