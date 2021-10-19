VPATH = src
CPPFLAGS = -I include

SOURCES = word_count.c lexer.c counter.c

word_count: libcounter.a -lfl

libcounter.a: libcounter.a(lexer.o) libcounter.a(counter.o)
	$(RANLIB) $@ # 生成归档索引

libcounter.a(lexer.o): lexer.o
	$(AR) $(ARFLAGS) $@ $<

libcounter.a(counter.o): counter.o
	$(AR) $(ARFLAGS) $@ $<

word_count.o: include/counter.h
counter.o: include/counter.h include/lexer.h
lexer.o: include/lexer.h

clean:
	rm -f lexer.c *.o word_count *.a
