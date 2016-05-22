
include ../common.mk

srcs=$(wildcard *.c)
objs=$(srcs:.c=.o)
exes=$(objs:.o=)

all: $(exes)

clean:
	$(RM) $(objs) $(exes)

