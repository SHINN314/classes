all: tz

CC = gcc
CFLAGS = -O3 -std=gnu11 -Wall

main: main.tex
	platex $@
	dvipdfmx -p a4 $@

tz: tz.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

tz.o: tz.c
	$(CC) $(CFLAGS) -c $^

simpson: simpson.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

simpson.o: simpson.c
	$(CC) $(CFLAGS) -c $^

simpson_2: simpson_2.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

simpson_2.o: simpson_2.c
	$(CC) $(CFLAGS) -c $^


clean:
	rm -f main.{aux,dvi,log,pdf} tz *.o *~
