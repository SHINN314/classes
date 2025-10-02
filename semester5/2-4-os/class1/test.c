#include <stdio.h>
#include <unistd.h>
int
main(int argc, char **argv)
{
         char buf[16];
         buf[0] = 'c';
         buf[1] = 'd';
         buf[15] = '\n';
         write(STDIN_FILENO, buf,16);
         write(2,"I major in Informatics.\n",24);
         return 0;
}