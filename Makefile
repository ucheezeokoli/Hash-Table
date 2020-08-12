CC = g++

all:
	$(CC) -std=c++11 -o a.exe uezeokoli.cpp

clean:
	rm -f a.exe

