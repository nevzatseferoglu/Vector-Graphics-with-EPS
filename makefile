target:exe

exe:main.c epsLib.c headers/epsLib.h
	gcc main.c epsLib.c -lm -o exe
	./exe