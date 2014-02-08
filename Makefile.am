SUBDIRS = DieHardConsole LibDieHardBuckets
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(top_srcdir)/LibDieHardBuckets -std=c++11

bin_PROGRAMS = DieHardBuckets DieHardTweet

DieHardBuckets_LDADD = \
	LibDieHardBuckets/libDieHardBackets.a
DieHardBuckets_SOURCES = \
	DieHardConsole/DieHardBuckets/ProblemDot.cpp \
	DieHardConsole/DieHardBuckets/main.cpp

DieHardTweet_LDADD = \
	LibDieHardBuckets/libDieHardBackets.a
DieHardTweet_SOURCES = \
	DieHardBucketsTweet/DieHardBucketsTweet/ProblemTweet.cpp \
	DieHardBucketsTweet/DieHardBucketsTweet/main.cpp
