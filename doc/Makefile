TARGETS := paxtest.1

all: $(TARGETS)

%.1: %.sgml
	docbook-to-man $< > $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean
