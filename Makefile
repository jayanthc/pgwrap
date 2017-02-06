#
# Makefile for pgwrap
#
# Created by Jayanth Chennamangalam on 2012.03.02
#

# C compiler and flags
CC = gcc
ifeq ($(shell uname), Darwin)
CFLAGS_INC_PGPLOT =-I/opt/local/include# define if needed (as -I[...])
else
CFLAGS_INC_PGPLOT =# define if needed (as -I[...])
endif
CFLAGS = -std=gnu99 -pedantic -Wall -fPIC $(CFLAGS_INC_PGPLOT)
CFLAGS_C_DEBUG = $(CFLAGS) -g -c
CFLAGS_C_RELEASE = $(CFLAGS) -O3 -c
ifeq ($(OPT_DEBUG), yes)
CFLAGS_C = $(CFLAGS_C_DEBUG)
else
CFLAGS_C = $(CFLAGS_C_RELEASE)
endif

# enable/disable the debug flag
ifeq ($(OPT_DEBUG), yes)
DDEBUG = -DDEBUG
endif

# directories
SRCDIR = src
MANDIR = man
LIBDIR = lib
# header file installation directory - modify if needed
INCINSTALLDIR = /usr/local/include
# library installation directory - modify if needed
LIBINSTALLDIR = /usr/local/lib
# man page installation directory - modify if needed
MANINSTALLDIR = /usr/local/share/man/man3

# copgwrapand definitions
DELCMD = rm

ifeq ($(shell uname), Darwin)
all: colourmap.o                                                              \
	 pgwrap.o                                                                 \
	 libpgwrap.a                                                              \
	 libpgwrap.1.dylib
else
all: colourmap.o                                                              \
	 pgwrap.o                                                                 \
	 libpgwrap.a                                                              \
	 libpgwrap.so.1
endif

colourmap.o: $(SRCDIR)/colourmap.c                                            \
		     $(SRCDIR)/pgwrap.h
	$(CC) $(CFLAGS_C) $< -o $(LIBDIR)/$@

pgwrap.o: $(SRCDIR)/pgwrap.c                                                  \
		  $(SRCDIR)/pgwrap.h
	$(CC) $(CFLAGS_C) $(SRCDIR)/pgwrap.c -o $(LIBDIR)/$@

libpgwrap.a: $(LIBDIR)/pgwrap.o $(LIBDIR)/colourmap.o
	ar cr $(LIBDIR)/$@ $^

ifeq ($(shell uname), Darwin)
libpgwrap.1.dylib: $(LIBDIR)/pgwrap.o $(LIBDIR)/colourmap.o
	ld -dylib -macosx_version_min 10.12 -undefined dynamic_lookup -o $(LIBDIR)/$@ -lc $^
else
libpgwrap.so.1: $(LIBDIR)/pgwrap.o $(LIBDIR)/colourmap.o
	ld -shared -soname $@ -o $(LIBDIR)/$@ -lc $^
endif

# install the library and man pages
install:
	@echo Copying libraries...
	cp $(SRCDIR)/pgwrap.h $(INCINSTALLDIR)
ifeq ($(shell uname), Darwin)
	cp $(LIBDIR)/libpgwrap.1.dylib $(LIBINSTALLDIR)
	ln -sf $(LIBINSTALLDIR)/libpgwrap.1.dylib $(LIBINSTALLDIR)/libpgwrap.dylib
else
	cp $(LIBDIR)/libpgwrap.so.1 $(LIBINSTALLDIR)
	ln -sf $(LIBINSTALLDIR)/libpgwrap.so.1 $(LIBINSTALLDIR)/libpgwrap.so
	ldconfig
endif
	@echo DONE
	#@echo Copying man pages...
	#cp $(MANDIR)/*.1 $(MANINSTALLDIR)
	#@echo DONE

clean:
	$(DELCMD) $(LIBDIR)/colourmap.o
	$(DELCMD) $(LIBDIR)/pgwrap.o
	$(DELCMD) $(LIBDIR)/libpgwrap.a
ifeq ($(shell uname), Darwin)
	$(DELCMD) $(LIBDIR)/libpgwrap.1.dylib
else
	$(DELCMD) $(LIBDIR)/libpgwrap.so.1
endif

