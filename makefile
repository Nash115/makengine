makengine: main.o warnings.o utils.o compilation.o
	gcc -o makengine main.o warnings.o utils.o compilation.o

main.o: src/main.c
	gcc -c src/main.c

warnings.o: src/warnings.c
	gcc -c src/warnings.c

utils.o: src/utils.c
	gcc -c src/utils.c

compilation.o: src/compilation.c
	gcc -c src/compilation.c

clean:
	rm -f *.o