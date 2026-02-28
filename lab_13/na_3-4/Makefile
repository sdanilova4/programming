.PHONY: clean

all: coffee_exe

coffee_exe: main.o libCOFFEE.so
	gcc main.o -o coffee_exe -L. -lCOFFEE -Wl,-rpath,.

main.o: src/main.c
	gcc -c src/main.c -o main.o -I ./include

coffeehouse.o: src/coffeehouse.c
	gcc -c src/coffeehouse.c -o coffeehouse.o -I ./include -fPIC 

libCOFFEE.so: coffeehouse.o
	gcc -shared coffeehouse.o -o libCOFFEE.so

clean:
	rm -rf *.o *.so coffee_exe

run: all
	./coffee_exe