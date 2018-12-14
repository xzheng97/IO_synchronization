CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = prodcomm
SCAN_BUILD_DIR = scan-build-out

all: main.o munch1.o munch2.o inputreader.o outputwriter.o Queue.o
	$(CC) -o $(EXE) main.o munch1.o munch2.o inputreader.o outputwriter.o Queue.o -lpthread

main.o: main.c munch1.h munch2.h inputreader.h outputwriter.h Queue.h
	$(CC) $(WARNING_FLAGS) -c main.c

inputreader.o: inputreader.c inputreader.h Queue.h
	$(CC) $(WARNING_FLAGS) -c inputreader.c

munch1.o: munch1.c munch1.h Queue.h
	$(CC) $(WARNING_FLAGS) -c munch1.c

munch2.o: munch2.c munch2.h Queue.h
	$(CC) $(WARNING_FLAGS) -c munch2.c

outputwriter.o: outputwriter.c outputwriter.h Queue.h 
	$(CC) $(WARNING_FLAGS) -c outputwriter.c

Queue.o: Queue.c Queue.h
	$(CC) $(WARNING_FLAGS) -c Queue.c

clean:
	rm $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
