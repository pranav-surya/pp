default: main
main: main.c
	gcc -o main main.c
clean:
	rm -rf main