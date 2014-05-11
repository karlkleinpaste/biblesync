#!/bin/sh
#******************************************************************************
#  usrinst.sh -	Convenience script specifying most common development options
#		to ./configure
#
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
#
OPTIONS="--prefix=/usr $OPTIONS"
if [ -d /usr/lib64 ]
then
	OPTIONS="--libdir=/usr/lib64 $OPTIONS"
else
	OPTIONS="--libdir=/usr/lib $OPTIONS"
fi
#OPTIONS="--disable-shared $OPTIONS"
#OPTIONS="--enable-debug $OPTIONS"
#OPTIONS="--enable-warnings $OPTIONS"

# Use these for Windows DLL build
#LIBS="$LIBS -no-undefined"
#OPTIONS="lt_cv_deplibs_check_method=pass_all $OPTIONS"

LIBS="$LIBS" ./configure $OPTIONS $*
