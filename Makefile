CC = gcc

TARGET = phonebook
OBJS = src/main.o src/note.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c note.h
	$(CC) -c main.c

note.o: note.c note.h
	$(CC) -c note.c

clean:
	rm -f $(OBJS) $(TARGET)
