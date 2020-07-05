# barr: main.o barr.o
# 	gcc -pthread main.o $@.o -o $@ 

barr: main.o barr.o array.o
	gcc -o barr -pthread main.o barr.o array.o

main.o: main.c
	gcc -c main.c

barr.o: barr.c
	gcc -c -pthread barr.c
	
array.o: array.c
	gcc -c array.c