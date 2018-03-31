part3:
	gcc print_help.o -o print_help
	gcc wallet_stat.c -o part3
clean:
	rm -f part3 print_help
