.PHONY: all


# all: cli walk vector
# 	gcc main.c cli.o walk.o vector.o -o app `pkg-config --cflags --libs glib-2.0` -I`jemalloc-config --includedir` \
# -L`jemalloc-config --libdir` -Wl,-rpath,`jemalloc-config --libdir` \
# -ljemalloc `jemalloc-config --libs`
all: cli walk vector
	gcc main.c cli.o walk.o vector.o -o app `pkg-config --cflags --libs glib-2.0`
cli: 
	gcc -c sources/cli.c -o cli.o `pkg-config --cflags --libs glib-2.0`
walk:
	gcc -c sources/walk.c -o walk.o
vector:
	gcc -c sources/vector.c -o vector.o