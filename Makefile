
include common.mk

DIRS = lib $(wildcard chap??)

all clean:
	@for i in $(DIRS); do         \
		$(call title,Making,$$i); \
		$(MAKE) -C $$i $@;        \
	done

