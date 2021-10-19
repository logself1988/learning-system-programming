word_count: word_count.o lexer.o
	gcc -o word_count word_count.o lexer.o -lfl 

word_count.o: word_count.c
	gcc -c word_count.c

lexer.o: lexer.c
	gcc -c lexer.c

lexer.c: lexer.l
	flex -o lexer.c lexer.l

clean:
	rm -f lexer.c *.o word_count
