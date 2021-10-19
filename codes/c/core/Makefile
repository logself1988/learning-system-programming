TARGETS = ch01 ch02 ch03 ch04 ch05 ch06 ch07 ch08
#TARGETS = ch08

all: $(TARGETS)
	for t in $(TARGETS); do \
		(echo "making $$t" && $(MAKE) --directory=$$t) || exit 1; \
	done

clean: $(TARGETS)
	for t in $(TARGETS); do \
		(echo "cleaing $$t" && $(MAKE) --directory=$$t clean) || exit 1; \
	done