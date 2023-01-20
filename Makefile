CC = clang
CFLAGS = -lm -Wall -Wextra -O3 -flto=full
INSTALL_PATH = /usr/local/bin

all:
	$(CC) $(CFLAGS) -o blmgr blmgr.c

install:
	cp -f blmgr $(INSTALL_PATH)

clean:
	rm -f blmgr

.PHONY: all install clean
