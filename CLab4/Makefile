CC = gcc
CFLAGS = -g -Wall -Wno-unknown-pragmas -std=c89

default:	build_first

build_first:	lab4_1.o text_io.o
				$(CC) main4_1.o first_tasks_of_the_lab.o text_io.o -o clab4_1.exe
				del main4_1.o first_tasks_of_the_lab.o text_io.o

build_second:	lab4_2.o text_io.o m_number.o
				$(CC) main4_2.o second_task_of_the_lab.o text_io.o doubly_linked_list.o math_for_m_numbers.o -o clab4_2.exe
				del main4_2.o second_task_of_the_lab.o text_io.o doubly_linked_list.o math_for_m_numbers.o

text_io.o:	text_io.c
			$(CC) $(CFLAGS) -c text_io.c

m_number.o:	doubly_linked_list.c math_for_m_numbers.c
			$(CC) $(CFLAGS) -c doubly_linked_list.c math_for_m_numbers.c

lab4_1.o:	main4_1.c first_tasks_of_the_lab.c
			$(CC) $(CFLAGS) -c main4_1.c first_tasks_of_the_lab.c

lab4_2.o:	main4_2.c second_task_of_the_lab.c
			$(CC) $(CFLAGS) -c main4_2.c second_task_of_the_lab.c

run_first:
	clab4_1.exe

run_second:
	clab4_2.exe

clean_txts:
	del *.txt

clean_exes:
	del *.exe

clean_all:	clean_txts	clean_exes

lint_all:
	splint main4_1.c main4_2.c text_io.c first_tasks_of_the_lab.c second_task_of_the_lab.c doubly_linked_list.c math_for_m_numbers.c