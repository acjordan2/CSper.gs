IDIR = ../includes
CC = gcc
CFLAGS = $(shell mysql_config --libs) -I.

ODIR=../obj
LDIR=../lib


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

testmake: user.o main.o
	gcc -o $@ $^ $(CFLAGS) ../lib/bcrypt/bcrypt.o ../lib/bcrypt/crypt_blowfish/*.o ../lib/mpsw/mpsw.o

