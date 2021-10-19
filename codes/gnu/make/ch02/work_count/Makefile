word_count: word_count.o lexer.o
	gcc -o $@ $^ -lfl 

word_count.o: word_count.c
	gcc -c $<

lexer.o: lexer.c
	gcc -c $<

lexer.c: lexer.l
	flex -o $@ $<

clean:
	rm -f lexer.c *.o word_count
