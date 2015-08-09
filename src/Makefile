IDIR = ../includes
CC = gcc
CFLAGS = $(shell mysql_config --libs && grep '^CFLAGS = ' ../lib/bcrypt/crypt_blowfish/Makefile | cut -d= -f2-) -std=c11 -I.

ODIR=../obj
LDIR=../lib


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

testmake: user.o main.o
	gcc -o $@ $^ $(CFLAGS) ../lib/bcrypt/bcrypt.o ../lib/bcrypt/crypt_blowfish/*.o ../lib/mpsw/mpsw.o

