#make

CC = g++
CFLAGS = -Wall

testsuite: main.o control.o view.o model.o
	$(CC) $(CFLAGS) main.o control.o view.o model.o -o testsuite

main.o: main.cpp view.h model.h control.h pipe.h
	$(CC) $(CFLAGS) -c main.cpp

control.o: control.cpp control.h
	$(CC) $(CFLAGS) -c control.cpp

view.o: view.cpp view.h
	$(CC) $(CFLAGS) -c view.cpp

model.o: model.cpp model.h
	$(CC) $(CFLAGS) -c model.cpp

clean:
	rm testsuite *.o
