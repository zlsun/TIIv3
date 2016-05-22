
ROOT = $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

INCLUDE = -I$(ROOT)/include
CFLAGS = -g -Wall $(INCLUDE)
LDFLAGS = -L$(ROOT)/lib
LDLIBS = -lcliserv

MAKE = make --no-print-directory

color = \e[$1m$2\e[0m
title = echo -e "$(call color,1;31,$1) $2"

