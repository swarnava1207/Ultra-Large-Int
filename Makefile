count_pairs.so : count_pairs.c
	gcc -fPIC -shared -O3 -o count_pairs.so count_pairs.c ultra.c
clean :
	rm -f count_pairs.so
