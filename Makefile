all: build clean

build:
	gcc -Wall PutinDeProjetFuse.c `pkg-config fuse3 --cflags --libs` -o projet
	./projet -f mountpoint
	

clean:
	umount mountpoint