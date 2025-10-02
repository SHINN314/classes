#include <stdio.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char **argv) {
  time_t now;

  time(&now);
  printf("now = %ld\n", now);
  
  sleep(5);

  time(&now);
  printf("now = %ld\n", now);

  return 0;

}