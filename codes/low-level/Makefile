TARGETS = lib ch02 ch03
#TARGETS = lib ch03

all: $(TARGETS)
	for t in $(TARGETS); do \
		(echo "making $$t:" && $(MAKE) --directory=$$t all) || exit 1; \
	done

clean: $(TARGETS)
	for t in $(TARGETS); do \
		(echo "cleaing $$t:" && $(MAKE) --directory=$$t clean) || exit 1; \
	done
