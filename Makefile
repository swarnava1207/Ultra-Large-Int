count_pairs.so : count_pairs.o
	gcc -shared -o count_pairs.so count_pairs.o