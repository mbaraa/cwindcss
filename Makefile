PREFIX?=/usr/local
LIB_DIR=$(PREFIX)/lib
INCLUDE_DIR=$(PREFIX)/include

all: libcwindcss.so

cwindcss.o: cwindcss.c cwindcss.h
	gcc -Wall -fPIC -g -c cwindcss.c -o cwindcss.o

libcwindcss.so: cwindcss.o
	gcc -shared -o libcwindcss.so cwindcss.o

install: libcwindcss.so
	mkdir -p $(LIB_DIR)
	mkdir -p $(INCLUDE_DIR)
	cp libcwindcss.so $(LIB_DIR)
	cp cwindcss.h $(INCLUDE_DIR)
	ldconfig

test:
	cd tests && go test -v ./...

clean:
	rm -f cwindcss.o libcwindcss.so

uninstall:
	rm -f $(LIB_DIR)/libcwindcss.so
	rm -rf $(INCLUDE_DIR)/cwindcss.h
	ldconfig

