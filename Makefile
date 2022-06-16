all : hof hof2

hof : hof.c
	gcc -o hof hof.c

hof2 : hof2.c
	gcc -o hof2 hof2.c

clean :
	rm hof hof2
