rm ./mod_test.so
gcc -Wall -fPIC -c mod_test.c
gcc -shared -Wl,-soname,mod_test.so.1 -o mod_test.so   *.o
rm ./mod_test.o

