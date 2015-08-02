# Makefile for libiconv/lib

#### Start of system configuration section. ####

# Directories used by "make":
srcdir = .

# Directories used by "make install":
prefix = /usr/local
local_prefix = /usr/local
exec_prefix = ${prefix}
libdir = ${exec_prefix}/lib

# Programs used by "make":
CC = gcc
CFLAGS = -g -O2 -fvisibility=hidden
CPPFLAGS = 
LDFLAGS =  $(LDFLAGS_no)
LDFLAGS_yes = -Wl,--export-all-symbols
LDFLAGS_no =
INCLUDES = -I. -I$(srcdir) -I $(top_builddir)/charset/ -I $(top_builddir)/include/

include_dir =  $(top_builddir)/include/

# -DBUILDING_LIBICONV: Change expansion of LIBICONV_DLL_EXPORTED macro.
# -DBUILDING_DLL: Change expansion of RELOCATABLE_DLL_EXPORTED macro.
DEFS = -DLIBDIR=\"$(libdir)\" -DBUILDING_LIBICONV -DBUILDING_DLL \
-DENABLE_RELOCATABLE=1 -DIN_LIBRARY -DINSTALLDIR=\"$(libdir)\" -DNO_XMALLOC \
-Dset_relocation_prefix=libiconv_set_relocation_prefix \
-Drelocate=libiconv_relocate -DHAVE_CONFIG_H

RC = 
CP = cp
MV = mv
LN = ln
LN_S = ln -s
RM = rm -f

# Programs used by "make install":
INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
mkinstalldirs = $(SHELL) ../build-aux/mkinstalldirs

#### End of system configuration section. ####

SHELL = /bin/sh

AR = ar
ARFLAGS = -cr

SOURCES = $(srcdir)/iconv.c $(srcdir)/relocatable.c

OBJECTS = iconv.o localcharset.o relocatable.o iconv_string.o

all : libiconv.a

libiconv.a : $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $+

iconv.o : $(srcdir)/iconv.c $(srcdir)/converters.h \
           $(srcdir)/encodings.def $(srcdir)/encodings_aix.def $(srcdir)/encodings_osf1.def $(srcdir)/encodings_dos.def $(srcdir)/encodings_local.def \
           $(srcdir)/aliases.h $(srcdir)/aliases_sysaix.h $(srcdir)/aliases_syshpux.h $(srcdir)/aliases_sysosf1.h $(srcdir)/aliases_syssolaris.h \
           $(srcdir)/aliases_aix.h $(srcdir)/aliases_aix_sysaix.h \
           $(srcdir)/aliases_osf1.h $(srcdir)/aliases_osf1_sysosf1.h \
           $(srcdir)/aliases_dos.h \
           $(srcdir)/aliases_extra.h \
           $(srcdir)/flags.h $(srcdir)/translit.h
	$(CC) $(INCLUDES) $(CPPFLAGS) $(CFLAGS) $(DEFS) -c $(srcdir)/iconv.c

localcharset.o : $(top_builddir)/charset/localcharset.c $(srcdir)/relocatable.h
	$(CC) $(INCLUDES) $(CPPFLAGS) $(CFLAGS) $(DEFS) -c $(top_builddir)/charset/localcharset.c

relocatable.o : $(srcdir)/relocatable.c $(srcdir)/relocatable.h
	$(CC) $(INCLUDES) $(CPPFLAGS) $(CFLAGS) $(DEFS) -c $(srcdir)/relocatable.c

iconv_string.o : $(srcdir)/iconv_string.c $(include_dir)/iconv_string.h
	$(CC) $(INCLUDES) $(CPPFLAGS) $(CFLAGS) $(DEFS) -c $(srcdir)/iconv_string.c

clean:
	rm -rf *.o *.a

