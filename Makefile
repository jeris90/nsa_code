CC=-pedantic -ansi


sem:main.c import.c parserASPARTIX.c nsa.c BH.c MT.c sem.h
	gcc $(CC) -o sem *.c -lm -g

clean:
	rm sem
