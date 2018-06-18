EXEC = main
CC = gcc
CFLAGS = -g -Wall

main: Polinomio.o PolParser.o main.o
	$(CC) $(CFLAGS) Polinomio.o PolParser.o main.o -o $(EXEC)

Polinomio.o: Polinomio.c
	$(CC) $(CFLAGS) -c Polinomio.c -o Polinomio.o

PolParser.o: PolParser.c
	$(CC) $(CFLAGS) -c PolParser.c -o PolParser.o

clean:
	-rm -f *.o
	-rm -f $(EXEC)
