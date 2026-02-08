# build static lib

gcc main.c coffeehouse.c -o app -I.

gcc -c main.c

gcc -c coffeehouse.c

gcc main.o coffeehouse.o

ar rc libCOFFEE.a coffeehouse.o

gcc main.o -o coffe_exe -L. -lCOFFE

./coffe_exe

