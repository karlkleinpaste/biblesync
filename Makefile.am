# BibleSync library
# Karl Kleinpaste, May 2014
# 
# All files related to implementation of BibleSync, including program
# source, READMEs, manual pages, and related similar documents, are in
# the public domain.  As a matter of simple decency, your social
# obligations are to credit the source and to coordinate any changes you
# make back to the origin repository.  These obligations are non-
# binding for public domain software, but they are to be seriously
# handled nonetheless.

AUTOMAKE_OPTIONS = 1.6

ACLOCAL_AMFLAGS = -I m4
LDADD = $(top_builddir)/lib/libbiblesync.la

# Global config directory
globalconfdir := @sysconfdir@

SUBDIRS = lib .

EXTRA_DIST = biblesync.spec biblesync-v1.png usrinst.sh autogen.sh sword.pc.in

if USE_PKGCONF
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = biblesync.pc

$(pkgconfig_DATA): config.status
endif

#include doc/Makefile.am

restore:
	cd $(top_srcdir) && ./scripts/restoremake.sh

install: install-recursive
	@echo ""
	@echo "BibleSync is installed."

dist-hook:
	(cd $(distdir) && ./autogen.sh)
	rm -r $(distdir)/autom4te.cache
