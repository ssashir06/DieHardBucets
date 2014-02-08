SUBDIRS = DieHardConsole LibDieHardBuckets
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(top_srcdir)/LibDieHardBuckets -std=c++11
bin_PROGRAMS = DieHardBuckets
DieHardBuckets_LDADD = \
	LibDieHardBuckets/libDieHardBackets.a
DieHardBuckets_SOURCES = \
	DieHardConsole/DieHardBuckets/ProblemDot.cpp \
	DieHardConsole/DieHardBuckets/main.cpp
