CC = g++

all:
	$(CC) -std=c++11 -o a.exe HashTable.cpp

clean:
	rm -f a.exe

