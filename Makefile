target:run

run:draw_bst_test.c src/epsLib.c src/bst.c src/headers/epsLib.h
	gcc draw_bst_test.c src/epsLib.c src/bst.c -lm -o run
	./run
