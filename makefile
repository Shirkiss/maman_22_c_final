mymat:mymat.o mat.o handle_text_functions.o
	gcc -g -ansi -pedantic -Wall -o mymat mymat.o mat.o handle_text_functions.o

mymat.o:mymat.c mat.h
	gcc -g -ansi -pedantic -Wall -c mymat.c
mat.o:mat.c mat.h
	gcc -g -ansi -pedantic -Wall -c mat.c
handle_text_functions.o : handle_text_functions.c mat.h
	gcc -g -ansi -pedantic -Wall -c handle_text_functions.c
