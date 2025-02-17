main: main.o generalfuncs.o initiating.o preprocess.o firstPass.o secondPass.o
	gcc -Wall -ansi -pedantic main.o generalfuncs.o initiating.o preprocess.o firstPass.o secondPass.o -o assembler
main.o: main.c general.h generalFuncs.h
	gcc -c -Wall -ansi -pedantic main.c -o main.o 
generalfuncs.o: generalfuncs.c general.h
	gcc -c -Wall -ansi -pedantic generalfuncs.c -o generalfuncs.o 
initiating.o: initiating.c general.h initiating.h
	gcc -c -Wall -ansi -pedantic initiating.c -o initiating.o
preprocess.o: preprocess.c general.h preprocess.h
	gcc -c -Wall -ansi -pedantic preprocess.c -o preprocess.o
firstPass.o: firstPass.c general.h firstPass.h
	gcc -c -Wall -ansi -pedantic firstPass.c -o firstPass.o
secondPass.o: secondPass.c general.h secondPass.h
	gcc -c -Wall -ansi -pedantic secondPass.c -o secondPass.o
