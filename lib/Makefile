
include ../common.mk

srcs=$(wildcard *.c)
objs=$(srcs:.c=.o)
lib=libcliserv.a

all: $(lib)

$(lib): $(objs)
	$(AR) rv $@ $?

clean:
	$(RM) $(lib) *.o

