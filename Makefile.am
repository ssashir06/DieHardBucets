SUBDIRS = Lib Console Tweet
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(top_srcdir)/Lib -std=c++11

bin_PROGRAMS = DieHardBuckets DieHardTweet

DieHardBuckets_LDADD = \
	Lib/libDieHardBackets.a
DieHardBuckets_SOURCES = \
	Console/DieHardBuckets/main.cpp

DieHardTweet_LDADD = \
	Lib/libDieHardBackets.a
DieHardTweet_SOURCES = \
	Tweet/ProblemTweet.cpp \
	Tweet/DieHardTweet/main.cpp
