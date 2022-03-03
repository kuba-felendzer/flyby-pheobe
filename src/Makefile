# build all .c files into an executable named "exe"
all: *.c
	gcc *.c -I. -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o exe && ./exe


# cleanup
clean:
	rm exe
