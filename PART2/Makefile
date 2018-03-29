part2: main.o solver trace fib 
	gcc -o part2 main.o
main.o: main.c
	gcc -c main.c
solver: solver.c
	gcc solver.c -o solver -lm
trace: trace.c
	gcc trace.c -o trace
fib: fib.c
	gcc fib.c -o fib
clean:
	rm -f part2 solver trace fib
