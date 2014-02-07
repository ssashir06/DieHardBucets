SUBDIRS = DieHardConsole LibDieHardBuckets
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -ILibDieHardBuckets -std=c++11 -stdlib=libstdc++
bin_PROGRAMS = DieHardBuckets
DieHardBuckets_LDADD = \
	LibDieHardBuckets/libDieHardBackets.a
DieHardBuckets_SOURCES = \
	DieHardConsole/DieHardBuckets/ProblemDot.cpp \
	DieHardConsole/DieHardBuckets/main.cpp
