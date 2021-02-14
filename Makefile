.PHONY: all rwmain clean

all: rwmain

rwmain: main.c
	gcc -pthread -o rwmain main.c

clean:
	rm rwmain