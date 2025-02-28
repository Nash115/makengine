main: main.o
	gcc -o makengine main.o

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o