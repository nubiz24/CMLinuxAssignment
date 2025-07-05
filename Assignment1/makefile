all: main.c strutils.c strutils.h
	gcc -c strutils.c -o strutils.o
	ar rsc libstrutils.a strutils.o
	gcc main.c -L. -lstrutils -o main_static
	rm strutils.o
	gcc -fPIC -c strutils.c -o strutils.o
	gcc -shared -o libstrutils.so strutils.o
	export LD_LIBRARY_PATH=.
	gcc main.c -L. libstrutils.so -o main_shared

static: main.c strutils.c strutils.h
	gcc -c strutils.c -o strutils.o
	ar rsc libstrutils.a strutils.o
	gcc main.c -L. -lstrutils -o main_static

shared: main.c strutils.c strutils.h
	gcc -fPIC -c strutils.c -o strutils.o
	gcc -shared -o libstrutils.so strutils.o
	export LD_LIBRARY_PATH=.
	gcc main.c -L. libstrutils.so -o main_shared

clean:
	rm -f *.o *.a *.so
	find . -maxdepth 1 -type f -executable -exec rm -f {} \;