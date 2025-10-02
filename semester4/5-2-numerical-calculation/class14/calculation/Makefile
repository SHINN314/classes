all: euler lorenz pendulum

CC = gcc
CFLAGS = -O3 -std=gnu11 -Wall

main: main.tex
	platex $@
	dvipdfmx -p a4 $@

euler: euler.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

lorenz: lorenz.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

pendulum: pendulum.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f *.o *~ euler lorenz pendulum main.{aux,dvi,log}
