
LD_FLAG = -lfl

# TARGET_FLEX = ex_wc
# TARGET_FLEX = ex_print_tokens
TARGET_FLEX = ex_print_tokens2

TARGET_FLEX_BISON = ex_calc

$(TARGET_FLEX): $(TARGET_FLEX).l
	flex -o $(TARGET_FLEX).c $<	# default lex.yy.c
	cc -o $@ $(TARGET_FLEX).c $(LD_FLAG)

$(TARGET_FLEX_BISON): $(TARGET_FLEX_BISON).y $(TARGET_FLEX_BISON).l
	bison -d $(TARGET_FLEX_BISON).y  # *.tab.h, *.tab.c
	flex -o $(TARGET_FLEX_BISON).lex.c $(TARGET_FLEX_BISON).l
	cc -o $@ $(TARGET_FLEX_BISON).tab.c $(TARGET_FLEX_BISON).lex.c $(LD_FLAG)

clean:
	rm $(TARGET_FLEX).c $(TARGET_FLEX) $(TARGET_FLEX_BISON) $(TARGET_FLEX_BISON).c $(TARGET_FLEX_BISON).tab*
