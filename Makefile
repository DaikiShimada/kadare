CC = g++
CFLAGS = -O3 -std=c++11

.PHONY: all install


all : libkadare.so

libkadare.so : src/kadare.cpp include/kadare/kadare.hpp
	$(CC) $(CFLAGS) -Iinclude -shared -fPIC -o libkadare.so src/kadare.cpp

install :
	cp -r include/kadare /usr/local/include/
	cp libkadare.so /usr/local/lib/ 
