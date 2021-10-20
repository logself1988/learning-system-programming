TARGETS = lib ch07
TARGETS = lib ch07

all: $(TARGETS)
	for t in $(TARGETS); do \
		(echo "making $$t" && $(MAKE) --directory=$$t) || exit 1; \
	done

clean: $(TARGETS)
	for t in $(TARGETS); do \
		(echo "cleaing $$t" && $(MAKE) --directory=$$t clean) || exit 1; \
	done
