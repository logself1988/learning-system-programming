
LD_FLAG = -lfl

# TARGET_FLEX = ex_wc_file
# TARGET_FLEX = ex_wc_files
# TARGET_FLEX = ex_c_include
TARGET_FLEX = ex_c_cross_reference

$(TARGET_FLEX): $(TARGET_FLEX).l
	flex -o $(TARGET_FLEX).c $<	# default lex.yy.c
	cc -o $@ $(TARGET_FLEX).c $(LD_FLAG)

clean:
	rm $(TARGET_FLEX).c $(TARGET_FLEX)
