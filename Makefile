# st - simple terminal
# See LICENSE file for copyright and license details.
.POSIX:

include config.mk

SRC = bd.c st.c uc.c util.c x.c
OBJ = $(SRC:.c=.o)

all: st

.c.o:
	$(CC) -c $(CFLAGS) $<

$(OBJ): config.h config.mk

st: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f st $(OBJ) st-$(VERSION).tar.gz

dist: clean
	mkdir -p st-$(VERSION)
	cp -R LICENSE Makefile README config.mk st.1 st.info\
		config.h arg.h bd.h st.h util.h win.h x.h $(SRC)\
		st-$(VERSION)
	tar -cf - st-$(VERSION) | gzip > st-$(VERSION).tar.gz
	rm -rf st-$(VERSION)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f st $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/st
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < st.1 > $(DESTDIR)$(MANPREFIX)/man1/st.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/st.1
	tic -sx st.info

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/st\
		$(DESTDIR)$(MANPREFIX)/man1/st.1

.PHONY: all clean dist install uninstall
