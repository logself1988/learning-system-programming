VPATH = src
CPPFLAGS = -I include


word_count: word_count.o counter.o lexer.o
	gcc -o $@ $^ -lfl 

word_count.o: word_count.c include/counter.h
	gcc $(CPPFLAGS) -c $<

counter.o: counter.c include/counter.h include/lexer.h
	gcc $(CPPFLAGS) -c $<

lexer.o: lexer.c include/lexer.h
	gcc -c $<

lexer.c: lexer.l
	flex -o $@ $<

clean:
	rm -f lexer.c *.o word_count
