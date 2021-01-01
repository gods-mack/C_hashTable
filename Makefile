
output: main.o hash_table.o
	gcc main.o hash_table.o -lm -o  output

main.o: main.c hash_table.c
	gcc -c main.c -lm

hash_table.o: hash_table.c hash_table.h
	gcc -c hash_table.c -lm

clean:
	rm *.o output				