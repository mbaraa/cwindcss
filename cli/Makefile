BINARY_NAME=cwindcss

all: build

build:
	gcc ../cwindcss.o cli.c -o $(BINARY_NAME)

install:
	@if [ "$(shell id -u)" = "0" ]; then \
		cp $(BINARY_NAME) /bin/; \
	else \
		mkdir -p /home/$$USER/.local/bin/; \
		cp $(BINARY_NAME) /home/$$USER/.local/bin/; \
	fi

uninstall:
	@if [ "$(shell id -u)" = "0" ]; then \
		rm -f /bin/$(BINARY_NAME); \
	else \
		rm -f /home/$$USER/.local/bin/$(BINARY_NAME); \
	fi

clean:
	rm $(BINARY_NAME)
