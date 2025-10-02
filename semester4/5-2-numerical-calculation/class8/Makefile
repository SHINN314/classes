all: lu

CC = gcc
CFLAGS = -O3 -std=gnu11 -Wall

main: main.tex
	platex $@
	dvipdfmx -p a4 $@

lu: lu.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

lu.o: lu.c
	$(CC) $(CFLAGS) -c $<

es: equetion_solution.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

es.o: equetion_solution.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *~

distclean: clean
	rm -rf lu main.{aux,dvi,log}
