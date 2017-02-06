# C compiler and flags
CC = gcc
CFLAGS_INC_PGPLOT =# define if needed (as -I[...])
CFLAGS = -std=gnu99 -pedantic -Wall -fPIC $(CFLAGS_INC_PGPLOT)
CFLAGS_C_DEBUG = $(CFLAGS) -g
CFLAGS_C_RELEASE = $(CFLAGS) -O3
ifeq ($(OPT_DEBUG), yes)
CFLAGS_C = $(CFLAGS_C_DEBUG)
else
CFLAGS_C = $(CFLAGS_C_RELEASE)
endif

# enable/disable the debug flag
ifeq ($(OPT_DEBUG), yes)
DDEBUG = -DDEBUG
endif

LFLAGS_PGPLOT_DIR =# define if not in $PATH (as -L[...])
LFLAGS = -lm $(LFLAGS_PGPLOT_DIR) -lcpgplot -lpgwrap

all: test

test: test.c
	$(CC) $(CFLAGS_C) $(DDEBUG) $< $(LFLAGS) -o $@
	# doesn't work -> $(CC) $(CFLAGS_C) $(DDEBUG) $(LFLAGS) $< -o $@

