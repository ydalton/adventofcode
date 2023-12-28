a.out: day1.c
	gcc $(shell pkg-config --libs --cflags glib-2.0) day1.c

clean: 
	rm -f a.out
.PHONY: clean a.out
