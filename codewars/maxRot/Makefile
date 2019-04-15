CC=gcc
CFLAGS=-std=c99 -Wall -Werror
LDLIBS=-lm
LDLIBST=$(LDLIBS) -lcriterion
DEPS=maxRot.h digits.h
OBJ=maxRot.o digits.o
OBJM=$(OBJ) main.o
OBJT=$(OBJ) test_maxRot.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

maxrot: $(OBJM)
	$(CC) $(LDLIBS) -o maxrot $(OBJM)

test_maxrot: $(OBJT)
	$(CC) $(LDLIBST) -o test_maxrot $(OBJT)

clean:
	rm *.o
	rm maxrot
	rm test_maxrot
