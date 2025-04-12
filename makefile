makengine: main.o warnings.o utils.o compilation.o settings.o
	gcc -o makengine main.o warnings.o utils.o compilation.o settings.o

main.o: src/main.c
	gcc -g -Wall -c src/main.c

warnings.o: src/warnings.c
	gcc -g -Wall -c src/warnings.c

utils.o: src/utils.c
	gcc -g -Wall -c src/utils.c

compilation.o: src/compilation.c
	gcc -g -Wall -c src/compilation.c

settings.o: src/settings.c
	gcc -g -Wall -c src/settings.c

clean:
	rm -f *.o