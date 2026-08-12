.PHONY: cwindcss.o libcwindcss.so test

CC=gcc

ifndef PREFIX
   PREFIX=/usr
else
   PREFIX=/usr/local
endif
LIB_DIR=$(PREFIX)/lib
INCLUDE_DIR=$(PREFIX)/include
CLI=cwindcss-cli
CFLAGS+=-Wall -Wextra -Wmissing-declarations -Wshadow
CFLAGS+=-Wstrict-prototypes -Wmissing-prototypes
CFLAGS+=-Wpointer-arith -Wsign-compare
CFLAGS+=-std=c23 -O2 -fPIC -g
CFLAGS+=-ldl -lm
LDFLAGS+=-ldl -lm

all: libcwindcss.so $(CLI)

objects:
	@$(CC) $(CFLAGS) -c ./lib/*.c $(LDFLAGS)

cwindcss.o: objects
	@$(CC) $(CFLAGS) -fPIC -g -c ./lib/cwindcss.c -o cwindcss.o $(LDFLAGS)

libcwindcss.so: cwindcss.o
	@ar rcs libcwindcss.a *.o

#$(CC) -shared -o libcwindcss.so *.o $(LDFLAGS)

test: cwindcss.o libcwindcss.so
	@cd tests && make && make run

$(CLI): cwindcss.o
	@cd cli && make

install: libcwindcss.so
	mkdir -p $(LIB_DIR)
	mkdir -p $(INCLUDE_DIR)
	cp libcwindcss.so $(LIB_DIR)
	cp cwindcss.h $(INCLUDE_DIR)
	ldconfig
	cd cli && make install

uninstall:
	rm -f $(LIB_DIR)/libcwindcss.so
	rm -rf $(INCLUDE_DIR)/cwindcss.h
	ldconfig
	cd cli && make uninstall

clean:
	rm -f *.o libcwindcss.a
	cd cli && make clean
	cd tests && make clean
