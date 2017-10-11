build:
	gcc -o brightness -I /usr/lib/include brightness.c

install:
	cp ./brightness /usr/local/bin

run:
	./brightness

show:
	./brightness show
