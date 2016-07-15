VERSION=1.0.1
CFLAGS=-O0 -g -Wall
CC = gcc


all: tt-demo teste_myops

.c.o:
	$(CC) $(CFLAGS) -c  $<

tinytest.o: tinytest.h

tinytest_demo.o: tinytest_macros.h tinytest.h

myops.o: myops.h myops.c

teste_myops.o: tinytest_macros.h tinytest.h myops.h

OBJS=tinytest.o tinytest_demo.o

OBJS2=tinytest.o myops.o teste_myops.o

tt-demo: $(OBJS)
	$(CC) $(CLAGS) $(OBJS) -o tt-demo

teste-myops: $(OBJS2)
	$(CC) $(CFLAGS) $(OBJS2) -o teste-myops

lines:
	wc -l tinytest.c tinytest_macros.h tinytest.h

clean:
	rm -f *.o *~ tt-demo teste_myops

DISTFILES=tinytest.c tinytest_demo.c tinytest.h tinytest_macros.h Makefile \
	README

dist:
	rm -rf tinytest-$(VERSION)
	mkdir tinytest-$(VERSION)
	cp $(DISTFILES) tinytest-$(VERSION)
	tar cf - tinytest-$(VERSION) | gzip -c -9 > tinytest-$(VERSION).tar.gz
