VPATH = src
CPPFLAGS = -I include

SOURCES = word_count.c lexer.c counter.c

word_count: counter.o lexer.o -lfl
word_count.o: include/counter.h
counter.o: include/counter.h include/lexer.h
lexer.o: include/lexer.h

# 手动生成依赖
# depend: $(SOURCES)
# 	$(CC) -M $(CPPFLAGS) $^ > $@

# include depend

# 自动生成依赖

# 包含Makefile
include $(subst .c,.d,$(SOURCES))

%.d: %.c
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -rf $@.$$$$

clean:
	rm -f lexer.c *.o word_count depend *.d
