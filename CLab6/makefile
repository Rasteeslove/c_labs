default: build run clean

build:	main.c task.c str_io.c bin_tree.c stack.c
		gcc -Wall -Wno-unknown-pragmas main.c task.c str_io.c bin_tree.c stack.c -o clab6.exe

run:
	clab6.exe

clean:
	del clab6.exe

#lint_all:
#	splint main.c task.c str_io.c bin_tree.c stack.c