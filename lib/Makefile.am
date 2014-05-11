AUTOMAKE_OPTIONS = 1.6

AM_CPPFLAGS = -I$(top_srcdir)/include

AM_CPPFLAGS += -I$(includedir) -DUSE_AUTOTOOLS -DUNIX -Dunix -D__unix__

# Global config directory
globalconfdir := @sysconfdir@

lib_LTLIBRARIES = libbiblesync.la

libbiblesync_la_SOURCES =

libbiblesync_la_LDFLAGS = -release $(VERSION)

libbiblesync_la_SOURCES += biblesync.cc
include ../include/Makefile.am


