
LD_FLAG = -lfl

TARGET_FLEX = ex_wc
TARGET_FLEX = ex_yy_decl

$(TARGET_FLEX): $(TARGET_FLEX).l
	flex -o $(TARGET_FLEX).c $<	# default lex.yy.c
	cc -o $@ $(TARGET_FLEX).c $(LD_FLAG)

clean:
	rm $(TARGET_FLEX).c $(TARGET_FLEX)
