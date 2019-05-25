target:exe

exe:main.c epsLib.c epsLib.h
	gcc main.c epsLib.c -lm -o exe
	./exe