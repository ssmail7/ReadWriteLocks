# ReadWriteLocks

For a detailed description of this project, please refer to Project 3 - RWLocks.pdf

HOW TO COMPILE

A. To compile program using Makefile (from Terminal):
	From the directory containing Makefile, main.c, readerwriter.c, & scenarios.txt:
		Type "make"
	(** Makefile will compile main.c & readerwriter.c into rwmain.exec **)

B. To compile programs manually (from Terminal):

	For main.c & readerwriter.c:
		Type "gcc -pthread -o rwmain main.c"


HOW TO RUN

Once the files have been compiled,

	For rwmain (w/ scenarios.txt in the same directory):
		Type "./rwmain"


HOW TO CLEAN (Remove rwmain)

	From the directory containing Makefile & rwmain:
		Type "make clean"
	(** Makefile will remove rwmain **)
