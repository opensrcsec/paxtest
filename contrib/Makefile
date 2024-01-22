CHPAXVER := 0.7
CHPAXDIR := chpax-$(CHPAXVER)

check_prog = $(shell if which "$1" >/dev/null 2>&1 ; \
	then echo "$1"; else echo "$2"; fi)

# check for installed binaries
ifeq ($(call check_prog chpax),)
TARGETS += chpax
endif

all: $(TARGETS)

clean:
	cd $(CHPAXDIR) && $(MAKE) fclean
	rm -f chpax

chpax:
	cd $(CHPAXDIR) && $(MAKE)
	ln -s $(CHPAXDIR)/$@

.PHONY: all clean
