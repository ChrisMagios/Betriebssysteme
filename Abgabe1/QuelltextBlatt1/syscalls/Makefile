hello: main.o hello.o
	gcc main.o $@.o -o $@ 
	
.c.o: main.c hello.h
	$(CC) -c $*.c
	
.c.o: hello.c hello.h
	$(CC) -c $*.c
