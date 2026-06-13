default:
	clang -g -Wall -o bin/prog src/main.c

clean:
	rm -f bin/*

run:
	./bin/prog
